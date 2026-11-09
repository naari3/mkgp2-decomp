#!/bin/bash
# cc.sh file.c [ver] -> disasm of .o
cd /home/user/mkgp2-decomp
v=${2:-1.3.2}
o=/tmp/claude-0/mt/out.o
build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/$v/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -O4,p -inline auto -pragma "cats off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -lang=c -use_lmw_stmw on -c "$1" -o $o >/dev/null || exit 1
build/tools/dtk elf disasm $o /tmp/claude-0/mt/out.s >/dev/null && grep -v '^\s*$' /tmp/claude-0/mt/out.s | sed -n '/^.fn/,/^.endfn/p' | cut -f2- | grep -v '^#'
