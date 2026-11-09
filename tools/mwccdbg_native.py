"""gdb-side shim: run cadmic/mwcc-debugger against a NATIVE mwcceppc.exe
process instead of retrowin32's gdb stub (Windows, no emulator, no fixed port,
so several runs can go in parallel).

Loaded by tools/mwccdbg.py as
    gdb -batch -nx -ex "py FUNCTION_NAME=...; OUTPUT_DIR=...; MWCCDBG_SCRIPT=..."
        -x tools/mwccdbg_native.py --args mwcceppc.exe ...
It rewrites the debugger's `target remote localhost:9001` into `starti`
(start the inferior, stop at its first instruction; the PE image is not
relocated, so the debugger's fixed breakpoint addresses are valid) and skips
`set osabi none`, then runs mwcc_debugger.py's gdb half unchanged.
"""
import runpy

import gdb  # noqa: F401  (only importable inside gdb)

_execute = gdb.execute


def _patched(cmd, *a, **k):
    c = cmd.strip()
    if c.startswith("target remote"):
        return _execute("starti", *a, **k)
    if c.startswith("set osabi"):
        return None
    if c == "quit":
        try:
            _execute("kill", *a, **k)
        except gdb.error:
            pass
    return _execute(cmd, *a, **k)


gdb.execute = _patched
_execute("set pagination off")
_execute("set confirm off")
# run_path executes in a fresh namespace, so hand over the globals that
# mwcc_debugger.py's gdb half reads (FUNCTION_NAME, OUTPUT_DIR; set with -ex).
runpy.run_path(MWCCDBG_SCRIPT, run_name="__main__",  # noqa: F821
               init_globals={"FUNCTION_NAME": FUNCTION_NAME, "OUTPUT_DIR": OUTPUT_DIR})  # noqa: F821
