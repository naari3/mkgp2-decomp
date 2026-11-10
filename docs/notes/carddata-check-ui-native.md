# carddata-check-ui-native

Source: Codex worker c18_u144_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1912 B.

c18_u144: CardDataCheck_UI 8006DB90/1912B now fully native100%. Different structural combination resolves c15/c16 park: TU-local CardDataCheck_DrawItems(TestPage*) uses explicit pointer loop, declarations int i; int sel=self->sub+3; MenuItem*it; then for(it=CardDataCheck_UI_data_803FCBA0,i=0;it->text;++it,++i). Pointer-loop helper alone gives cursorr28/indexr30/selr27. Declaring i before it raises99.93724 and makes cursorr30; selection still parameter hasr27 while indexr28. Computing selection as the middle helper local fixes both to target selr28/indexr27. All1912B text,8B extab,12B index exact. Matching source input and actual main.elf8006DB90/1912 verified; full DOL SHA1 ea30f3b1 OK. No ranges/headers/bridges/layout flags changed.
