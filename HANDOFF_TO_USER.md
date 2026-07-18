# Orchestrator handoff

- 2026-07-18T12:55Z: `git push origin main` for EffectSteering merge commit `dbe831b` was rejected because remote `main` advanced to `316a5f2` with CI-only commits. Fetch succeeded; main will rebase the local merge commit onto `origin/main`, re-run SHA-1 verification, and retry push.
- 2026-07-18T13:08Z: `git push origin main` for EffectActor merge commit `cf7a567` was rejected because remote `main` advanced again. Main will fetch/rebase, re-run SHA-1 verification, and retry push before processing the remaining completion hooks.
# Push recovery: PlayStats_Clear (2026-07-19)

- Local commit `b932bb4` was rejected by `git push origin main` because remote `main` advanced concurrently.
- Recovery in progress: fetch/rebase, full SHA-1 verification, then retry push.
# Push recovery: SceneRender unit (2026-07-19)

- Local SceneRender completion commit was rejected because remote `main` advanced concurrently.
- Claim issue #11 was reopened immediately; recovery is fetch/rebase, SHA-1 verification, push, then `claim_unit.py done SceneRender`.

# Push recovery: JointByName unit (2026-07-19)

- Local JointByName commit `17c54d4` passed the full SHA-1 check, but `git push origin main` was rejected because remote `main` advanced concurrently.
- Recovery: reopen the unit claim, fetch/rebase onto `origin/main`, rerun the SHA-1 check, push, then close the claim.

# Push recovery: TaRecord unit (2026-07-19)

- Local TaRecord commit `54d2689` passed the full SHA-1 check, but its first push was rejected because remote `main` advanced concurrently.
- Recovery: fetch/rebase, rerun the SHA-1 check, push, then close claim issue #20.

# Push recovery: HeartCompoundItem / CarrotItemEffect / TwinSpriteOverlay (2026-07-19)

- Local commit `1030193` passed the full SHA-1 check, but its first push was rejected because remote `main` advanced concurrently.
- Recovery: fetch/rebase, resolve any SoT conflicts while retaining both sides, rerun SHA-1, push, then close issues #23-#25.
