# dn-static-initializers-native

Source: Codex worker cxc_u14_dn223_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 928 B.

Observed: GC/2.6 reproduces fn_80227FA4 exactly with angle factor literal 0.017453288659453392f; an extern factor load produces 97.70588% and adding a named factor local is byte-invariant. Existing postprocess_sdata2 maps the literal to lbl_806DB488. fn_80228D64 matches from sixteen explicit min/max helper calls in min-then-max order. fn_80228F80/98 match float ternaries and share an EH-free 48-byte contiguous target blob. All four text sections and static-initializer extab/extabindex/ctors compare 100%; full link/SHA-1 pending. Renderer fn_8022BFA8 best 84.24808% after three structural approaches; copied local Vec3c with inline empty destructor naturally emits DESTROYLOCAL but PC range and owned EH remain mismatched.

## c19_u115_20261107
Source: Codex worker c19_u115_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c19_u115: fresh default objdiff baseline is 84.24808, not assignment report 85.44. UV struct-array representation does not prevent all-quad scalar hoisting. Full vertex value helper changes load order adversely. Vec3c copy initialization is byte-invariant vs assignment; return-by-value getter regresses. Snapshotting x/z once after GXBegin only for final overlay quad removes six repeated loads (24 bytes), gives 84.29528 /3700B with unchanged owned EH payload and index scores. Global caching shifts EH PC range and lowers object EH score to75, so rejected under nonregression contract. Existing external rodata base is already hoisted in r31; no ownership change attempted. No singleton null-to-null select occurs here. One-function TU remains NM; no native gain. Full fallback-linked DOL SHA1 exact.

## c20_u146_20261108
Source: Codex worker c20_u146_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 3648 B.

c20_u146: direct EnemyFaceDraw baseline84.29528 ->84.42810 (report85.62129) by reusing mesh/UV cursors and i/j across successive layers. Source3700B, EH78.57143/index66.66667 unchanged, weak dtor unchanged. Canonical GX position/color/texcoord helper boundaries77.24149; memcpy offset-copy84.55324 emits extra call and lowers EH75; POD-base Vec3c inheritance invariant. Rejected probes restored, header byte-identical. Persistent vertex/alternate bases, self/save partition, UV hoisting, integer local-copy and owned EH PC range remain. Pool base803DA710 already r31; offsets444..6EC belong to EnmyFaceEffect_nm1.cpp outside claim. No A/B, one-function NM, native gain0. Full coordinator fallback DOL SHA1ea30f3b1 exact.

## c21_u130_20261108
Source: Codex worker c21_u130_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_u130: EnemyFaceDraw direct84.42810->86.026344/report87.239296, EH78.57143->82.14286/index66.66667. Ordered explicit z/y/x projection/displacement stores fix chained-assignment reversal. Vec3c union {FaceDrawVec value; float components[3];} preserves whole-object copy, yielding target exact lwz/stw+reload/FP sequence for local offset without memcpy/casts. Explicit main vertexBase/alternateBase and UV base initialized after face lookup recover frame2C0/savedr17-r31 and verticesr30/altr28/UVr29. Selfr27 vs26, UV hoisting, repeated displacement loads, body3724vs3644 and PC B54:B80vsB0C:B38 remain. IMPORTANT EnemyFaceDraw.h is shared by matched fn801E68B4; preserve it and use new EnemyFaceDraw_private.h. Initial request caught this dependency; final full all_source+DOL SHA1ea30f3b1 exact, otherconsumer100%. Onefn NM/noA-B/no native gain; neighbour pool remains out of claim.

## c21_p60_20261108
Source: Codex worker c21_p60_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c21_p60: EnemyFaceDraw direct86.026344->86.15038/report87.239296->87.363335, body3724->3652. Per-vertex FIFO helpers and one displacement x/z snapshot after GXBegin remove72B; owned24B EH+relocation exact with PC B0C:B38. Whole extab85.71429/index66.66667 include extra weak dtor; primary index still lengthE44vsE3C. Pair-only UV helper85.98792 and fully unrolled vertex loops86.026344 rejected. Pool OTHER+MIXED: base803DA710 prefix..AB54 unowned, EnmyFaceEffect_nm1 ownsAB54..AE88. Coordinator merge must also coordinate intermediate fn8022CDE4 and EnmyFaceEffect for contiguous text. No config/split/header edits; onefn NM, nativegain0. Full fallback DOL SHA1ea30f3b1 exact.

## c23_u68_20261109
Source: Codex worker c23_u68_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c23_u68: EnemyFaceDraw direct86.15038->86.82437/report87.363335->88.03732,3652B/EH85.71429/index66.66667 unchanged. Per early layer initialize draw=vertices; out=draw before transform loops and retain draw through texture lookup into rendering. Whole-function persistent base84.780464, canonical FIFO layout invariant86.15038, per-vertex by-value UV86.506035 rejected. Current pool prefix803DA710..803DAB54 unowned, nm1 owns803DAB54..803DAE88. Contiguous merge requires EnemyFaceDraw + fn8022CDE4 + EnmyFaceEffect + EnmyFaceEffect_nm1 (textBFA8..300C8), coordinator-only. Primary EH payload/relocation/PCB0C:B38 exact, lengthE44vsE3C; source fallback-linked. SinglefnNM/noA-B/native0; coordinator full DOL SHA1ea30f3b1 OK.
