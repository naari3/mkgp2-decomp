#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "GNLJ82",  # 0 — Mario Kart Arcade GP2 (Triforce, JP)
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-multibyte",  # For Wii compilers, replace with `-enc SJIS`
    "-i include",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-sdata 0",
    "-sdata2 0",
]

config.linker_version = "GC/1.3.2"

# Per-lib compiler (mwcceppc) versions. `config.linker_version` above is only
# the final linker (mwldeppc); each lib picks its own compiler below.
mw_version_init = "GC/1.0"      # confirmed against __check_pad3 prologue
mw_version_init_sdk = "GC/2.7"  # tentative: memset/__fill_mem/memcpy in .init use stwu-first prologue (newer CW)
mw_version_hsd  = "GC/1.3.2"    # SSBM uses GC/1.2.5n but mkgp2 prologue is stwu-first / lr@0x24 = newer CW


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "progress_category": "game",
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "init",
        "mw_version": mw_version_init,
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": [
            Object(Matching, "init/__check_pad3.c"),
            Object(Matching, "init/debug_bba.c"),
        ],
    },
    {
        "lib": "init_sdk",
        "mw_version": mw_version_init_sdk,
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "init/__init_hardware.c"),
            Object(Matching, "init/__flush_cache.c"),
            Object(Matching, "init/fn_80003458.c"),
            Object(Matching, "init/fn_80003488.c"),
            Object(Matching, "init/fn_800053E0.c"),
            Object(Matching, "init/memset.c"),
            Object(Matching, "init/__fill_mem.c"),
            Object(Matching, "init/memcpy.c"),
        ],
    },
    {
        "lib": "sysdolphin",
        "mw_version": mw_version_hsd,
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "sysdolphin/baselib/_hsd_consts.c"),
            Object(Matching, "sysdolphin/baselib/aobj.c"),
            Object(Matching, "sysdolphin/baselib/dobj.c"),
            Object(Matching, "sysdolphin/baselib/fobj.c"),  # TEST: post-process fobj.o with _externize_sdata2.py
            Object(Matching, "sysdolphin/baselib/jobj.c"),
            Object(NonMatching, "sysdolphin/baselib/jobj_anim_all.c"),
            Object(Matching, "sysdolphin/baselib/jobj_anim_misc.c"),
            Object(Matching, "sysdolphin/baselib/robj.c"),
        ],
    },
    {
        "lib": "game_extab",
        "mw_version": "GC/1.3.2",
        "cflags": [*cflags_base, "-Cpp_exceptions on"],
        "progress_category": "game",
        "objects": [
            # 1 TU = 1 dtk reversed-extab group bundle (6 functions).
            # Phase 1b: held as Matching with all 6 fns as asm_fn + manually
            # emitted extab/extabindex (via __declspec(section ".extab_user")
            # + tools/postprocess_extab_user.py rename). The extab_padding
            # kwarg routes this TU through the mwcc_sjis_extab build rule so
            # the postprocess hook runs.
            Object(Matching, "game/HeapStats.c", extab_padding=b"\x00\x00"),
                    Object(Matching, "game/auto_800A8F4C_block.c", extab_padding=b"\x00\x00"),
],
    },
    {
        "lib": "game",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": [
            Object(Matching, "game/Vtable_CallSlot2.cpp"),
            Object(Matching, "game/ObjectBase.c"),
            Object(Matching, "game/CardTaskWelcome_Dtor.c"),
            Object(Matching, "game/clCGameDemo_Dtor.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/BtMode_BaseDtor.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/GameMode_Base.c"),
            Object(Matching, "game/Debug.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Camera.c"),
            Object(Matching, "game/Profiler.c"),
            Object(Matching, "game/Profiler_RecordFrame.c"),
            Object(Matching, "game/SceneRender.c"),
            Object(Matching, "game/Archive.c"),
            Object(Matching, "game/CollisionFile_FixupPointers.c"),
            Object(Matching, "game/Collision.c"),
            Object(Matching, "game/StrPcb_988.c"),
            Object(Matching, "game/StrPcb.c"),
            Object(Matching, "game/Clamp.c"),
            Object(Matching, "game/InputMgr_GetPlayer.c"),
            Object(Matching, "game/InputMgr.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/DMAChannelManager_Init.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/InputObj.c"),
            Object(Matching, "game/InputObj_Ctor.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemHolder.c"),
            Object(Matching, "game/ItemRes_Thunk.c"),
            Object(Matching, "game/dtor_8024F40C.c"),
            Object(Matching, "game/dtor_80091284.c"),
            Object(Matching, "game/PathCursor_ResetToPath.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/PathCursor_Free.c"),
            Object(Matching, "game/PathManager_Lookups.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/PathManager_RefreshFinishPositions.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/dtor_8006178C.c"),
            Object(Matching, "game/dtor_80064CD4.c"),
            Object(Matching, "game/LakituStart_Dtor.c"),
            Object(Matching, "game/dtor_801EECD8.c"),
            Object(Matching, "game/dtor_801F8214.c"),
            Object(Matching, "game/TexMgr_Init.c"),
            Object(Matching, "game/dtor_80209180.c"),
            Object(Matching, "game/dtor_801FE870.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/dtor_801FEA70.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/GetCourseSectionType.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/InitRumbleController.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/LapDisp_SetTotalLaps.c"),
            Object(Matching, "game/LapDisp_SetCurrentLap.c"),
            Object(Matching, "game/HUD_SetRacePosition.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/RnkDisp_SetPosition.c"),
            Object(Matching, "game/HUD_SetTotalLaps.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/HUD_SetCurrentLap.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/BootNotice_CheckEnterCondition.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/BootPCBCheck_Init.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/GetTextureByIdAndLang.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemDisplay_Stop.c"),
            Object(Matching, "game/ItemDisplay_Destroy.c"),
            Object(Matching, "game/ItemDisplay_GetOrCreate.c"),
            Object(Matching, "game/ItemSelect.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/DisplayBuffer_GetByIndex.c"),
            Object(Matching, "game/GX_BeginDraw.c"),
            Object(Matching, "game/TexMgr_Apply.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/ProcessSystemTick.c"),
            Object(Matching, "game/NokoNoko_CountDefeated.c"),
            Object(Matching, "game/NokoNoko.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/GameModeBase.cpp"),
            Object(Matching, "game/KartMovement_SetPosition.c"),
            Object(Matching, "game/NamCam_LoadImage.c"),
            Object(Matching, "game/ISESlot_Deactivate.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CourseAuxClass_VtableDtor.c"),
            Object(Matching, "game/dtor_8021617C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/WarpZone_Dtor.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/LiveConn.c"),
            Object(Matching, "game/PlaySoundDSP.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "ui/CursorSound.c"),
            Object(Matching, "game/InitBGM.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/dtor_801BA14C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "ui/FrameSelection.c"),
            Object(Matching, "ui/UI_PlaySeToggle.c"),
            Object(Matching, "ui/UISoundClSound4D.c"),
            Object(Matching, "ui/UI_PlaySeDecide.c"),
            Object(Matching, "game/CarObject_ResetPhysics.c"),
            Object(Matching, "game/KartBody.c"),
            Object(Matching, "game/KartMovement.c"),
            Object(Matching, "game/KartMovement_GetVelocityMagnitude.c"),
            Object(Matching, "game/KartMovement_CanReceiveItem.c"),
            Object(Matching, "game/KartMovement_GetCurrentItemId.c"),
            Object(Matching, "game/KartReaction.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/LakituStart.c"),
            Object(Matching, "game/CourseData.c"),
            Object(Matching, "game/GlobalTimer.c"),
            Object(Matching, "game/PhysicsState.c"),
            Object(Matching, "game/Rand.c"),
            Object(Matching, "game/RaceScene_PlayerSlots.c"),
            Object(Matching, "game/RivalRun_PathFollowerInit.c"),
            Object(Matching, "game/GameModeBase_FrameUpdate2.cpp"),
            Object(Matching, "game/SpawnTable.c"),
            Object(Matching, "game/VBlank.c"),
            Object(Matching, "game/SyncSlot.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SyncSlot_ApplyCourseChoice.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/PCBComm_PromoteToClientConfirmed.c"),
            Object(Matching, "game/TCPConn_LogError.c"),
            Object(Matching, "game/TCPConn.c"),
            Object(Matching, "game/TCPConn_Reset.c"),
            Object(Matching, "game/main.c"),
            Object(Matching, "game/ServiceMenu.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/AddCoinsFromExtraStage.c"),
            Object(Matching, "game/NokoNokoChallenge_TransitionToResult.c"),
            Object(Matching, "game/NokoNokoChallenge.c", extra_cflags=["-use_lmw_stmw on", "-Cpp_exceptions on"], extab_padding=b"\x00\x00"),
            Object(Matching, "game/SuikaBallObj_Render.c"),
            Object(Matching, "game/WeatherSystem_PickVariant.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Sprite_Destroy.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/SpriteSystem_EnsureInit.c"),
            Object(Matching, "game/Scene3D_GetCameraPos.c"),
            Object(Matching, "game/LUT_Sin12Bit.c"),
            Object(Matching, "game/LookupSin.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/LookupCos.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/LUT_Sine.c"),
            Object(Matching, "game/LUT_Cosine.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/AI_UseItem.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/AI_GetLapDifference.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/AI_GetYaw.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/AI_HasItem.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/AI_GetItemType.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Item_GetDescriptor.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Item_GetDescriptorField0.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EnemyRunType2_Init.c"),
            Object(Matching, "game/EnemyRunType1_Init.c"),
            Object(Matching, "game/PathFollower_EnsureGlobalAlloc.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CourseData_GetDefaultPathKey_Safe.c"),
            Object(Matching, "game/JObj_Visibility.c"),
            Object(Matching, "game/CourseBgm_Free.c"),
            Object(Matching, "game/CourseBgm_Load.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/clNormal3D_Construct.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/FreeMediaBuffers.c", extab_padding=b"\x00\x00"),
            # Phase 3a-small: 11-fn dtk reversed-extab group bundle (no extab
            # entries, just .text). All 11 fns initially asm_fn; promote to
            # matched 1 fn at a time via sub-agent dispatch.
            Object(Matching, "game/auto_801223E8_block.c"),
            Object(Matching, "game/Archive_GetCurrent.c"),
        ],
    },
    {
        "lib": "resource",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": [
            Object(Matching, "resource/ResourceLoading.c"),
        ],
    },
    {
        "lib": "util",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": [
            Object(Matching, "util/bitpack.c", extab_padding=b"\x00\x00"),
        ],
    },
    {
        "lib": "sound",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": [
            Object(Matching, "sound/ISESlot.c"),
            Object(Matching, "sound/ISESlot_StopEffect.c"),
            Object(Matching, "sound/SoundMgr_PlaySE.c"),
            Object(Matching, "sound/SoundCtrl_SetVolume.c"),
            Object(Matching, "sound/MediaBoard_PollCompletion.c"),
            Object(Matching, "sound/SoundChannels.c"),
        ],
    },
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",  # str | List[str]
        "objects": [
            Object(Matching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(Matching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
        ],
    },
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

def _inject_sdata2_postprocess(config: ProjectConfig) -> None:
    """Append a post-compile step to MWCC rules in build.ninja.

    Rewrites anonymous local sdata2 symbols (@N) to named externals when their
    bytes match a known global from the shared sdata2 pool. No-op for objects
    that contain no matching anonymous local sdata2 symbols, so it can be
    applied to all C/C++ compile rules safely.

    Workaround: dtk-template provides no per-object post-compile hook. The
    `custom_build_steps` mechanism (PR encounter/dtk-template#27) runs at phase
    boundaries, not per-file, so we patch the rule commands directly here.
    """
    build_ninja = Path("build.ninja")
    if not build_ninja.exists():
        return

    # The target .o (built by dtk via asm at build/<ver>/obj/<src>.o) is the
    # source of truth for which sda21 reloc target name a given .text offset
    # expects. The script auto-derives target path from $out by substituting
    # 'src' -> 'obj' in the path.
    hook = ' && $python tools/postprocess_sdata2.py $out $out'
    marker = "postprocess_sdata2.py"

    rules = ("mwcc_sjis", "mwcc_sjis_extab", "mwcc", "mwcc_extab")
    text = build_ninja.read_text(encoding="utf-8")
    lines = text.splitlines(keepends=True)

    def _is_cmd_start(s: str) -> bool:
        return s.lstrip().startswith("command = ")

    i = 0
    while i < len(lines):
        line = lines[i]
        if line.startswith("rule ") and line[5:].strip() in rules:
            # Find command block (may span multiple continuation lines ending in " $")
            j = i + 1
            while j < len(lines) and not _is_cmd_start(lines[j]):
                j += 1
            if j >= len(lines):
                i += 1
                continue
            # j is the first line of command; collect until non-continuation
            k = j
            while k < len(lines) and lines[k].rstrip("\r\n").endswith(" $"):
                k += 1
            # k is the last command line (no trailing " $")
            block = "".join(lines[j:k + 1])
            if marker in block:
                i = k + 1
                continue
            last = lines[k].rstrip("\r\n")
            lines[k] = last + hook + "\n"
            # Prepend `cmd /c` if missing (Windows needs it for `&&`)
            if sys.platform == "win32" and "cmd /c " not in lines[j]:
                lines[j] = lines[j].replace("command = ", "command = cmd /c ", 1)
            i = k + 1
            continue
        i += 1

    build_ninja.write_text("".join(lines), encoding="utf-8")


if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
    _inject_sdata2_postprocess(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
