/* The adjacent callers share only this TU-local observed camera layout.
 * Keep this bounded NonMatching body separate from the exact 200-byte caller.
 * CW 1.3.2 canonicalizes both null-view branches to the opposite block order.
 */
#define COBJ_PROJECT_POINT_ONLY
#include "src/game/CObjProject.c"
