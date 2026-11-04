# ItemSelect refill/setup/update (anon_802386E0, cxb_r1, 2026-11-04)

Source: Codex worker cxb_r1_itemsel386_20261104 (gpt-6.1-sol/medium) + coordinator acceptance.

- fn_80238980 setup (1052B) native exact incl. 24B automatic DELETEPOINTER extab + extabindex: genuine `new TextManager`, per-TU ctor bridge to TexMgr_Init, `-Cpp_exceptions on` + lmw/stmw. In the four-text-manager loop declare `int i` before the explicit cursor (i=r29, cursor=r28); the reversed declaration leaves a pure r28/r29 swap at 99.79%.
- Honest NonMatching after 3 approaches: fn_802386E0 refill 91.79% (direct scalar 77.38%, explicit layout pointers/top-tested wait 90.15%), fn_80238D9C update 87.94%.
