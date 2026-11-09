# TextPanelC ctor (fn_801500F4, Q176): where the template and strings land

The target has the ctor template `{316,314,218,217}` at 0x80367368. Its
two format strings ("MAIN  BD ID %s", "MEDIA BD ID %s") sit at
0x803675B4/C4, AFTER the objects 0x80367378..0x803675B3.

## Probes (GC/2.6, C++, -inline auto)

- A local initializer template is emitted at PARSE time, so it lands
  right after the statics defined above the function.
- `readonly_strings` literals are emitted at CODEGEN time.
- A free function whose codegen is deferred puts its literals after
  the statics that follow it. The trigger seen was a call to an inline
  member returning a class by value. Codegen flushes when the next
  function (even an asm one) is parsed.
- Ctors and member functions were NOT deferred with that trigger.
- An `inline` ctor inlined into a later function behaves the same way:
  template at parse, literals at the caller's codegen.

## So

The original most likely had the ctor's codegen deferred past
0x80367378..0x803675B3, which also explains the strings' position.

`scene.diff` plus `rodata_b1.inc` / `rodata_b2.inc` split the pool around
the ctor (part A, then the ctor, then b1, then fn_801502AC, then b2). The
remaining problem is getting the ctor's codegen deferred while keeping
it out of line at 0x801500F4.
