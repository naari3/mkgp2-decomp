# flow-card-check-unlock

Source: Codex worker c3_u11_flowcard_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 5 fn / 176 B.

FlowCardCheck original source omitted 24 functions. Safe cuts at 80232924 and 802379E8 accepted by dtk, rescuing Draw160B and four empty base hooks16B. Shared base dtor must stay out-of-line in nm1 to retain vtable emission; derived inlining/text remains exact. No-EH hooks use ordinary compile with target symbols renamed to actual native C++ names. Correct vtable identities differ from original empty-method bridge. GP table symbol boundaries eliminate synthetic pool residuals in GP Update; actual instructions were exact. Remaining missed methods still prevent EH-group rescue; no new asm/manual EH/fillers added.
