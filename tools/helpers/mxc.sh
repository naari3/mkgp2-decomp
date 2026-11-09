cd "$(git rev-parse --show-toplevel)"
f=$1; shift
python3 $(dirname $0)/cmp.py $f --cc GC/1.3.2 --preset base -i ${MUSYX:-/home/claude/refs/musyx}/include -i ${MUSYX:-/home/claude/refs/musyx}/src/musyx/runtime -i include/libc -DMUSY_TARGET=1 "$@" 2>&1
