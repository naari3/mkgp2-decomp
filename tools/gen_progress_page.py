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
import bisect
import html
import json
import math
import shutil
import sys
from dataclasses import dataclass
from datetime import date, datetime, timedelta
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


def _unit_address(u: Dict[str, Any]) -> int:
    """Lowest virtual_address across this unit's sections; 0 if none recorded."""
    addrs: List[int] = []
    for s in u.get("sections", []):
        va = s.get("metadata", {}).get("virtual_address")
        if va is None:
            continue
        try:
            addrs.append(int(va))
        except (TypeError, ValueError):
            continue
    return min(addrs) if addrs else 0


def _binary_split(
    rect: Tuple[float, float, float, float],
    indices: List[int],
    sums: List[float],
    offset: float,
    value: float,
    out_rects: List[Tuple[float, float, float, float]],
) -> None:
    """streemap-rs `binary` port: bisect items by cumulative size, split rect along the longer axis."""
    n = len(indices)
    if n == 0 or value <= 0:
        return
    if n == 1:
        out_rects[indices[0]] = rect
        return
    target = value / 2.0 + offset
    mid = bisect.bisect_right(sums, target)
    if mid == 0:
        mid = 1
    if mid >= n:
        mid = n - 1
    left = sums[mid - 1] - offset
    right = value - left
    x, y, w, h = rect
    if w > h:
        xe = x + w
        xm = (x * right + xe * left) / value
        lrect = (x, y, xm - x, h)
        rrect = (xm, y, xe - xm, h)
    else:
        ye = y + h
        ym = (y * right + ye * left) / value
        lrect = (x, y, w, ym - y)
        rrect = (x, ym, w, ye - ym)
    if mid == 1:
        out_rects[indices[0]] = lrect
    else:
        _binary_split(lrect, indices[:mid], sums[:mid], offset, left, out_rects)
    rest = indices[mid:]
    if len(rest) == 1:
        out_rects[rest[0]] = rrect
    elif rest:
        _binary_split(rrect, rest, sums[mid:], sums[mid - 1], right, out_rects)


def _unit_status_label(u: Dict[str, Any], matched: float) -> str:
    """Plain-text status label for tooltip (no HTML markup)."""
    if u.get("metadata", {}).get("complete"):
        return "linked"
    if matched >= 99.999:
        return "matched"
    if matched > 0:
        return "in progress"
    if u.get("metadata", {}).get("auto_generated"):
        return "auto"
    return "—"


def build_treemap(units: List[Dict[str, Any]], width: int = 1000, height: int = 600) -> str:
    """Binary-split treemap of units (decomp.dev / streemap-rs `binary`), nested by function.

    Outer layout splits units in caller-supplied order (typically address). Within each
    unit rect, the same algorithm splits the unit's functions in address order so the
    visual carries both unit-level boundaries and function-level granularity."""
    items: List[Tuple[Dict[str, Any], int, float, float]] = []
    for u in units:
        m = u.get("measures", {})
        size = _to_int(m.get("total_code"))
        if size <= 0:
            continue
        items.append((
            u, size,
            _to_float(m.get("matched_code_percent")),
            _to_float(m.get("fuzzy_match_percent")),
        ))
    if not items:
        return f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}"></svg>'

    sums: List[float] = []
    total = 0.0
    for _, size, _, _ in items:
        total += size
        sums.append(total)
    out_rects: List[Tuple[float, float, float, float]] = [(0.0, 0.0, 0.0, 0.0)] * len(items)
    _binary_split(
        (0.0, 0.0, float(width), float(height)),
        list(range(len(items))), sums, 0.0, total, out_rects,
    )

    # Inline unit-level outline first (background tier), then overlay function-level rects
    # on top. Function rects shadow their unit rect's fill so the visible color is per-fn.
    unit_rects: List[str] = []
    fn_rects: List[str] = []
    for (u, size, matched, fuzzy), (x, y, w, h) in zip(items, out_rects):
        unit_addr = _unit_address(u)
        unit_addr_str = f"0x{unit_addr:08X}" if unit_addr else ""
        unit_status = _unit_status_label(u, matched)
        unit_name_esc = html.escape(u["name"], quote=True)

        # Unit-level rect: thin border, faint fill (kept so empty/tiny gaps still show color).
        unit_rects.append(
            f'<rect x="{x:.2f}" y="{y:.2f}" width="{w:.2f}" height="{h:.2f}" '
            f'fill="{color_for_pct(matched)}" stroke="#0d1117" stroke-width="0.8"/>'
        )

        fns = u.get("functions") or []
        if not fns:
            # No fn breakdown — make the unit rect itself the interactive tile.
            fn_rects.append(
                f'<rect x="{x:.2f}" y="{y:.2f}" width="{w:.2f}" height="{h:.2f}" '
                f'fill="transparent" stroke="none" '
                f'data-name="{unit_name_esc}" '
                f'data-addr="{unit_addr_str}" '
                f'data-size="{format_bytes(size)}" '
                f'data-matched="{matched:.2f}%" '
                f'data-fuzzy="{fuzzy:.2f}%" '
                f'data-status="{unit_status}"/>'
            )
            continue

        # Inner layout: split unit rect by function size.
        fn_sums: List[float] = []
        fn_total = 0.0
        for f in fns:
            fn_total += _to_int(f.get("size"))
            fn_sums.append(fn_total)
        if fn_total <= 0:
            continue
        inner_rects: List[Tuple[float, float, float, float]] = [(0.0, 0.0, 0.0, 0.0)] * len(fns)
        _binary_split((x, y, w, h), list(range(len(fns))), fn_sums, 0.0, fn_total, inner_rects)

        for f, (fx, fy, fw, fh) in zip(fns, inner_rects):
            if fw < 0.5 or fh < 0.5:
                continue  # cull below visible pixel
            fn_size = _to_int(f.get("size"))
            fn_fuzzy = _to_float(f.get("fuzzy_match_percent"))
            fn_va = f.get("metadata", {}).get("virtual_address")
            fn_addr_str = ""
            if fn_va is not None:
                try:
                    fn_addr_str = f"0x{int(fn_va):08X}"
                except (TypeError, ValueError):
                    pass
            fn_rects.append(
                f'<rect x="{fx:.2f}" y="{fy:.2f}" width="{fw:.2f}" height="{fh:.2f}" '
                f'fill="{color_for_pct(fn_fuzzy)}" stroke="#0d1117" stroke-width="0.2" '
                f'data-name="{html.escape(f.get("name", "?"), quote=True)}" '
                f'data-addr="{fn_addr_str}" '
                f'data-size="{format_bytes(fn_size)}" '
                f'data-fuzzy="{fn_fuzzy:.2f}%" '
                f'data-unit="{unit_name_esc}"/>'
            )

    return (
        f'<svg id="treemap-svg" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" '
        f'width="100%" preserveAspectRatio="xMidYMid meet" role="img" '
        f'aria-label="Treemap: outer rects are object files in address order, inner rects are functions.">'
        f'<rect width="{width}" height="{height}" fill="#0d1117"/>'
        + "".join(unit_rects)
        + "".join(fn_rects)
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
  .treemap-wrap {{ position: relative; background: #0d1117; border: 1px solid #30363d; border-radius: 6px; padding: 0.5rem; }}
  .treemap-wrap svg rect[data-name] {{ cursor: default; }}
  .treemap-wrap svg rect[data-name]:hover {{ stroke: #f0f6fc; stroke-width: 1.5; }}
  #treemap-tooltip {{
    position: absolute; pointer-events: none; display: none;
    background: #21262d; color: #f0f6fc; border: 1px solid #30363d; border-radius: 4px;
    padding: 0.5rem 0.7rem; font-size: 0.8rem; line-height: 1.4; z-index: 10;
    box-shadow: 0 4px 12px rgba(0,0,0,0.5); min-width: 200px;
  }}
  #treemap-tooltip .tt-name {{ font-weight: 600; word-break: break-all; margin-bottom: 0.3rem; color: #58a6ff; }}
  #treemap-tooltip .tt-row {{ display: flex; justify-content: space-between; gap: 1rem; }}
  #treemap-tooltip .tt-row .tt-label {{ color: #8b949e; }}
  details {{ margin-top: 1rem; }}
  summary {{ cursor: pointer; color: #8b949e; }}
  .chart-card {{ background: #161b22; border: 1px solid #30363d; border-radius: 6px; padding: 1rem; margin-bottom: 1rem; }}
  .chart-head {{ display: flex; justify-content: space-between; align-items: baseline; flex-wrap: wrap; gap: 0.5rem; margin-bottom: 0.5rem; }}
  .chart-title {{ color: #f0f6fc; font-weight: 600; font-size: 0.95rem; }}
  .chart-legend {{ display: flex; gap: 1.2rem; font-size: 0.8rem; color: #8b949e; }}
  .chart-legend .key {{ display: inline-block; width: 14px; height: 2px; border-radius: 1px; margin-right: 0.4rem; vertical-align: middle; }}
  .chart-controls {{ display: flex; gap: 1.2rem; align-items: center; flex-wrap: wrap; }}
  .chart-hint {{ font-size: 0.78rem; margin: 0 0 0.5rem; }}
  .range-btns {{ display: flex; gap: 0.25rem; }}
  .range-btns button {{ background: transparent; border: 1px solid #30363d; color: #8b949e;
    border-radius: 4px; font-size: 0.75rem; padding: 0.15rem 0.55rem; cursor: pointer; font-family: inherit; }}
  .range-btns button:hover {{ color: #f0f6fc; border-color: #8b949e; }}
  .range-btns button.active {{ background: #21262d; color: #f0f6fc; }}
  #tl-svg {{ touch-action: pan-y; cursor: crosshair; }}
  .chart-wrap {{ position: relative; }}
  .chart-wrap svg text {{ font-family: inherit; }}
  .viz-tip {{
    position: absolute; pointer-events: none; display: none;
    background: #21262d; color: #f0f6fc; border: 1px solid #30363d; border-radius: 4px;
    padding: 0.5rem 0.7rem; font-size: 0.8rem; line-height: 1.5; z-index: 10;
    box-shadow: 0 4px 12px rgba(0,0,0,0.5); min-width: 170px;
  }}
  .viz-tip .tip-head {{ color: #8b949e; margin-bottom: 0.25rem; white-space: nowrap; }}
  .viz-tip .tip-row {{ display: flex; align-items: center; gap: 0.5rem; white-space: nowrap; }}
  .viz-tip .tip-key {{ display: inline-block; width: 12px; height: 2px; border-radius: 1px; flex: none; }}
  .viz-tip .tip-val {{ font-weight: 600; font-variant-numeric: tabular-nums; }}
  .viz-tip .tip-label {{ color: #8b949e; }}
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
{history_section}
  <h2>Categories</h2>
  {category_rows}

  <h2>Treemap (sized by code bytes, colored by matched%, ordered by address)</h2>
  <div class="treemap-wrap">
    {treemap_svg}
    <div id="treemap-tooltip"></div>
  </div>

  <h2>Units (by address)</h2>
  <p class="meta">Units in section virtual-address order. First {top_n} shown; expand below for the full list.</p>
  <table>
    <thead><tr><th class="num">Address</th><th>Unit</th><th class="num">Code</th><th class="num">Matched</th><th class="num">Fuzzy</th><th>Status</th></tr></thead>
    <tbody>{top_addr_rows}</tbody>
  </table>
  <details>
    <summary>All units by address ({n_units})</summary>
    <table>
      <thead><tr><th class="num">Address</th><th>Unit</th><th class="num">Code</th><th class="num">Matched</th><th class="num">Fuzzy</th><th>Status</th></tr></thead>
      <tbody>{all_addr_rows}</tbody>
    </table>
  </details>

  <h2>Units (by size)</h2>
  <p class="meta">Largest units by code size. First {top_n} shown; expand below for the full list.</p>
  <table>
    <thead><tr><th class="num">Address</th><th>Unit</th><th class="num">Code</th><th class="num">Matched</th><th class="num">Fuzzy</th><th>Status</th></tr></thead>
    <tbody>{top_size_rows}</tbody>
  </table>
  <details>
    <summary>All units by size ({n_units})</summary>
    <table>
      <thead><tr><th class="num">Address</th><th>Unit</th><th class="num">Code</th><th class="num">Matched</th><th class="num">Fuzzy</th><th>Status</th></tr></thead>
      <tbody>{all_size_rows}</tbody>
    </table>
  </details>

  <p class="meta" style="margin-top:2rem"><a href="report.json">Raw report.json</a> · <a href="shield.json">Shield JSON</a> · <a href="history.jsonl">History JSONL</a></p>
</main>
<script>
(() => {{
  const svg = document.getElementById('treemap-svg');
  const tip = document.getElementById('treemap-tooltip');
  if (!svg || !tip) return;
  const wrap = svg.parentElement;
  const fields = [
    ['Address', 'addr'], ['Size', 'size'],
    ['Matched', 'matched'], ['Fuzzy', 'fuzzy'], ['Status', 'status'],
    ['Unit', 'unit'],
  ];
  const show = (rect, evt) => {{
    const name = rect.getAttribute('data-name');
    if (!name) return;
    let html = `<div class="tt-name">${{name}}</div>`;
    for (const [label, key] of fields) {{
      const v = rect.getAttribute('data-' + key);
      if (!v) continue;
      html += `<div class="tt-row"><span class="tt-label">${{label}}</span><span>${{v}}</span></div>`;
    }}
    tip.innerHTML = html;
    tip.style.display = 'block';
    const wrapRect = wrap.getBoundingClientRect();
    const tipRect = tip.getBoundingClientRect();
    let x = evt.clientX - wrapRect.left + 12;
    let y = evt.clientY - wrapRect.top + 12;
    if (x + tipRect.width > wrapRect.width) x = evt.clientX - wrapRect.left - tipRect.width - 12;
    if (y + tipRect.height > wrapRect.height) y = evt.clientY - wrapRect.top - tipRect.height - 12;
    tip.style.left = Math.max(0, x) + 'px';
    tip.style.top = Math.max(0, y) + 'px';
  }};
  svg.addEventListener('mousemove', (e) => {{
    const t = e.target;
    if (t && t.tagName === 'rect' && t.hasAttribute('data-name')) show(t, e);
    else tip.style.display = 'none';
  }});
  svg.addEventListener('mouseleave', () => {{ tip.style.display = 'none'; }});
}})();
</script>
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
    addr = _unit_address(u)
    addr_cell = f"0x{addr:08X}" if addr else "—"
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
        f'<td class="num"><code>{addr_cell}</code></td>'
        f"<td><code>{html.escape(u['name'])}</code></td>"
        f'<td class="num">{format_bytes(code)}</td>'
        f'<td class="num">{matched:.2f}%</td>'
        f'<td class="num">{fuzzy:.2f}%</td>'
        f"<td>{status}</td>"
        "</tr>"
    )


# ---------------------------------------------------------------------------
# Progress-over-time section (history JSONL maintained on the progress-data
# branch by tools/progress_history.py).
# ---------------------------------------------------------------------------

# Series colors: categorical slots 1/2 (dark) — CVD + contrast validated
# against the page surface #0d1117 (skill dataviz validate_palette, all PASS).
C_MATCHED = "#3987e5"
C_LINKED = "#008300"
C_NEG = "#e66767"
INK = "#f0f6fc"
INK_MUTED = "#8b949e"
C_GRID = "#1c2330"
C_BASELINE = "#30363d"
C_SURFACE = "#0d1117"
C_DELTA_GOOD = "#0ca30c"


def load_history_file(path: Path) -> List[Dict[str, Any]]:
    rows = []
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if line:
            rows.append(json.loads(line))
    rows.sort(key=lambda r: (r["ts"], r["sha"]))
    return rows


def _parse_ts(s: str) -> datetime:
    return datetime.fromisoformat(s.replace("Z", "+00:00"))


def _nice_step(span: float, target_ticks: int = 4) -> float:
    """Pick a 1/2/2.5/5 ladder step so span/step lands near target_ticks."""
    if span <= 0:
        return 1.0
    raw = span / target_ticks
    mag = 10 ** math.floor(math.log10(raw))
    for m in (1, 2, 2.5, 5, 10):
        if raw <= m * mag:
            return m * mag
    return 10 * mag


def _fmt_day(d: date) -> str:
    return f"{d.month}/{d.day}"


def timeline_points(rows: List[Dict[str, Any]]) -> List[Dict[str, Any]]:
    """Raw per-commit points for the client-rendered timeline chart.

    The timeline supports date-range zoom and a conditional y-axis break, so
    scales are dynamic — rendering lives in JS (see build_history_section);
    Python only emits the data."""
    pts = []
    prev: Optional[float] = None
    for r in rows:
        m = _to_float(r["matched_code_percent"])
        pts.append({
            "t": round(_parse_ts(r["ts"]).timestamp()),
            "date": r["ts"][:16].replace("T", " "),
            "sha": r["sha"][:9],
            "m": round(m, 4),
            "l": round(_to_float(r.get("complete_code_percent")), 4),
            "dm": round(m - prev, 4) if prev is not None else None,
        })
        prev = m
    return pts


def build_daily_chart(
    rows: List[Dict[str, Any]], width: int = 1000, height: int = 200
) -> Tuple[str, List[Dict[str, Any]]]:
    """Bar chart: matched-code percentage points gained per day (day-end vs
    previous day-end). Single series; days without commits stay empty."""
    ml, mr, mt, mb = 52, 16, 12, 26
    iw, ih = width - ml - mr, height - mt - mb

    # Day-end value per calendar day (committer-local date from the ISO string).
    day_end: Dict[str, float] = {}
    day_commits: Dict[str, int] = {}
    for r in rows:
        d = r["ts"][:10]
        day_end[d] = _to_float(r["matched_code_percent"])
        day_commits[d] = day_commits.get(d, 0) + 1

    days_sorted = sorted(day_end)
    deltas: Dict[str, float] = {}
    prev = _to_float(rows[0]["matched_code_percent"])
    for d in days_sorted:
        deltas[d] = day_end[d] - prev
        prev = day_end[d]

    d0 = date.fromisoformat(days_sorted[0])
    d1 = date.fromisoformat(days_sorted[-1])
    ndays = (d1 - d0).days + 1
    slot_w = iw / ndays
    bar_w = max(2.0, min(24.0, slot_w * 0.66))

    vmax = max(0.0, *deltas.values())
    vmin = min(0.0, *deltas.values())
    if vmax == vmin == 0.0:
        vmax = 1.0
    step = _nice_step(vmax - vmin)

    def y_at(v: float) -> float:
        return mt + (vmax - v) / (vmax - vmin or 1.0) * ih

    parts: List[str] = []
    tick = 0.0
    while tick <= vmax + 1e-9:
        if tick >= vmin:
            y = y_at(tick)
            parts.append(
                f'<line x1="{ml}" y1="{y:.1f}" x2="{ml + iw}" y2="{y:.1f}" '
                f'stroke="{C_GRID if tick else C_BASELINE}" stroke-width="1"/>'
            )
            parts.append(
                f'<text x="{ml - 8}" y="{y + 4:.1f}" text-anchor="end" '
                f'fill="{INK_MUTED}" font-size="11">{f"{tick:+g}" if tick else "0"}</text>'
            )
        tick += step
    tick = -step
    while tick >= vmin - 1e-9:
        y = y_at(tick)
        parts.append(
            f'<line x1="{ml}" y1="{y:.1f}" x2="{ml + iw}" y2="{y:.1f}" '
            f'stroke="{C_GRID}" stroke-width="1"/>'
        )
        parts.append(
            f'<text x="{ml - 8}" y="{y + 4:.1f}" text-anchor="end" '
            f'fill="{INK_MUTED}" font-size="11">{tick:+g}</text>'
        )
        tick -= step

    # X ticks reuse the same cadence as the timeline.
    step_days = max(1, round(max(1, ndays - 1) / 6))
    d = d0 + timedelta(days=step_days)
    while d <= d1:
        x = ml + ((d - d0).days + 0.5) * slot_w
        parts.append(
            f'<text x="{x:.1f}" y="{mt + ih + 18}" text-anchor="middle" '
            f'fill="{INK_MUTED}" font-size="11">{_fmt_day(d)}</text>'
        )
        d += timedelta(days=step_days)

    def bar_path(x: float, v: float) -> str:
        """4px rounded data-end, square at the zero baseline."""
        y0, y1 = y_at(0.0), y_at(v)
        r = min(4.0, bar_w / 2, abs(y1 - y0))
        if v >= 0:
            return (
                f"M {x:.2f},{y0:.2f} L {x:.2f},{y1 + r:.2f} "
                f"Q {x:.2f},{y1:.2f} {x + r:.2f},{y1:.2f} "
                f"L {x + bar_w - r:.2f},{y1:.2f} "
                f"Q {x + bar_w:.2f},{y1:.2f} {x + bar_w:.2f},{y1 + r:.2f} "
                f"L {x + bar_w:.2f},{y0:.2f} Z"
            )
        return (
            f"M {x:.2f},{y0:.2f} L {x:.2f},{y1 - r:.2f} "
            f"Q {x:.2f},{y1:.2f} {x + r:.2f},{y1:.2f} "
            f"L {x + bar_w - r:.2f},{y1:.2f} "
            f"Q {x + bar_w:.2f},{y1:.2f} {x + bar_w:.2f},{y1 - r:.2f} "
            f"L {x + bar_w:.2f},{y0:.2f} Z"
        )

    hover_days: List[Dict[str, Any]] = []
    for ds in days_sorted:
        v = deltas[ds]
        i = (date.fromisoformat(ds) - d0).days
        x = ml + i * slot_w + (slot_w - bar_w) / 2
        if abs(v) > 1e-9:
            parts.append(
                f'<path d="{bar_path(x, v)}" '
                f'fill="{C_MATCHED if v >= 0 else C_NEG}"/>'
            )
        # Full-height transparent hit target (wider than the mark).
        parts.append(
            f'<rect class="dg-hit" data-i="{len(hover_days)}" '
            f'x="{ml + i * slot_w:.2f}" y="{mt}" '
            f'width="{slot_w:.2f}" height="{ih}" fill="transparent"/>'
        )
        hover_days.append({
            "x": round(ml + i * slot_w + slot_w / 2, 2),
            "date": ds, "d": round(v, 3), "n": day_commits[ds],
        })

    svg = (
        f'<svg id="dg-svg" xmlns="http://www.w3.org/2000/svg" '
        f'viewBox="0 0 {width} {height}" width="100%" '
        f'preserveAspectRatio="xMidYMid meet" role="img" '
        f'aria-label="Matched-code percentage points gained per day.">'
        + "".join(parts) + "</svg>"
    )
    return svg, hover_days


def history_commit_rows(rows: List[Dict[str, Any]], repo_url: str) -> List[str]:
    """Per-commit table rows, newest first, with deltas vs the previous commit."""
    out: List[str] = []
    prev_pct: Optional[float] = None
    prev_bytes: Optional[int] = None
    annotated = []
    for r in rows:
        pct = _to_float(r["matched_code_percent"])
        b = _to_int(r["matched_code"])
        annotated.append((r, pct,
                          None if prev_pct is None else pct - prev_pct,
                          None if prev_bytes is None else b - prev_bytes))
        prev_pct, prev_bytes = pct, b
    for r, pct, dpct, dbytes in reversed(annotated):
        sha = html.escape(r["sha"])
        if dpct is None:
            delta_cell = '<span style="color:#8b949e">—</span>'
            bytes_cell = "—"
        else:
            if dpct > 0:
                color = C_DELTA_GOOD
            elif dpct < 0:
                color = C_NEG
            else:
                color = "#8b949e"
            prec = 4 if abs(dpct) < 0.01 else 3
            delta_cell = f'<span style="color:{color}">{dpct:+.{prec}f}pp</span>'
            bytes_cell = f"{dbytes:+,} B" if dbytes else "±0 B"
        out.append(
            "<tr>"
            f'<td>{html.escape(r["ts"][:16].replace("T", " "))}</td>'
            f'<td><a href="{html.escape(repo_url)}/commit/{sha}"><code>{sha[:9]}</code></a></td>'
            f'<td class="num">{pct:.3f}%</td>'
            f'<td class="num">{delta_cell}</td>'
            f'<td class="num">{bytes_cell}</td>'
            f'<td class="num">{_to_float(r.get("complete_code_percent")):.2f}%</td>'
            f'<td class="num">{_to_int(r.get("matched_functions"))} / {_to_int(r.get("total_functions"))}</td>'
            "</tr>"
        )
    return out


def _pace_cards(rows: List[Dict[str, Any]]) -> str:
    """Stat tiles: recent gain and a naive ETA to 100% (estimate, labeled)."""
    last = rows[-1]
    last_t = _parse_ts(last["ts"])
    last_pct = _to_float(last["matched_code_percent"])

    def gain_over(days: int) -> Optional[float]:
        cutoff = last_t - timedelta(days=days)
        base = None
        for r in rows:
            if _parse_ts(r["ts"]) <= cutoff:
                base = _to_float(r["matched_code_percent"])
        if base is None:
            base = _to_float(rows[0]["matched_code_percent"])
        return last_pct - base

    g7 = gain_over(7)
    g30 = gain_over(30)
    span_days = max(1.0, (last_t - _parse_ts(rows[0]["ts"])).days or 1.0)
    pace = g30 / min(30.0, span_days) if g30 is not None else None
    if pace and pace > 0:
        eta_days = (100.0 - last_pct) / pace
        eta = (last_t + timedelta(days=eta_days)).date()
        eta_val, eta_sub = f"{eta.year}-{eta.month:02d}", f"~{eta_days:.0f} days at 30d pace (estimate)"
    else:
        eta_val, eta_sub = "—", "no positive 30d pace"
    return (
        '<div class="summary" style="margin-bottom:1rem">'
        f'<div class="card"><div class="label">Last 7 days</div>'
        f'<div class="value">{g7:+.3f}pp</div><div class="sub">matched code</div></div>'
        f'<div class="card"><div class="label">Last 30 days</div>'
        f'<div class="value">{g30:+.3f}pp</div><div class="sub">{pace:+.3f}pp / day avg</div></div>'
        f'<div class="card"><div class="label">100% reached</div>'
        f'<div class="value">{eta_val}</div><div class="sub">{eta_sub}</div></div>'
        "</div>"
    )


def _json_for_html(data: Any) -> str:
    return json.dumps(data, separators=(",", ":")).replace("</", "<\\/")


# Timeline renderer. Lives client-side because the date-range zoom and the
# conditional y-axis snip make the scales dynamic. Kept as a plain string
# (tokens __C_M__/__C_L__) so braces need no escaping; injected into the
# history-section f-string next to the shared tooltip helpers it uses.
TL_JS = r"""
    // ---- Timeline: client-rendered so date-range zoom + axis snip work ----
    const tlSvg = document.getElementById('tl-svg');
    if (tlSvg) {
      const NS = 'http://www.w3.org/2000/svg';
      const pts = JSON.parse(document.getElementById('tl-data').textContent);
      const wrap = document.getElementById('tl-wrap');
      const tip = document.getElementById('tl-tip');
      const W = 1000, H = 360, ML = 52, MR = 100, MT = 14, MB = 30;
      const IW = W - ML - MR, IH = H - MT - MB, YBOT = MT + IH;
      const CM = '__C_M__', CL = '__C_L__';
      const GRID = '#1c2330', BASE = '#30363d', MUT = '#8b949e';
      const INK2 = '#f0f6fc', SURF = '#0d1117';
      const tMin = pts[0].t, tMax = pts[pts.length - 1].t;
      let domain = [tMin, tMax];
      let vis = [];  // visible points with px coords, for hover

      const el = (n, at, parent) => {
        const e = document.createElementNS(NS, n);
        for (const k in at) e.setAttribute(k, at[k]);
        if (parent) parent.appendChild(e);
        return e;
      };
      const label = (parent, x, y, s, anchor, fill, size, weight) => {
        const t = el('text', {x, y, 'text-anchor': anchor || 'start',
                              fill: fill || MUT, 'font-size': size || 11}, parent);
        if (weight) t.setAttribute('font-weight', weight);
        t.textContent = s;
      };
      const niceStep = raw => {
        const mag = Math.pow(10, Math.floor(Math.log10(raw)));
        for (const m of [1, 2, 2.5, 5, 10]) if (raw <= m * mag) return m * mag;
        return 10 * mag;
      };
      const fmtPct = v => +v.toFixed(2) + '%';

      const defs = el('defs', {}, tlSvg);
      const clip = el('clipPath', {id: 'tl-clip'}, defs);
      const clipRect = el('rect', {x: ML, y: MT, width: IW, height: IH}, clip);
      const plotG = el('g', {}, tlSvg);
      const seriesG = el('g', {'clip-path': 'url(#tl-clip)'}, tlSvg);
      const topG = el('g', {}, tlSvg);
      const hoverG = el('g', {}, tlSvg);
      const cross = el('line', {y1: MT, y2: YBOT, stroke: MUT, 'stroke-width': 1, opacity: 0}, hoverG);
      const dotM = el('circle', {r: 4, fill: CM, stroke: SURF, 'stroke-width': 2, opacity: 0}, hoverG);
      const dotL = el('circle', {r: 4, fill: CL, stroke: SURF, 'stroke-width': 2, opacity: 0}, hoverG);
      const selRect = el('rect', {y: MT, height: IH, fill: CM, opacity: 0.15, display: 'none'}, hoverG);

      const hideHover = () => {
        tip.style.display = 'none';
        for (const e of [cross, dotM, dotL]) e.setAttribute('opacity', '0');
      };

      function render() {
        const [t0, t1] = domain;
        const pad = (t1 - t0) * 0.02;
        const tA = t0 - pad, tB = t1 + pad;
        const xAt = t => ML + (t - tA) / (tB - tA) * IW;

        const first = pts.findIndex(p => p.t >= t0);
        let last = -1;
        for (let i = pts.length - 1; i >= 0; i--) if (pts[i].t <= t1) { last = i; break; }
        const shown = (first < 0 || last < first) ? [] : pts.slice(first, last + 1);

        // Full 0-100 when the data is close to the goal; otherwise snip the
        // axis: 0..yTop to scale, a marked break band, then the 100% line.
        const dataMax = shown.length ? Math.max(...shown.map(p => Math.max(p.m, p.l))) : 100;
        const snip = dataMax < 50;
        let yTop, yDataTop, gstep;
        if (snip) {
          gstep = niceStep(Math.max(dataMax, 1e-4) / 4);
          yTop = gstep * Math.ceil(dataMax / gstep);
          if (!yTop || yTop - dataMax < gstep * 0.2) yTop += gstep;
          yDataTop = MT + 44;
        } else {
          yTop = 100; gstep = 25; yDataTop = MT;
        }
        const yAt = v => YBOT - (v / yTop) * (YBOT - yDataTop);
        clipRect.setAttribute('y', yDataTop - 5);
        clipRect.setAttribute('height', YBOT - yDataTop + 10);

        plotG.replaceChildren();
        seriesG.replaceChildren();
        topG.replaceChildren();

        for (let v = 0; v <= yTop + 1e-9; v += gstep) {
          const y = yAt(v);
          el('line', {x1: ML, y1: y, x2: ML + IW, y2: y,
                      stroke: v ? GRID : BASE, 'stroke-width': 1}, plotG);
          label(plotG, ML - 8, y + 4, fmtPct(v), 'end');
        }
        if (snip) {
          const yGoal = MT + 6;
          el('line', {x1: ML, y1: yGoal, x2: ML + IW, y2: yGoal, stroke: GRID, 'stroke-width': 1}, plotG);
          label(plotG, ML - 8, yGoal + 4, '100%', 'end');
          label(plotG, ML + IW, yGoal - 5, 'goal', 'end');
          // the snip: double slash marks at both edges of the break band
          const yb = (yGoal + yDataTop) / 2;
          for (const x of [ML, ML + IW]) {
            for (const dy of [-4, 4]) {
              el('line', {x1: x - 7, y1: yb + dy + 4, x2: x + 7, y2: yb + dy - 4,
                          stroke: MUT, 'stroke-width': 1.2}, plotG);
            }
          }
        } else {
          label(plotG, ML + IW, yAt(100) - 6, 'goal', 'end');
        }

        const spanDays = Math.max(1, (tB - tA) / 86400);
        const stepDays = Math.max(1, Math.round(spanDays / 6));
        const dEnd = new Date(tB * 1000);
        let d = new Date(tA * 1000);
        d.setHours(0, 0, 0, 0);
        d = new Date(d.getTime() + 86400000 * stepDays);
        for (; d <= dEnd; d = new Date(d.getTime() + 86400000 * stepDays)) {
          const x = xAt(d.getTime() / 1000);
          if (x < ML || x > ML + IW) continue;
          el('line', {x1: x, y1: yDataTop, x2: x, y2: YBOT, stroke: GRID, 'stroke-width': 1}, plotG);
          label(plotG, x, YBOT + 18, (d.getMonth() + 1) + '/' + d.getDate(), 'middle');
        }

        vis = shown.map(p => ({x: xAt(p.t), ym: yAt(p.m), yl: yAt(p.l), p}));
        if (vis.length) {
          // one neighbor each side so lines run to the plot edge (clipped)
          const ext = [];
          if (first > 0) ext.push(pts[first - 1]);
          ext.push(...shown);
          if (last < pts.length - 1) ext.push(pts[last + 1]);
          const ep = ext.map(p => ({x: xAt(p.t), ym: yAt(p.m), yl: yAt(p.l)}));
          const lineOf = key => ep.map(q => q.x.toFixed(2) + ',' + q[key].toFixed(2)).join(' ');
          const wash = 'M ' + ep[0].x.toFixed(2) + ',' + yAt(0).toFixed(2) + ' L ' +
            ep.map(q => q.x.toFixed(2) + ',' + q.ym.toFixed(2)).join(' L ') +
            ' L ' + ep[ep.length - 1].x.toFixed(2) + ',' + yAt(0).toFixed(2) + ' Z';
          el('path', {d: wash, fill: CM, opacity: 0.08}, seriesG);
          el('polyline', {points: lineOf('yl'), fill: 'none', stroke: CL, 'stroke-width': 2,
                          'stroke-linejoin': 'round', 'stroke-linecap': 'round'}, seriesG);
          el('polyline', {points: lineOf('ym'), fill: 'none', stroke: CM, 'stroke-width': 2,
                          'stroke-linejoin': 'round', 'stroke-linecap': 'round'}, seriesG);

          const e2 = vis[vis.length - 1];
          let lm = e2.ym, ll = e2.yl;
          if (Math.abs(lm - ll) < 16) {
            const mid = (lm + ll) / 2;
            if (lm <= ll) { lm = mid - 8; ll = mid + 8; } else { lm = mid + 8; ll = mid - 8; }
          }
          for (const [ey, ly, color, val] of [[e2.ym, lm, CM, e2.p.m], [e2.yl, ll, CL, e2.p.l]]) {
            if (Math.abs(ly - ey) > 1) {
              el('line', {x1: e2.x + 6, y1: ey, x2: e2.x + 16, y2: ly, stroke: GRID, 'stroke-width': 1}, topG);
            }
            el('circle', {cx: e2.x, cy: ey, r: 4.5, fill: color, stroke: SURF, 'stroke-width': 2}, topG);
            label(topG, e2.x + 20, ly + 4, val.toFixed(2) + '%', 'start', INK2, 12, 600);
          }
        }
        cross.setAttribute('y1', yDataTop);
        hideHover();
      }

      const viewXOf = evt => {
        const r = tlSvg.getBoundingClientRect();
        return (evt.clientX - r.left) * W / r.width;
      };
      const btns = document.querySelectorAll('#tl-range button');
      const setActive = id => btns.forEach(b => b.classList.toggle('active', b.dataset.d === id));
      btns.forEach(b => b.addEventListener('click', () => {
        domain = b.dataset.d === 'all' ? [tMin, tMax]
          : [Math.max(tMin, tMax - (+b.dataset.d) * 86400), tMax];
        setActive(b.dataset.d);
        render();
      }));

      let drag = null;
      tlSvg.addEventListener('pointerdown', e => {
        drag = {x0: viewXOf(e), moved: false};
        tlSvg.setPointerCapture(e.pointerId);
      });
      tlSvg.addEventListener('pointermove', e => {
        const x = viewXOf(e);
        if (drag) {
          if (Math.abs(x - drag.x0) > 4) drag.moved = true;
          if (drag.moved) {
            hideHover();
            const a = Math.max(ML, Math.min(x, drag.x0));
            const b2 = Math.min(ML + IW, Math.max(x, drag.x0));
            selRect.setAttribute('x', a);
            selRect.setAttribute('width', Math.max(0, b2 - a));
            selRect.removeAttribute('display');
            return;
          }
        }
        if (!vis.length) return;
        let best = 0, bd = Infinity;
        for (let i = 0; i < vis.length; i++) {
          const dd = Math.abs(vis[i].x - x);
          if (dd < bd) { bd = dd; best = i; }
        }
        const v = vis[best], p = v.p;
        cross.setAttribute('x1', v.x); cross.setAttribute('x2', v.x);
        cross.setAttribute('opacity', '0.5');
        dotM.setAttribute('cx', v.x); dotM.setAttribute('cy', v.ym);
        dotL.setAttribute('cx', v.x); dotL.setAttribute('cy', v.yl);
        dotM.setAttribute('opacity', '1'); dotL.setAttribute('opacity', '1');
        tip.replaceChildren();
        const head = document.createElement('div');
        head.className = 'tip-head';
        head.textContent = p.date + ' · ' + p.sha;
        tip.appendChild(head);
        const dm = p.dm == null ? '' : ' (' + (p.dm >= 0 ? '+' : '') + p.dm.toFixed(3) + 'pp)';
        mkRow(tip, p.m.toFixed(3) + '%' + dm, 'matched', CM);
        mkRow(tip, p.l.toFixed(2) + '%', 'linked', CL);
        place(tip, wrap, e);
      });
      const endDrag = e => {
        if (!drag) return;
        const wasDrag = drag.moved;
        const x1 = drag.x0, x2 = viewXOf(e);
        drag = null;
        selRect.setAttribute('display', 'none');
        if (!wasDrag) return;
        const [t0, t1] = domain;
        const pad = (t1 - t0) * 0.02;
        const tA = t0 - pad, tB = t1 + pad;
        const tOf = x => tA + (Math.max(ML, Math.min(ML + IW, x)) - ML) / IW * (tB - tA);
        let lo = tOf(Math.min(x1, x2)), hi = tOf(Math.max(x1, x2));
        const minSpan = 6 * 3600;
        if (hi - lo < minSpan) { const c = (lo + hi) / 2; lo = c - minSpan / 2; hi = c + minSpan / 2; }
        domain = [lo, hi];
        setActive('');
        render();
      };
      tlSvg.addEventListener('pointerup', endDrag);
      tlSvg.addEventListener('pointercancel', () => { drag = null; selRect.setAttribute('display', 'none'); });
      tlSvg.addEventListener('mouseleave', hideHover);
      tlSvg.addEventListener('dblclick', () => { domain = [tMin, tMax]; setActive('all'); render(); });

      render();
    }
"""


def build_history_section(rows: List[Dict[str, Any]], repo_url: str) -> str:
    if len(rows) < 2:
        return ""
    tl_pts = timeline_points(rows)
    tl_script = TL_JS.replace("__C_M__", C_MATCHED).replace("__C_L__", C_LINKED)
    dg_svg, dg_days = build_daily_chart(rows)
    commit_rows = history_commit_rows(rows, repo_url)
    top_n = 20
    if len(commit_rows) > top_n:
        table_meta = (f"Latest {top_n} commits on <code>main</code> with a successful "
                      f"build; expand below for all {len(commit_rows)}.")
        table_details = f"""
  <details>
    <summary>All commits ({len(commit_rows)})</summary>
    <table>
      <thead><tr><th>Date</th><th>Commit</th><th class="num">Matched</th><th class="num">Δ matched</th><th class="num">Δ bytes</th><th class="num">Linked</th><th class="num">Fns</th></tr></thead>
      <tbody>{"".join(commit_rows)}</tbody>
    </table>
  </details>"""
    else:
        table_meta = (f"All {len(commit_rows)} commits on <code>main</code> "
                      f"with a successful build.")
        table_details = ""

    return f"""
  <h2>Progress over time</h2>
  {_pace_cards(rows)}
  <div class="chart-card">
    <div class="chart-head">
      <div class="chart-title">Matched code toward the 100% goal</div>
      <div class="chart-controls">
        <div class="range-btns" id="tl-range">
          <button data-d="7">7d</button><button data-d="30">30d</button><button data-d="90">90d</button><button data-d="all" class="active">All</button>
        </div>
        <div class="chart-legend">
          <span><span class="key" style="background:{C_MATCHED}"></span>Matched code</span>
          <span><span class="key" style="background:{C_LINKED}"></span>Linked</span>
        </div>
      </div>
    </div>
    <p class="meta chart-hint">Drag to zoom to a date range · double-click or All to reset. While far from the goal, the y axis is snipped: 0–fit, break, 100%.</p>
    <div class="chart-wrap" id="tl-wrap">
      <svg id="tl-svg" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1000 360" width="100%"
           preserveAspectRatio="xMidYMid meet" role="img"
           aria-label="Matched and linked code percentage per commit over time, toward the 100% goal. Y axis may show a break between the data range and 100%."></svg>
      <noscript><p class="meta">The timeline chart needs JavaScript; the per-commit table below has the same data.</p></noscript>
      <div class="viz-tip" id="tl-tip"></div>
    </div>
  </div>
  <div class="chart-card">
    <div class="chart-head">
      <div class="chart-title">Daily gain — matched code, percentage points per day</div>
    </div>
    <div class="chart-wrap" id="dg-wrap">
      {dg_svg}
      <div class="viz-tip" id="dg-tip"></div>
    </div>
  </div>

  <h2>Per-commit progress</h2>
  <p class="meta">{table_meta}</p>
  <table>
    <thead><tr><th>Date</th><th>Commit</th><th class="num">Matched</th><th class="num">Δ matched</th><th class="num">Δ bytes</th><th class="num">Linked</th><th class="num">Fns</th></tr></thead>
    <tbody>{"".join(commit_rows[:top_n])}</tbody>
  </table>{table_details}

  <script type="application/json" id="tl-data">{_json_for_html(tl_pts)}</script>
  <script type="application/json" id="dg-data">{_json_for_html(dg_days)}</script>
  <script>
  (() => {{
    // Shared tooltip helpers (textContent only — no innerHTML for data).
    const mkRow = (tip, value, label, keyColor) => {{
      const row = document.createElement('div');
      row.className = 'tip-row';
      if (keyColor) {{
        const key = document.createElement('span');
        key.className = 'tip-key';
        key.style.background = keyColor;
        row.appendChild(key);
      }}
      const val = document.createElement('span');
      val.className = 'tip-val';
      val.textContent = value;
      const lab = document.createElement('span');
      lab.className = 'tip-label';
      lab.textContent = label;
      row.appendChild(val);
      row.appendChild(lab);
      tip.appendChild(row);
    }};
    const place = (tip, wrap, evt) => {{
      tip.style.display = 'block';
      const wr = wrap.getBoundingClientRect();
      const tr = tip.getBoundingClientRect();
      let x = evt.clientX - wr.left + 14, y = evt.clientY - wr.top + 14;
      if (x + tr.width > wr.width) x = evt.clientX - wr.left - tr.width - 14;
      if (y + tr.height > wr.height) y = Math.max(0, wr.height - tr.height);
      tip.style.left = Math.max(0, x) + 'px';
      tip.style.top = Math.max(0, y) + 'px';
    }};
{tl_script}

    // Daily bars: the (full-height) hit rect is the target.
    const dgSvg = document.getElementById('dg-svg');
    if (dgSvg) {{
      const days = JSON.parse(document.getElementById('dg-data').textContent);
      const wrap = document.getElementById('dg-wrap');
      const tip = document.getElementById('dg-tip');
      dgSvg.addEventListener('mousemove', (e) => {{
        const t = e.target;
        if (!t.classList || !t.classList.contains('dg-hit')) {{
          tip.style.display = 'none';
          return;
        }}
        const d = days[+t.dataset.i];
        tip.replaceChildren();
        const head = document.createElement('div');
        head.className = 'tip-head';
        head.textContent = d.date;
        tip.appendChild(head);
        mkRow(tip, (d.d >= 0 ? '+' : '') + d.d.toFixed(3) + 'pp',
              d.n + (d.n === 1 ? ' commit' : ' commits'), '{C_MATCHED}');
        place(tip, wrap, e);
      }});
      dgSvg.addEventListener('mouseleave', () => {{ tip.style.display = 'none'; }});
    }}
  }})();
  </script>
"""


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("report", type=Path, help="Path to report.json")
    ap.add_argument("--out-dir", type=Path, default=Path("site"))
    ap.add_argument("--version", default="GNLJ82")
    ap.add_argument("--title", default="Mario Kart Arcade GP2 — decomp progress")
    ap.add_argument("--commit", default=None, help="Optional commit SHA to display")
    ap.add_argument("--history", type=Path, default=None,
                    help="Per-commit history JSONL (progress-data branch)")
    ap.add_argument("--repo-url", default="https://github.com/naari3/mkgp2-decomp")
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
    units_with_code.sort(key=_unit_address)
    units_by_size = sorted(
        units_with_code,
        key=lambda u: _to_int(u["measures"].get("total_code")),
        reverse=True,
    )

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

    history_section = ""
    if args.history and args.history.is_file():
        hist_rows = load_history_file(args.history)
        if hist_rows:
            history_section = build_history_section(hist_rows, args.repo_url)
            shutil.copyfile(args.history, args.out_dir / "history.jsonl")

    commit_part = f" · commit <code>{html.escape(args.commit)}</code>" if args.commit else ""

    html_out = HTML_TEMPLATE.format(
        title=html.escape(args.title),
        version=html.escape(args.version),
        commit_part=commit_part,
        history_section=history_section,
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
        top_addr_rows="\n".join(unit_row(u) for u in units_with_code[:30]),
        all_addr_rows="\n".join(unit_row(u) for u in units_with_code),
        top_size_rows="\n".join(unit_row(u) for u in units_by_size[:30]),
        all_size_rows="\n".join(unit_row(u) for u in units_by_size),
        n_units=len(units_with_code),
        top_n=30,
    )
    (args.out_dir / "index.html").write_text(html_out, encoding="utf-8")

    print(f"wrote {args.out_dir / 'index.html'}")
    print(f"  matched code: {measures.matched_code_percent:.2f}% "
          f"({measures.matched_code}/{measures.total_code} bytes)")
    print(f"  linked units: {measures.complete_units}/{measures.total_units}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
