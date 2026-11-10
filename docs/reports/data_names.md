# Unnamed data symbols (tools/data_names.py census)

Regenerate with `python3 tools/data_names.py census` after a build.

| Item | Count |
|---|---|
| data objects in symbols.txt | 32323 |
| still `lbl_` | 24609 |
| `apply` would name now | 0 |

| Outcome for each `lbl_` object | Count |
|---|---|
| string | 13006 |
| section .sdata2 | 8518 |
| no single named user | 2678 |
| no reference | 307 |
| compiler literal | 72 |
| section .sbss2 | 28 |
