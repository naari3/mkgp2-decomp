# switch-test-near-miss

Source: Codex worker c18_u156_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u156: SwitchTest_Page 800715AC baseline 99.86487,1332B, EH8/index12 exact. Raw axes use volatile r7/r4/r5 versus target r30/r28/r27 before division. After phase==2 dispatch, reusing phase parameter for acceleration raw/clamped delta fixes r30 on subf., li zero and srawi, raising99.90991 without any instruction/size/EH change. Reusing int coin for steering gives no gain and was removed. Inline mutating-ref/input-output-ref/draw helper variants rematerialize divisions at use and regress94.57357; long raw locals invariant; returning helper named quotient changes coin/menu homes and regresses99.6997. Remaining six operand differences are steering r4 vs r28 and brake r5 vs r27. Keep NonMatching; singleton has no mechanism B split; final fallback DOL SHA1 exact.
