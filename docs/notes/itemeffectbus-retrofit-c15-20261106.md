# itemeffectbus-retrofit-c15-20261106

Source: Codex worker c15_a89_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 10 fn / 1844 B.

# ItemEffectBus C retrofit, c15_a89_20261106

Ten functions / 1844 bytes promoted to genuine C. Four original asm bodies retained byte-identically. No source draft blocks remain.

History: 7406f906 introduced this TU as an asm fallback bundle, with no per-function natural-C rejection rationale in the commit. The two CW132 notes document its aligned u64 argument ABI. All target EH entries are 8 bytes without actions.

The converted functions use a private layout header, ordinary u64 expressions, scoped `#pragma exceptions on`, and `#pragma auto_inline off` to preserve the original calls. The manual EH arrays/index objects for converted functions were removed. The remaining four manual EH entries are unchanged.

ApplyItemEventSet matched after accumulating `add |= bus->mask` before Commit. Its generated switch table is now owned by the same TU (.data 0x803FF968..0x803FFDF0), with one new scoped rename @153 -> jumptable_803FF968. No padding, section-forcing additions, build-flag changes, TU splits, or shared-header changes.

Partial C drafts below are documentation only. ClearByTable8 and TickTornadoCooldown require their high-word declarations to be `extern const ItemEffectMask lbl_...;` in the u64-load drafts. Other scalar constants remain existing unsigned-int externs. These typed-load drafts have relocation-identity differences and are not counted as matches.

### ItemEffectBus_ClearByTable8

Native u64 constants reproduce all instructions but the low-half relocations use high_label+4 rather than the separate low-word symbols. Explicit split-word construction changes scratch-register allocation (97.741936%). Attempted high-symbol size 8 / low-symbol size 0 was rejected by dtk as overlapping; restored symbols.txt exactly. Original asm preserved.

```c
void ItemEffectBus_ClearByTable8(ItemEffectBus *bus, unsigned int table)
{
    ItemEffectMask clear = 0;
    if (table & 0x1) clear |= lbl_806D34B8;
    if (table & 0x2) clear |= lbl_806D34C0;
    if (table & 0x4) clear |= lbl_806D34C8;
    if (table & 0x8) clear |= lbl_806D34D0;
    if (table & 0x10) clear |= lbl_806D34D8;
    if (table & 0x20) clear |= lbl_806D34E0;
    if (table & 0x40) clear |= lbl_806D34E8;
    if (table & 0x80) clear |= lbl_806D34F0;
    ItemEffectBus_Commit(bus, bus->mask & ~clear);
}
```

### ItemEffectBus_TickTornadoCooldown

u64 constant load produces identical instructions but the low-half relocation is lbl_806D3570+4 rather than lbl_806D3574. Split expression gives 99.6% with scratch r4 instead of r0; explicit high/low locals gives 91.6%. Original asm preserved.

```c
void ItemEffectBus_TickTornadoCooldown(ItemEffectBus *bus)
{
    ItemEffectMask clear = 0xC000000000000000ULL;
    if (bus->tornadoCooldown > 0)
        bus->tornadoCooldown--;
    else
        clear |= lbl_806D3570;
    ItemEffectBus_Commit(bus, bus->mask & ~clear);
}
```

### ItemEffectBus_ApplyItemConfirm

Split locals first gave 82.07101%; using one u64 state and target case-body order gives 98.34319%. Constructed constant halves occupy r4/r0 instead of r0/r4. A generic inline high/low mask constructor produced identical residual; stopped. Original asm preserved.

```c
void ItemEffectBus_ApplyItemConfirm(ItemEffectBus *bus, int event)
{
    ItemEffectMask mask = bus->mask;
    switch (event) {
    case 0x142: mask |= ((ItemEffectMask)lbl_806D3508 << 32) | lbl_806D350C; break;
    case 0x22: mask |= ((ItemEffectMask)lbl_806D3510 << 32) | lbl_806D3514; break;
    case 0x1B: mask |= ((ItemEffectMask)lbl_806D3518 << 32) | lbl_806D351C; break;
    case 0x2C: mask |= ((ItemEffectMask)lbl_806D3520 << 32) | lbl_806D3524; break;
    case 0x3C: mask |= ((ItemEffectMask)lbl_806D3528 << 32) | lbl_806D352C; break;
    case 0x23: mask |= ((ItemEffectMask)lbl_806D3530 << 32) | lbl_806D3534; break;
    case 0x52: mask |= ((ItemEffectMask)lbl_806D3538 << 32) | lbl_806D353C; break;
    case 0x1D: mask |= ((ItemEffectMask)lbl_806D3540 << 32) | lbl_806D3544; break;
    case 0x1A: mask |= ((ItemEffectMask)lbl_806D3508 << 32) | lbl_806D350C; break;
    case 0x9B: mask |= ((ItemEffectMask)lbl_806D3548 << 32) | lbl_806D354C; break;
    case 0xE:
    case 0x10:
    case 0x15:
    case 0x16:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x24:
    case 0x28:
        mask |= 0x10020000040ULL; break;
    case 0x21: mask = 0x8000000080ULL; break;
    case 0x1C: mask = 0x8000000000ULL; break;
    case 0xC:
    case 0xD:
    case 0xF:
    case 0x11:
    case 0x13:
    case 0x14:
    case 0x18:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x8B:
    case 0x91:
        mask |= 0x140ULL; break;
    case 0x99: mask |= ((ItemEffectMask)lbl_806D3550 << 32) | lbl_806D3554; break;
    case 0x9A: mask |= ((ItemEffectMask)lbl_806D3558 << 32) | lbl_806D355C; break;
    case 0x8C: mask |= ((ItemEffectMask)lbl_806D3560 << 32) | lbl_806D3564; break;
    case 0x9D: mask |= ((ItemEffectMask)lbl_806D3568 << 32) | lbl_806D356C; break;
    }
    ItemEffectBus_Commit(bus, mask);
}
```

### ItemEffectBus_ApplyItemEventClear

Natural u64-table version gives 92.50944%; split high/low table accumulation gives 96.169815%. Residual includes table-symbol ownership, scratch-register identities, driver-byte-store scheduling, redundant target timer reset, and the target AND-with-all-ones path. Did not add a redundant timer store or fake operations to recover missing bytes. Original asm preserved.

```c
void ItemEffectBus_ApplyItemEventClear(ItemEffectBus *bus, unsigned int event)
{
    unsigned int table = 0;
    unsigned int high, low;
    bus->timer28 = 0.0f;
    switch (event) {
    case 0x2B:
    case 0x2D:
    case 0x46:
    case 0x4A:
    case 0x4B:
    case 0x50:
    case 0x5B:
    case 0x5C:
    case 0x5D:
    case 0x8D:
        table = lbl_806D34F8; break;
    case 0x3C:
    case 0x71:
    case 0x72:
    case 0x73:
        table = lbl_806D34FC; break;
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x18:
    case 0x19:
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x8B:
    case 0x91:
        table = lbl_806D3500; break;
    case 0x1A:
    case 0x23:
        table = lbl_806D3500;
        ((unsigned char *)bus->driver)[0x2B1] = 0; break;
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
    case 0x5:
    case 0x6:
    case 0x8:
    case 0x9:
    case 0xB:
    case 0x12:
    case 0x2E:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x37:
    case 0x38:
    case 0x3D:
    case 0x3E:
    case 0x3F:
    case 0x45:
    case 0x4D:
    case 0x4F:
    case 0x5F:
    case 0x60:
    case 0x61:
    case 0x63:
    case 0x6A:
    case 0x70:
    case 0x76:
    case 0x89:
    case 0x8A:
    case 0x96:
    case 0x11C:
    case 0x121:
        table = lbl_806D3504; break;
    case 0x59:
        ItemEffectBus_Commit(bus, bus->mask & ~0x800000ULL); break;
    case 0x5A:
        ItemEffectBus_Commit(bus, bus->mask); break;
    case 0x74:
        ItemEffectBus_Commit(bus, bus->mask & ~0x40000000ULL); break;
    case 0x75:
        ItemEffectBus_Commit(bus, bus->mask & ~0x1000000000ULL); break;
    case 0x55:
        ItemEffectBus_Commit(bus, bus->mask & ~0x800000000ULL); break;
    case 0x85:
        ItemEffectBus_Commit(bus, bus->mask & ~0x800000000ULL); break;
    case 0x58:
        ItemEffectBus_Commit(bus, bus->mask & ~0x2000000000ULL); break;
    case 0x98:
        ItemEffectBus_Commit(bus, bus->mask & ~0x100000000000ULL); break;
    case 0x95:
        ItemEffectBus_Commit(bus, bus->mask & ~0x2000000000000ULL); break;
    case 0x88:
        ItemEffectBus_Commit(bus, bus->mask & ~0x4000000000000ULL); break;
    case 0x8F:
        ItemEffectBus_Commit(bus, bus->mask & ~0x8000000000000ULL); break;
    case 0x93:
        ItemEffectBus_Commit(bus, bus->mask & ~0x10000000000000ULL); break;
    case 0x94:
        ItemEffectBus_Commit(bus, bus->mask & ~0x20000000000000ULL); break;
    case 0x68:
    case 0x79:
        ItemEffectBus_Commit(bus, bus->mask & ~0x4000000000ULL); break;
    case 0x99:
        ItemEffectBus_Commit(bus, bus->mask & ~0x800000000000ULL); break;
    case 0x9A:
        ItemEffectBus_Commit(bus, bus->mask & ~0x400000000000ULL); break;
    case 0x8C:
        ItemEffectBus_Commit(bus, bus->mask & ~0x1000000000000ULL); break;
    case 0x9B:
        ItemEffectBus_Commit(bus, bus->mask & ~0x400200000000000ULL); break;
    case 0x9D:
        ItemEffectBus_Commit(bus, bus->mask & ~0x40000000000ULL); break;
    case 0x9E:
        ItemEffectBus_Commit(bus, bus->mask & ~0x80000000000ULL); break;
    default: return;
    }
    high = low = 0;
    if (table & 0x1) { high |= lbl_806D34B8; low |= lbl_806D34BC; }
    if (table & 0x2) { high |= lbl_806D34C0; low |= lbl_806D34C4; }
    if (table & 0x4) { high |= lbl_806D34C8; low |= lbl_806D34CC; }
    if (table & 0x8) { high |= lbl_806D34D0; low |= lbl_806D34D4; }
    if (table & 0x10) { high |= lbl_806D34D8; low |= lbl_806D34DC; }
    if (table & 0x20) { high |= lbl_806D34E0; low |= lbl_806D34E4; }
    if (table & 0x40) { high |= lbl_806D34E8; low |= lbl_806D34EC; }
    if (table & 0x80) { high |= lbl_806D34F0; low |= lbl_806D34F4; }
    ItemEffectBus_Commit(bus, bus->mask & ~(((ItemEffectMask)high << 32) | low));
}
```

