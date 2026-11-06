# kart-controller-update

Source: Codex worker c16_u71_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u71: fresh KartController_Update 801E6ED4 74.69466 ->89.697205 with KCMatrix::multiply float out[16] replacing default-constructed KCMatrix out and out[i*4+j] indexing. Removes repeated redundant identity initialization and restores indexed stores/two-row unroll. Cached row + n++ gives62.828667; accumulating directly into out[n] gives65.300255. Remaining target element-index recurrence vs byte-offset strength reduction, operand FP homes, extra f29/frame+16, matrix temporary order and terrain calculation homes. Singleton remains NonMatching; source primary4600 vs target4716; no safe TU rescue cut. Full fallback DOL SHA-1 exact.
