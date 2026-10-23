"""Shared, conservative source-linked metrics for page and history."""
from __future__ import annotations


def unit_source_path(unit: dict) -> str:
    """Prefer explicit source ownership; report names may have module prefixes."""
    metadata = unit.get("metadata", {})
    path = metadata.get("source_path")
    if path:
        return path.replace("\\", "/").removeprefix("src/")
    name = unit.get("name", "").replace("\\", "/")
    module = metadata.get("module_name", "main")
    return name.removeprefix(module + "/")


def is_nonmatching(unit: dict, paths: set[str]) -> bool:
    path = unit_source_path(unit)
    return path in paths or path.rsplit(".", 1)[0] in paths


def source_metrics(report: dict, scan: dict) -> dict:
    """Count exact functions only in linked source units, excluding ASM.

    Aggregate objdiff matched_code includes exact fragments in unlinked TUs.
    Subtracting all scanned ASM bytes also wrongly subtracts unlinked ASM.
    Iterate actual linked functions instead, deduplicating address identities.
    """
    asm_names = set(scan["asm_fns"])
    nm_paths = set(scan["nonmatching_units"])
    seen = set()
    code = functions = 0
    for unit in report.get("units", []):
        metadata = unit.get("metadata", {})
        if (not metadata.get("complete") or metadata.get("auto_generated")
                or is_nonmatching(unit, nm_paths)):
            continue
        for fn in unit.get("functions", []):
            if (fn.get("name") in asm_names
                    or float(fn.get("fuzzy_match_percent", 0)) < 99.999):
                continue
            addr = fn.get("metadata", {}).get("virtual_address")
            identity = (metadata.get("module_id", 0), addr) if addr is not None else (
                unit.get("name"), fn.get("name"))
            if identity in seen:
                continue
            seen.add(identity)
            code += int(fn.get("size", 0))
            functions += 1
    total = int(report.get("measures", {}).get("total_code", 0))
    return {"true_matched_code": code, "true_matched_functions": functions,
            "true_matched_code_percent": round(code / total * 100, 4) if total else 0,
            "true_c_metric_version": 2}
