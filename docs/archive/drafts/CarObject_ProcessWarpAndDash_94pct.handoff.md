# HANDOFF batch_promote_8004d1a8_warpdash

## Result: skipped (94.60% reached; residual is register-choice-only, new hard-block flavor)

CarObject_ProcessWarpAndDash (0x8004D1A8, 0x25C, extab-bearing, approach B) was taken from
asm to 94.60% / 154-instr C. The final diff (49 rows) contains ZERO instruction-content
differences except:

1. **callee-saved web swap**: target self=r31 / mov=r30; CW 1.3.2 emits mov=r31 / self=r30
   from every C form tried. ~45 of 49 rows are this single swap.
2. Two single-slot scheduler swaps (lfs f2,0xc vs lwz r3,0x28 order; stfs f3,0x30 vs
   lwz r3,0x34 order) - likely tied to (1).

### Probe result (load-bearing): NOT the section-14.2 approach-B class

Compiling the identical source with `-Cpp_exceptions on` (pragma removed) produces
**byte-identical output** to the `#pragma exceptions off` build. The exceptions-off
regalloc hard-block (CarObject_HandleObstacleHit class) is NOT the cause here.

### Bisect evidence: allocation flips with block composition (tie-break artifact)

- warp-block only                -> mov=r31 (wrong)
- warp+dash blocks               -> mov=r30 (TARGET allocation)
- warp+dash+mgr blocks (full fn) -> mov=r31 (wrong)
- full minus WarpZone_CalcExitPosition call -> mov=r30 (TARGET)

The 9-arg CalcExitPosition callsite (only r8-consuming call) flips the tie-break, but
warp-only also flips it, so it is not a single-cause; it behaves like an internal
allocator ordering/counter artifact. Levers tried with NO effect: local decl order
permutations, `register` keyword, explicit `sv = self` copies (always coalesced),
provably-false folded guards (`if (sv != self)`, `if (self != self)`, memory-reload
guards), early-return restructure, yaw temps, extra unused parameters (1 and 2).

### Verified idioms for the future retry (do not rediscover)

- **Scratch locals = TWO structs**: `struct { float exitYaw, yawAngle, vz, vy, vx; } s;`
  + `struct { float exitPos[3]; float warpPos[3]; } t;`. exitPos at struct offset 0 is
  load-bearing: when exitPos was an interior member (offset 0x14 of a single struct),
  CW CSE'd `&s.exitPos` (used by CalcExitPosition r5 and KartMovement_SetPosition r4)
  into an extra callee-saved web (`addi r29,r1,0x1c` + mr/mr), frame 0x60, 4 saves.
  Base-offset member address is rematerialized (2x addi) exactly like target.
  Union access-path split does NOT defeat that CSE; only base-offset placement does.
- Dead warpPos stores (sp+0x28..0x30) survive DSE via membership in the escaping struct t.
- **Struct decl order t-then-s yields stack order s@0x8, t@0x1c** (inverse!); s-then-t
  yielded t@0x8. CW inserts a fixed 0x10 gap between locals and GPR saves in this fn;
  locals must total exactly 0x2c for frame 0x50.
- fp temps after WarpAutoRun_GetParam: named locals fvx/fvy/fvz/fyaw; decl order
  fyaw,fvz,fvy,fvx -> f2,f3,f4,f5 (ascending by decl). fyaw must be *born before fvx's
  last use* (statement order: `fyaw = s.yawAngle; m = self->movement;
  t.warpPos[0] = fvx; m->speed = fyaw;`), otherwise CW shares f2 for both.
- **cam-in-r3 idiom** for `lwz r3,g(r13); cmplwi r3,0; bne; li r3,0`:
  `cam = g; if (cam != g) { } else if (cam == 0) { cam = 0; } f(cam, ...)`.
  Plain `if (cam == 0) cam = 0;` puts cam in r0 + extra `mr r3,r0`; both ternary
  directions (`g ? g : 0`, `g == 0 ? 0 : g`) go branchless (neg/or/srawi or cntlzw).
- 9-clear block needs a short-lived `m = self->movement;` temp (single lwz for 9 stfs);
  per-statement `self->movement->...` would reload per store (aliasing).
- Extern refinements used (kept in the diff-able branch, NOT applied to main since skip):
  typed prototypes for WarpZone_CheckEntry (returns unsigned char), WarpAutoRun_OnEnter
  (8-arg, matches sibling bundle), DashZone_ProcessAutoRun (int return), WarpAutoRun_GetParam,
  WarpDashMgr_GetInstance (`void *(unsigned char)`), WarpZone_CalcExitPosition (9-arg),
  WarpZone_FindContaining, CameraEffect_Apply(u32,int,float), SoundCtrl_SetVolume,
  KartMovement_RotateByYaw/SetPosition, Camera_RotateByYaw; data:
  lbl_806D26EC / lbl_806D26FC / lbl_806D2798 -> `extern const float` (sdata2/r2).
- View structs written (CarObjWarpView, KartMovementWarpView) - see this worktree's HEAD~
  reflog if needed; offsets: self 0x20 u8 isPlayer, 0x24 soundCtrl, 0x28 movement,
  0x2c renderObj, 0x34 kartBody, 0x38 camera, 0x54 warpCtx, 0x9c f32[3], 0xf4 u8, 0x108 u8 mgrIndex;
  movement 0x88 pos[3], 0x17c vel[3], 0x194 prevVel[3], 0x1ac vel2[3], 0x1c8 speed.

The worktree TU was restored with `git checkout` and full `ninja build/GNLJ82/ok` is green.

```json
{
  "batch_id": "batch_promote_8004d1a8_warpdash",
  "sub_summary": "CarObject_ProcessWarpAndDash promote: skipped at 94.60% - all residual diffs are a self/mov r31<->r30 callee-saved tie-break swap (+2 dependent scheduler slots); exceptions on/off probe identical, so NOT the 14.2 approach-B class; new allocator tie-break hard-block flavor",

  "results": [
    {
      "addr": "0x8004D1A8",
      "name": "CarObject_ProcessWarpAndDash",
      "status": "skipped",
      "src_path": null,
      "objdiff_percent": null,
      "notes": "best 94.60% (154 instrs, content-identical except r30/r31 web swap and 2 scheduler slots). Hard-block class: CW1.3.2 callee-saved allocation order tie-break (self-copy web vs first-local web) flips with block composition (bisect: warp-only bad, warp+dash good, +mgr-block bad; removing the 9-arg CalcExitPosition call restores target order). Unreachable via decl order / register kw / copy locals / folded guards / early-return / unused params. Exceptions on/off codegen identical (probe). 3-trial+time budget exhausted. Verified idioms and view structs documented in HANDOFF body for retry; sibling fns using &localStruct interior members for multi-use out-params will hit the same addi-CSE issue - put out-param arrays at struct offset 0."
    }
  ],

  "configure_py": { "add_objects": [] },
  "splits_txt": { "add_entries": [] },
  "symbols_txt": { "set_scope": [], "set_attr": [], "rename": [] },

  "docs_notes": [],

  "build_verified": {
    "command": "ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 0
  },

  "blocked_reason": "register-allocation tie-break only: target wants self=r31/mov=r30, CW emits mov=r31/self=r30 for every source form; 94.60%, instruction content matches. New hard-block flavor (not 14.2 class 1-3).",
  "user_attention": "PRE-EXISTING BUILD BREAKAGE ON MAIN (not caused by this batch): 3 TUs contain UTF-8 bytes in comments that fail sjiswrap, so `ninja build/GNLJ82/ok` cannot run from a clean checkout: src/game/ISESlot_Lifecycle.c (em-dash x4, section-sign x1; commit 64f38a9), src/game/auto_801223E8_block.c (em-dash, section-sign), src/game/LookupCos.c (em-dash, section-sign). Fix = replace with ASCII ('--', 'section '). This worktree carries the comment-only fixes uncommitted (needed to verify sha1); main must apply the same fix or re-harvest from this worktree before it is removed."
}
```

## Appendix: best-attempt C (94.60%) - paste-ready for retry

```c
/* view structs (add next to existing KartItem*View blocks) */
typedef struct KartMovementWarpView {
    char pad_0x0[0x88];
    float pos[3];         /* 0x88 */
    char pad_0x94[0xe8];
    float vel[3];         /* 0x17c */
    char pad_0x188[0xc];
    float prevVel[3];     /* 0x194 */
    char pad_0x1a0[0xc];
    float vel2[3];        /* 0x1ac */
    char pad_0x1b8[0x10];
    float speed;          /* 0x1c8 */
} KartMovementWarpView;

typedef struct CarObjWarpView {
    char pad_0x0[0x20];
    unsigned char isPlayer;        /* 0x20 */
    char pad_0x21[0x3];
    void *soundCtrl;               /* 0x24 */
    KartMovementWarpView *movement;/* 0x28 */
    void *renderObj;               /* 0x2c */
    char pad_0x30[0x4];
    void *kartBody;                /* 0x34 */
    void *camera;                  /* 0x38 */
    char pad_0x3c[0x18];
    void *warpCtx;                 /* 0x54 */
    char pad_0x58[0x44];
    float effectVec[3];            /* 0x9c */
    char pad_0xa8[0x4c];
    unsigned char warpSoundActive; /* 0xf4 */
    char pad_0xf5[0x13];
    unsigned char mgrIndex;        /* 0x108 */
} CarObjWarpView;

#pragma exceptions off
void CarObject_ProcessWarpAndDash(CarObjWarpView *self) { /* 0x8004D1A8 size:0x25C */
    KartMovementWarpView *mov;
    void *mgr;
    int zone;
    int state;
    KartMovementWarpView *m;
    float fyaw;
    float fvz;
    float fvy;
    float fvx;
    unsigned int cam;
    struct {
        float exitPos[3];  /* sp+0x1c */
        float warpPos[3];  /* sp+0x28 */
    } t;
    struct {
        float exitYaw;     /* sp+0x08 */
        float yawAngle;    /* sp+0x0c */
        float vz;          /* sp+0x10 */
        float vy;          /* sp+0x14 */
        float vx;          /* sp+0x18 */
    } s;

    mov = self->movement;
    if (WarpZone_CheckEntry(self->warpCtx, mov->pos[0], mov->pos[1], mov->pos[2]) == 1) {
        WarpAutoRun_OnEnter(self->warpCtx, mov->pos[0], mov->pos[1], mov->pos[2],
                            self->movement->speed, self->movement->vel[0],
                            self->movement->vel[1], self->movement->vel[2]);
        if (self->isPlayer == 1) {
            cam = lbl_806D109C;
            if (cam != lbl_806D109C) {
            } else if (cam == 0) {
                cam = 0;
            }
            CameraEffect_Apply(cam, 6, lbl_806D2798);
        }
        if (self->warpSoundActive == 0 && self->isPlayer == 1) {
            SoundObj_PlaySE(self->soundCtrl, 0x12);
            SoundObj_PlaySE_Direct(self->soundCtrl, 0x55);
            SoundObj_PlaySE_Direct(self->soundCtrl, 0x30);
        }
        SoundCtrl_SetVolume(self->soundCtrl, lbl_806D26FC);
        self->warpSoundActive = 1;
    } else {
        self->warpSoundActive = 0;
    }

    state = DashZone_ProcessAutoRun(self->warpCtx, mov->pos[0], mov->pos[1], mov->pos[2],
                                    self->movement->speed);
    if (state == 1) {
        m = self->movement;
        m->vel[0] = lbl_806D26EC;
        m->vel[1] = lbl_806D26EC;
        m->vel[2] = lbl_806D26EC;
        m->prevVel[0] = lbl_806D26EC;
        m->prevVel[1] = lbl_806D26EC;
        m->prevVel[2] = lbl_806D26EC;
        m->vel2[0] = lbl_806D26EC;
        m->vel2[1] = lbl_806D26EC;
        m->vel2[2] = lbl_806D26EC;
        WarpAutoRun_GetParam(self->warpCtx, &s.vx, &s.vy, &s.vz, &s.yawAngle);
        fvx = s.vx;
        fvy = s.vy;
        fvz = s.vz;
        m = self->movement;
        m->vel[0] = fvx;
        m->vel[1] = fvy;
        m->vel[2] = fvz;
        fyaw = s.yawAngle;
        m = self->movement;
        t.warpPos[0] = fvx;
        m->speed = fyaw;
        self->effectVec[0] = lbl_806D26EC;
        self->effectVec[1] = lbl_806D26FC;
        self->effectVec[2] = lbl_806D26EC;
        t.warpPos[1] = fvy;
        t.warpPos[2] = fvz;
        KartBody_SetWarpTransitFlag(self->kartBody, 1);
    } else if (state == 2) {
        KartBody_SetWarpTransitFlag(self->kartBody, 0);
    }

    mgr = WarpDashMgr_GetInstance(self->mgrIndex);
    zone = WarpZone_FindContaining(mgr, mov->pos[0], mov->pos[1], mov->pos[2]);
    if (zone != -1) {
        WarpZone_CalcExitPosition(mgr, zone, mov->pos[0], mov->pos[1], mov->pos[2],
                                  &t.exitPos[0], &t.exitPos[1], &t.exitPos[2], &s.exitYaw);
        KartMovement_SetPosition(self->movement, t.exitPos, 1);
        KartMovement_RotateByYaw(self->movement, s.exitYaw);
        Camera_RotateByYaw(self->camera, s.exitYaw);
        RenderObj_ToggleLapSegment(self->renderObj, -1);
    }
}
#pragma exceptions reset
```

Required extern refinements (replace the open prototypes in the TU extern block):

```c
extern void CameraEffect_Apply(unsigned int cam, int type, float scale);
extern void Camera_RotateByYaw(void *camera, float yaw);
extern int DashZone_ProcessAutoRun(void *warpCtx, float x, float y, float z, float speed);
extern void KartMovement_RotateByYaw(void *mov, float yaw);
extern void KartMovement_SetPosition(void *mov, float *pos, int flag);
extern void SoundCtrl_SetVolume(void *soundCtrl, float vol);
extern void WarpAutoRun_GetParam(void *warpCtx, float *vx, float *vy, float *vz, float *yaw);
extern void WarpAutoRun_OnEnter(void *self, float f1, float f2, float f3, float f4, float vx, float vy, float vz);
extern void *WarpDashMgr_GetInstance(unsigned char id);
extern void WarpZone_CalcExitPosition(void *mgr, int zone, float x, float y, float z, float *ox, float *oy, float *oz, float *oyaw);
extern unsigned char WarpZone_CheckEntry(void *warpCtx, float x, float y, float z);
extern int WarpZone_FindContaining(void *mgr, float x, float y, float z);
/* data: change to const float (sdata2/r2): */
extern const float lbl_806D26EC;  /* 0.0f */
extern const float lbl_806D26FC;  /* 6.0f */
extern const float lbl_806D2798;  /* camera effect scale */
```

Forward decl: `void CarObject_ProcessWarpAndDash(CarObjWarpView *self);` replaces the asm one.
Keep the manual extab/extabindex emits (approach B).
