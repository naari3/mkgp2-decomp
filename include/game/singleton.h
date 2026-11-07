#ifndef GAME_SINGLETON_H
#define GAME_SINGLETON_H

/*
 * Defensive singleton getter of the original code.
 *
 * Many manager singletons are read with the shape
 *     lwz r3, ms_pInstance; cmplwi r3, 0; bne L; li r3, 0; L:
 * i.e. "if the instance is null return null, else return it". MWCC does not
 * fold this no-op select, and no cast / reference / wrapper construct produces
 * it; only an explicit "== 0 -> 0" accessor does (the opposite polarity
 * `p ? p : 0` yields a different branch layout). The identical shape at 100+
 * sites across many TUs indicates one defensive GetInstance()-style accessor
 * per manager class in the original source.
 *
 * Use this macro for that read and nothing else; do not hand-write ad-hoc null
 * re-tests at call sites. Approved by the repo owner (2026-11-07).
 * Details: docs/notes/singleton-getter.md
 */
#define SINGLETON_INSTANCE(p) ((p) == 0 ? 0 : (p))

#endif /* GAME_SINGLETON_H */
