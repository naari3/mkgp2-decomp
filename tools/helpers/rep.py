import json,sys
r=json.load(open('build/GNLJ82/report.json'))
for u in r['units']:
    if sys.argv[1] in u['name']:
        print(u['name'],u['measures'].get('fuzzy_match_percent'))
        for f in u.get('functions',[]): print(' ',f['name'],f['size'],round(f.get('fuzzy_match_percent',0),2))
