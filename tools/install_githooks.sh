#!/bin/sh
# Install the repo's git hooks and say which side of the agent board you are.
#   sh tools/install_githooks.sh n3   # naari3's threads
#   sh tools/install_githooks.sh om   # onmokoworks's workers
# After this, every git pull / rebase prints the board messages still open
# for you (nothing when there are none). Undo: git config --unset core.hooksPath
set -e
side="${1:-}"
case "$side" in n3|om) ;; *) echo "usage: sh tools/install_githooks.sh n3|om"; exit 2;; esac
cd "$(git rev-parse --show-toplevel)"
existing="$(git config --get core.hooksPath || true)"
if [ -n "$existing" ] && [ "$existing" != "tools/githooks" ]; then
  echo "core.hooksPath is already '$existing'; add tools/githooks/post-merge and post-rewrite there instead."
  git config mkgp2.agentSide "$side"
  exit 0
fi
chmod +x tools/githooks/* 2>/dev/null || true
git config core.hooksPath tools/githooks
git config mkgp2.agentSide "$side"
echo "hooks: core.hooksPath=tools/githooks, agent side=$side"
python3 tools/agent_board.py open --quiet || true
