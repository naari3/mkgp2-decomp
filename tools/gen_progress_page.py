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


def build_timeline_chart(
    rows: List[Dict[str, Any]], width: int = 1000, height: int = 360
) -> Tuple[str, List[Dict[str, Any]]]:
    """Line chart: matched/linked code % per commit over time, y fixed 0-100
    so the distance to the 100% goal stays honest. Returns (svg, hover_points)."""
    ml, mr, mt, mb = 52, 100, 14, 30
    iw, ih = width - ml - mr, height - mt - mb

    times = [_parse_ts(r["ts"]).timestamp() for r in rows]
    t0, t1 = min(times), max(times)
    if t1 - t0 < 86400:
        pad = (86400 - (t1 - t0)) / 2
        t0, t1 = t0 - pad, t1 + pad

    def x_at(t: float) -> float:
        return ml + (t - t0) / (t1 - t0) * iw

    def y_at(pct: float) -> float:
        return mt + (100.0 - pct) / 100.0 * ih

    parts: List[str] = []
    # Horizontal gridlines every 25%, hairline; 100% doubles as the goal line.
    for pct in (0, 25, 50, 75, 100):
        y = y_at(pct)
        stroke = C_BASELINE if pct == 0 else C_GRID
        parts.append(
            f'<line x1="{ml}" y1="{y:.1f}" x2="{ml + iw}" y2="{y:.1f}" '
            f'stroke="{stroke}" stroke-width="1"/>'
        )
        parts.append(
            f'<text x="{ml - 8}" y="{y + 4:.1f}" text-anchor="end" '
            f'fill="{INK_MUTED}" font-size="11">{pct}%</text>'
        )
    parts.append(
        f'<text x="{ml + iw}" y="{y_at(100) - 6:.1f}" text-anchor="end" '
        f'fill="{INK_MUTED}" font-size="11">goal</text>'
    )

    # X ticks on day boundaries, ~6 across the range.
    d0 = datetime.fromtimestamp(t0).date()
    d1 = datetime.fromtimestamp(t1).date()
    ndays = max(1, (d1 - d0).days)
    step_days = max(1, round(ndays / 6))
    d = d0 + timedelta(days=step_days)
    while d <= d1:
        t = datetime(d.year, d.month, d.day).timestamp()
        if t0 <= t <= t1:
            x = x_at(t)
            parts.append(
                f'<line x1="{x:.1f}" y1="{mt}" x2="{x:.1f}" y2="{mt + ih}" '
                f'stroke="{C_GRID}" stroke-width="1"/>'
            )
            parts.append(
                f'<text x="{x:.1f}" y="{mt + ih + 18}" text-anchor="middle" '
                f'fill="{INK_MUTED}" font-size="11">{_fmt_day(d)}</text>'
            )
        d += timedelta(days=step_days)

    pts_m = [(x_at(t), y_at(_to_float(r["matched_code_percent"])))
             for t, r in zip(times, rows)]
    pts_l = [(x_at(t), y_at(_to_float(r.get("complete_code_percent"))))
             for t, r in zip(times, rows)]

    def poly(pts: List[Tuple[float, float]]) -> str:
        return " ".join(f"{x:.2f},{y:.2f}" for x, y in pts)

    # Area wash under the primary series only (~8% opacity).
    wash = (
        f'<path d="M {pts_m[0][0]:.2f},{y_at(0):.2f} '
        + " ".join(f"L {x:.2f},{y:.2f}" for x, y in pts_m)
        + f' L {pts_m[-1][0]:.2f},{y_at(0):.2f} Z" fill="{C_MATCHED}" opacity="0.08"/>'
    )
    parts.append(wash)
    for pts, color in ((pts_l, C_LINKED), (pts_m, C_MATCHED)):
        parts.append(
            f'<polyline points="{poly(pts)}" fill="none" stroke="{color}" '
            f'stroke-width="2" stroke-linejoin="round" stroke-linecap="round"/>'
        )

    # End markers (surface ring) + direct value labels in ink, nudged apart
    # with leader lines when the two endpoints collide.
    end_m, end_l = pts_m[-1], pts_l[-1]
    lab_m, lab_l = end_m[1], end_l[1]
    if abs(lab_m - lab_l) < 16:
        mid = (lab_m + lab_l) / 2
        if lab_m <= lab_l:
            lab_m, lab_l = mid - 8, mid + 8
        else:
            lab_m, lab_l = mid + 8, mid - 8
    for (ex, ey), ly, color, val in (
        (end_m, lab_m, C_MATCHED, _to_float(rows[-1]["matched_code_percent"])),
        (end_l, lab_l, C_LINKED, _to_float(rows[-1].get("complete_code_percent"))),
    ):
        if abs(ly - ey) > 1:
            parts.append(
                f'<line x1="{ex + 6:.1f}" y1="{ey:.1f}" x2="{ex + 16:.1f}" y2="{ly:.1f}" '
                f'stroke="{C_GRID}" stroke-width="1"/>'
            )
        parts.append(
            f'<circle cx="{ex:.1f}" cy="{ey:.1f}" r="4.5" fill="{color}" '
            f'stroke="{C_SURFACE}" stroke-width="2"/>'
        )
        parts.append(
            f'<text x="{ex + 20:.1f}" y="{ly + 4:.1f}" fill="{INK}" '
            f'font-size="12" font-weight="600">{val:.2f}%</text>'
        )

    # Crosshair + hover dots, driven by JS.
    parts.append(
        f'<line id="tl-cross" x1="0" y1="{mt}" x2="0" y2="{mt + ih}" '
        f'stroke="{INK_MUTED}" stroke-width="1" opacity="0"/>'
    )
    for dot_id, color in (("tl-dot-m", C_MATCHED), ("tl-dot-l", C_LINKED)):
        parts.append(
            f'<circle id="{dot_id}" r="4" fill="{color}" '
            f'stroke="{C_SURFACE}" stroke-width="2" opacity="0"/>'
        )

    svg = (
        f'<svg id="tl-svg" xmlns="http://www.w3.org/2000/svg" '
        f'viewBox="0 0 {width} {height}" width="100%" '
        f'preserveAspectRatio="xMidYMid meet" role="img" '
        f'aria-label="Matched and linked code percentage per commit over time, toward the 100% goal.">'
        + "".join(parts) + "</svg>"
    )

    hover_pts = []
    prev = None
    for r, (xm, ym), (xl, yl) in zip(rows, pts_m, pts_l):
        m = _to_float(r["matched_code_percent"])
        hover_pts.append({
            "x": round(xm, 2), "ym": round(ym, 2), "yl": round(yl, 2),
            "sha": r["sha"][:9],
            "date": r["ts"][:16].replace("T", " "),
            "m": round(m, 3),
            "l": round(_to_float(r.get("complete_code_percent")), 3),
            "dm": round(m - prev, 3) if prev is not None else None,
        })
        prev = m
    return svg, hover_pts


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


def build_history_section(rows: List[Dict[str, Any]], repo_url: str) -> str:
    if len(rows) < 2:
        return ""
    tl_svg, tl_pts = build_timeline_chart(rows)
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
      <div class="chart-legend">
        <span><span class="key" style="background:{C_MATCHED}"></span>Matched code</span>
        <span><span class="key" style="background:{C_LINKED}"></span>Linked</span>
      </div>
    </div>
    <div class="chart-wrap" id="tl-wrap">
      {tl_svg}
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
    const viewX = (svg, evt) => {{
      const r = svg.getBoundingClientRect();
      return (evt.clientX - r.left) * svg.viewBox.baseVal.width / r.width;
    }};

    // Timeline: crosshair snaps to the nearest commit; one tooltip, every series.
    const tlSvg = document.getElementById('tl-svg');
    if (tlSvg) {{
      const pts = JSON.parse(document.getElementById('tl-data').textContent);
      const wrap = document.getElementById('tl-wrap');
      const tip = document.getElementById('tl-tip');
      const cross = document.getElementById('tl-cross');
      const dotM = document.getElementById('tl-dot-m');
      const dotL = document.getElementById('tl-dot-l');
      const hide = () => {{
        tip.style.display = 'none';
        for (const el of [cross, dotM, dotL]) el.setAttribute('opacity', '0');
      }};
      tlSvg.addEventListener('mousemove', (e) => {{
        const x = viewX(tlSvg, e);
        let best = 0, bd = Infinity;
        for (let i = 0; i < pts.length; i++) {{
          const d = Math.abs(pts[i].x - x);
          if (d < bd) {{ bd = d; best = i; }}
        }}
        const p = pts[best];
        cross.setAttribute('x1', p.x); cross.setAttribute('x2', p.x);
        cross.setAttribute('opacity', '0.5');
        dotM.setAttribute('cx', p.x); dotM.setAttribute('cy', p.ym);
        dotL.setAttribute('cx', p.x); dotL.setAttribute('cy', p.yl);
        dotM.setAttribute('opacity', '1'); dotL.setAttribute('opacity', '1');
        tip.replaceChildren();
        const head = document.createElement('div');
        head.className = 'tip-head';
        head.textContent = p.date + ' · ' + p.sha;
        tip.appendChild(head);
        const dm = p.dm === null ? '' : ' (' + (p.dm >= 0 ? '+' : '') + p.dm.toFixed(3) + 'pp)';
        mkRow(tip, p.m.toFixed(3) + '%' + dm, 'matched', '{C_MATCHED}');
        mkRow(tip, p.l.toFixed(2) + '%', 'linked', '{C_LINKED}');
        place(tip, wrap, e);
      }});
      tlSvg.addEventListener('mouseleave', hide);
    }}

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
