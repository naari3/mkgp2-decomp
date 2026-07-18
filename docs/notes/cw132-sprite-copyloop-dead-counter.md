# CW 1.3.2 unsolved idiom: dead row counter in sprite template copy loop (2026-07-19)

対象: SpriteAnimParamBlock_Reload (0x8023F05C, asm_fn 退避済), fn_8023F320, SpriteGroup_CreateOrInit の 3 fn が共有する template copy loop (10 rows x 5 shorts, -1 sentinel, ctr=10)。

観察: preheader で `li rC, 0`、loop 末尾 (src/dst cursor の addi 0xa の直後) に `addi rC, rC, 0x4`。rC に読み手なし (dead)。register は Reload/CreateOrInit で r4、fn_8023F320 で r5 (= arg slot 固定ではなく通常 web)。

probe 済み (全 negative, mwcc GC/1.3.2 -O4,p -Cpp_exceptions on):
- plain dead counter / static inline helper returned-counter / plain static helper returned-counter (inline 側) -> DCE で li/addi とも消える
- loop control 化 `count < 40` / `count != 40` / comma / `&&` 二重条件 / do-while / top-break `for(;;)` -> LFTR+ctr 変換で消えるか、cmpwi+branch が余分に残る (`if (count == 40) break;` は counter を残すが cmpwi+beq +2 命令)
- register volatile -> stack traffic が出る
- NULL-base `int*` の dead load (orphaned SR cursor 狙い) / param 再利用 -> 消える
- plain static helper の standalone emission 側では counter が残る (returned value ゆえ live)。inline 先では消える -> CW の post-inline DCE は生きている

仮説 (未検証): original は同 TU 内 helper の auto-inline で、trip-count と冗長になる第 2 exit test が loop 変換後に落とされ induction update だけ残る等の pass-ordering 産物。解ければ Reload の C 昇格 + fn_8023F320 / SpriteGroup_CreateOrInit の 2 sibling が unlock される。

関連: Reload にはもう 1 点、flush loop の i/cursor callee-saved swap (target i=r31/cursor=r30) がある。explicit pointer cursor を i より先に宣言する Phase 2f web-birth lever が未検証の候補。
