#!/usr/bin/env python3
"""Generate a static decomp progress dashboard from objdiff report.json.

Outputs (under --out-dir):
  index.html        Standalone dashboard with summary + per-category bars +
                    treemap-style unit grid + per-unit table.
  report.json       Copy of the input report for direct download.
  shield.json       shields.io endpoint payload (matched code %).

Used by .github/workflows/build.yml to publish to GitHub Pages, and also runs
locally — `python tools/gen_progress_page.py build/GNLJ82/report.json`.
"""
from __future__ import annotations

import argparse
import html
import json
import math
import shutil
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple


def _to_int(v: Any) -> int:
    if isinstance(v, str):
        return int(v) if v.isdigit() else 0
    return int(v or 0)


def _to_float(v: Any) -> float:
    return float(v or 0.0)


@dataclass
class Measures:
    fuzzy_match_percent: float
    matched_code: int
    total_code: int
    matched_code_percent: float
    matched_data: int
    total_data: int
    matched_data_percent: float
    matched_functions: int
    total_functions: int
    complete_code: int
    complete_code_percent: float
    complete_units: int
    total_units: int

    @classmethod
    def from_dict(cls, m: Dict[str, Any]) -> "Measures":
        return cls(
            fuzzy_match_percent=_to_float(m.get("fuzzy_match_percent")),
            matched_code=_to_int(m.get("matched_code")),
            total_code=_to_int(m.get("total_code")),
            matched_code_percent=_to_float(m.get("matched_code_percent")),
            matched_data=_to_int(m.get("matched_data")),
            total_data=_to_int(m.get("total_data")),
            matched_data_percent=_to_float(m.get("matched_data_percent")),
            matched_functions=_to_int(m.get("matched_functions")),
            total_functions=_to_int(m.get("total_functions")),
            complete_code=_to_int(m.get("complete_code")),
            complete_code_percent=_to_float(m.get("complete_code_percent")),
            complete_units=_to_int(m.get("complete_units")),
            total_units=_to_int(m.get("total_units")),
        )


def color_for_pct(pct: float) -> str:
    """Green at 100, gray at 0, blue gradient for in-progress."""
    if pct >= 99.999:
        return "#1f9d3a"
    if pct <= 0.001:
        return "#2a2f3a"
    # Interpolate between dark blue (#193b5e) and bright blue (#3fa9ff)
    t = max(0.0, min(1.0, pct / 100.0))
    r = int(0x19 + (0x3f - 0x19) * t)
    g = int(0x3b + (0xa9 - 0x3b) * t)
    b = int(0x5e + (0xff - 0x5e) * t)
    return f"#{r:02x}{g:02x}{b:02x}"


def build_treemap(units: List[Dict[str, Any]], width: int = 1000, height: int = 600) -> str:
    """Squarified treemap of units sized by total_code, colored by matched%."""
    items: List[Tuple[str, int, float]] = []
    for u in units:
        m = u.get("measures", {})
        size = _to_int(m.get("total_code"))
        if size <= 0:
            continue
        items.append((u["name"], size, _to_float(m.get("matched_code_percent"))))
    if not items:
        return f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}"></svg>'
    items.sort(key=lambda x: x[1], reverse=True)
    total = sum(s for _, s, _ in items)
    scale = (width * height) / total

    rects: List[str] = []

    def worst_aspect(row: List[float], w: float) -> float:
        s = sum(row)
        r_max = max(row)
        r_min = min(row)
        if s == 0 or w == 0:
            return math.inf
        return max((w * w * r_max) / (s * s), (s * s) / (w * w * r_min))

    def layout_row(row: List[Tuple[str, int, float]], x: float, y: float, w: float, h: float, horizontal: bool) -> Tuple[float, float, float, float]:
        s = sum(area for _, area, _ in [(n, a * scale, p) for n, a, p in row])
        if horizontal:
            row_h = s / w if w else 0
            cx = x
            for name, area, pct in row:
                a = area * scale
                rw = a / row_h if row_h else 0
                rects.append(
                    f'<rect x="{cx:.2f}" y="{y:.2f}" width="{rw:.2f}" height="{row_h:.2f}" '
                    f'fill="{color_for_pct(pct)}" stroke="#0d1117" stroke-width="0.5">'
                    f'<title>{html.escape(name)}&#10;{area} bytes&#10;{pct:.2f}% matched</title></rect>'
                )
                cx += rw
            return x, y + row_h, w, h - row_h
        else:
            row_w = s / h if h else 0
            cy = y
            for name, area, pct in row:
                a = area * scale
                rh = a / row_w if row_w else 0
                rects.append(
                    f'<rect x="{x:.2f}" y="{cy:.2f}" width="{row_w:.2f}" height="{rh:.2f}" '
                    f'fill="{color_for_pct(pct)}" stroke="#0d1117" stroke-width="0.5">'
                    f'<title>{html.escape(name)}&#10;{area} bytes&#10;{pct:.2f}% matched</title></rect>'
                )
                cy += rh
            return x + row_w, y, w - row_w, h

    x, y, w, h = 0.0, 0.0, float(width), float(height)
    remaining = list(items)
    row: List[Tuple[str, int, float]] = []
    while remaining:
        side = min(w, h)
        if side == 0:
            break
        item = remaining[0]
        trial = row + [item]
        trial_areas = [a * scale for _, a, _ in trial]
        row_areas = [a * scale for _, a, _ in row]
        if not row or worst_aspect(trial_areas, side) <= worst_aspect(row_areas, side):
            row = trial
            remaining.pop(0)
        else:
            x, y, w, h = layout_row(row, x, y, w, h, horizontal=(w >= h))
            row = []
    if row:
        layout_row(row, x, y, w, h, horizontal=(w >= h))

    return (
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" '
        f'width="100%" preserveAspectRatio="xMidYMid meet" role="img" '
        f'aria-label="Unit treemap: each rect is one object file, sized by code bytes, colored by matched %.">'
        f'<rect width="{width}" height="{height}" fill="#0d1117"/>'
        + "".join(rects)
        + "</svg>"
    )


def format_bytes(n: int) -> str:
    for unit in ("B", "KiB", "MiB", "GiB"):
        if n < 1024:
            return f"{n:.1f} {unit}" if unit != "B" else f"{n} B"
        n /= 1024
    return f"{n:.1f} TiB"


def render_bar(pct: float, width: int = 320) -> str:
    pct = max(0.0, min(100.0, pct))
    fill_w = int(width * pct / 100)
    return (
        f'<div class="bar"><div class="bar-fill" style="width:{fill_w}px;background:{color_for_pct(pct)}"></div>'
        f'<span class="bar-label">{pct:.2f}%</span></div>'
    )


HTML_TEMPLATE = """<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>{title}</title>
<style>
  :root {{ color-scheme: dark; }}
  body {{
    margin: 0; padding: 2rem 1.5rem;
    background: #0d1117; color: #c9d1d9;
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", system-ui, sans-serif;
    line-height: 1.5;
  }}
  main {{ max-width: 1100px; margin: 0 auto; }}
  h1, h2 {{ color: #f0f6fc; }}
  h1 {{ font-size: 1.75rem; margin: 0 0 0.5rem; }}
  h2 {{ font-size: 1.2rem; margin: 2rem 0 1rem; border-bottom: 1px solid #30363d; padding-bottom: 0.3rem; }}
  a {{ color: #58a6ff; }}
  .summary {{ display: grid; gap: 0.75rem; grid-template-columns: repeat(auto-fit, minmax(220px, 1fr)); margin-top: 1rem; }}
  .card {{ background: #161b22; border: 1px solid #30363d; border-radius: 6px; padding: 1rem; }}
  .card .label {{ font-size: 0.85rem; color: #8b949e; text-transform: uppercase; letter-spacing: 0.04em; }}
  .card .value {{ font-size: 1.6rem; font-weight: 600; color: #f0f6fc; margin-top: 0.25rem; }}
  .card .sub {{ font-size: 0.85rem; color: #8b949e; margin-top: 0.25rem; }}
  .bar {{ position: relative; height: 1.4rem; background: #21262d; border-radius: 3px; overflow: hidden; }}
  .bar-fill {{ height: 100%; }}
  .bar-label {{ position: absolute; inset: 0; display: flex; align-items: center; justify-content: center;
                font-size: 0.8rem; color: #f0f6fc; text-shadow: 0 0 2px #000; }}
  table {{ width: 100%; border-collapse: collapse; font-size: 0.85rem; }}
  th, td {{ padding: 0.4rem 0.6rem; text-align: left; border-bottom: 1px solid #21262d; }}
  th {{ color: #8b949e; font-weight: 500; }}
  tr:hover td {{ background: #161b22; }}
  td.num {{ text-align: right; font-variant-numeric: tabular-nums; }}
  .meta {{ color: #8b949e; font-size: 0.9rem; }}
  .cat-row {{ display: grid; grid-template-columns: minmax(120px, 200px) 1fr auto; gap: 1rem; align-items: center; margin-bottom: 0.5rem; }}
  .treemap-wrap {{ background: #0d1117; border: 1px solid #30363d; border-radius: 6px; padding: 0.5rem; }}
  details {{ margin-top: 1rem; }}
  summary {{ cursor: pointer; color: #8b949e; }}
</style>
</head>
<body>
<main>
  <h1>{title}</h1>
  <p class="meta">Version <code>{version}</code> · Generated from <code>report.json</code>{commit_part}</p>

  <h2>Overall</h2>
  <div class="summary">
    <div class="card"><div class="label">Matched code</div><div class="value">{matched_pct:.2f}%</div>
      <div class="sub">{matched_bytes} / {total_bytes}</div></div>
    <div class="card"><div class="label">Linked (complete)</div><div class="value">{complete_pct:.2f}%</div>
      <div class="sub">{complete_units} / {total_units} files</div></div>
    <div class="card"><div class="label">Matched functions</div><div class="value">{matched_fns} / {total_fns}</div>
      <div class="sub">{fn_pct:.2f}%</div></div>
    <div class="card"><div class="label">Fuzzy match</div><div class="value">{fuzzy_pct:.2f}%</div>
      <div class="sub">objdiff fuzzy score</div></div>
  </div>

  <h2>Categories</h2>
  {category_rows}

  <h2>Treemap (sized by code bytes, colored by matched%)</h2>
  <div class="treemap-wrap">{treemap_svg}</div>

  <h2>Top units</h2>
  <p class="meta">Largest units by code size, with their match status.</p>
  <table>
    <thead><tr><th>Unit</th><th class="num">Code</th><th class="num">Matched</th><th class="num">Fuzzy</th><th>Status</th></tr></thead>
    <tbody>{top_units_rows}</tbody>
  </table>

  <details>
    <summary>All units ({n_units})</summary>
    <table>
      <thead><tr><th>Unit</th><th class="num">Code</th><th class="num">Matched</th><th class="num">Fuzzy</th><th>Status</th></tr></thead>
      <tbody>{all_units_rows}</tbody>
    </table>
  </details>

  <p class="meta" style="margin-top:2rem"><a href="report.json">Raw report.json</a> · <a href="shield.json">Shield JSON</a></p>
</main>
</body>
</html>
"""


def unit_row(u: Dict[str, Any]) -> str:
    m = u.get("measures", {})
    code = _to_int(m.get("total_code"))
    matched = _to_float(m.get("matched_code_percent"))
    fuzzy = _to_float(m.get("fuzzy_match_percent"))
    complete = bool(u.get("metadata", {}).get("complete"))
    auto = bool(u.get("metadata", {}).get("auto_generated"))
    if complete:
        status = '<span style="color:#1f9d3a">linked</span>'
    elif matched >= 99.999:
        status = '<span style="color:#3fa9ff">matched</span>'
    elif matched > 0:
        status = '<span style="color:#8b949e">in progress</span>'
    elif auto:
        status = '<span style="color:#444c56">auto</span>'
    else:
        status = '<span style="color:#8b949e">—</span>'
    return (
        "<tr>"
        f"<td><code>{html.escape(u['name'])}</code></td>"
        f'<td class="num">{format_bytes(code)}</td>'
        f'<td class="num">{matched:.2f}%</td>'
        f'<td class="num">{fuzzy:.2f}%</td>'
        f"<td>{status}</td>"
        "</tr>"
    )


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("report", type=Path, help="Path to report.json")
    ap.add_argument("--out-dir", type=Path, default=Path("site"))
    ap.add_argument("--version", default="GNLJ82")
    ap.add_argument("--title", default="Mario Kart Arcade GP2 — decomp progress")
    ap.add_argument("--commit", default=None, help="Optional commit SHA to display")
    args = ap.parse_args()

    if not args.report.is_file():
        print(f"error: {args.report} not found", file=sys.stderr)
        return 1

    with args.report.open("r", encoding="utf-8") as f:
        report = json.load(f)

    measures = Measures.from_dict(report.get("measures", {}))
    categories = report.get("categories", [])
    units = report.get("units", [])

    units_with_code = [u for u in units if _to_int(u.get("measures", {}).get("total_code")) > 0]
    units_with_code.sort(key=lambda u: _to_int(u["measures"].get("total_code")), reverse=True)

    category_rows = []
    for c in categories:
        cm = Measures.from_dict(c.get("measures", {}))
        category_rows.append(
            f'<div class="cat-row">'
            f'<div><strong>{html.escape(c.get("name", c.get("id", "?")))}</strong>'
            f'<div class="meta">{cm.matched_functions} / {cm.total_functions} fns · '
            f'{format_bytes(cm.total_code)} code</div></div>'
            f'{render_bar(cm.matched_code_percent)}'
            f'<div class="meta">{cm.matched_code_percent:.2f}%</div>'
            f"</div>"
        )

    args.out_dir.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(args.report, args.out_dir / "report.json")

    shield = {
        "schemaVersion": 1,
        "label": "matched",
        "message": f"{measures.matched_code_percent:.2f}%",
        "color": "blue" if measures.matched_code_percent < 99.99 else "brightgreen",
    }
    (args.out_dir / "shield.json").write_text(json.dumps(shield), encoding="utf-8")

    treemap_svg = build_treemap(units_with_code, width=1000, height=520)

    commit_part = f" · commit <code>{html.escape(args.commit)}</code>" if args.commit else ""

    html_out = HTML_TEMPLATE.format(
        title=html.escape(args.title),
        version=html.escape(args.version),
        commit_part=commit_part,
        matched_pct=measures.matched_code_percent,
        matched_bytes=format_bytes(measures.matched_code),
        total_bytes=format_bytes(measures.total_code),
        complete_pct=measures.complete_code_percent,
        complete_units=measures.complete_units,
        total_units=measures.total_units,
        matched_fns=measures.matched_functions,
        total_fns=measures.total_functions,
        fn_pct=(measures.matched_functions / measures.total_functions * 100.0) if measures.total_functions else 0.0,
        fuzzy_pct=measures.fuzzy_match_percent,
        category_rows="\n".join(category_rows) or '<p class="meta">No categories defined.</p>',
        treemap_svg=treemap_svg,
        top_units_rows="\n".join(unit_row(u) for u in units_with_code[:30]),
        all_units_rows="\n".join(unit_row(u) for u in units_with_code),
        n_units=len(units_with_code),
    )
    (args.out_dir / "index.html").write_text(html_out, encoding="utf-8")

    print(f"wrote {args.out_dir / 'index.html'}")
    print(f"  matched code: {measures.matched_code_percent:.2f}% "
          f"({measures.matched_code}/{measures.total_code} bytes)")
    print(f"  linked units: {measures.complete_units}/{measures.total_units}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
