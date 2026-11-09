#!/usr/bin/env python3
"""mkgp2card.py - Mario Kart Arcade GP 2 magnetic card image tool.

Derived from the mkgp2-decomp sources (card_pack / card_unpack / bitpack /
Card_VerifyChecksum / Sci2Card_BuildPacket). Schema tables and the name
character table were dumped from main.dol (GNLJ82).

Card image = 69 (0x45) bytes, the payload the game hands to the card unit
with command 0x53 and gets back from command 0x33 (response bytes 6..74).

Usage:
  mkgp2card.py decode card.bin          # dump fields (v0/v1 = MKGP1, v2 = MKGP2)
  mkgp2card.py new out.bin --name マリオ  # make a fresh MKGP2 image
  mkgp2card.py set in.bin out.bin WINS=100 LOSE=3   # edit fields, fix checksum
  mkgp2card.py frame 33|53 [card.bin]   # print the raw RS-232 frame bytes

The 69-byte .bin is also a valid single-track card image for YACardEmu
(github.com/GXTX/YACardEmu, device C1231LR, 9600 none).
"""
import sys

SCHEMAS = {'v0': [('APP-CODE', 8, 3), ('CHECKSUM', 8, 1), ('VERSION', 3, 1), ('LOCATION-TEST', 1, 1), ('COUNTRY', 1, 1), ('REMAIN', 6, 1), ('UPDATE', 1, 1), ('NAME', 8, 5), ('CHARA', 4, 1), ('TITLE', 8, 1), ('TITLE-PARAM', 3, 1), ('VOLUME', 3, 1), ('URA', 1, 1), ('WINS', 10, 1), ('LOSE', 10, 1), ('GET-ITEM-LIST', 1, 88), ('LAST-GET-ITEM', 8, 1), ('ITEMPACK-1', 7, 3), ('ITEMPACK-2', 7, 3), ('ITEMPACK-3', 7, 3), ('RESULT-GP-MR', 1, 4), ('RESULT-GP-DK', 1, 4), ('RESULT-GP-WC', 1, 4), ('RESULT-GP-PC', 1, 4), ('RESULT-GP-KP', 1, 4), ('RESULT-GP-RB', 1, 4), ('GHOST-MR', 1, 4), ('GHOST-DK', 1, 4), ('GHOST-WC', 1, 4), ('GHOST-PC', 1, 4), ('GHOST-KP', 1, 4), ('GHOST-RB', 1, 4), ('WIN-GHOST-MR', 1, 4), ('WIN-GHOST-DK', 1, 4), ('WIN-GHOST-WC', 1, 4), ('WIN-GHOST-PC', 1, 4), ('WIN-GHOST-KP', 1, 4), ('WIN-GHOST-RB', 1, 4), ('RECORD-TA', 19, 6), ('RECORD-STG', 3, 6), ('RECORD-CRS', 1, 6), ('RECORD-DIR', 1, 6), ('MISS-GP', 1, 1), ('BATTLE-WIN-MR-TAG', 6, 1), ('BATTLE-WIN-DK-TAG', 6, 1), ('BATTLE-WIN-WC-TAG', 6, 1), ('BATTLE-WIN-PC-TAG', 6, 1), ('BATTLE-WIN-KP-TAG', 6, 1), ('BATTLE-WIN-RB-TAG', 6, 1), ('BATTLE-LOSE-MR-TAG', 1, 1), ('BATTLE-LOSE-DK-TAG', 1, 1), ('BATTLE-LOSE-WC-TAG', 1, 1), ('BATTLE-LOSE-PC-TAG', 1, 1), ('BATTLE-LOSE-KP-TAG', 1, 1), ('BATTLE-LOSE-RB-TAG', 1, 1)], 'v1': [('APP-CODE', 8, 3), ('CHECKSUM', 8, 1), ('VERSION', 3, 1), ('COUNTRY', 1, 1), ('CAMERA-TAG', 1, 1), ('REMAIN', 6, 1), ('UPDATE', 1, 1), ('NAME', 8, 5), ('CHARA', 4, 1), ('TITLE', 8, 1), ('TITLE-PARAM', 3, 1), ('VOLUME', 3, 1), ('URA', 2, 1), ('WINS', 10, 1), ('LOSE', 10, 1), ('GET-ITEM-LIST', 1, 100), ('LAST-GET-ITEM', 8, 1), ('ITEMPACK-1', 8, 3), ('ITEMPACK-2', 8, 3), ('RESULT-GP-MR', 1, 4), ('RESULT-GP-DK', 1, 4), ('RESULT-GP-WC', 1, 4), ('RESULT-GP-PC', 1, 4), ('RESULT-GP-KP', 1, 4), ('RESULT-GP-RB', 1, 4), ('GHOST-MR', 1, 4), ('GHOST-DK', 1, 4), ('GHOST-WC', 1, 4), ('GHOST-PC', 1, 4), ('GHOST-KP', 1, 4), ('GHOST-RB', 1, 4), ('WIN-GHOST-MR', 1, 4), ('WIN-GHOST-DK', 1, 4), ('WIN-GHOST-WC', 1, 4), ('WIN-GHOST-PC', 1, 4), ('WIN-GHOST-KP', 1, 4), ('WIN-GHOST-RB', 1, 4), ('RECORD-TA', 19, 4), ('RECORD-STG', 3, 4), ('RECORD-CRS', 1, 4), ('RECORD-DIR', 1, 4), ('RECORD-CLASS', 1, 4), ('MISS-GP', 1, 1), ('BATTLE-WIN-MR-TAG', 6, 1), ('BATTLE-WIN-DK-TAG', 6, 1), ('BATTLE-WIN-WC-TAG', 6, 1), ('BATTLE-WIN-PC-TAG', 6, 1), ('BATTLE-WIN-KP-TAG', 6, 1), ('BATTLE-WIN-RB-TAG', 6, 1), ('BATTLE-LOSE-MR-TAG', 1, 1), ('BATTLE-LOSE-DK-TAG', 1, 1), ('BATTLE-LOSE-WC-TAG', 1, 1), ('BATTLE-LOSE-PC-TAG', 1, 1), ('BATTLE-LOSE-KP-TAG', 1, 1), ('BATTLE-LOSE-RB-TAG', 1, 1), ('PLAYCOUNT-TAG', 6, 1), ('PLAY-SUNDAYCOUNT-TAG', 6, 1), ('ITEMPACK-LAST-TAG', 1, 1), ('TA-RECORD-TA', 19, 1), ('TA-RECORD-STG', 3, 1), ('TA-RECORD-CRS', 1, 1), ('TA-RECORD-DIR', 1, 1), ('TITLE-PARAM2', 1, 1), ('TA-RECORD-CLASS', 1, 1)], 'v2': [('APP-CODE', 8, 3), ('CHECKSUM', 8, 1), ('VERSION', 3, 1), ('COUNTRY', 1, 1), ('CAMERA-TAG', 1, 1), ('REMAIN', 6, 1), ('UPDATE', 1, 1), ('NAME', 8, 5), ('LAST_CHARA_TAG', 4, 1), ('LAST_KART_TAG', 1, 1), ('TITLE', 10, 1), ('TITLE-PARAM', 3, 1), ('VOLUME', 3, 1), ('WINS', 10, 1), ('LOSE', 10, 1), ('GET-ITEM-LIST', 1, 105), ('LAST-GET-ITEM', 7, 1), ('COIN_MILAGE_TAG', 17, 1), ('ITEMPACK-1', 7, 3), ('RESULT-GP-50-MR', 4, 1), ('RESULT-GP-50-DK', 4, 1), ('RESULT-GP-50-WC', 4, 1), ('RESULT-GP-50-PC', 4, 1), ('RESULT-GP-50-KP', 4, 1), ('RESULT-GP-50-RB', 4, 1), ('RESULT-GP-50-YI', 4, 1), ('RESULT-GP-50-DN', 4, 1), ('RESULT-GP-100-MR', 4, 1), ('RESULT-GP-100-DK', 4, 1), ('RESULT-GP-100-WC', 4, 1), ('RESULT-GP-100-PC', 4, 1), ('RESULT-GP-100-KP', 4, 1), ('RESULT-GP-100-RB', 4, 1), ('RESULT-GP-100-YI', 4, 1), ('RESULT-GP-100-DN', 4, 1), ('RESULT-GP-150-MR', 4, 1), ('RESULT-GP-150-DK', 4, 1), ('RESULT-GP-150-WC', 4, 1), ('RESULT-GP-150-PC', 4, 1), ('RESULT-GP-150-KP', 4, 1), ('RESULT-GP-150-RB', 4, 1), ('RESULT-GP-150-YI', 4, 1), ('RESULT-GP-150-DN', 4, 1), ('GHOST-MR', 1, 4), ('GHOST-DK', 1, 4), ('GHOST-WC', 1, 4), ('GHOST-PC', 1, 4), ('GHOST-KP', 1, 4), ('GHOST-RB', 1, 4), ('GHOST-YI', 1, 4), ('GHOST-DN', 1, 4), ('WIN-GHOST-MR', 1, 4), ('WIN-GHOST-DK', 1, 4), ('WIN-GHOST-WC', 1, 4), ('WIN-GHOST-PC', 1, 4), ('WIN-GHOST-KP', 1, 4), ('WIN-GHOST-RB', 1, 4), ('WIN-GHOST-YI', 1, 4), ('WIN-GHOST-DN', 1, 4), ('MISS-GP', 1, 1), ('PLAYCOUNT-TAG', 6, 1), ('TA-RECORD-TA', 19, 1), ('TA-RECORD-STG', 3, 1), ('TA-RECORD-CRS', 1, 1), ('TA-RECORD-DIR', 1, 1), ('TITLE-PARAM2', 1, 1), ('TA-RECORD-CLASS', 2, 1), ('TA-RECORD-CHARA', 4, 1), ('TA-RECORD-KART', 2, 1), ('LAST-CLEAR-CUP-CLASS-TAG', 2, 1), ('LAST-CLEAR-CUP-URA-TAG', 1, 1), ('LIVE-TAG', 1, 1), ('RANKIN-TAG', 1, 5)]}
SCHEMAS = {k: SCHEMAS[k] for k in ("v0", "v1", "v2")}
CHARS = '\x00 ０１２３４５６７８９’”ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ\u3000あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよらりるれろわをんぁぃぅぇぉゃゅょっがぎぐげござじずぜぞだぢづでどばびぶべぼぱぴぷぺぽアイウエオカキクケコサシスセソタチツテトナニヌネノハヒフヘホマミムメモヤユヨラリルレロワヲンァィゥェォャュョッガギグゲゴザジズゼゾダヂヅデドバビブベボパピプペポ。、「」！？＆＠（）＜＞＾＋ー×÷＝／＼＿｜・；：＊◇？．♪'   # card code 0..255 -> character (code 0 is a full-width space)
SIZE = 0x45
APP_CODE = b"MKA"

def layout(schema):
    out, bit = {}, 0
    for name, width, slots in schema:
        out[name] = (bit, width, slots)
        bit += width * slots
    return out

def get(buf, lay, name, idx=0):
    off, w, n = lay[name]
    pos, v = off + idx * w, 0
    for i in range(w):            # MSB first, bit 0 = MSB of byte 0
        b = pos + i
        v = (v << 1) | ((buf[b >> 3] >> (7 - (b & 7))) & 1)
    return v

def put(buf, lay, name, value, idx=0):
    off, w, n = lay[name]
    assert idx < n
    pos = off + idx * w
    for i in range(w):
        b = pos + w - 1 - i
        if (value >> i) & 1: buf[b >> 3] |= 0x80 >> (b & 7)
        else:                buf[b >> 3] &= ~(0x80 >> (b & 7)) & 0xFF

HDR = layout(SCHEMAS["v2"][:3])   # APP-CODE / CHECKSUM / VERSION are shared

def checksum(buf):
    tmp = bytearray(buf); tmp[3] = 0
    return sum(tmp) & 0xFF

def fix_checksum(buf):
    buf[3] = checksum(buf)

def check(buf):
    """Returns (ok, version, reasons) using the game's acceptance rules."""
    why = []
    if bytes(buf[:3]) != APP_CODE: why.append("APP-CODE is not 'MKA'")
    if buf[3] != checksum(buf): why.append("checksum mismatch (stored %02X, calc %02X)" % (buf[3], checksum(buf)))
    ver = get(buf, HDR, "VERSION")
    if ver > 2: why.append("unknown VERSION %d" % ver)
    if ver == 2 and get(buf, layout(SCHEMAS["v2"]), "COUNTRY") != 0:
        why.append("COUNTRY must be 0 (isJapanese() returns 0 on this build)")
    return (not why), ver, why

def decode(buf):
    ver = get(buf, HDR, "VERSION")
    sch = SCHEMAS.get("v%d" % ver, SCHEMAS["v2"])
    lay = layout(sch)
    res = {}
    for name, w, n in sch:
        vals = [get(buf, lay, name, i) for i in range(n)]
        res[name] = vals[0] if n == 1 else vals
    if "NAME" in res:
        res["NAME(text)"] = "".join(CHARS[c] for c in res["NAME"]).rstrip("\u3000")
    return res

def encode_name(text):
    codes = [CHARS.index(c) for c in text]
    if len(codes) > 5: raise ValueError("name is at most 5 characters")
    return codes + [0] * (5 - len(codes))

def new_card(name):
    buf = bytearray(SIZE)
    lay = layout(SCHEMAS["v2"])
    for i, c in enumerate(APP_CODE): put(buf, lay, "APP-CODE", c, i)
    put(buf, lay, "VERSION", 2)
    put(buf, lay, "COUNTRY", 0)
    for i, c in enumerate(encode_name(name)): put(buf, lay, "NAME", c, i)
    put(buf, lay, "VOLUME", 3)
    fix_checksum(buf)
    return buf

def frame(cmd, data=b""):
    """Sanwa-style frame: 02 len cmd 00 00 00 data 03 bcc (bcc = XOR len..ETX)."""
    body = bytes([6 + len(data), cmd, 0, 0, 0]) + bytes(data) + b"\x03"
    bcc = 0
    for x in body: bcc ^= x
    return b"\x02" + body + bytes([bcc])

def main(a):
    if not a: print(__doc__); return
    if a[0] == "decode":
        buf = open(a[1], "rb").read()[:SIZE]
        ok, ver, why = check(buf)
        print("valid" if ok else "INVALID: " + "; ".join(why), "| version", ver)
        for k, v in decode(buf).items(): print("%-26s %s" % (k, v))
    elif a[0] == "new":
        name = a[a.index("--name") + 1] if "--name" in a else "マリオ"
        open(a[1], "wb").write(new_card(name)); print("wrote", a[1])
    elif a[0] == "set":
        buf = bytearray(open(a[1], "rb").read()[:SIZE])
        lay = layout(SCHEMAS["v%d" % get(buf, HDR, "VERSION")])
        for kv in a[3:]:
            k, v = kv.split("=", 1)
            idx = 0
            if "[" in k: k, idx = k[:-1].split("["); idx = int(idx)
            if k == "NAME":
                for i, c in enumerate(encode_name(v)): put(buf, lay, "NAME", c, i)
            else:
                put(buf, lay, k, int(v, 0), idx)
        fix_checksum(buf); open(a[2], "wb").write(buf); print("wrote", a[2])
    elif a[0] == "frame":
        cmd = int(a[1], 16)
        if cmd == 0x33: data = b"010"          # mode 0 (69B), 8bit no parity, track 1
        elif cmd == 0x53: data = (b"010" + open(a[2], "rb").read()[:SIZE]).ljust(0x48, b"\0")
        else: data = b""
        print(frame(cmd, data).hex(" "))

if __name__ == "__main__":
    main(sys.argv[1:])
