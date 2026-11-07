# collision-support-unlock

Source: Codex worker c19_u61_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1920 B.

c19_u61 fn_802086AC802086AC resolves98.5->100%/1920B with static inline int Col_GetType(const CollisionObject *o){return o->type;} used ONLY in generic Col_Support guard. All helper parameters const alone is byte-invariant1904B. Accessor restores nested type lwz/cmpwi pairs at2DC/2E0 and598/59C AND four-way a/b/pa/pb saved-GPR homes; text/EH8/index12 all100. No synthetic check, volatile, extra data ownership, bridge or layout change. Existing unused32B compiler literal pool is link-discarded. Matching full DOL SHA1ea30f3b1 exact; linked ELF function802086AC/1920 and owned EH1934C/index29A2C exact. Native gain1fn1920B despite unchanged progress matched-function count; linked TUs+1. Prior c3/c18 aliases/direct-position/whole-contact-helper/Vec-by-value dead ends need not be repeated.
