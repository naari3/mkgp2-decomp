#!/usr/bin/env python3
# Driver: spawn the PRIVATE CW 1.3.2 compiler under frida, inject
# frida_colorer_probe.js, compile a probe .c, and stream the colorer's
# pop/visit order + assigned home registers to stdout.
#
# The frida CLI mangles compiler flags that start with '-' (e.g. -proc), so we
# drive the frida python bindings directly here.
#
# Usage: python frida_colorer_run.py <probe.c> [extra mwcc flags...]
import os
import sys
import frida

HERE = os.path.dirname(os.path.abspath(__file__))
WT = os.path.abspath(os.path.join(HERE, "..", ".."))
TMP = os.path.join(WT, "tmp_probe")
PRIV = os.path.join(TMP, "mwcceppc_priv.exe")
JS = os.path.join(HERE, "frida_colorer_probe.js")

BASE_FLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "on", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off",
    "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-fp_contract", "on",
    "-str", "reuse", "-multibyte", "-use_lmw_stmw", "on",
]


def main():
    if len(sys.argv) < 2:
        print("usage: frida_colorer_run.py <probe.c> [extra flags...]")
        sys.exit(2)
    src = sys.argv[1]
    if not os.path.isabs(src):
        src = os.path.join(HERE, src)
    extra = sys.argv[2:]
    obj = os.path.join(TMP, "alloc_out.o")
    if os.path.exists(obj):
        os.remove(obj)

    argv = [PRIV] + BASE_FLAGS + extra + ["-c", src, "-o", obj]

    with open(JS, "r", encoding="utf-8") as f:
        script_src = f.read()

    device = frida.get_local_device()
    pid = device.spawn(argv, cwd=TMP)
    session = device.attach(pid)
    script = session.create_script(script_src, runtime="v8")

    def on_message(message, data):
        if message["type"] == "send":
            print(message["payload"], flush=True)
        elif message["type"] == "error":
            print("[frida-error] " + message.get("stack", str(message)), flush=True)

    def on_log(level, text):
        print(text, flush=True)

    script.on("message", on_message)
    script.set_log_handler(on_log)
    script.load()
    device.resume(pid)

    # Wait for the compiler to exit.
    import time
    for _ in range(600):
        try:
            # poll: querying a detached session raises
            session.enumerate_exports if False else None
        except Exception:
            break
        time.sleep(0.1)
        # crude: check whether the object file was produced
        if os.path.exists(obj):
            time.sleep(0.3)
            break
    try:
        session.detach()
    except Exception:
        pass
    print("[driver] obj produced: " + str(os.path.exists(obj)), flush=True)


if __name__ == "__main__":
    main()
