"""Regression tests for operational progress and publication acceptance."""
import io
import unittest
from unittest.mock import patch

from progress_metrics import is_nonmatching, source_metrics
from verify_publication import verify
from gen_progress_page import unit_row, timeline_points


class ProgressTests(unittest.TestCase):
    def test_module_prefix_and_source_path(self):
        self.assertTrue(is_nonmatching({"name": "main/game/A",
            "metadata": {"source_path": "src/game/A.cpp"}}, {"game/A.cpp"}))
        self.assertTrue(is_nonmatching({"name": "main/game/A"}, {"game/A"}))
        self.assertFalse(is_nonmatching({"name": "main/game/AB"}, {"game/A"}))
        row = unit_row({"name": "main/game/A", "metadata": {
            "source_path": "src/game/A.cpp"}}, {}, {"game/A.cpp"})
        self.assertIn(">nonmatching</span>", row)

    def test_linked_exact_native_only(self):
        def unit(name, complete, fns):
            return {"name": name, "metadata": {"complete": complete}, "functions": fns}
        def fn(name, size, pct=100):
            return {"name": name, "size": str(size), "fuzzy_match_percent": pct}
        report = {"measures": {"total_code": "1000"}, "units": [
            unit("main/game/A", True, [fn("native", 100), fn("asm", 40), fn("near", 20, 99)]),
            unit("main/game/B", False, [fn("source_only", 300)]),
            unit("main/game/C", True, [fn("nm", 200)])]}
        scan = {"asm_fns": {"asm": {}, "unlinked_asm": {}},
                "nonmatching_units": ["game/C"]}
        self.assertEqual(source_metrics(report, scan)["true_matched_code"], 100)
        self.assertEqual(source_metrics(report, scan)["true_matched_functions"], 1)

    def test_old_metric_series_is_not_joined_to_new_definition(self):
        row = {"sha": "a" * 40, "ts": "2026-10-23T00:00:00Z",
               "matched_code_percent": 10, "true_matched_code_percent": 2}
        points = timeline_points([row, dict(row, true_c_metric_version=2)])
        self.assertIsNone(points[0]["c"])
        self.assertEqual(points[1]["c"], 2)

    def test_empty_report_is_zero(self):
        self.assertEqual(source_metrics({}, {"asm_fns": {},
            "nonmatching_units": []})["true_matched_code"], 0)

    def test_history_uses_shared_linked_definition(self):
        from pathlib import Path
        from progress_history import entry_from_report
        scan = {"asm_fns": {}, "nonmatching_units": [],
                "asm_fn_count": 0, "asm_fn_code": 0}
        with patch.object(Path, "open", return_value=io.StringIO(
                '{"measures":{"matched_code":"99","total_code":"100"},"units":[]}')):
            with patch("scan_asm_fns.scan_repo", return_value=scan):
                entry = entry_from_report(Path("report"), "a" * 40, "now")
        self.assertEqual(entry["true_matched_code"], 0)
        self.assertEqual(entry["true_c_metric_version"], 2)


class PublicationTests(unittest.TestCase):
    sha = "a" * 40

    def check(self, conclusion="success", public=None, deploy="success"):
        runs = [{"headSha": self.sha, "databaseId": 1}]
        details = {"status": "completed", "conclusion": conclusion, "url": "run",
                   "jobs": [{"name": "build (GNLJ82)", "conclusion": "success"},
                            {"name": "deploy-pages", "conclusion": deploy}]}
        response = io.BytesIO(("commit <code>" + (public or self.sha) + "</code>").encode())
        response.status = 200
        with patch("verify_publication.gh_json", side_effect=[runs, details]), patch(
                "verify_publication.urllib.request.urlopen", return_value=response) as url:
            result = verify(self.sha, "repo", "https://example.org/")
            return result, url.called

    def test_success_requires_public_sha(self):
        self.assertTrue(self.check()[0]["ok"])
        self.assertFalse(self.check(public="b" * 40)[0]["ok"])

    def test_ci_or_deploy_failure_never_accepts(self):
        self.assertEqual(self.check(conclusion="failure")[1], False)
        self.assertEqual(self.check(deploy="skipped")[1], False)

    def test_pending_run_not_success(self):
        with patch("verify_publication.gh_json", return_value=[]):
            self.assertEqual(verify(self.sha, "repo", "page")["reason"], "ci_not_started")

    def test_short_sha_rejected(self):
        with self.assertRaises(ValueError):
            verify("abc123", "repo", "page")


if __name__ == "__main__":
    unittest.main()
