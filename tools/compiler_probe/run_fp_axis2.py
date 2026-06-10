import os
from probe_fp import probe, ROOT

CC = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2", "mwcceppc.exe")

PRAGMAS = [
    "peephole off",
    "scheduling off",
    "global_optimizer off",
    "global_optimizer on",
    "optimize_for_size on",
    "optimization_level 0",
    "optimization_level 1",
    "optimization_level 2",
    "optimization_level 3",
    "optimization_level 4",
    "opt_propagation off",
    "opt_dead_code off",
    "opt_dead_assignments off",
    "opt_lifetimes off",
    "opt_common_subs off",
    "opt_strength_reduction off",
    "opt_strength_reduction_strict on",
    "opt_loop_invariants off",
    "opt_unroll_loops off",
    "opt_vectorize_loops off",
    "opt_pointer_analysis off",
    "ppc_opt_bclr_bcctr off",
    "ppc_opt_bclr_bcctr on",
    "gen_fsel off",
    "gen_fsel always",
    "gen_isel on",
    "defer_codegen on",
    "defer_codegen off",
    "inline_bottom_up on",
    "inline_bottom_up off",
    "auto_inline off",
    "optimizewithasm on",
    "optimizewithasm off",
    "disable_registers on",
    "profile on",
    "ibm_stackframe on",
    "no_register_save_helpers on",
    "switch_tables off",
    "prepare_compress on",
    "gprfloatcopy off",
    "block_assign on",
    "has8bytebitfields on",
    "optEH off",
    "optEH2 off",
    "suppress_init_code on",
    "side_effects off",
    "explicit_zero_data on",
    "readonly_strings on",
    "misaligned_mem_access on",
    "misaligned_mem_access off",
    "unsafe_global_reg_vars on",
    "ignore_global_reg_vars on",
    "longlong_prepeval on",
    "float_constants on",
    "experimental on",
    "gcc_extensions on",
    "cpp_extensions off",
    "ANSI_strict on",
    "defer_codegen on\n#pragma peephole off",
    "peephole off\n#pragma scheduling off",
    "global_optimizer off\n#pragma peephole off",
    "global_optimizer off\n#pragma peephole off\n#pragma scheduling off",
]

lines = []
for p in PRAGMAS:
    tag = "pragma:" + p.replace("\n#pragma ", " + ")
    prelude = "#pragma warn_illpragma on\n#pragma " + p
    lines.append(probe(tag, CC, prelude=prelude))

with open("results_fp_axis2.tsv", "w") as f:
    f.write("\n".join(lines) + "\n")
