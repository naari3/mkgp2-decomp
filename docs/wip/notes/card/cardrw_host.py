#!/usr/bin/env python3
"""cardrw_host.py - drive a real Sanwa CRP-1231 card reader/writer from a PC
(the PC plays the role of the MKGP2 game board). UNTESTED on hardware.

Protocol as implemented by the game (Sci2Card_Tick / Sci2Card_BuildPacket):
  host -> unit : 02 LEN CMD 00 00 00 <data> 03 BCC     (BCC = XOR of LEN..03)
  unit -> host : 06 (ACK)                             (anything else = resend)
  host -> unit : 05 (ENQ)
  unit -> host : 02 LEN CMD R P S <data> 03 BCC
                 R = card position, P = error ('0' ok), S = job ('3' = still running,
                 then ENQ again; '4' waiting for card; '5' dispenser empty)
Serial: LR (MKGP/WMMT1-2) 9600 8N1, BR (Initial D/F-Zero AX) 9600 8E1.

  pip install pyserial
  cardrw_host.py --port COM3 [--parity E] status
  cardrw_host.py --port COM3 read out.bin        # waits for a card, reads track 1 (69 B)
  cardrw_host.py --port COM3 readall out.bin     # tracks 1-3 (207 B), YACardEmu/Dolphin image
  cardrw_host.py --port COM3 write in.bin        # writes track 1 (8-bit, no parity)
  cardrw_host.py --port COM3 eject
  cardrw_host.py --port COM3 raw 20 [hexdata]    # any command, e.g. 'raw 10 30'
"""
import argparse, sys, time
import serial

def frame(cmd, data=b""):
    body = bytes([6 + len(data), cmd, 0, 0, 0]) + bytes(data) + b"\x03"
    bcc = 0
    for x in body:
        bcc ^= x
    return b"\x02" + body + bytes([bcc])

class CardRW:
    def __init__(self, port, parity):
        self.s = serial.Serial(port, 9600, bytesize=8, parity=parity, stopbits=1,
                               rtscts=False, timeout=2)

    def _read_frame(self):
        b = self.s.read(1)
        while b and b != b"\x02":
            b = self.s.read(1)
        if not b:
            raise TimeoutError("no response frame")
        n = self.s.read(1)[0]
        rest = self.s.read(n)
        pkt = b"\x02" + bytes([n]) + rest
        bcc = 0
        for x in pkt[1:-1]:
            bcc ^= x
        if bcc != pkt[-1]:
            raise IOError("bad BCC: " + pkt.hex(" "))
        return pkt

    def cmd(self, cmd, data=b"", wait=60.0, verbose=True):
        pkt = frame(cmd, data)
        for _ in range(8):
            self.s.reset_input_buffer()
            self.s.write(pkt)
            if self.s.read(1) == b"\x06":
                break
        else:
            raise IOError("no ACK for command %02X" % cmd)
        end = time.time() + wait
        while True:
            time.sleep(0.1)
            self.s.write(b"\x05")
            rsp = self._read_frame()
            r, p, st = rsp[3:6]
            if verbose:
                print("cmd %02X -> R=%s P=%s S=%s len=%d" % (cmd, chr(r), chr(p), chr(st), len(rsp)))
            if not (p == 0x30 and st == 0x33) or time.time() > end:
                return rsp, rsp[6:-2]

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", required=True)
    ap.add_argument("--parity", default="N", choices="NEO")
    ap.add_argument("op")
    ap.add_argument("args", nargs="*")
    a = ap.parse_args()
    rw = CardRW(a.port, a.parity)
    if a.op == "status":
        rw.cmd(0x20)
    elif a.op == "init":
        rw.cmd(0x10, b"0")
    elif a.op in ("read", "readall"):
        rw.cmd(0x33, b"210")                         # mode '2' = take the card in
        tracks = b"010" if a.op == "read" else b"016"  # track '0' = 1, '6' = 1+2+3
        rsp, data = rw.cmd(0x33, tracks)
        print(data.hex(" "))
        open(a.args[0], "wb").write(data)
        if data[:3] == b"MKA":
            print("looks like an MKGP card (APP-CODE 'MKA')")
    elif a.op == "write":
        img = open(a.args[0], "rb").read()[:69].ljust(69, b"\0")
        rw.cmd(0x33, b"210")
        rw.cmd(0x53, b"010" + img)
    elif a.op == "eject":
        rw.cmd(0x80)
    elif a.op == "raw":
        rsp, data = rw.cmd(int(a.args[0], 16), bytes.fromhex("".join(a.args[1:])))
        print(rsp.hex(" "))

if __name__ == "__main__":
    main()
