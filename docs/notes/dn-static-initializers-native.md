# dn-static-initializers-native

Source: Codex worker cxc_u14_dn223_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 928 B.

Observed: GC/2.6 reproduces fn_80227FA4 exactly with angle factor literal 0.017453288659453392f; an extern factor load produces 97.70588% and adding a named factor local is byte-invariant. Existing postprocess_sdata2 maps the literal to lbl_806DB488. fn_80228D64 matches from sixteen explicit min/max helper calls in min-then-max order. fn_80228F80/98 match float ternaries and share an EH-free 48-byte contiguous target blob. All four text sections and static-initializer extab/extabindex/ctors compare 100%; full link/SHA-1 pending. Renderer fn_8022BFA8 best 84.24808% after three structural approaches; copied local Vec3c with inline empty destructor naturally emits DESTROYLOCAL but PC range and owned EH remain mismatched.

## c19_u115_20261107
Source: Codex worker c19_u115_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u115: fresh default objdiff baseline is 84.24808, not assignment report 85.44. UV struct-array representation does not prevent all-quad scalar hoisting. Full vertex value helper changes load order adversely. Vec3c copy initialization is byte-invariant vs assignment; return-by-value getter regresses. Snapshotting x/z once after GXBegin only for final overlay quad removes six repeated loads (24 bytes), gives 84.29528 /3700B with unchanged owned EH payload and index scores. Global caching shifts EH PC range and lowers object EH score to75, so rejected under nonregression contract. Existing external rodata base is already hoisted in r31; no ownership change attempted. No singleton null-to-null select occurs here. One-function TU remains NM; no native gain. Full fallback-linked DOL SHA1 exact.

## c20_u146_20261108
Source: Codex worker c20_u146_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 3648 B.

c20_u146: direct EnemyFaceDraw baseline84.29528 ->84.42810 (report85.62129) by reusing mesh/UV cursors and i/j across successive layers. Source3700B, EH78.57143/index66.66667 unchanged, weak dtor unchanged. Canonical GX position/color/texcoord helper boundaries77.24149; memcpy offset-copy84.55324 emits extra call and lowers EH75; POD-base Vec3c inheritance invariant. Rejected probes restored, header byte-identical. Persistent vertex/alternate bases, self/save partition, UV hoisting, integer local-copy and owned EH PC range remain. Pool base803DA710 already r31; offsets444..6EC belong to EnmyFaceEffect_nm1.cpp outside claim. No A/B, one-function NM, native gain0. Full coordinator fallback DOL SHA1ea30f3b1 exact.
