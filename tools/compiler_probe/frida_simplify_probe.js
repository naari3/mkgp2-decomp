// Trace the Chaitin simplify-stack BUILD order (FUN_00507b50).
// Two removal sites:
//   0x507bbc  trivial removal (degree < k): node in EAX, `or [eax+0x16],2` then push to ebp
//   0x507ca1  optimistic-spill removal:     node in ECX, `or [ecx+0x16],2` then push to ebp
// Removal order = reverse of color order. SELECT colors stack top (last removed) first
// -> last-removed = highest reg. We log each removal with key/degree/adjN/cost so the
// sort rule (which node is picked when stuck) is directly observable.
'use strict';
const IMAGE_BASE = 0x400000;
let BASE = null;
function modBase() {
  if (BASE) return BASE;
  for (const n of ['mwcceppc_priv.exe', 'mwcceppc.exe']) {
    try { const b = Module.getBaseAddress(n); if (b) { BASE = b; return b; } } catch (e) {}
  }
  BASE = Process.enumerateModules()[0].base; return BASE;
}
function va(a) { return modBase().add(a - IMAGE_BASE); }
function classOf() { return va(0x5e931f).readU8(); }

let seq = 0;
function logNode(p, kind) {
  const key = p.add(0x10).readU16();
  const deg = p.add(0x12).readS16();   // dynamic degree at removal time
  const adjN = p.add(0x18).readU16();
  const cost = p.add(0x0c).readS32();
  const cls = classOf();
  if (cls !== 4) return;               // GPR only
  console.log('REMOVE seq=' + (seq++) + ' ' + kind +
              ' key=' + key + ' dyndeg=' + deg + ' adjN=' + adjN + ' cost=' + cost);
}

Interceptor.attach(va(0x507bbc), { onEnter: function () { logNode(this.context.eax, 'trivial'); } });
Interceptor.attach(va(0x507ca1), { onEnter: function () { logNode(this.context.ecx, 'spill  '); } });

// mark function boundaries so we can isolate OnKartHit's run (driver re-enters per fn)
Interceptor.attach(va(0x5077b0), { onEnter: function () { console.log('=== RegisterColoring driver enter ==='); seq = 0; } });

console.log('[frida] simplify tracer armed. base=' + modBase());
