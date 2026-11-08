# terrain-findtriangle-native

Source: Codex worker c20_u141_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 3648 B.

c20_u141: OutsideEdges nested if chain -> for(outside=3,edge=0;outside>0;--outside,++edge), break on EdgeSide with literal zero, improves98.40625->99.90625 (640B). This structural loop recovers exact target edge FPRs and per-triangle zero reload, unlike prior standalone literal probes97.90625. Only count lwz/mtctr/cmpwi r0 instead ofr4 at80035FA8/FAC/FB0 remains. Search helper93.125; remaining-count and count-before-tri declarations invariant99.90625; cell-pointer and direct-memory-loop-bound forms98.59375. Retain H1. Added owned literal .sdata2 range806D2384..806D2388, postprocess exports generated0.0f as lbl_806D2384, data/EH/index100. TU remainsNM, source not linked, fallback full DOL SHA1 exact. DTK warns sdata2 expected8 at address4mod8; source .sdata2 alignment8, reference4: future native flip needs alignment review; no unauthorized SDATA2_ALIGN4 list change.

## c21_u98_20261108
Source: Codex worker c21_u98_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 640 B.

c21_u98: indexed outer traversal fixes final count home: TerrainTri *triangles=cell.tris; for(i=0;i<count;i++){ tri=&triangles[i]; ... } instead of tri++ walker gives99.90625->100%,640B/extab8/index12. Signed-long count and narrow TriangleCount inline accessor were invariant99.90625. Native flip with owned zero806D2384..2388 failed SHA due sdata2 alignment/SDA2 shifts; returning that4B range to shared auto pool uses existing literal postprocessor and restores full SHA1ea30f3b1. Final main.elf uses src object, no obj fallback, range80035ED4..80036154 independently byte-exact. Matching, native+1fn/+640B. No build hooks/SDATA2_ALIGN4 edits.
