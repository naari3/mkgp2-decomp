# renderobj-itemstatemachine-native-draft

Source: Codex worker c9_L3_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

RenderObj_ItemStateMachine 800426C8 owns exactly text 800426C8..80044498, extab 80006290..80006430 and index 8001FF58..8001FF64. Nested ObjectTree_BlendOrCopy_Timed(output, Archive_GetRootJObj(secondary), Archive_GetRootJObj(primary), Archive_GetRootJObj(output), weight) reproduces the target right-to-left lookup order without extra r3->r0->saved copies. Initializing MatrixDirty result only after the possible assert avoids a saved-register boolean web. ScopedTimer automatic EH recreates the cleanup chain; weak destructor emits 164 extra text bytes and an extra 8/12-byte EH/index entry. Primary function is 7632 bytes and 99.155136% but remaining owned EH PC and FP scheduling differences prevent promotion. Current NonMatching source is not a native linking gain.
