# dlistutil-extractors

Source: Codex worker c7_s19_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Both assigned auto blobs contain one function and only an 8-byte extab with no actions. fn_80184928 transforms quad/triangle-strip data into six 48-byte quad slots, returning 1 only when all six are filled. fn_80184F24 fills 60-byte records with four transformed vertices, a zero int, and two values from lbl_806D927C; it returns the number of records. Vertex descriptors use ushort stride at +0x12, float-array pointer +0x14; attr 9 is position, type 3 uses ushort indices. Matrix +0x44 lies inside the canonical HSD_JObj partial header padding. Explicit float field copies reproduce target lfs/stfs; struct assignments emit integer copies. Native first function reaches exact size and exact EH, but only argument/register differences remain. Second function hoists jobj matrix address, adds 4 bytes and one saved GPR. No handwritten asm or EH payloads used.

## c13_u19_20261106
Source: Codex worker c13_u19_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

fn_80183CC4: changing indexed pointer expression d->array+index*(d->stride/4) into v=d->array; v+=index*(d->stride/4) inside a TU-local copy of ReadPosition resolves the vertex-reader load scheduling and GPR homes. Text 96.99299 -> 97.693924, size 1712 and extab8/index12 stay exact. Explicit billboard guard+field stores fixes those rows but adds 4 bytes because other residuals remain; do not keep separately under unchanged-EH rule. Remaining zero-load loop hoist and matrix-address CSE. Whole display-scan inline extraction regresses to 53.03% with extra emitted function/EH; zero/matrix accessors do not prevent CSE.

## c13_u28_20261106
Source: Codex worker c13_u28_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1128 B.

fn_80184374: local reader v=d->array; v+=index*(d->stride/4) fixes load timing and scratch GPRs. Replacing Transform(j,&v) with SetupMatrix(j); PSMTXMultVec(&j->_pad_1c[0x28],&v,&v) uses the canonical partial JObj member at matrix offset 0x44 and prevents arithmetic loop hoisting: extra r29 matrix home disappears, frame 0x50->0x40 and EH becomes exact. Remaining plain-local count/cursor/end cycle resolves by declaring n before p/end. Final text1128/extab8/index12 all 100%, source-linked DOL SHA-1 OK. Vertex-run helper extraction emitted out of line and regressed; reverted.
