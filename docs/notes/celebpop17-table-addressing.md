# CelebPop17 Update: remaining table addressing

The native Update scaffold currently matches 84.17391%; automatic EH matches.
Two structural approaches (typed aggregate fields and pointer-offset arrays)
produce the same remaining addressing differences.

The target keeps lbl_80328EB8 in r31 and accesses tables at offsets
0x74C through 0x8E4. symbols.txt declares that symbol as only 0x3FC bytes,
so the source overlay spans adjacent rodata objects. The target uses
addi plus indexed loads where the scaffold uses add plus displacement.

Inference: original TU-local pooled arrays may explain this shape. Testing
that requires checking ownership, splits and references of the adjacent
shared rodata, followed by compiler pooling and payload verification.
Do not restart register permutations or expand this function's data ownership
without those checks. The readable NonMatching source remains available.
