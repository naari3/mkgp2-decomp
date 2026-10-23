
## CoinEvent sound callbacks (2026-10-23)
ResultSE (80049F60,124B) and AlternatingSE (80049FDC,112B) matched native C++ plus automatic EH on first trial. Result uses nested mode==12/result==0 branches and sets bytes +109=1/+FD=0 after SoundObj_PlaySE. Alternating lazy state requires signed-char initialization flag and explicitly sized int[2] extern lookup to retain SDA21 access. Narrow context view follows target ASM; sibling CoinEvent_PlaySE_0x13 remains unchanged. Direct .text/extab/extabindex all 100%, actual native main.elf input and complete DOL SHA-1 verified.
