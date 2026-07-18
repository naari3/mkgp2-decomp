#!/usr/bin/env python3
"""Reorder extab/extabindex entries in a CW .o into a declared order.

Why: a mixed TU (some functions with CW auto-emitted extab under
#pragma exceptions on, others with manual .extab_user emission) produces TWO
sections named extab / extabindex, and mwld concatenates them in
section-index order (auto pair first) — NOT interleaved. Converting one
mid-TU function from manual to auto therefore moves its extab entry to the
front and breaks SHA-1 (confirmed experimentally 2026-07-19).

The target extab order is NOT reliably function-address order either
(auto_800A8F4C_block: the last function's entry sits FIRST in the target
extab — original-TU link-order artefacts survive in the binary). So this
tool does not guess: the desired order is declared per TU in
tools/extab_order.json:

  {
    "src/game/ServiceMenu_Page.c": [
      "ServiceMenu_Draw", "ServiceMenu_Tick", "ServiceMenu_Dtor",
      "ServiceMenu_Init"
    ],
    "src/game/auto_ONKARTHIT_block.c": {
      "extab":      ["dtor_...", "KartItem_...", "..."],
      "extabindex": ["KartItem_...", "dtor_...", "..."]
    }
  }

Names are the FUNCTIONS the entries describe (resolved via the extabindex
fn relocations). A plain list declares one order used for both sections;
the object form declares extab and extabindex orders separately (they are
independent in the target: extabindex is address-sorted while extab keeps
original link-order artefacts, e.g. auto_800A8F4C_block). Objects without
a declaration are never touched, regardless of section layout.

Called from tools/postprocess_extab_user.py after the rename/redefine step
(before `dtk extab clean`). The TU is identified by matching the declared
function-name set against the object's entries.
"""
from __future__ import annotations

import json
import struct
import sys
from pathlib import Path

ORDER_JSON = Path(__file__).resolve().parent / "extab_order.json"


def u16(b: bytes, o: int) -> int:
    return int.from_bytes(b[o:o + 2], "big")


def u32(b: bytes, o: int) -> int:
    return int.from_bytes(b[o:o + 4], "big")


class Elf:
    def __init__(self, data: bytes):
        self.data = bytearray(data)
        d = self.data
        if d[:4] != b"\x7fELF" or d[5] != 2:
            raise ValueError("not a big-endian ELF")
        self.shoff = u32(d, 0x20)
        self.shentsize = u16(d, 0x2E)
        self.shnum = u16(d, 0x30)
        self.shstrndx = u16(d, 0x32)
        self.secs = []
        shstr_off = u32(d, self.shoff + self.shstrndx * self.shentsize + 0x10)
        for i in range(self.shnum):
            h = self.shoff + i * self.shentsize
            name_off = u32(d, h)
            end = d.index(b"\0", shstr_off + name_off)
            s = {
                "i": i,
                "name": bytes(d[shstr_off + name_off:end]).decode(),
                "name_off": name_off,
                "type": u32(d, h + 0x04),
                "flags": u32(d, h + 0x08),
                "addr": u32(d, h + 0x0C),
                "off": u32(d, h + 0x10),
                "size": u32(d, h + 0x14),
                "link": u32(d, h + 0x18),
                "info": u32(d, h + 0x1C),
                "align": u32(d, h + 0x20),
                "entsize": u32(d, h + 0x24),
            }
            s["data"] = bytes(d[s["off"]:s["off"] + s["size"]]) if s["type"] != 8 else b""
            self.secs.append(s)

    def symtab(self):
        return next(s for s in self.secs if s["type"] == 2)

    def strtab(self):
        return self.secs[self.symtab()["link"]]

    def symbols(self):
        st = self.symtab()
        strd = self.strtab()["data"]
        out = []
        for i in range(0, st["size"], 16):
            b = st["data"][i:i + 16]
            no = u32(b, 0)
            end = strd.index(b"\0", no)
            out.append({
                "idx": i // 16,
                "name": strd[no:end].decode("ascii", errors="replace"),
                "value": u32(b, 4), "size": u32(b, 8),
                "info": b[12], "shndx": u16(b, 14),
            })
        return out

    def rewrite(self) -> bytes:
        d = self.data
        out = bytearray(d[:0x34])
        pos = 0x34
        for s in self.secs:
            if s["i"] == 0 or s["type"] == 8:
                continue
            align = max(s["align"], 1)
            pad = (-pos) % align
            out += b"\0" * pad
            pos += pad
            s["off"] = pos
            out += s["data"]
            pos += len(s["data"])
        pad = (-pos) % 4
        out += b"\0" * pad
        pos += pad
        shoff = pos
        for s in self.secs:
            out += struct.pack(
                ">10I", s["name_off"], s["type"], s["flags"], s["addr"],
                s["off"] if s["i"] else 0,
                len(s["data"]) if s["type"] != 8 else s["size"],
                s["link"], s["info"], s["align"], s["entsize"],
            )
        out[0x20:0x24] = struct.pack(">I", shoff)
        return bytes(out)


def parse_relas(sec):
    return [{"off": u32(sec["data"], i), "info": u32(sec["data"], i + 4),
             "addend": u32(sec["data"], i + 8)}
            for i in range(0, len(sec["data"]), 12)]


def main() -> int:
    if len(sys.argv) != 2:
        sys.exit("usage: reorder_extab.py <object.o>")
    path = Path(sys.argv[1])
    if not ORDER_JSON.is_file():
        return 0
    orders = json.loads(ORDER_JSON.read_text(encoding="utf-8"))
    if not orders:
        return 0

    elf = Elf(path.read_bytes())
    etabs = [s for s in elf.secs if s["name"] == "extab" and s["type"] == 1]
    eidxs = [s for s in elf.secs if s["name"] == "extabindex" and s["type"] == 1]
    if not etabs or not eidxs:
        return 0

    syms = elf.symbols()
    etab_ids = {s["i"] for s in etabs}
    eidx_ids = {s["i"] for s in eidxs}

    idx_relas, etab_relas = [], []
    for rs in elf.secs:
        if rs["type"] != 4:
            continue
        if rs["info"] in eidx_ids:
            idx_relas += [(rs["info"], r) for r in parse_relas(rs)]
        elif rs["info"] in etab_ids:
            etab_relas += [(rs["info"], r) for r in parse_relas(rs)]

    # collect entries: (isec, ioff) -> fn name + extab location
    entries = []
    for isec in sorted(eidx_ids):
        for ioff in range(0, len(elf.secs[isec]["data"]), 12):
            fn_name = None
            esec = eoff = None
            for tsec, r in idx_relas:
                if tsec != isec:
                    continue
                if r["off"] == ioff:
                    s = syms[r["info"] >> 8]
                    if (s["info"] & 0xF) == 3:  # section-relative fn ref
                        fn_name = None  # resolve below by addr if needed
                        fn_off = r["addend"]
                        # find function symbol at that offset
                        cand = [x for x in syms
                                if x["shndx"] == s["shndx"] and x["value"] == fn_off
                                and (x["info"] & 0xF) in (0, 2) and x["name"]]
                        if cand:
                            fn_name = cand[0]["name"]
                    else:
                        fn_name = s["name"]
                elif r["off"] == ioff + 8:
                    s = syms[r["info"] >> 8]
                    if (s["info"] & 0xF) == 3:
                        esec, eoff = s["shndx"], r["addend"]
                    else:
                        esec, eoff = s["shndx"], s["value"] + r["addend"]
            if fn_name is None or esec is None:
                return 0  # can't resolve safely -> leave object alone
            entries.append({"isec": isec, "ioff": ioff, "fn": fn_name,
                            "esec": esec, "eoff": eoff})

    # match a declared order by function-name set.
    # extab entries can be SHARED by multiple functions (observed in
    # auto_ONKARTHIT_block: 76 extabindex rows, 62 extab entries), so the
    # extab list names one REPRESENTATIVE fn per unique entry while the
    # extabindex list names every fn.
    by_fn = {e["fn"]: e for e in entries}
    uniq_keys = {(e["esec"], e["eoff"]) for e in entries}
    e_order_names = i_order_names = None
    fn_set = set(by_fn)
    for tu, decl in orders.items():
        if isinstance(decl, dict):
            en, inames = decl.get("extab"), decl.get("extabindex")
        else:
            en = inames = decl
        if not en or not inames:
            continue
        if set(inames) != fn_set or len(inames) != len(entries):
            continue
        if not set(en) <= fn_set:
            continue
        keys = [(by_fn[n]["esec"], by_fn[n]["eoff"]) for n in en]
        if len(keys) != len(uniq_keys) or set(keys) != uniq_keys:
            continue
        e_order_names, i_order_names = en, inames
        break
    if e_order_names is None:
        return 0
    if ([e["fn"] for e in entries] == i_order_names
            and len(etabs) == 1 and len(eidxs) == 1):
        return 0  # single pair already in declared index order

    order = [by_fn[n] for n in e_order_names]       # extab placement order
    iorder = [by_fn[n] for n in i_order_names]      # extabindex placement order

    # entry boundaries per extab section
    starts = {i: sorted({e["eoff"] for e in entries if e["esec"] == i})
              for i in etab_ids}
    esize = {}
    for i, ss in starts.items():
        secsz = len(elf.secs[i]["data"])
        for k, stt in enumerate(ss):
            end = ss[k + 1] if k + 1 < len(ss) else secsz
            esize[(i, stt)] = end - stt

    def pick_host(secs, relas):
        with_rela = [s for s in secs if any(t == s["i"] for t, _ in relas)]
        return (with_rela or secs)[0]

    host_e = pick_host(etabs, etab_relas)
    host_i = pick_host(eidxs, idx_relas)

    new_eoff, blob = {}, bytearray()
    for e in order:
        key = (e["esec"], e["eoff"])
        if key in new_eoff:
            continue  # shared entry already placed
        sz = esize[key]
        new_eoff[key] = len(blob)
        blob += elf.secs[e["esec"]]["data"][e["eoff"]:e["eoff"] + sz]
    new_ioff, iblob = {}, bytearray()
    for e in iorder:
        new_ioff[(e["isec"], e["ioff"])] = len(iblob)
        iblob += elf.secs[e["isec"]]["data"][e["ioff"]:e["ioff"] + 12]

    for s in etabs:
        s["data"] = bytes(blob) if s["i"] == host_e["i"] else b""
    for s in eidxs:
        s["data"] = bytes(iblob) if s["i"] == host_i["i"] else b""

    # move entry symbols into hosts
    sec_sym = {s["shndx"]: s["idx"] for s in syms if (s["info"] & 0xF) == 3}
    st = elf.symtab()
    stdata = bytearray(st["data"])
    for s in syms:
        if (s["info"] & 0xF) == 3:
            continue
        if s["shndx"] in etab_ids and (s["shndx"], s["value"]) in new_eoff:
            struct.pack_into(">I", stdata, s["idx"] * 16 + 4,
                             new_eoff[(s["shndx"], s["value"])])
            struct.pack_into(">H", stdata, s["idx"] * 16 + 14, host_e["i"])
        elif s["shndx"] in eidx_ids and (s["shndx"], s["value"]) in new_ioff:
            struct.pack_into(">I", stdata, s["idx"] * 16 + 4,
                             new_ioff[(s["shndx"], s["value"])])
            struct.pack_into(">H", stdata, s["idx"] * 16 + 14, host_i["i"])
    st["data"] = bytes(stdata)
    syms = elf.symbols()

    def entry_base(esec, off):
        base = 0
        for stt in reversed(starts[esec]):
            if stt <= off:
                base = stt
                break
        return base

    new_etab, new_idx = [], []
    for tsec, r in etab_relas:
        base = entry_base(tsec, r["off"])
        new_etab.append({**r, "off": new_eoff[(tsec, base)] + (r["off"] - base)})
    for tsec, r in idx_relas:
        base = (r["off"] // 12) * 12
        delta = r["off"] - base
        r2 = {**r, "off": new_ioff[(tsec, base)] + delta}
        s = syms[r["info"] >> 8]
        if delta == 8 and (s["info"] & 0xF) == 3 and s["shndx"] in etab_ids:
            r2["addend"] = new_eoff[(s["shndx"], r["addend"])]
            r2["info"] = (sec_sym[host_e["i"]] << 8) | (r["info"] & 0xFF)
        new_idx.append(r2)

    def pack(relas):
        relas = sorted(relas, key=lambda r: r["off"])
        return b"".join(struct.pack(">3I", r["off"], r["info"], r["addend"])
                        for r in relas)

    host_e_rela = next((rs for rs in elf.secs if rs["type"] == 4
                        and rs["info"] == host_e["i"]), None)
    host_i_rela = next((rs for rs in elf.secs if rs["type"] == 4
                        and rs["info"] == host_i["i"]), None)
    if new_etab:
        if host_e_rela is None:
            sys.exit(f"reorder_extab: no rela section for host extab in {path}")
        host_e_rela["data"] = pack(new_etab)
    if host_i_rela is None:
        sys.exit(f"reorder_extab: no rela section for host extabindex in {path}")
    host_i_rela["data"] = pack(new_idx)
    for rs in elf.secs:
        if rs["type"] != 4:
            continue
        if rs["info"] in etab_ids and rs is not host_e_rela:
            rs["data"] = b""
        elif rs["info"] in eidx_ids and rs is not host_i_rela:
            rs["data"] = b""

    path.write_bytes(elf.rewrite())
    print(f"reorder_extab: applied declared order ({len(order)} entries, "
          f"{path.name})")
    return 0


if __name__ == "__main__":
    sys.exit(main())
