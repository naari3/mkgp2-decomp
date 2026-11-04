# dn-static-initializers-native

Source: Codex worker cxc_u14_dn223_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 4 fn / 928 B.

Observed: GC/2.6 reproduces fn_80227FA4 exactly with angle factor literal 0.017453288659453392f; an extern factor load produces 97.70588% and adding a named factor local is byte-invariant. Existing postprocess_sdata2 maps the literal to lbl_806DB488. fn_80228D64 matches from sixteen explicit min/max helper calls in min-then-max order. fn_80228F80/98 match float ternaries and share an EH-free 48-byte contiguous target blob. All four text sections and static-initializer extab/extabindex/ctors compare 100%; full link/SHA-1 pending. Renderer fn_8022BFA8 best 84.24808% after three structural approaches; copied local Vec3c with inline empty destructor naturally emits DESTROYLOCAL but PC range and owned EH remain mismatched.
