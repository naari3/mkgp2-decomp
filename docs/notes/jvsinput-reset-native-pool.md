# jvsinput-reset-native-pool

Source: Codex worker c17_u17_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 156 B.

JvsInput_ResetCalibration 800396E4/156B: old19.49 external-pool probes rematerialized addresses (164B,56.974358%). Restoring actual TU-owned const char arrays for802E98E0..802E994C makes GC/1.3.2 automatically pool their section base in saved r31 before ClearBuffers, exactly matching all instructions and EH. Define original five strings with lengthsD/11/17/17/18; retain existing global symbols for cross-TU references. Own108B rodata via split; no filler, pragma or EH bridge. All owned sections100%, source object in main.elf at correct address/size, coordinator full DOL SHA1 exact. MechanismA; singleton needs no split.
