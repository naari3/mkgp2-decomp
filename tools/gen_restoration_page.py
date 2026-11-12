#!/usr/bin/env python3
"""Render the "Source restoration" page of the Pages site (restoration.html).

Numbers come from tools/restoration.py, the history from the progress-data
branch (history/GNLJ82_restoration.jsonl). Called by tools/gen_progress_page.py;
to look at the page alone:

    python3 tools/gen_restoration_page.py --out site/restoration.html [--history F]
"""
import argparse, collections, html, json, os, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import restoration

E = html.escape

# key, title, how to read one history row, unit, which way is progress, note
SERIES = [
    ('classes', 'Vtables emitted by the compiler', lambda r: _ratio(r, 'vt_real', 'vt_total'), '%', 'up',
     'of the vtables the original program has'),
    ('types', 'Type names with one definition', lambda r: _ratio_left(r, 'type_dup_names', 'type_names'), '%', 'up',
     'struct / class / union names in src/game and include/game'),
    ('data', 'Initialised data defined by its own unit', lambda r: _ratio(r, 'data_in_tu', 'data_total'), '%', 'up',
     'bytes of .rodata / .data / .sdata / .sdata2'),
    ('fnames', 'Functions with a name', lambda r: _ratio(r, 'fn_named', 'fn_total'), '%', 'up', 'symbols.txt'),
    ('dnames', 'Data symbols with a name', lambda r: _ratio(r, 'dsym_named', 'dsym_total'), '%', 'up', 'symbols.txt'),
    ('offsets', 'Accesses by byte offset', lambda r: r.get('offset_accesses'), '', 'down',
     'reads and writes like *(float *)(p + 0x1C) instead of a member'),
    ('unk', 'Members without a name', lambda r: r.get('unk_members'), '', 'down', 'unk_10, field_0x10 and the like'),
    ('units', 'Source units named by address', lambda r: r.get('units_addr_named'), '', 'down',
     'files like anon_80209FA4.cpp; data-only units not counted'),
]


def _ratio(r, a, b):
    return 100.0 * r[a] / r[b] if r.get(b) and a in r else None


def _ratio_left(r, a, b):
    return 100.0 * (r[b] - r[a]) / r[b] if r.get(b) and a in r else None


def daily(rows):
    """Last row of each UTC day, oldest first."""
    by = {}
    for r in sorted(rows, key=lambda r: restoration._utc(r['ts'])):
        by[restoration._utc(r['ts']).date().isoformat()] = r
    return [dict(v, day=k) for k, v in sorted(by.items())]


def fmt(n):
    return f'{n:,}'


def meter(a, b):
    p = 100.0 * a / b if b else 0.0
    return ('<div class="meter" role="img" aria-label="%.1f%%"><div class="meter-fill" style="width:%.2f%%"></div></div>' % (p, p))


def tile(label, value, sub, ratio=None):
    return ('<div class="card"><div class="label">%s</div><div class="value">%s</div>%s<div class="sub">%s</div></div>'
            % (E(label), E(value), meter(*ratio) if ratio else '', E(sub)))


def tiles(s):
    g = s.get
    out = []
    if 'vt_total' in s:
        out.append(tile('C++ classes restored', '%.1f%%' % (100.0 * s['vt_real'] / s['vt_total']),
                        '%s of %s vtables come from a class definition; %s still written out as data'
                        % (fmt(s['vt_real']), fmt(s['vt_total']), fmt(s['vt_total'] - s['vt_real'])), (s['vt_real'], s['vt_total'])))
    if 'type_names' in s:
        one = s['type_names'] - s['type_dup_names']
        out.append(tile('Types with one definition', '%.1f%%' % (100.0 * one / s['type_names']),
                        '%s of %s names; %s extra copies in other files'
                        % (fmt(one), fmt(s['type_names']), fmt(s['type_extra_copies'])), (one, s['type_names'])))
    if 'data_total' in s:
        out.append(tile('Data owned by its unit', '%.1f%%' % (100.0 * s['data_in_tu'] / s['data_total']),
                        '%s of %s bytes; the rest sits in data-only units'
                        % (fmt(s['data_in_tu']), fmt(s['data_total'])), (s['data_in_tu'], s['data_total'])))
    if 'fn_total' in s:
        out.append(tile('Functions named', '%.1f%%' % (100.0 * s['fn_named'] / s['fn_total']),
                        '%s of %s' % (fmt(s['fn_named']), fmt(s['fn_total'])), (s['fn_named'], s['fn_total'])))
        out.append(tile('Data symbols named', '%.1f%%' % (100.0 * s['dsym_named'] / s['dsym_total']),
                        '%s of %s' % (fmt(s['dsym_named']), fmt(s['dsym_total'])), (s['dsym_named'], s['dsym_total'])))
    if 'offset_accesses' in s:
        out.append(tile('Byte-offset accesses left', fmt(s['offset_accesses']), 'goal 0: every access goes through a member'))
    if 'unk_members' in s:
        out.append(tile('Unnamed members left', fmt(s['unk_members']), 'unk_10, field_0x10 and the like'))
    if 'units' in s:
        out.append(tile('Units named by address', fmt(s['units_addr_named']),
                        'of %s source units; plus %s data-only units' % (fmt(s['units']), fmt(g('units_data_only', 0)))))
    return '\n'.join(out)


STATE_LABEL = {'named': 'Class, original name', 'real': 'Class, placeholder name', 'hand': 'Table written by hand'}


def classes_section(c, repo_url, commit):
    if 'error' in c:
        return '<p class="meta">Class list not available: %s</p>' % E(c['error'])
    rows = c['rows']
    fam = collections.defaultdict(lambda: [0, 0])
    for r in rows:
        fam[r['family']][1] += 1
        fam[r['family']][0] += r['state'] != 'hand'
    big = sorted(((k, v) for k, v in fam.items() if v[1] >= 4), key=lambda kv: (-kv[1][1], kv[0]))
    rest = [v for k, v in fam.items() if v[1] < 4]
    fam_rows = ''.join(
        '<div class="fam"><div class="fam-name"><code>%s</code></div>%s<div class="fam-n">%d / %d</div></div>'
        % (E(k), meter(v[0], v[1]), v[0], v[1]) for k, v in big)
    if rest:
        a, b = sum(v[0] for v in rest), sum(v[1] for v in rest)
        fam_rows += ('<div class="fam"><div class="fam-name">%d smaller families</div>%s<div class="fam-n">%d / %d</div></div>'
                     % (len(rest), meter(a, b), a, b))
    ref = commit or 'main'
    data = [[r['class'], ', '.join(r['bases']), r['state'], r['unit'], r['symbol'], r['slots']] for r in rows]
    n = collections.Counter(r['state'] for r in rows)
    chips = ''.join('<button type="button" class="chip" data-state="%s"><span class="dot dot-%s"></span>%s <b>%d</b></button>'
                    % (k, k, E(STATE_LABEL[k]), n[k]) for k in ('named', 'real', 'hand'))
    return '''
  <p class="meta">The game was built with RTTI, so the binary still names every class that has virtual functions
  and its bases: %d vtables, %d class names. A class counts as restored when the compiler emits its vtable from a
  <code>class</code> definition; until then the table is an array of function pointers that somebody typed in.
  List and recipe: <a href="%s/blob/%s/docs/notes/rtti_classes.md">docs/notes/rtti_classes.md</a>.</p>
  <h3>By base class</h3>
  <div class="fams">%s</div>
  <h3>Every vtable</h3>
  <div class="controls"><input type="search" id="cls-q" placeholder="Filter by class, base, unit or symbol" aria-label="Filter classes">
    <div class="chips" id="cls-chips">%s</div><span class="meta" id="cls-count"></span></div>
  <div class="table-wrap"><table id="cls-table"><thead><tr><th>Class</th><th>Bases</th><th>State</th><th>Unit holding the table</th>
    <th>Symbol today</th><th class="num">Slots</th></tr></thead><tbody></tbody></table></div>
  <script type="application/json" id="cls-data">%s</script>
''' % (c['tables'], c['class_names'], E(repo_url), E(ref), fam_rows, chips, json.dumps(data).replace('</', '<\\/'))


def details_table(title, head, rows):
    trs = ''.join('<tr>%s</tr>' % ''.join('<td%s>%s</td>' % (' class="num"' if isinstance(c, int) else '', fmt(c) if isinstance(c, int) else c)
                                          for c in r) for r in rows)
    ths = ''.join('<th%s>%s</th>' % (' class="num"' if h.startswith('#') else '', E(h.lstrip('#'))) for h in head)
    return '<details><summary>%s</summary><div class="table-wrap"><table><thead><tr>%s</tr></thead><tbody>%s</tbody></table></div></details>' % (
        E(title), ths, trs)


def render(d, hist_rows, version='GNLJ82', commit=None, repo_url='https://github.com/naari3/mkgp2-decomp', extra_html=''):
    s = restoration.summary(d)
    days = daily(hist_rows)
    if commit and not any(r.get('sha') == commit for r in hist_rows):
        from datetime import datetime, timezone
        days = [x for x in days] + [dict(s, sha=commit, day=datetime.now(timezone.utc).date().isoformat())]
        days = list({x['day']: x for x in days}.values())
    # Chart the current stretch of work only: start after the last pause longer
    # than 30 days, so that months without a commit do not flatten the lines.
    from datetime import date
    start = 0
    for i in range(1, len(days)):
        if (date.fromisoformat(days[i]['day']) - date.fromisoformat(days[i - 1]['day'])).days > 30:
            start = i
    days = days[start:]
    charts = []
    for key, title, get, unit, good, note in SERIES:
        pts = [[x['day'], round(v, 3)] for x in days for v in [get(x)] if v is not None]
        if pts:
            charts.append({'key': key, 'title': title, 'unit': unit, 'good': good, 'note': note, 'pts': pts})
    chart_html = ''.join(
        '<div class="chart-card"><div class="chart-title">%s</div><div class="chart-now" id="now-%s"></div>'
        '<div class="chart-wrap" id="chart-%s"></div><div class="meta chart-note">%s</div></div>'
        % (E(c['title']), c['key'], c['key'], E(c['note'])) for c in charts)
    if len(days) < 2:
        chart_html = '<p class="meta">The history starts with this commit; the charts appear once there are two days of it.</p>'

    t = d.get('types', {})
    types_extra = ''
    if 'top_dups' in t:
        types_extra = details_table('Type names with the most definitions (%d names have more than one)' % t['dup_names'],
                                    ['Name', '#Files defining it'], [['<code>%s</code>' % E(n), k] for n, k in t['top_dups']])
    dt = d.get('data', {})
    data_extra = ''
    if 'sections' in dt:
        data_extra = details_table('Initialised data by section (bytes)',
                                   ['Section', '#In the unit that uses it', '#Data-only unit, typed', '#Data-only unit, layout unknown', '#No C definition'],
                                   [['<code>%s</code>' % E(k), v['in_tu'], v['typed'], v['unk'], v['no_c']] for k, v in dt['sections'].items()])
    of = d.get('offsets', {})
    off_extra = ''
    if 'top_files' in of:
        ref = commit or 'main'
        off_extra = details_table('Files with the most byte-offset accesses (%s through per-file macros, %s written out, %s files)'
                                  % (fmt(of['through_macros']), fmt(of['written_out']), fmt(of['files'])),
                                  ['File', '#Accesses'],
                                  [['<a href="%s/blob/%s/%s"><code>%s</code></a>' % (E(repo_url), E(ref), E(f), E(f)), k] for f, k in of['top_files']])
    a = d.get('asm', {})
    asm_line = ''
    if 'asm_functions' in a:
        asm_line = ('<p class="meta">%d game functions are still inline asm in the default build; %d of them have an equivalent C body '
                    'under <code>NON_MATCHING</code>.</p>' % (a['asm_functions'], a['with_c_body']))

    commit_part = ' · commit <code>%s</code>' % E(commit) if commit else ''
    return PAGE.format(
        version=E(version), commit_part=commit_part, tiles=tiles(s), charts=chart_html,
        chart_data=json.dumps(charts).replace('</', '<\\/'),
        classes=classes_section(d.get('classes', {'error': 'missing'}), repo_url, commit),
        types_extra=types_extra, data_extra=data_extra, off_extra=off_extra, asm_line=asm_line,
        state_labels=json.dumps(STATE_LABEL), repo=E(repo_url), extra=extra_html)


PAGE = '''<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Mario Kart Arcade GP2 — source restoration</title>
<style>
  :root {{ color-scheme: dark; --bg:#0d1117; --panel:#161b22; --line:#30363d; --grid:#21262d; --ink:#f0f6fc; --text:#c9d1d9;
          --muted:#8b949e; --accent:#58a6ff; --named:#3fb950; --real:#58a6ff; --hand:#6e7681; }}
  body {{ margin:0; padding:2rem 1.5rem; background:var(--bg); color:var(--text);
         font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",system-ui,sans-serif; line-height:1.5; }}
  main {{ max-width:1100px; margin:0 auto; }}
  h1,h2,h3 {{ color:var(--ink); }}
  h1 {{ font-size:1.75rem; margin:0 0 0.5rem; }}
  h2 {{ font-size:1.2rem; margin:2.2rem 0 1rem; border-bottom:1px solid var(--line); padding-bottom:0.3rem; }}
  h3 {{ font-size:0.95rem; margin:1.4rem 0 0.6rem; }}
  a {{ color:var(--accent); }}
  code {{ font-family:ui-monospace,SFMono-Regular,Menlo,monospace; font-size:0.9em; }}
  .meta {{ color:var(--muted); font-size:0.9rem; }}
  .nav {{ display:flex; gap:0.4rem; margin:0.8rem 0 0; flex-wrap:wrap; }}
  .nav a {{ padding:0.3rem 0.8rem; border:1px solid var(--line); border-radius:6px; text-decoration:none; color:var(--muted); font-size:0.9rem; }}
  .nav a.here {{ background:var(--grid); color:var(--ink); border-color:var(--muted); }}
  .summary {{ display:grid; gap:0.75rem; grid-template-columns:repeat(auto-fit,minmax(230px,1fr)); margin-top:1rem; }}
  .card {{ background:var(--panel); border:1px solid var(--line); border-radius:6px; padding:1rem; }}
  .card .label {{ font-size:0.85rem; color:var(--muted); text-transform:uppercase; letter-spacing:0.04em; }}
  .card .value {{ font-size:1.6rem; font-weight:600; color:var(--ink); margin-top:0.25rem; font-variant-numeric:tabular-nums; }}
  .card .sub {{ font-size:0.85rem; color:var(--muted); margin-top:0.35rem; }}
  .meter {{ height:6px; background:var(--grid); border-radius:3px; overflow:hidden; margin-top:0.5rem; }}
  .meter-fill {{ height:100%; background:var(--accent); border-radius:3px; }}
  .charts {{ display:grid; gap:0.75rem; grid-template-columns:repeat(auto-fit,minmax(320px,1fr)); }}
  .chart-card {{ background:var(--panel); border:1px solid var(--line); border-radius:6px; padding:0.9rem 1rem; min-width:0; }}
  .chart-title {{ color:var(--ink); font-weight:600; font-size:0.95rem; }}
  .chart-now {{ font-size:0.85rem; color:var(--muted); font-variant-numeric:tabular-nums; min-height:1.3em; }}
  .chart-now b {{ color:var(--ink); font-size:1.15rem; margin-right:0.4rem; }}
  .chart-wrap {{ position:relative; margin-top:0.3rem; }}
  .chart-wrap svg {{ display:block; width:100%; height:auto; cursor:crosshair; touch-action:pan-y; }}
  .chart-wrap svg text {{ font-family:inherit; font-size:11px; fill:var(--muted); }}
  .chart-note {{ font-size:0.78rem; margin-top:0.2rem; }}
  .tip {{ position:absolute; pointer-events:none; display:none; background:var(--grid); color:var(--ink); border:1px solid var(--line);
         border-radius:4px; padding:0.35rem 0.6rem; font-size:0.8rem; white-space:nowrap; z-index:5; box-shadow:0 4px 12px rgba(0,0,0,.5); }}
  .tip span {{ color:var(--muted); margin-right:0.5rem; }}
  .fams {{ display:grid; gap:0.35rem 2rem; grid-template-columns:repeat(auto-fit,minmax(380px,1fr)); }}
  .fam {{ display:grid; grid-template-columns:minmax(0,190px) 1fr 4.5rem; gap:0.75rem; align-items:center; font-size:0.85rem; }}
  .fam .meter {{ margin-top:0; }}
  .fam-name {{ overflow:hidden; text-overflow:ellipsis; white-space:nowrap; }}
  .fam-n {{ text-align:right; color:var(--muted); font-variant-numeric:tabular-nums; }}
  .controls {{ display:flex; gap:0.75rem; align-items:center; flex-wrap:wrap; margin-bottom:0.5rem; }}
  .controls input {{ flex:1 1 240px; max-width:380px; background:var(--bg); color:var(--ink); border:1px solid var(--line);
                    border-radius:4px; padding:0.35rem 0.6rem; font:inherit; font-size:0.85rem; }}
  .chips {{ display:flex; gap:0.35rem; flex-wrap:wrap; }}
  .chip {{ background:transparent; border:1px solid var(--line); color:var(--text); border-radius:999px; padding:0.2rem 0.7rem;
          font:inherit; font-size:0.8rem; cursor:pointer; }}
  .chip:hover {{ border-color:var(--muted); }}
  .chip.active {{ background:var(--grid); border-color:var(--accent); color:var(--ink); }}
  .dot {{ display:inline-block; width:9px; height:9px; border-radius:50%; margin-right:0.35rem; }}
  .dot-named {{ background:var(--named); }} .dot-real {{ background:var(--real); }} .dot-hand {{ background:var(--hand); }}
  .table-wrap {{ max-height:620px; overflow:auto; border:1px solid var(--line); border-radius:6px; }}
  table {{ width:100%; border-collapse:collapse; font-size:0.85rem; }}
  th,td {{ padding:0.4rem 0.6rem; text-align:left; border-bottom:1px solid var(--grid); vertical-align:top; }}
  thead th {{ position:sticky; top:0; background:var(--panel); color:var(--muted); font-weight:500; white-space:nowrap; }}
  td.num,th.num {{ text-align:right; font-variant-numeric:tabular-nums; }}
  td.mono {{ font-family:ui-monospace,SFMono-Regular,Menlo,monospace; font-size:0.8rem; word-break:break-all; }}
  td.dim {{ color:var(--muted); }}
  td.nw {{ white-space:nowrap; }}
  tr:hover td {{ background:var(--panel); }}
  details {{ margin-top:0.8rem; }}
  summary {{ cursor:pointer; color:var(--muted); margin-bottom:0.5rem; }}
  @media (max-width:600px) {{ body {{ padding:1rem 1rem; }} h1 {{ font-size:1.4rem; }}
    .fams {{ grid-template-columns:1fr; }} .fam {{ grid-template-columns:minmax(0,130px) 1fr 4rem; }} }}
</style>
</head>
<body>
<main>
  <h1>Mario Kart Arcade GP2 — source restoration</h1>
  <p class="meta">Version <code>{version}</code> · measured from the tracked sources by <code>tools/restoration.py</code>{commit_part}</p>
  <nav class="nav"><a href="index.html">Matching</a><a class="here" href="restoration.html">Source restoration</a></nav>

  <p>Matching says the compiled bytes are the original ones. This page follows the other half of the work: getting the
  sources back to the form the game was written in. Classes that are classes, one definition per type, data that has a
  type and lives in the file that uses it, names instead of addresses.</p>

  <h2>Now</h2>
  <div class="summary">
{tiles}
  </div>

  <h2>Over time</h2>
  <div class="charts">{charts}</div>

  <h2>C++ classes</h2>
{classes}

  <h2>Types</h2>
  <p class="meta">A struct that several files each define for themselves is a struct nobody can change safely. The goal is one
  definition per name, shared through a header, with every member named.</p>
  {types_extra}

  <h2>Data</h2>
  <p class="meta">Data starts out as bytes linked from the original binary. It is restored when the unit that uses it
  defines it with a real type; data-only units under <code>src/game/autodata</code> are the step in between.</p>
  {data_extra}

  <h2>Code shape</h2>
  <p class="meta">An access by byte offset is a member whose struct is not written down yet.</p>
  {off_extra}
  {asm_line}

<div style="overflow-x:auto">
{extra}
</div>
  <p class="meta" style="margin-top:2rem"><a href="restoration.json">restoration.json</a> ·
  <a href="restoration_history.jsonl">restoration_history.jsonl</a> ·
  <a href="{repo}/blob/main/docs/notes/restoration.md">how each number is counted</a></p>
</main>
<script type="application/json" id="series-json">{chart_data}</script>
<script>
(function () {{
  var NS = 'http://www.w3.org/2000/svg';
  function el(n, a, t) {{ var e = document.createElementNS(NS, n); for (var k in a) e.setAttribute(k, a[k]); if (t != null) e.textContent = t; return e; }}
  function fmtv(v, unit) {{ return unit === '%' ? v.toFixed(1) + '%' : Math.round(v).toLocaleString('en-US'); }}
  function dnum(s) {{ return Date.parse(s + 'T00:00:00Z') / 864e5; }}
  var charts = JSON.parse(document.getElementById("series-json").textContent);
  charts.forEach(function (c) {{
    var host = document.getElementById('chart-' + c.key), now = document.getElementById('now-' + c.key);
    if (!host) return;
    var pts = c.pts, last = pts[pts.length - 1], first = pts[0];
    var delta = last[1] - first[1], sign = delta > 0 ? '+' : delta < 0 ? '\\u2212' : '\\u00b1';
    now.innerHTML = '<b>' + fmtv(last[1], c.unit) + '</b>' + sign + (c.unit === '%' ? Math.abs(delta).toFixed(1) + ' pt' : Math.round(Math.abs(delta)).toLocaleString('en-US')) +
      ' since ' + first[0] + (c.good === 'down' ? ' · lower is better' : '');
    if (pts.length < 2) return;
    var W = 460, H = 150, ml = 46, mr = 10, mt = 8, mb = 22, iw = W - ml - mr, ih = H - mt - mb;
    var xs = pts.map(function (p) {{ return dnum(p[0]); }}), ys = pts.map(function (p) {{ return p[1]; }});
    var x0 = xs[0], x1 = xs[xs.length - 1], lo = Math.min.apply(null, ys), hi = Math.max.apply(null, ys);
    if (hi === lo) {{ hi += 1; lo -= 1; }}
    var pad = (hi - lo) * 0.08; lo -= pad; hi += pad;
    if (c.unit === '%') {{ lo = Math.max(0, lo); hi = Math.min(100, hi); }} else {{ lo = Math.max(0, lo); }}
    function X(v) {{ return ml + (x1 === x0 ? iw / 2 : (v - x0) / (x1 - x0) * iw); }}
    function Y(v) {{ return mt + (1 - (v - lo) / (hi - lo)) * ih; }}
    var svg = el('svg', {{ viewBox: '0 0 ' + W + ' ' + H, role: 'img', 'aria-label': c.title + ' over time' }});
    [lo, (lo + hi) / 2, hi].forEach(function (v) {{
      svg.appendChild(el('line', {{ x1: ml, x2: W - mr, y1: Y(v), y2: Y(v), stroke: '#21262d', 'stroke-width': 1 }}));
      svg.appendChild(el('text', {{ x: ml - 6, y: Y(v) + 4, 'text-anchor': 'end' }}, fmtv(v, c.unit)));
    }});
    svg.appendChild(el('text', {{ x: ml, y: H - 5, 'text-anchor': 'start' }}, first[0]));
    svg.appendChild(el('text', {{ x: W - mr, y: H - 5, 'text-anchor': 'end' }}, last[0]));
    var dpath = pts.map(function (p, i) {{ return (i ? 'L' : 'M') + X(xs[i]).toFixed(1) + ' ' + Y(p[1]).toFixed(1); }}).join(' ');
    svg.appendChild(el('path', {{ d: dpath, fill: 'none', stroke: '#58a6ff', 'stroke-width': 2, 'stroke-linejoin': 'round', 'stroke-linecap': 'round' }}));
    svg.appendChild(el('circle', {{ cx: X(x1), cy: Y(last[1]), r: 4, fill: '#58a6ff', stroke: '#161b22', 'stroke-width': 2 }}));
    var cross = el('line', {{ y1: mt, y2: mt + ih, stroke: '#8b949e', 'stroke-width': 1, visibility: 'hidden' }});
    var dot = el('circle', {{ r: 4, fill: '#58a6ff', stroke: '#161b22', 'stroke-width': 2, visibility: 'hidden' }});
    svg.appendChild(cross); svg.appendChild(dot);
    host.appendChild(svg);
    var tip = document.createElement('div'); tip.className = 'tip'; host.appendChild(tip);
    function move(ev) {{
      var r = svg.getBoundingClientRect(), px = (ev.clientX - r.left) / r.width * W, best = 0, bd = 1e9;
      xs.forEach(function (v, i) {{ var d = Math.abs(X(v) - px); if (d < bd) {{ bd = d; best = i; }} }});
      var cx = X(xs[best]), cy = Y(pts[best][1]);
      cross.setAttribute('x1', cx); cross.setAttribute('x2', cx); cross.setAttribute('visibility', 'visible');
      dot.setAttribute('cx', cx); dot.setAttribute('cy', cy); dot.setAttribute('visibility', 'visible');
      tip.innerHTML = '<span>' + pts[best][0] + '</span><b>' + fmtv(pts[best][1], c.unit) + '</b>';
      tip.style.display = 'block';
      var left = cx / W * r.width + 10; if (left + tip.offsetWidth > r.width) left = cx / W * r.width - tip.offsetWidth - 10;
      tip.style.left = left + 'px'; tip.style.top = Math.max(0, cy / H * r.height - 34) + 'px';
    }}
    function leave() {{ cross.setAttribute('visibility', 'hidden'); dot.setAttribute('visibility', 'hidden'); tip.style.display = 'none'; }}
    svg.addEventListener('pointermove', move); svg.addEventListener('pointerdown', move); svg.addEventListener('pointerleave', leave);
  }});

  var dataEl = document.getElementById('cls-data');
  if (!dataEl) return;
  var rows = JSON.parse(dataEl.textContent), labels = {state_labels};
  var tbody = document.querySelector('#cls-table tbody'), q = document.getElementById('cls-q'), count = document.getElementById('cls-count');
  var state = null;
  function esc(s) {{ return String(s).replace(/[&<>"]/g, function (c) {{ return {{ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }}[c]; }}); }}
  function draw() {{
    var needle = q.value.trim().toLowerCase(), out = [], n = 0;
    rows.forEach(function (r) {{
      if (state && r[2] !== state) return;
      if (needle && (r[0] + ' ' + r[1] + ' ' + r[3] + ' ' + r[4]).toLowerCase().indexOf(needle) < 0) return;
      n++;
      out.push('<tr><td class="mono">' + esc(r[0]) + '</td><td class="mono dim">' + esc(r[1]) + '</td><td class="nw"><span class="dot dot-' + r[2] + '"></span>' +
        esc(labels[r[2]]) + '</td><td class="mono dim">' + esc(r[3]) + '</td><td class="mono dim">' + esc(r[4]) + '</td><td class="num">' + r[5] + '</td></tr>');
    }});
    tbody.innerHTML = out.join('');
    count.textContent = n + ' of ' + rows.length;
  }}
  q.addEventListener('input', draw);
  document.getElementById('cls-chips').addEventListener('click', function (ev) {{
    var b = ev.target.closest('.chip'); if (!b) return;
    state = state === b.dataset.state ? null : b.dataset.state;
    Array.prototype.forEach.call(this.children, function (x) {{ x.classList.toggle('active', x.dataset.state === state); }});
    draw();
  }});
  draw();
}})();
</script>
</body>
</html>
'''


def write(out_dir, history=None, version='GNLJ82', commit=None, repo_url='https://github.com/naari3/mkgp2-decomp', extra_html=''):
    """Write restoration.html, restoration.json and the history copy; returns the summary."""
    d = restoration.collect()
    rows = restoration.load_history(history) if history else []
    os.makedirs(out_dir, exist_ok=True)
    open(os.path.join(out_dir, 'restoration.html'), 'w', encoding='utf-8').write(render(d, rows, version, commit, repo_url, extra_html))
    json.dump(d, open(os.path.join(out_dir, 'restoration.json'), 'w', encoding='utf-8'), indent=1)
    with open(os.path.join(out_dir, 'restoration_history.jsonl'), 'w', encoding='utf-8') as f:
        for r in rows:
            f.write(json.dumps(r, sort_keys=True) + '\n')
    return restoration.summary(d)


def index_section(s):
    """Short block for index.html that points at the restoration page."""
    cards = []
    if 'vt_total' in s:
        cards.append(('C++ classes restored', '%.1f%%' % (100.0 * s['vt_real'] / s['vt_total']),
                      '%s / %s vtables from a class definition' % (fmt(s['vt_real']), fmt(s['vt_total']))))
    if 'type_names' in s:
        one = s['type_names'] - s['type_dup_names']
        cards.append(('Types with one definition', '%.1f%%' % (100.0 * one / s['type_names']), '%s / %s names' % (fmt(one), fmt(s['type_names']))))
    if 'data_total' in s:
        cards.append(('Data owned by its unit', '%.1f%%' % (100.0 * s['data_in_tu'] / s['data_total']), 'of initialised data bytes'))
    if 'fn_total' in s:
        cards.append(('Functions named', '%.1f%%' % (100.0 * s['fn_named'] / s['fn_total']), '%s / %s' % (fmt(s['fn_named']), fmt(s['fn_total']))))
    body = ''.join('<div class="card"><div class="label">%s</div><div class="value">%s</div><div class="sub">%s</div></div>'
                   % tuple(E(x) for x in c) for c in cards)
    return ('  <h2>Source restoration</h2>\n'
            '  <p class="meta">Matched bytes are one half; the other is getting the sources back to the form they were written in. '
            '<a href="restoration.html">Full page: classes, types, data, names, history</a>.</p>\n'
            '  <div class="summary">%s</div>\n' % body)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--out-dir', default='site'); ap.add_argument('--history', default=None)
    ap.add_argument('--commit', default=None); ap.add_argument('--version', default='GNLJ82')
    a = ap.parse_args()
    write(a.out_dir, a.history, a.version, a.commit)
    print('wrote %s' % os.path.join(a.out_dir, 'restoration.html'))


if __name__ == '__main__':
    main()
