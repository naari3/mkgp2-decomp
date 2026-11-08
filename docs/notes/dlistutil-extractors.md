# dlistutil-extractors

Source: Codex worker c7_s19_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Both assigned auto blobs contain one function and only an 8-byte extab with no actions. fn_80184928 transforms quad/triangle-strip data into six 48-byte quad slots, returning 1 only when all six are filled. fn_80184F24 fills 60-byte records with four transformed vertices, a zero int, and two values from lbl_806D927C; it returns the number of records. Vertex descriptors use ushort stride at +0x12, float-array pointer +0x14; attr 9 is position, type 3 uses ushort indices. Matrix +0x44 lies inside the canonical HSD_JObj partial header padding. Explicit float field copies reproduce target lfs/stfs; struct assignments emit integer copies. Native first function reaches exact size and exact EH, but only argument/register differences remain. Second function hoists jobj matrix address, adds 4 bytes and one saved GPR. No handwritten asm or EH payloads used.

## c13_u19_20261106
Source: Codex worker c13_u19_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_80183CC4: changing indexed pointer expression d->array+index*(d->stride/4) into v=d->array; v+=index*(d->stride/4) inside a TU-local copy of ReadPosition resolves the vertex-reader load scheduling and GPR homes. Text 96.99299 -> 97.693924, size 1712 and extab8/index12 stay exact. Explicit billboard guard+field stores fixes those rows but adds 4 bytes because other residuals remain; do not keep separately under unchanged-EH rule. Remaining zero-load loop hoist and matrix-address CSE. Whole display-scan inline extraction regresses to 53.03% with extra emitted function/EH; zero/matrix accessors do not prevent CSE.

## c13_u28_20261106
Source: Codex worker c13_u28_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1128 B.

fn_80184374: local reader v=d->array; v+=index*(d->stride/4) fixes load timing and scratch GPRs. Replacing Transform(j,&v) with SetupMatrix(j); PSMTXMultVec(&j->_pad_1c[0x28],&v,&v) uses the canonical partial JObj member at matrix offset 0x44 and prevents arithmetic loop hoisting: extra r29 matrix home disappears, frame 0x50->0x40 and EH becomes exact. Remaining plain-local count/cursor/end cycle resolves by declaring n before p/end. Final text1128/extab8/index12 all 100%, source-linked DOL SHA-1 OK. Vertex-run helper extraction emitted out of line and regressed; reverted.

## c13_u42_20261106
Source: Codex worker c13_u42_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u42 fn_80185630: explicit x/y/z strip copies restore target floating lfs/stfs (95.5611 -> 96.2074). TU-local GetMatrix equivalent returning (float (*)[4])&jobj->_pad_1c[0x28] prevents matrix address hoist and removes extra saved GPR (98.49679%, extab100). Remaining GPR/coalescing differences and two missing pointer mr instructions leave text2480 versus target2488; index91.66667. Target-derived declaration order changed loop homes but regressed98.40836 and was reverted. Singleton kept NonMatching; full fallback SHA-1 OK.

## c13_u50_20261106
Source: Codex worker c13_u50_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c13_u50: fn_80184F24 TU-local matrix getter returning (MtxPtr)&jobj->_pad_1c[0x28] removes matrix-address hoist, extra instruction and saved GPR: text95.028824 ->97.52772, exact1804B/extab8/index12. Inline transform wrapper and separate SetupMatrix with DListJObjMatrixView address were byte-identical to baseline. Residual saved-register partition plus quad-address scheduling remains; retain NonMatching. Coordinator full fallback build SHA-1 OK.

## c16_u56_20261106
Source: Codex worker c16_u56_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 332 B.

fn_801847DC 0x801847DC (332B): existing traversal body/register allocation was exact; 80.24097% residual came entirely from nullable JObj getter branch layout. Both if (!p) return 0; return field and if (p) return field; return 0 emit load-first blocks. return p == 0 ? 0 : p->field preserves null-first blocks, matching GetChild/GetNext/GetParent including nested parent/next reuse. DNext remains p ? p->next : 0 because its target is load-first. Text332/extab8/index12 all100; sole TU flipped Matching; source-linked full DOL SHA-1 verified.

## c18_u30_20261107
Source: Codex worker c18_u30_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u30 fn_80185630: separate read-only incoming faces from mutable output cursor out, and display base from mutable p. This restores mr r31,r5 at +5C and mr r25,r17 at +7C structurally (with different actual register homes), text2480->2488, extab/index100. Target-derived plain-local declarations yield98.95499 versus98.49679 baseline. Final121 differing rows are GPR operands only, no insertion/deletion. Target/source: p31/26,count30/25,capacity29/31,jobj28/30,attr table27/29,face26/24,out25/23,second vertex24/28,third23/27; primitive22,n21,needed20,parity19,i18,end16,fourth17 exact. Whole-scan static inline outlines (public160 + helper2400); explicit vertex pointers add8B and regress97.840836. No singleton or table ownership unlock, one-function TU staysNonMatching. Coordinator fallback DOL SHA1 exact; native gain0.

## c18_u76_20261107
Source: Codex worker c18_u76_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u76 fn_80184F24: first matrix getter into a block-local MtxPtr before assigning quad fixes premature output-base add in both primitive branches (97.52772 -> 98.59202). Target-derived plain-local declaration order plus scan-scoped offset reaches 99.37916, exact text1804/extab8/index12. Remaining 52 rows are only four-register rotation: target jobj23/out24/capacity25/offset22 vs source22/23/24/25; all loops, table and vertex pointers exact, no inserted/deleted rows. Inline stride helper and unsigned offset invariant; combined matrix/quad helper regresses98.7694. Keep best NonMatching; singleton no safe subset, no bridge/pool rescue needed. Coordinator fallback-linked full DOL SHA-1 exact. Six hypotheses exhausted.

## c18_u47_20261107
Source: Codex worker c18_u47_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c18_u47 fn_80184928: TU-local DListGetPosition equivalent using src=desc->array; src+=index*(desc->stride/4) improves text98.08094->98.18538 with exact1532B/extab8/index12. Canonical matrix member getter is byte-identical; independent per-primitive loop state regresses97.663185. Retained source; residual99 instruction rows are GPR homes plus three stack coordinate addressing forms. Single-function TU staysNonMatching, no A/B unlock. Full coordinator fallback DOL SHA1 exact.

## c18_u67_20261107
Source: Codex worker c18_u67_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1712 B.

c18_u67 fn_80183CC4: canonical member address &j->_pad_1c[0x28] after each SetupMatrix eliminates cross-call matrix CSE (97.693924 ->99.03505). Guard nonzero billboard mask before switch and explicit ordered component stores restore target guard and 1712B size (99.299065). TU-local ExtendBounds using 0.0f comparisons instead of extern const lbl_806D927C prevents loop-hoisted zero/FPR web, reaches text1712/extab8/index12 all100. Existing sdata2 postprocess maps literal back to UND lbl_806D927C. Matching flag only; no split/header/pool/bridge changes. Source-linked full DOL SHA-1 exact, +1 native /1712B.

## c18_u94_20261107
Source: Codex worker c18_u94_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1780 B.

c18_u94 fn_80185FE8: c13 retry unlocks 96.66292 ->100% with three structural changes. TU-local matrix getter uses canonical (float (*)[4])&jobj->_pad_1c[0x28] after existing checks/setup; unrelated DListJObjMatrix view had cached matrix across calls. This fixes saved GPR partition and reaches99.70786 (1776B). Separate immutable display base and mutable p, with end computed from display before p=display, restores missing mr r30,r5 and reaches99.955055 (1780B). TU-local ReadPosition stages v=desc->array; v+=index*(desc->stride/4), giving final pointer r8 instead of r7 and all100 text1780/extab8/index12. Matching source object appears in main.elf edge, ELF symbol80185FE8/1780, coordinator full DOL SHA1 exact. No shared header, EH bridge, order, data, split or symbol changes.

## c19_u45_20261107
Source: Codex worker c19_u45_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1804 B.

c19_u45 fn_80184F24: replacing independent int offset, casted out+offset, and offset+=sizeof(DListQuadInfo) with quad=&out[count] in both primitive branches resolves all 52 GPR-only residual rows (99.37916 ->100%). MWCC generates the same 60-byte induction but colors it r22, with jobj/out/capacity r23/r24/r25 as target. Text1804/extab8/index12 all100. Sole TU promoted Matching; source object in main.elf edge, ELF symbol80184F24/1804, report complete, coordinator full DOL SHA-1 exact. One semantics-first hypothesis; no rescue data/EH/split/header changes.

## c20_u66_20261108
Source: Codex worker c20_u66_20261108 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c20_u66 fn_80184928: target-derived declaration ordering (size/primitive/half after persistent locals) improves98.18538->98.28982, exact1532B/extab8/index12. dst/table base becomes target r21, quad cursor r21->r20; 99->92 formatted differing rows. Float-component reader is instruction-identical; reuse command-size/vertex-count n regresses98.133156. Retain H2 NonMatching. Residual GPR partition, three stack-versus-pointer coordinate accesses, quad-reader scratch registers and quad induction scheduling. No singleton/pool rescue or B subset. Full fallback DOL SHA1 exact.
