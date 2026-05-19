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
    """Binary-split treemap of units (decomp.dev / streemap-rs `binary`), input order preserved.

    Caller passes units already in the desired order — typically address order — so spatial
    adjacency follows input order rather than size-descending packing."""
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

    rects: List[str] = []
    for (u, size, matched, fuzzy), (x, y, w, h) in zip(items, out_rects):
        addr = _unit_address(u)
        addr_str = f"0x{addr:08X}" if addr else ""
        status = _unit_status_label(u, matched)
        rects.append(
            f'<rect x="{x:.2f}" y="{y:.2f}" width="{w:.2f}" height="{h:.2f}" '
            f'fill="{color_for_pct(matched)}" stroke="#0d1117" stroke-width="0.5" '
            f'data-name="{html.escape(u["name"], quote=True)}" '
            f'data-addr="{addr_str}" '
            f'data-size="{format_bytes(size)}" '
            f'data-matched="{matched:.2f}%" '
            f'data-fuzzy="{fuzzy:.2f}%" '
            f'data-status="{status}"/>'
        )
    return (
        f'<svg id="treemap-svg" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" '
        f'width="100%" preserveAspectRatio="xMidYMid meet" role="img" '
        f'aria-label="Unit treemap: each rect is one object file, sized by code bytes, colored by matched %, in address order.">'
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

  <p class="meta" style="margin-top:2rem"><a href="report.json">Raw report.json</a> · <a href="shield.json">Shield JSON</a></p>
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
