// Phase 2f-2: frida reader for the CW 1.3.2 graph-coloring register allocator.
//
// STATUS: VERIFIED reader. Hooks the select/color function and the simplify
// stack builder to observe (a) the order in which webs are popped & colored and
// (b) the physical register each web receives. The per-pass listing dump is a
// dead stub in this release (see docs/notes/cw132-allocator-phase2f-research.md),
// so run-time hooking is the only way to read the colorer's visit order. ASLR is
// OFF for this PE (DllCharacteristics=0, ImageBase=0x400000), so module base ==
// 0x400000 and VAs map directly.
//
// Confirmed by static disasm of mwcceppc.exe 1.3.2 (objdump, image base 0x400000):
//
//   0x5077b0  FUN_005077b0 RegisterColoring driver (Coloring.c). Outer loop over
//             register class DAT_005e931f = 0..4. For each class with webs it runs
//             a while loop: 0x579cf0 (build/coalesce) -> 0x507d40 -> 0x507b50
//             (build simplify/select stack, returns stack head in eax) -> 0x507a30
//             (assign colors over that stack; returns 0 => spill needed).
//
//   0x507b50  FUN_00507b50 Chaitin/Briggs simplify+spill-pick. Pushes interference
//             nodes onto a singly-linked stack via `*node = prevHead; head = node`.
//             Trivially-colorable nodes (degree [+0x12] < k) pushed first; then a
//             degree/spill-cost ratio picks optimistic-spill candidates. RETURNS
//             eax = head of that stack. The stack's *pop* order (head-first walk
//             via *p==next) IS the order FUN_00507a30 colors the webs.
//
//   0x507a30  FUN_00507a30 select/assign. Walks the stack from its arg via
//             `ebx = *ebx`. For each web: builds a forbidden-color mask from
//             colored neighbours' [+0x14], then assigns the LOWEST free physical
//             register number into WORD [ebx+0x14]. Forced/required regs come from
//             FUN_004fd5a0. Sets flag bit0 [+0x16]|=1 on spill (no color). Returns
//             1 if all colored, 0 if any spilled.
//
// Interference-graph NODE struct (elements of array DAT_005e87d0, index = class
// register number; these are what the stack links together):
//   [+0x00] u32  next-in-select-stack (also reused as generic *next during build)
//   [+0x04] u32  -> sub-object (web/temp record; FUN_004cff40 reads it)
//   [+0x0c] u32  spill-cost numerator (int; fild'd in the cost ratio)
//   [+0x10] u16  index/key compared against DAT_005df940 (class web count)
//   [+0x12] u16  current interference DEGREE (decremented as nbrs are removed)
//   [+0x14] u16  HOME PHYSICAL REGISTER  <<< the deliverable. 0xffff = uncolored.
//   [+0x16] u16  flags: 0x1=spilled, 0x2=removed/on-select-stack,
//                       0x8=coalesce-related, 0x40=coalesced-into another web
//                       (0x30 mask gates the build-time skip in FUN_00579d50)
//   [+0x18] u16  adjacency count
//   [+0x1a] u16[] adjacency: indices into DAT_005e87d0
//
// Web/temp LIST (the other structure; head DAT_005e87b0, singly linked *p==next):
//   [+0x00] u32 next   [+0x18] u32 node-chain head   [+0x1c] u32 index (p[7])
//   This is the value-numbered web list consumed by FUN_00579cf0's build. We dump
//   it too (read-only) so the node<->web correlation can be eyeballed.
//
// Register-number -> name decoding: classes are GPR/FPR/CR/.. The driver sets
// DAT_005e931f = class. For GPR (class 4) the physical number is the r-index
// directly; for FPR similar with 'f'. We print the raw number + a best-effort
// name keyed off the class.
//
// Usage:
//   frida -f <priv_mwcceppc.exe> <compile-args...> -l frida_colorer_probe.js -q
//   (always against a PRIVATE copy; never the shipped binary.)

'use strict';

const IMAGE_BASE = 0x400000;
let BASE = null;
function modBase() {
  if (BASE) return BASE;
  const names = ['mwcceppc_priv.exe', 'mwcceppc.exe'];
  for (const n of names) {
    try { const b = Module.getBaseAddress(n); if (b) { BASE = b; return b; } } catch (e) {}
  }
  // fallback: first module is the main exe
  const m = Process.enumerateModules()[0];
  BASE = m.base;
  return BASE;
}
function va(addr) { return modBase().add(addr - IMAGE_BASE); }

const ADDR = {
  driver:      0x5077b0,
  buildStack:  0x507b50,   // returns select-stack head
  select:      0x507a30,   // assigns [+0x14]
  classByte:   0x5e931f,   // DAT_005e931f current register class
  webListHead: 0x5e87b0,   // DAT_005e87b0
  nodeArray:   0x5e87d0,   // DAT_005e87d0 (pointer to node-ptr array base)
  lowReg:      0x5e8778,   // (&DAT_005e8778)[class] = first usable reg index
  webCount:    0x5e8a7c,   // (&DAT_005e8a7c)[class] = node count for class
};

function classOf() { return va(ADDR.classByte).readU8(); }
function lowReg(cls) { return va(ADDR.lowReg).add(cls * 4).readS32(); }
function webCount(cls) { return va(ADDR.webCount).add(cls * 4).readS32(); }

// crude reg name; class index meaning confirmed empirically (4==GPR seen most).
function regName(cls, n) {
  if (n === 0xffff || n === -1) return 'UNCOLORED';
  if (cls === 4) return 'r' + n;          // GPR (hypothesis: class 4)
  return 'c' + cls + ':' + n;             // other classes: raw
}

let stepCounter = 0;
let lastSig = null;

// Walk the select stack from `head` via *p==next, returning array of node ptrs.
function walkStack(head) {
  const out = [];
  let p = head;
  let guard = 0;
  while (!p.isNull() && guard++ < 8192) {
    out.push(p);
    p = p.readPointer();
  }
  return out;
}

function dumpNode(p, cls) {
  const idx    = p.add(0x10).readU16();
  const degree = p.add(0x12).readU16();
  let reg = p.add(0x14).readU16();
  const flags  = p.add(0x16).readU16();
  const adjN   = p.add(0x18).readU16();
  return 'node@' + p + ' key=' + idx + ' deg=' + degree +
         ' reg=' + (reg === 0xffff ? '--' : regName(cls, reg)) +
         ' flags=0x' + flags.toString(16) + ' adjN=' + adjN;
}

// Dump the value-numbered web list (head DAT_005e87b0) read-only.
function dumpWebList() {
  let p = va(ADDR.webListHead).readPointer();
  const out = [];
  let guard = 0;
  while (!p.isNull() && guard++ < 8192) {
    const index = p.add(0x1c).readU32();   // p[7]
    out.push('web@' + p + ' idx=' + index);
    p = p.readPointer();
  }
  return out;
}

// ---- hook buildStack: capture the select-stack head it returns ----
let lastStackHead = null;
Interceptor.attach(va(ADDR.buildStack), {
  onLeave: function (retval) {
    lastStackHead = ptr(retval.toString());
  }
});

// ---- hook select: dump pop order + final regs ----
Interceptor.attach(va(ADDR.select), {
  onEnter: function (args) {
    const cls = classOf();
    // arg is on the i386 cdecl stack: [esp+0]. Frida gives args[0] for cdecl.
    this.cls = cls;
    this.head = this.context.esp ? this.context.esp.add(4).readPointer() : args[0];
    // Snapshot the pop order (node ptrs) BEFORE coloring runs.
    this.order = walkStack(this.head);
  },
  onLeave: function (retval) {
    const cls = this.cls;
    const ret = retval.toInt32();
    // Build a signature so we can skip identical recolor passes (the driver
    // re-runs the color step in a while-loop after each coalesce round; only the
    // distinct (key->reg) outcomes are interesting).
    let pos = 0;
    const nodeLines = [];
    const sigParts = [];
    for (const p of this.order) {
      const idx    = p.add(0x10).readU16();
      const reg    = p.add(0x14).readU16();
      sigParts.push(idx + ':' + reg);
      nodeLines.push('  #' + (pos++) + ' ' + dumpNode(p, cls));
    }
    const sig = cls + '|' + sigParts.join(',');
    if (sig === lastSig) return;          // skip duplicate pass
    lastSig = sig;
    const lines = [];
    lines.push('========================================================');
    lines.push('[COLOR step #' + (stepCounter++) + '] class=' + cls +
               ' lowReg=' + lowReg(cls) + ' webCount=' + webCount(cls) +
               ' allColored=' + ret + ' (0=spill)  n=' + this.order.length);
    lines.push('-- POP/VISIT ORDER (stack head -> tail = color order) --');
    for (const l of nodeLines) lines.push(l);
    console.log(lines.join('\n'));
  }
});

console.log('[frida] colorer reader armed. base=' + modBase() +
            ' select=' + va(ADDR.select) + ' buildStack=' + va(ADDR.buildStack));
