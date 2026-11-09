#!/usr/bin/env python3
"""Bring up the loopback interface (for `unshare -n`), then exec argv.
Lets several mwcc-debugger runs (fixed gdb port 9001) run in parallel."""
import fcntl, os, socket, struct, sys
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
ifr = struct.pack("16sH14s", b"lo", 0, b"")
flags = struct.unpack("16sH14s", fcntl.ioctl(s, 0x8913, ifr))[1]   # SIOCGIFFLAGS
fcntl.ioctl(s, 0x8914, struct.pack("16sH14s", b"lo", flags | 1, b""))  # SIOCSIFFLAGS IFF_UP
os.execvp(sys.argv[1], sys.argv[1:])
