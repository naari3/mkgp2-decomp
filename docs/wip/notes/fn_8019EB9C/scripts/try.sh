cd /home/user/mkgp2-decomp
ninja build/GNLJ82/src/game/kartmove/carobject.o >/dev/null 2>&1 || { echo BUILD FAIL; exit 1; }
B=build/binutils
for o in obj src; do build/binutils/powerpc-eabi-objdump -d --no-show-raw-insn build/GNLJ82/$o/game/kartmove/carobject.o | awk '/<fn_8019EB9C>:/,/blr/' | tail -n +2 | cut -f2- > /tmp/claude-0/$o.s; done
diff /tmp/claude-0/obj.s /tmp/claude-0/src.s | grep -c '^[<>]'
