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

# MetroTRK flags (pikmin2's TRK build; self-contained headers)
cflags_trk = [
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
    "-multibyte",
    "-i src/TRK_MINNOW_DOLPHIN/include",
    "-i src/TRK_MINNOW_DOLPHIN/include/stl",
    "-use_lmw_stmw on",
    "-str reuse,readonly",
    "-common off",
    "-inline deferred",
    "-sdata 0",
    "-sdata2 0",
]

# MSL_C flags (match zeldaret/tp's MSL build)
cflags_msl = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
    "-char signed",
    "-func_align 4",
    "-inline deferred,auto",
    "-DMSL_USE_INLINES=1",
    "-i include/MSL_C",
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


# Dolphin SDK flags (mirrors doldecomp/dolsdk2004 release build flags)
cflags_dolphin = [
    "-nodefaults",
    "-proc gekko",
    "-fp hard",
    "-Cpp_exceptions off",
    "-enum int",
    '-pragma "cats off"',
    "-O4,p",
    "-inline auto",
    "-char unsigned",
    "-I-",
    "-i include",
    "-i include/libc",
    "-ir src/dolphin",
    f"-i build/{config.version}/include",
    "-D__GEKKO__",
    "-DRELEASE",
]


def SdkLib(
    lib_name: str,
    objects: List[Object],
    revision: int = 2,
    extra_cflags: List[str] = [],
) -> Dict[str, Any]:
    # SDK_REVISION selects the dolsdk2004 variant: 1 = May 21 2004 build (OS in this game)
    return {
        "lib": lib_name,
        "src_dir": "src",
        "mw_version": "GC/1.2.5n",
        "cflags": [*cflags_dolphin, f"-DSDK_REVISION={revision}", *extra_cflags],
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
            Object(Matching, "init/__start.c"),
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
            Object(Matching, "init/memset_returning_dst.c"),
            Object(Matching, "init/memcpy_bytewise.c"),
            Object(Matching, "init/OSResetSystem_NoArgs.c"),
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
            Object(Matching, "game/FlowDispatcher_ScopedTimer.c", extab_padding=b"\x00\x00", extra_cflags=["-lang=c++"]),
            Object(Matching, "game/HeapStats.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/AnimStatePool.c", extab_padding=b""),
            Object(Matching, "game/RaceContext_Dtor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/RaceContext_InitDefaults.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/RaceContext_EnsureSingleton.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CoinSystem_UpdateAll.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CoinSystem_Init.c", extab_padding=b"\x00\x00", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/CardTaskManager_RenderOverlay.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardTaskManager_Dtor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NetDiag_CounterPage.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NetDiag_QualityPage.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NetDiag_PacketPage.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Rand_RangeFloat.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Rand_RangeFloatMax.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/ItemObjectManager_RenderImpl.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/ItemObjectManager_PerFrameUpdate.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/RaceContextSlotGet.c"),
            Object(NonMatching, "game/Items.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/ClStrPcb.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/OperationClock.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/KartFootEffect_Tick.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartFootEffect_Spawn.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/ItemSelectState_Init.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/ItemSelectState_Dtor.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/SceneDrawList.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/RaceContextSlot.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/RaceContextSlotDriver.c"),
            Object(Matching, "game/ItemObjectManager_TickActiveItems.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/JumpDistanceMode_InitTimerDisplay.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/JumpDistanceMode_HandlePhysics.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/JumpDistanceMode_Update.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/JumpDistanceMode_Init.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/JumpDistanceMode_UpdateGameplay.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/BombItem_Tick.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/BombItem_Update.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/BombItem_TickActive.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_SetJointScaleByName.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_SetJointVisibilityByName.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_SetTransform.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_SetAnimFrameAndApplyScale.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_RegisterDraw.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_SetMatrixSourceEnabled_WithReseed.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_InitLoop.c", extra_cflags=["-Cpp_exceptions on"], extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_TickAnim.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/BtMode_RenderFrame.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/BtMode_Dtor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBoxResponder_DebrisArray_Dtor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBoxResponder_DebrisParticle_Dtor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBoxResponder_Rebind.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBoxResponder_DrawDebris.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBoxResponder_DrawDebrisParticle.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBoxResponder_TickDebris.c"),
            Object(Matching, "game/clItemBoxResponder_SpawnDebris.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBoxResponder.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBoxResponder_Ctor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartAudioChannel.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartAudioChannel_Set24WithSeStop.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartAudioChannel_PlayColorMatchSE.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartAudioChannel_StopSE8a.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartAudioChannel_PlayJumpSE.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxEffect_InitVariantAndResetPos.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxEffect_UpdateTwoChildSpinAndSound_Helper.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxEffect_UpdateChildPosScaleAlpha_Helper.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxEffect_UpdateChildVisScale_Helper.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxEffect_UpdateChildSpinMatrix_Helper.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Backup_Shutdown.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Backup_ClearAll.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Backup_ClearBookkeeping.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Backup_GetMinutesSinceBoot.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/card.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Backup_ClearHiScores.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Backup_LoadFromMemoryOrInit.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Backup_PublishShadowCopy.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Backup_PublishShadowCopy_Inline.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SoundMgr_PlaySE_WithChannel.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SoundMgr_StopSE_OrSpecial.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SoundMgr_CountActiveSEInstances.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SoundMgr_PlaySE_Positional.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SoundMgr_Play.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VSMode_SeedRandomItemSequence.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VSMode_FrameUpdate.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VSMode_Init.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clFlowKart_HandleConfirm.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clFlowKart_SetupTextLayout.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clFlowKart_UpdateDisplay.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clFlowKart_Init.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clFlowKart_Update.c", extab_padding=b"\x00\x00", extra_cflags=["-lang=c++"]),
            Object(Matching, "game/CardRW_CleaningTest_Page.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardRW_TestTopMenu_Page.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardRW_DispenseTest_Page.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardRW_PrintTest_Page.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardRW_ErrorDisplay.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardRW_ReadWriteTest_Page.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardRW_HardwareInit_Page.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardRW_Reprint_Page.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardRW_Renew_Page.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardRW_DataRepair_Page.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/HUD_RegisterOverlay.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/HUD_Init.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/HUD_FrameUpdate.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_GetJoint13_WorldPos.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_GetKartRootMtx.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_TriggerSlotC3Action.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_TickAction_79234.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_TickAction_79244.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_TickAction_79260.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_TickAction_78778.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_TickAction_78a3c.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_TickAction_78d00.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_TickAction_79268_AndSetSlot5aEulerZ.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_GetJointPosition.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_GetJointMatrix4x3.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_New_Full.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/KartDriver_TransformWorldToLocalY0.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxSlotMgrShutdown.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/VfxSlotMgr.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartDriver_RenderTimed.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartDriver_SetJointPosY_Slot3d.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_SetJointPosY_Slot3c.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_SetJointPosY_Slot3b.c", extab_padding=b"\x00\x00"),
                    Object(Matching, "game/auto_800A8F4C_block.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/auto_ONKARTHIT_block.c", extab_padding=b"\x00\x00", extra_cflags=["-use_lmw_stmw on", "-Cpp_exceptions on"]),
            Object(Matching, "game/InputCmdDetect.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/InputCmdLeaf.c"),
            Object(Matching, "game/CObjLineBuffer.c"),
            Object(Matching, "game/CObjProject.c", extra_cflags=["-use_lmw_stmw on", "-Cpp_exceptions on"]),
            Object(NonMatching, "game/CObjProjectPoint.c", extra_cflags=["-use_lmw_stmw on", "-Cpp_exceptions on"]),
            Object(Matching, "game/CObj_GlobalProjPushFrame.c", extab_padding=b""),
            Object(Matching, "game/CObjViewport.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/CObjLinePath.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/CObjCached.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CObjDebugRender.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CObjUnproject.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartDriver_BuildJoint12EulerTransform.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_SetUniformScale_4Wheels.c", extab_padding=b"\x00\x00"),
        ],
    },
    {
        "lib": "game",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": [
            Object(Matching, "game/TEXLoadPalette.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ReplayRandCursor.c"),
            Object(Matching, "game/RaceContextArray.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/RaceContextArrayInit.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectSmokeRing3.cpp", extra_cflags=["-use_lmw_stmw on", "-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectCompoundRing.cpp", extra_cflags=["-use_lmw_stmw on", "-Cpp_exceptions on"]),
            Object(Matching, "game/EffectKartAura.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/EffectKartAuraCompound.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on", "-i src/game"]),
            Object(Matching, "game/CommBroadcast.c"),
            Object(Matching, "game/TitleTracker_Stubs.c"),
            Object(Matching, "game/KartItemAudio.c"),
            Object(Matching, "game/KartItemAudio_PlaySEByItemId.c"),
            Object(Matching, "game/WrapInRange.c"),
            Object(Matching, "game/InputCmdSamples.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Vtable_CallSlot2.cpp"),
            Object(Matching, "game/ObjectBase.c"),
            Object(Matching, "game/Stub_NoOp_80030aec.c"),
            Object(Matching, "game/LinkedNode_GetField10_OrFallback.c"),
            Object(Matching, "game/NoopRenderHook_Pending_80064d28.c"),
            Object(Matching, "game/Allocator_DestroyEntry_Noop.c"),
            Object(Matching, "game/PlayStats_ShutdownStub.c"),
            Object(Matching, "game/PlayStats_Clear.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/TEXBindPaletteEntry.c", extab_padding=b"", extra_cflags=["-i src"]),
            Object(Matching, "game/Object_JObjUpdate.c"),
            Object(Matching, "game/Object_SetJObjRotation.c"),
            Object(Matching, "game/Object_GetJObjRotation.c"),
            Object(Matching, "game/Object_ReleaseAnimResource.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_Draw.cpp"),
            Object(Matching, "game/MObj1.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/MObj.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Object_Color.c", extab_padding=b""),
            Object(Matching, "game/Object_SetByte48.c"),
            Object(Matching, "game/Object_GetJObjPositionVec.c"),
            Object(Matching, "game/fn_801DEC3C.c"),
            Object(Matching, "game/fn_80253DF0.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_801DB99C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80146188.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80146160.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80252D6C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80252D48.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_8024B544.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80241BE0.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_8022664C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80218F1C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80218B5C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_8020E3AC.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_8020E388.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_801E6594.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_801DBA84.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_801DBA60.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_801B7CAC.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_801B7C64.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_801B7C40.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_801B7C1C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_8017218C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_8014E028.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_8014E004.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_8014DD5C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80141A70.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80089C30.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_802712C8.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80255620.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_8023D8F8.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_8022CDE4.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_801E4524.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_801DAA84.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80169DF0.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/fn_80241C04.c"),
            Object(Matching, "game/fn_8023CFC8.c"),
            Object(Matching, "game/fn_80224EBC.c"),
            Object(Matching, "game/fn_8021ED0C.c"),
            Object(Matching, "game/fn_8024F400.c"),
            Object(Matching, "game/fn_8024E338.c"),
            Object(Matching, "game/fn_80242DE0.c"),
            Object(Matching, "game/fn_80226640.c"),
            Object(Matching, "game/fn_8020F268.c"),
            Object(Matching, "game/Sci2Card_FlagReceiptTestEnable.c"),
            Object(Matching, "game/fn_802379E8.c"),
            Object(Matching, "game/KartController_GetRenderObj.c"),
            Object(Matching, "game/fn_80174698.c"),
            Object(Matching, "game/fn_80253EB8.c"),
            Object(Matching, "game/fn_8021A7BC.c"),
            Object(Matching, "game/fn_801E93A0.c"),
            Object(Matching, "game/fn_80143880.c"),
            Object(Matching, "game/fn_800D2BE0.c"),
            Object(Matching, "game/fn_80089E6C.c"),
            Object(Matching, "game/fn_80253F2C.c"),
            Object(Matching, "game/fn_80218D90.c"),
            Object(Matching, "game/fn_801ECAFC.c"),
            Object(Matching, "game/fn_801E6DD4.c"),
            Object(Matching, "game/fn_801E6D64.c"),
            Object(Matching, "game/fn_801DBA58.c"),
            Object(Matching, "game/fn_801DBA2C.c"),
            Object(Matching, "game/fn_801DB994.c"),
            Object(Matching, "game/fn_801DAB18.c"),
            Object(Matching, "game/fn_801932F8.c"),
            Object(Matching, "game/fn_80190658.c"),
            Object(Matching, "game/fn_801805AC.c"),
            Object(Matching, "game/fn_80147468.c"),
            Object(Matching, "game/fn_80089F9C.c"),
            Object(Matching, "game/fn_80250F34.c"),
            Object(Matching, "game/fn_80245700.c"),
            Object(Matching, "game/fn_8023D2B4.c"),
            Object(Matching, "game/fn_80231D4C.c"),
            Object(Matching, "game/fn_80230ED4.c"),
            Object(Matching, "game/fn_80230400.c"),
            Object(Matching, "game/fn_802300C8.c"),
            Object(Matching, "game/fn_80215508.c"),
            Object(Matching, "game/fn_80208E2C.c"),
            Object(Matching, "game/fn_801F0CBC.c"),
            Object(Matching, "game/fn_801DC510.c"),
            Object(Matching, "game/fn_801B129C.c"),
            Object(Matching, "game/fn_8016FC70.c"),
            Object(Matching, "game/fn_8014D2AC.c"),
            Object(Matching, "game/fn_8014CFA0.c"),
            Object(Matching, "game/fn_8014640C.c"),
            Object(Matching, "game/fn_80141A6C.c"),
            Object(Matching, "game/fn_80141450.c"),
            Object(Matching, "game/fn_800D748C.c"),
            Object(Matching, "game/fn_800A5608.c"),
            Object(Matching, "game/CarObjects_FindByEventType.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/ItemSpawner_TimedRemapAndSpawn.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ISESlot_TickIfActiveNotBattle6.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/BananaPositionData_Init.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/DebugTextOutput.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemUse_Gateway.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/JObj_SetScale.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Vec3_Normalize_SafeXZY.c"),
            Object(Matching, "game/Vec3_ToYawPitch.c", mw_version="GC/2.7"),
            Object(Matching, "game/CalcSoundDirection.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/InitGlobalTimer.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/dtor_801D8284.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/ServiceMode_UpdateScheduleGate.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/NokoNokoChallenge_GetCoinDivisor.c"),
            Object(Matching, "game/DVDFile_LoadSync.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/FileLoader_LoadBin.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Math_Segment2DIntersect.c"),
            Object(Matching, "game/ItemObject_TargetFirstHomingMatch.c"),
            Object(Matching, "game/Vec3_ToPitch.c", mw_version="GC/2.7"),
            Object(Matching, "game/EffectSpeed_TickAndGet.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/JObj_SetRotationQuat.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/clModelM_Construct.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/CourseObjectManager_Init.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene3D_SetupProjection.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EnemyRunType1_CalcSteering.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemObject_DispatchVtable1C_IfBoundedItem.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/SpeedBoost_Apply.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemObject_AllocFromPool.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/AudioChannel_DtorWithSeStop.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Profiler_DrawBar.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Object_DtorWithGXSync.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ResolveJointByName.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/dtor_80060024.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/dtor_8007D9C4.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_RenderCb_Mode7_Post.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Mtx4x4_TransposeTo4x3.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemObject_GetByteAt0xEC.c"),
            Object(Matching, "game/Vec3_Subtract_DestFirst.c"),
            Object(Matching, "game/DrawEffect_ApplyScaleAndIntensity.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/IsAudioMutedItem.c"),
            Object(Matching, "game/KartItem_RenderCb_Mode6_Post.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_RenderCb_Mode5_Post.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_RenderCb_Mode3_Post.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_RenderCb_DefaultCycle_Post.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemStateGuard_PruneIfDeadAndReport.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/BackupBuffer_InitAsTexture.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_IsAtStartSlot.c"),
            Object(Matching, "game/InputObj_Ctor_Internal.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/PlayStats_LoadOrInitForBoot.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/clACamera_Dtor_WC.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/SmallObj_Dtor_VtableA.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/model_jobj_ClassInit.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/RandSeedDebug_SetEnable.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectState_ReleaseAndClear.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/InputObj_TickAndDispatch.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemObject_DecrementCategoryBudget.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Object_CopyFieldsRotPosScale.c"),
            Object(Matching, "game/SpriteSlot_SetScale.c"),
            Object(Matching, "game/SpriteSlot_SetTranslateDxDy.c"),
            Object(Matching, "game/VfxSlot_SetUVScroll.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/VfxSlot_SetMatrixSourceEnabled.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxSlot_SetScaleUniform.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxSlot_SetRotationXYZFromVec.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxSlot_SetPositionFromVec.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxSlot_SetAnim.c"),
            Object(Matching, "game/VfxSlot_Release.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxSlot_RegisterDraw.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxSlot_Render.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxSlot_TickAnim.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxSlot_BindResource.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxSlot_BindResourceEx.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/VfxSlot_ResolveJoint.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/VfxSlot_SetScaleVec3.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/VfxSlot_SetRotationZ.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/VfxSlot_SetRotationXYZ.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/SpriteSlot_SetScaleXYZ.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/SpriteSlot_SetRotationQuat.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/SpriteSlot_Render.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Vec3_Magnitude_Wrapper.c"),
            Object(Matching, "game/Mtx_Copy.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Vec3_ToYaw.c", extab_padding=b""),
            Object(Matching, "game/Vec3_Scale.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Vec2.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/JointByName.c"),
            Object(Matching, "game/TaRecord.c"),
            Object(Matching, "game/TaRecord_InsertResult.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Tachometer.c", extab_padding=b"\x00\x00", extra_cflags=["-i src/game"]),
            Object(Matching, "game/ParticleBurst.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartTireFX.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/HeartCompoundItem.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CarrotItemEffect_Update.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CarrotItemEffect_Render.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CarrotItemEffect_AddDraw.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/TwinSpriteOverlay.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clMiyoshiCardCreate.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/BiribiriLand.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardSave_Tick.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardSave_Tick_PollCleaningResult.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardSave_Tick_CaptureAndStart.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/PowItem.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ShellItem.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/TornadoItem.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/StarItem.c", extab_padding=b""),
            Object(Matching, "game/MukadeItem.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/GameSetting.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clFlowCup.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on", "-lang=c++", "-use_lmw_stmw on"]),
            Object(Matching, "game/clFlowRound.c", extab_padding=b"\x00\x00", extra_cflags=["-lang=c++", "-use_lmw_stmw on"]),
            Object(Matching, "game/clFlowItemSelect_CommitSlotAnim.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clFlowItemSelect_Draw.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clFlowItemSelect_Update.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clFlowItemSelect_Dtor.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/clFlowItemSelect_Init.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/ObjectTree_BlendOrCopy.c", extab_padding=b""),
            Object(Matching, "game/ObjectTree_BlendOrCopy_Timed.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ObjectTree_BlendQuatLerp.c", extab_padding=b""),
            Object(Matching, "game/clNormal3D.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/Normal3DScale.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/Normal3DLoad.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Normal3DFlatten.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/clRomLifecycle.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on", "-lang=c++"]),
            Object(Matching, "game/clRomOverlay.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/SpriteAnimParamBlock.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/VolumeCalibration.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-lang=c++", "-use_lmw_stmw on"]),
            Object(Matching, "game/ItemHitRegistry.c"),
            Object(Matching, "game/ItemLocalizedAsset.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/ItemHitBurst.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/ItemHitPropagation.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/ItemGroundExplosion.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Item.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemMotion.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/ItemHoming.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/ItemAcceleration.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/ItemLaunch.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/ItemFlyingRender.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemTrackedHoming.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/ItemTrackedHomingState.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemGroundProbes.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/ItemCharacterRender.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/ItemHandheldRender.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartCharacterParam.c"),
            Object(Matching, "game/Frame.c", extab_padding=b"\x00\x00", extra_cflags=["-lang=c++"]),
            Object(Matching, "game/TransparentDraw.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/TripleBladeRing.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/TripleBladeRing_SetWorldYaw.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/TripleBladeRing_Update.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Vec3_ScaleXZ.c"),
            Object(Matching, "game/TornadoEffect.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-i src/game"]),
            Object(Matching, "game/ItemStateGuard_IsActive.c"),
            Object(Matching, "game/ItemEffectDamp_Init.c"),
            Object(Matching, "game/KartItem_Stub_Returns0.c"),
            Object(Matching, "game/KartEffectFadeTransit_Tick.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartEffectFadeTransit_GetActiveValue.c"),
            Object(Matching, "game/KartEffectFadeTransit_Dtor.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartEffectFadeTransit_Init.c"),
            Object(Matching, "game/KartItem_FlushRender.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_RenderCb_Mode7_Pre.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_RenderCb_DefaultCycle_Pre.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_RenderCb_Mode3_Pre.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_RenderCb_Mode5_Pre.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_RenderCb_Mode6_Pre.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_RenderCb_Mode2or4_Pre.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartItem_RenderCb_Modes.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectState_HasContent.c"),
            Object(Matching, "game/EffectSteering.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/EffectSteeringCtor.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectActor_BindKartTargetPair.c"),
            Object(Matching, "game/DebrisArray_DrawForward.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/DebrisArrayDraw.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/DebrisArray.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/DemoFlow_ResetTwoFlags.c"),
            Object(Matching, "game/ItemObject_RaycastWallStub.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Item_DecayVelocityScalar.c"),
            Object(Matching, "game/ItemObject_SetByte18c.c"),
            # group2 batch (0x8009B98C..0x801077C8)
            Object(Matching, "game/RankSlot_AppendOrUpdate.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/PlayerData_ApplyItemUnlockById.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/PlayerData_GetUnlockedItemIdByIndex_U8.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/PlayerData_ResetForFlow.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/KartDriverArray_StaticCtor.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/ISE_ScaleColumnDirectionByMagnitude.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Unknown_DeleteIfFlag_800a5188.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/VSModeIntro_Dtor.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/VSModeIntro_Ctor.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/TitleTracker_Dtor.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/WarpZone_VtableTrim.c"),  #g2
            Object(Matching, "game/ShadowAreaMgr_Dtor.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/dtor_800AA980.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/ShadowAreaEdge_Dtor.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/ShadowAreaMgr_Ctor.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/HitMessageOverlay_Destroy.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/TweenInterp_VtableTrim.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/GameMode_Title_Ctor.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/AnimState_Reset.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/AnimState_New.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_SetFlagsByte.c"),  #g2
            Object(Matching, "game/DrawEffect_Free.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_SpawnWithDescriptor.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/DrawEffect_SpawnByType.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_SpawnDirect.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/VfxLaughInner_Tick.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/CharaPop12_SpawnAll.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/KartShellRibbon_DrawCb.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/SpawnRisingTextAndBurst.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_SetFloat110.c"),  #g2
            Object(Matching, "game/DrawEffect_Cb_DualBurstSpawner_2x4.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/EffectItem4SpawnSubFlamePair_Tick.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_RalySmokeSpawner_4Wheel.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartVfx4B_StubInit.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_ItemBoxBurstFlash_Tick.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_ItemBoxBurstSpawner.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_UVScroll_Tick.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartHaloPlate_Init.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_TrailDot_Spawn.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DbgMenu_Dtor.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DbgScene_InitAnimSlotArray.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DbgScene_CopyMatrix3x4Transpose.c"),  #g2
            Object(Matching, "game/Mtx_TransposeToMtx44.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Vec3_HorizontalYawTo.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Vec3_PitchTo.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Vec3_HorizontalDistance.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/fn_800D3184.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Mtx44_TransformVec3.c"),  #g2
            Object(Matching, "game/BuildOrientationFromYaw.c"),  #g2
            Object(Matching, "game/Mtx44_GetTranslation_RowMajor.c"),  #g2
            Object(Matching, "game/Mtx44_GetYawOfPosZ.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Mtx44_GetTranslation_ColMajor.c"),  #g2
            Object(Matching, "game/ItemAliasTable_LookupSlotIndex.c"),  #g2
            Object(Matching, "game/ItemObject_GetGroundTypeAt.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Vec3_AddNormalizedXZ.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/ItemObject_AllocGabyou.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(NonMatching, "game/KartItem_QueryEffectStateFromIse.c"),  #g2
            Object(Matching, "game/ItemObject_Tick_AwaitInitThenFree.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartShadow_TwoSlot.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/DrawEffect_SpawnWithMatrix.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/DrawEffect_KartWheel_TripleChildSpawn.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/DrawEffect_KartImpactRing_AdvanceByVfxDelta.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/KartFadeInEffect_Update.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_BurstSpawner_Bind6Then4or5.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/GameMode_DispatchSceneInit.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/fn_800AE71C.c"),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartFlatBurst_Spawner.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_SmokePuff_Update.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/HandOverItem_Tick.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Mtx44_GetYawOfPosZ_Padded.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/CourseInteractMover_Update.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartSparkleSpray_Spawner.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_ItemHitFx_Spawn.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(NonMatching, "game/Item_ComputeBiasedTargetPos.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/ItemRes_LookupDatPathByKey.c"),  #g2
            Object(NonMatching, "game/DrawEffect_TickAndCull.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_HitFlash_Update.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Mtx44_GetPitchOfNegX_Lean.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Mtx44_GetPitchOfPosZ.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_KartItemTrail_ExplodeAndPropagate.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartItemTrail_SpawnerSwarm.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(NonMatching, "game/AngleStepForward_OrSnap.c"),  #g2
            Object(Matching, "game/Mtx44_Scale_Uniform.c"),  #g2
            Object(Matching, "game/HitMessageOverlay_Init.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Splatter_Update.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/FindNearestDriverWithinConeAndRadius.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/EffectVfx86_BoostRingCenter_Tick.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(NonMatching, "game/Vec3_OrthoProjectThenScaleByLen.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/BombExplosion_InitOrDestroy.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/EffectVfx16_StarItemBurst_Tick.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/VfxLaugh_Tick.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/KartItem_ApplyEffectToTarget.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(NonMatching, "game/ZlibInflate_BufferToBuffer.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_MatrixSourced_Bind63.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_KartImpactRing_SpawnFromVfx.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_CircleFlare_Tick.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_SparkDescend_Update.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/KartBurstShard_SpawnSet.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/Mtx44_GetPitchOfNegX.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Mtx44_GetPitchOfPosZ_Padded.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartTwoPlaneRing_Tick.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/Mtx44_GetYawPitchOfPosZ.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(NonMatching, "game/Item_BendVelocityByGroundProbe.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/ItemObject_Tick_Kind2426_FastDrop.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(NonMatching, "game/Terrain_FlagsToTypeId.c"),  #g2
            Object(Matching, "game/ItemObject_CheckPairCollision.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartVfx_Bind1_Damage.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartVfx_Bind6_YawZ.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(NonMatching, "game/ItemObject_CheckKartCollision.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/EffectVfx82_FieldItemDropPuff_Tick.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/KartShellRibbon_Update.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartTrail_Bind3E.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartRotatingSparkle_Tick.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/DrawEffect_Cb_KartFlatBurst_Tick.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(NonMatching, "game/fn_80105CC4.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),  #g2
            Object(NonMatching, "game/Terrain_FlagsToDebugString.c", extra_cflags=["-Cpp_exceptions on", "-str reuse,readonly"]),  #g2
            Object(Matching, "game/Effect_KartGlow_Update.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/Mtx44_Translate.c", extra_cflags=["-Cpp_exceptions on"]),  #g2
            Object(Matching, "game/ItemObject_WriteVectors.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemTracker.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/clFlowItem.c", extab_padding=b"\xc7\x02" * 6, extra_cflags=["-Cpp_exceptions on", "-lang=c++", "-use_lmw_stmw on"]),
            Object(Matching, "game/LapBannerScene.c"),
            Object(Matching, "game/SeqMenuScene.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-lang=c++", "-use_lmw_stmw on"]),
            Object(Matching, "game/FinalLapCoinJump_SetEnable.c"),
            Object(Matching, "game/FinalLapCoinJump_CheckActiveForObject.c"),
            Object(Matching, "game/card_is_ejected.c"),
            Object(Matching, "game/card_ping_clear_pending_flag.c"),
            Object(Matching, "game/Jyugemu_ReverseFlag.c"),
            Object(Matching, "game/Jyugemu_Flag_SetKartDriver.c"),
            Object(Matching, "game/Jyugemu_Flag_Render.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Jyugemu_Flag_Tick.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Jyugemu_Flag_Dtor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Jyugemu_Flag_Ctor.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-lang=c++"]),
            Object(Matching, "game/Jyugemu_ReverseFlag_Tick.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Jyugemu_ReverseFlag_Dtor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/Jyugemu_ReverseFlag_Ctor.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Jyugemu_ReverseFlag_Enable.c"),
            Object(Matching, "game/TEXPaletteAccessors.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CardTaskPrintJob_IsSuccess.c"),
            Object(Matching, "game/CardTaskPrintJob_IsRunning_Thunk.cpp"),
            Object(Matching, "game/CardTaskPrintJob_InitStateVector.c"),
            Object(Matching, "game/CardRW_GetSubState.c"),
            Object(Matching, "game/card_rw_get_substate.c"),
            Object(Matching, "game/CardReadCommand.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CardReadCommandUnused.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CardCleaningCommand.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CardEjectCommand.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/CardForceBackup.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/CardUnpackV1.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/CardUnpackLegacy.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/InputCmdLifetime.cpp", extab_padding=b"\xc6\x02", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CardPingCommand.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Sci2Card_GetPrintErrorCode.c"),
            Object(Matching, "game/Sci2Card_GetResponsePayload.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Sci2Card_ForceFail.c"),
            Object(Matching, "game/card_send_track_data.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/PostRace_StartScoreEntryFlow.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/PostRace_StartScoreEntryFlow_WithCardSave.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Sci2Card_Singleton_Get.c"),
            Object(Matching, "game/Sci2Card_SendCmds.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/CardTaskWelcome_Dtor.c"),
            Object(Matching, "game/card_task_manager_create.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clCGameDemoWC_Stubs.c"),
            Object(Matching, "game/clCGameDemoWC/Dtor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clCGameDemoWC/Render.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clCGameDemoWC/Tick.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clCGameDemoWC/Ctor.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/clCGameDemo_Dtor.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/BtMode_BaseDtor.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/GameMode_Base.c"),
            Object(Matching, "game/Debug.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Camera.c"),
            Object(Matching, "game/Game_Shutdown.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Profiler.c"),
            Object(Matching, "game/Cleanup_DtorMinimal.c"),
            Object(Matching, "game/Profiler_RecordFrame.c"),
            Object(Matching, "game/MetricsTable.c"),
            Object(Matching, "game/LObjList.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Sci2Card_Init.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Sci2Card_BuildPacket.c"),
            Object(Matching, "game/Sci2Card_Lifetime.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/MemoryManager_Alloc.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/MemoryManager_TimedFree.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/SceneFlow.c"),
            Object(Matching, "game/card_eject.c"),
            Object(Matching, "game/Sci2Card_Status.c"),
            Object(Matching, "game/SceneRender.c", extab_padding=b""),
            Object(Matching, "game/clRomAccessors.c"),
            Object(Matching, "game/clRomDtor.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Archive.c"),
            Object(Matching, "game/CollisionFile_FixupPointers.c"),
            Object(NonMatching, "game/Terrain_GetGroundHeight.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/Terrain_FindTriangleAtPosition.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Math_SegmentIntersection2D.c"),
            Object(Matching, "game/Terrain_WallSegmentTest.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/Collision.c"),
            Object(Matching, "game/Terrain_StepAndResolve.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/Terrain_WallEdgeTest.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/StrPcb_988.c"),
            Object(Matching, "game/StrPcb.c"),
            Object(Matching, "game/StrPcb_Tick.c", mw_version="GC/2.6", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/StrPcb_Control.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/StrPcb_WaitForState1.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/StrPcb_Commands.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/StrPcb_GetInstance.c"),
            Object(Matching, "game/SetPcbScratchFlag_806d11a4.c"),
            Object(Matching, "game/PcbConn_MarkDisabled.c"),
            Object(Matching, "game/PcbConn_RecycleIfOver.c"),
            Object(Matching, "game/Clamp.c"),
            Object(Matching, "game/NoOpStubs_38f54.c"),
            Object(Matching, "game/Allocator_Deallocate.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Stub_NoOp_38f80.c"),
            Object(Matching, "game/InputMgr_GetPlayer.c"),
            Object(Matching, "game/QuadFrame_FromPackedCorners.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/QuadFrame_FromCornerPtrs.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/InputMgr.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/DMAChannelManager_Init.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-lang=c++", "-use_lmw_stmw on"]),
            Object(Matching, "game/ItemObjectManager_Init.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/InputObj.c"),
            Object(Matching, "game/JvsInput_Calibration.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/JvsInputReset.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/JvsInput_TickPoll.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/JvsInputPoll.c", extra_cflags=["-use_lmw_stmw on", "-Cpp_exceptions on"]),
            Object(Matching, "game/JvsInputClear.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/JvsInputStubs.c"),
            Object(Matching, "game/JvsInputLifetime.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/JvsInputMetrics.cpp", extab_padding=b""),
            Object(Matching, "game/InputObj_Ctor.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/InputMgr_TeardownStub.c"),
            Object(Matching, "game/ItemHolder.c"),
            Object(Matching, "game/ItemHolder_Init.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/ItemRes_Thunk.c"),
            Object(Matching, "game/dtor_8024F40C.c"),
            Object(Matching, "game/ItemEffectBus.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/PathCursor_ResetToPath.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/PathCursor_Free.c"),
            Object(Matching, "game/PathCursor_InitFromPath.c", extab_padding=b"\x00\x00"),
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
            Object(Matching, "game/dtor_801FEA70.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/GetCourseSectionType.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/InitRumbleController.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/LapDisp_SetTotalLaps.c"),
            Object(Matching, "game/LapDisp_SetCurrentLap.c"),
            Object(Matching, "game/HUD_SetRacePosition.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/RnkDisp_SetPosition.c"),
            Object(Matching, "game/HUD_SetTotalLaps.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/HUD_SetCurrentLap.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/IsCardValid.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/BootNotice_CheckEnterCondition.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/BootPCBCheck_Init.c", extab_padding=b"\x00\x00"),
            Object(NonMatching, "game/PCBCheckRecv.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/PCBCommSendPeers.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/PCBCommCompute.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/PCBCheckProcess.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/GetTextureByIdAndLang.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/AssocTree.c"),
            Object(Matching, "game/ItemDisplay_Stop.c"),
            Object(Matching, "game/ItemDisplay_Destroy.c"),
            Object(Matching, "game/ItemDisplay_GetOrCreate.c"),
            Object(Matching, "game/ItemSelect.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemSelect_DrawUIHelperIfActive.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemSelect_Pending.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBox_StepFn_Bobbing.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBox_StepFn_PopOut.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBox_ResetTimer_IsPickedUp.c"),
            Object(Matching, "game/clItemBox_TransitionToDebris.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBox_Draw.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBox_Tick.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBox_Dtor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBox_Ctor_XYZ.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/clItemBox_Ctor_GroundSnap.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/clItemBoxManager_Assets.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/clItemBoxManager_StepTable.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/clItemBox_FactoryCreate.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/MJObj_ColorFloat.c", extab_padding=b""),
            Object(Matching, "game/MJObj_InitMember.c", extab_padding=b""),
            Object(Matching, "game/MJObj_SetColor.c", extab_padding=b""),
            Object(Matching, "game/DisplayBuffer_GetByIndex.c"),
            Object(Matching, "game/GX_BeginDraw.c"),
            Object(Matching, "game/GX_EndDraw.c", extra_cflags=["-sdata 16"]),
            Object(Matching, "game/TexMgr_Apply.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/ProcessSystemTick.c"),
            Object(Matching, "game/Effect.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartFx.c", extab_padding=b"\x00\x00"),
            Object(NonMatching, "game/KartFxDustPiece.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartFxDust.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/KartFxBoost.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/KartFxBoostFlame.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on", "-i src/game"]),
            Object(NonMatching, "game/KartFxJump.cpp", extra_cflags=["-Cpp_exceptions on", "-i src/game"]),
            Object(Matching, "game/KartFxJumpSpawner.cpp", extra_cflags=["-Cpp_exceptions on", "-i src/game"]),
            Object(Matching, "game/KartFxLand.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/KartFxFlash.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/KartFxAuxAccel.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/KartFxSlot60.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/KartFxDriftParticle.cpp", extra_cflags=["-Cpp_exceptions on", "-i src/game"]),
            Object(Matching, "game/KartFxDrift.cpp", extra_cflags=["-Cpp_exceptions on", "-i src/game"]),
            Object(NonMatching, "game/KartFxHorn.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/KartFxDriftSparkParticle.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartFxChargeIcon.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartFxDispatchA.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/KartFxDispatchE.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/KartFxDispatchD.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/KartFxRingRay.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/KartFxExhaustRay.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/KartFxBurnout.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartFxRing.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartFxDispatchB.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/EffectTwoChild8F.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/EffectChild35.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/EffectFourSpark.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/EffectChild3C.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/EffectSparkSprayInit.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/EffectKartAttach59.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectInit7E.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectBurst8F.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectSpinBurst.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectKartWaveGlow.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectDustBurst4.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/EffectHitFlash.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectExplosionPiece.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectKartOrbitSpark.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectStarBurst.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectSparkPlain.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectCluster16.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/EffectKartJoint15.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectDrift7A.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectSpark72.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectDrift79.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectExplosionCompound.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectKartJoint12.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/EffectInit5F.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectVfxRenderHook.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectVfx.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectSeC2.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectInit25.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/VfxSpritePopup.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectInit31.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectInit76.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectChildPair.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectPlaceE4.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/EffectAnim5A.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectDustScatter.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectYawPitch.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/CoinJumpFx.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/CelebPop17Update.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CelebPop17Spawn.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CoinJumpFxSpawn.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/EffectKartTrail3A.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectUvScroll.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectRotatePair.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/EffectVariant77.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectSparkSprayPlace.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EffectSparkSprayCompound.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/NokoNoko_CountDefeated.c"),
            Object(Matching, "game/NokoNoko_Update.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NokoNoko_InitEntity.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NokoNoko_FindNearest.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NokoNoko_CheckHitAndKill.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NokoNoko_Render.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NokoNoko_Init.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/clFlowChara_HandleConfirm.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clFlowChara_Update.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clFlowChara_Destructor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NokoNoko.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/GameModeBase.cpp"),
            Object(Matching, "game/KartMovement_SetPosition.c"),
            Object(Matching, "game/TrampolineTo_801ba110.c"),
            Object(Matching, "game/NamCam_LoadImage.c"),
            Object(Matching, "game/NamCam_GetImageHandle.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NamCam_TickShutdownCountdown.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NamCam_End.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NamCam_Init.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/ISESlot_Update.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ISESlot_Deactivate.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ISESlot_Lifecycle.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/CourseAuxClass_VtableDtor.c"),
            Object(Matching, "game/dtor_8021617C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/WarpZone_Dtor.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/LiveConn.c"),
            Object(Matching, "game/PlaySoundDSP.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "ui/CursorSound.c"),
            Object(Matching, "game/InitBGM.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/dtor_801BA14C.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "ui/FrameSelection.c"),
            Object(Matching, "ui/FrameSelection_Methods.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-lang=c++", "-use_lmw_stmw on"]),
            Object(Matching, "ui/UI_PlaySeToggle.c"),
            Object(Matching, "ui/UISoundClSound4D.c"),
            Object(Matching, "ui/UI_PlaySeDecide.c"),
            Object(Matching, "game/CarObject_ResetPhysics.c"),
            Object(Matching, "game/CoinEvent.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/CoinEvent_PlaySE_0x13.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/DebugOverlay_KartPhysicsForLocalPlayer.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartMovement.c"),
            Object(Matching, "game/KartDriver_GetJObjRootIfReady.c"),
            Object(Matching, "game/KartDriver_New_Empty.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/GetItemDataEntry_Bounded.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemUseStats.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/PathCursor.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/PathCursor_FindNearest.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartMovement_GetVelocityMagnitude.c"),
            Object(Matching, "game/KartItem_TriggerStateAction.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/KartMovement_CanReceiveItem.c"),
            Object(Matching, "game/KartMovement_GetCurrentItemId.c"),
            Object(Matching, "game/KartReaction.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/LakituStart.c"),
            Object(Matching, "game/CourseData.c"),
            Object(Matching, "game/GlobalTimer.c"),
            Object(Matching, "game/PhysicsState.c"),
            Object(Matching, "game/Rand.c"),
            Object(Matching, "game/Rand_RangeInt.c"),
            Object(Matching, "game/ItemObjectManager_Controls.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/JumpDistanceMode_PredictLanding.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/JumpDistanceMode_CopyKartMovement.c"),
            Object(Matching, "game/BombItem_DropAndSpawnExplosionTick.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_SetRotationQuatFromVec.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_SetPositionFromVec.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_Destroy.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_Container_Free.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteSlot_InitNonLoop.c", extra_cflags=["-Cpp_exceptions on"], extab_padding=b"\x00\x00"),
            Object(Matching, "game/BtMode_Init.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/clItemBoxResponder_CmdGroup.c"),
            Object(Matching, "game/Rand_RangeIntMax.c"),
            Object(Matching, "game/RaceScene_PlayerSlots.c"),
            Object(Matching, "game/RivalRun_PathFollowerInit.c"),
            Object(Matching, "game/RivalRun.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/EggItem.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/GabyouItem.c", extab_padding=b"\x00\x00"),
            Object(NonMatching, "game/GabyouItemFlight.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/GabyouItemHit.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/GabyouItemImpact.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/GabyouItemReturn.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/GabyouItemFall.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/GabyouItemTick.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/GabyouItemActive.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/GabyouItemHeld.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/GabyouItemUpdate.cpp", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/GabyouItemDispatch.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/GabyouTripleChild.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/TaruItem_OnGroundDriftTick_25.c", extab_padding=b""),
            Object(Matching, "game/TaruItem_Tick_HeldAndHoming_25.c", extab_padding=b""),
            Object(Matching, "game/TaruItem_Dispatch_25.c", extab_padding=b""),
            Object(Matching, "game/ReverseChallenge.c", extab_padding=b"\x00\x00", extra_cflags=["-i src/game"]),
            Object(Matching, "game/OnchiSpeaker_State2_Active.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/OnchiSpeaker_State2_Flight.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/OnchiSpeaker_State1_Held.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/ItemObject_Tick_Kind3c_OnchiSpeaker.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/BananaTriple_StuckOnDriverTick.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/BananaTriple_OnImpactTick.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/BananaTriple_Tick_HeldAndHoming.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/BananaTriple_Dispatch.c", extab_padding=b"\x00\x00"),
            Object(NonMatching, "game/KartPhysics_ApplyCollisionForce.cpp", extab_padding=b"\x00\x00"),
            Object(Matching, "game/GameModeBase_FrameUpdate2.cpp"),
            Object(Matching, "game/SpawnTable.c"),
            Object(Matching, "game/VBlank.c"),
            Object(Matching, "game/SyncSlot.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/ResetIOPorts.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/PcbSyncTable_Ptr.c"),
            Object(NonMatching, "game/PcbSlotReset.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/PcbSlotSync.c"),
            Object(Matching, "game/PCBCommHostConfirm.c"),
            Object(Matching, "game/PCBCommSnapshot.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/Matrix4Translation.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/Matrix4RotZ.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Matrix4Leaf.c"),
            Object(NonMatching, "game/PCBCommLifecycle.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/Matrix4RotXY.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/Matrix4Multiply.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/PCBCommPhase5.c", extra_cflags=["-use_lmw_stmw on"], extab_padding=b""),
            Object(NonMatching, "game/PCBCommBroadcast.c", extra_cflags=["-lang=c++", "-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/PCBCommPhase1.c", extab_padding=b""),
            Object(Matching, "game/CommBroadcast_ClearTable.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CardTaskManager_Tick.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/NetDiag_PacketRatioPage.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CoinSystem_RemoveCoins.c"),
            Object(Matching, "game/DVDLoad_Stats.c"),
            Object(Matching, "game/GXChannel_PushTransform.c", extab_padding=b""),
            Object(Matching, "game/GXChannel_PushChannelColors.c", extab_padding=b""),
            Object(Matching, "game/GXChannel_Unbind.c", extab_padding=b""),
            Object(Matching, "game/GXChannel_Bind.c", extab_padding=b""),
            Object(Matching, "game/GXChannel_Init.c", extab_padding=b""),
            Object(Matching, "game/BananaField_Render.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/BananaField_CheckCollision.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/BananaField_TestHitBox.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/DVDLoad_DrawDoneCallback.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/DVDLoad_AsyncStop.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/DVDLoad_AsyncStart.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/DVDLoad_OpenAllocReadRelocSync.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/DVDLoad_ReadChunkHandle.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/DVDLoad_WaitIfSamePage.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/DVDLoad_RecordOpStart.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/RingBuffer_Getters.c"),
            Object(Matching, "game/SyncSlot_ApplyCourseChoice.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/PCBComm_PromoteToClientConfirmed.c"),
            Object(Matching, "game/PcbConn_GetStateName.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/PcbListener_GetStateName.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/PcbListenerAccept.c"),
            Object(Matching, "game/PcbListenerLifetime.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/TCPConn_LogError.c"),
            Object(NonMatching, "game/TCPConnRecv.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/TCPConnSend.c", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/TCPConn.c"),
            Object(Matching, "game/TCPConnEnqueue.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/TCPConn_Reset.c"),
            Object(Matching, "game/TCPConnPoll.c", extra_cflags=["-Cpp_exceptions on"], extab_padding=b"\x00\x00"),
            Object(Matching, "game/TCPConnCloseInit.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/TCPConnLeaf.c"),
            Object(Matching, "game/TCPConn_AllocTxBuffer.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/main.c"),
            Object(Matching, "game/ServiceMenu.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/ServiceMenu_Page.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-lang=c++"]),
            Object(Matching, "game/AddCoinsFromExtraStage.c"),
            Object(Matching, "game/GetKartParamBlock.c"),
            Object(Matching, "game/NokoNokoChallenge_TransitionToResult.c"),
            Object(Matching, "game/MiniGame.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-lang=c++"]),
            Object(Matching, "game/MiniGameBase.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/CoinChallengeUpdate.cpp", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(NonMatching, "game/CoinChallengeInit.cpp", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            # group6 (0x801FC1E0..0x8024D764) TUs
            Object(NonMatching, "game/UISeHelpers.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_801FC1E0.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_801FD320.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_801FD924.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_801FE3BC.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_801FE8B8.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_801FEBD8.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-RTTI on", "-use_lmw_stmw on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_801FF670.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_8020007C.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_80202148.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on", "-RTTI on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_80202BCC.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on", "-inline noauto"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_8020314C.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on", "-RTTI on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_80203EA0.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on", "-RTTI on", "-inline noauto"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_80204474.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on", "-RTTI on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_802052E0.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"], mw_version="GC/2.6"),
            Object(NonMatching, "game/anon_80205DCC.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"], mw_version="GC/2.6"),
            # group6-end
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
            Object(Matching, "game/AI_GrantItem.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/AI_HasItem.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(NonMatching, "game/AI_GetItemType.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Item_GetDescriptor.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Item_GetDescriptorField0.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/EnemyRunType2_Init.c"),
            Object(Matching, "game/EnemyRunType1_Init.c"),
            Object(Matching, "game/PathFollower_EnsureGlobalAlloc.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/GetEnemyParam.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CourseData_GetDefaultPathKey_Safe.c"),
            Object(Matching, "game/CourseData_Lookup.c", extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/JObj_Visibility.c"),
            Object(Matching, "game/CourseBgm_Free.c"),
            Object(Matching, "game/CourseBgm_Load.c", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/clNormal3D_Construct.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/cLNormal3DWrap_Mgr_GetPeakActiveCount.c"),
            Object(Matching, "game/FreeMediaBuffers.c", extab_padding=b"\x00\x00"),
            # Phase 3a-small: 11-fn dtk reversed-extab group bundle (no extab
            # entries, just .text). All 11 fns initially asm_fn; promote to
            # matched 1 fn at a time via sub-agent dispatch.
            Object(Matching, "game/auto_801223E8_block.c"),
            Object(Matching, "game/Archive_GetCurrent.c"),
            Object(Matching, "game/ItemAlias.c"),
            Object(Matching, "game/KartDriver_SetJointPosY_Slot3a.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_Dtor.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_Render.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_SetEulerY_4Joints_LastMirrored.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_GetJointByIdx.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_Init.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/KartDriver_InitFull.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CoinChallengeRender.cpp", extra_cflags=["-Cpp_exceptions on"]),
        ],
    },
    {
        # .text 0x801077C8..0x8015A6E4 (coins / minigame objects / sprites)
        "lib": "game_801077C8",
        "mw_version": "GC/1.3.2",
        "cflags": [*cflags_base, "-Cpp_exceptions on"],
        "progress_category": "game",
        "objects": [
            Object(Matching, "game/csAnim.c", extab_padding=b"\x00\x00", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/csAnim_Reset.c"),
            Object(Matching, "game/KartPreview.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/PreviewModel.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/SpriteEffects.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/RenderTargetSingleton.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/CourseTables.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/OrthoCam.c", extab_padding=b"\x00\x00"),
            Object(Matching, "game/ZoneList.c", extab_padding=b"\x00\x00", extra_cflags=["-use_lmw_stmw on"]),
        ],
    },
    {
        # .text 0x801A9D58..0x801FC1E0 (Voice / clFlow / AI / KartPhysics / KartController).
        "lib": "game_ai",
        "mw_version": "GC/1.3.2",
        "cflags": [*cflags_base, "-Cpp_exceptions on"],
        "progress_category": "game",
        "objects": [
            Object(Matching, "game/fn_801DB800.c"),
            Object(Matching, "game/fn_801DB8BC.c"),
            Object(Matching, "game/fn_801DB8F0.c"),
            Object(Matching, "game/fn_801DB928.c"),
            Object(Matching, "game/fn_801DB95C.c"),
            Object(Matching, "game/fn_801DB9C4.c"),
            Object(Matching, "game/fn_801DC4DC.c"),
            Object(Matching, "game/fn_801DC5C0.c"),
            Object(Matching, "game/fn_801DC630.c"),
            Object(Matching, "game/fn_801DC664.c"),
            Object(Matching, "game/fn_801DC69C.c"),
            Object(Matching, "game/fn_801DC740.c"),
            Object(Matching, "game/fn_801DC9AC.c"),
            Object(Matching, "game/fn_801DCC6C.c"),
            Object(Matching, "game/fn_801DD8E4.c"),
            Object(Matching, "game/fn_801DDA8C.c"),
            Object(Matching, "game/fn_801DE7B0.c"),
            Object(Matching, "game/fn_801DE7DC.c"),
            Object(Matching, "game/fn_801DE810.c"),
            Object(Matching, "game/fn_801E6B0C.c"),
            Object(Matching, "game/fn_801E6B38.c"),
            Object(Matching, "game/fn_801E6B64.c"),
            Object(Matching, "game/fn_801E6C10.c"),
            Object(Matching, "game/fn_801E6C54.c"),
            Object(Matching, "game/fn_801E6C68.c"),
            Object(Matching, "game/fn_801E6CC8.c"),
            Object(Matching, "game/fn_801E6CFC.c"),
            Object(Matching, "game/fn_801E6DDC.c"),
            Object(Matching, "game/fn_801E6E20.c"),
            Object(Matching, "game/fn_801EC700.c"),
            Object(Matching, "game/PhysicsState_GetSpeed.c"),
            Object(Matching, "game/fn_801E8C7C.c"),
            Object(Matching, "game/fn_801E9290.c"),
            Object(Matching, "game/fn_801B0F20.c"),
            Object(Matching, "game/fn_801B11B8.c", extab_padding=b""),
            Object(Matching, "game/fn_801B14B8.c"),
            Object(Matching, "game/fn_801B158C.c"),
            Object(Matching, "game/fn_801B377C.c", extab_padding=b""),
            Object(Matching, "game/VoiceSystem_SetCheckpointsForTotalLaps.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/fn_801B3980.c"),
            Object(Matching, "game/fn_801B3A4C.c"),
            Object(Matching, "game/VoiceQueue_Clear.c"),
            Object(Matching, "game/fn_801B3B7C.c"),
            Object(Matching, "game/fn_801B3CE0.c"),
            Object(Matching, "game/fn_801B6B94.c"),
            Object(Matching, "game/fn_801B75A0.c"),
            Object(Matching, "game/fn_801B7B04.c"),
            Object(Matching, "game/fn_801B8398.c"),
            Object(Matching, "game/fn_801B8434.c"),
            Object(Matching, "game/fn_801B84B4.c"),
            Object(Matching, "game/fn_801B8540.c"),
            Object(Matching, "game/fn_801B87B0.c"),
            Object(Matching, "game/fn_801B87D8.c"),
            Object(Matching, "game/fn_801B8874.c"),
            Object(Matching, "game/fn_801B8918.cpp", extab_padding=b""),
            Object(Matching, "game/fn_801B89C8.c"),
            Object(Matching, "game/GetCourseSelectEntry.c"),
            Object(Matching, "game/fn_801BA318.c"),
            Object(Matching, "game/GetFrameIdxFromVisualIdx.c"),
            Object(Matching, "game/fn_801D394C.c"),
            Object(Matching, "game/fn_801D3FF0.c"),
            Object(Matching, "game/PlayerData_ResolveUnlockedIdByIndex.c"),
            Object(Matching, "game/fn_801D67F4.c"),
            Object(Matching, "game/fn_801D895C.c"),
            Object(Matching, "game/fn_801D8A98.c"),
            Object(Matching, "game/fn_801D8D3C.c"),
            Object(Matching, "game/fn_801D8DF8.c"),
            Object(Matching, "game/fn_801D9180.c"),
            Object(Matching, "game/fn_801D9F88.c", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/fn_801DAAA4.cpp", extab_padding=b""),
            Object(Matching, "game/fn_801DAB20.c"),
            Object(Matching, "game/fn_801DAB7C.c"),
            Object(Matching, "game/fn_801DAE54.c"),
            Object(Matching, "game/fn_801DAEC0.cpp", extab_padding=b""),
            Object(Matching, "game/fn_801DB68C.c"),
            Object(Matching, "game/DisplayContext_Init.c"),
            Object(Matching, "game/PathData_GetByContext.c"),
            Object(Matching, "game/fn_801DE15C.c"),
            Object(Matching, "game/fn_801DE1B0.cpp", extab_padding=b""),
            Object(Matching, "game/fn_801DE6E8.c"),
            Object(Matching, "game/fn_801E5A84.c"),
            Object(Matching, "game/fn_801E6670.c"),
            Object(Matching, "game/fn_801E6E4C.c"),
            Object(Matching, "game/KartController_TimedUpdate.cpp", extab_padding=b""),
            Object(Matching, "game/dtor_801CCA30.cpp", extab_padding=b"\x00\x00"),
            Object(Matching, "game/dtor_801DC460.cpp", extab_padding=b"\x00\x00"),
            Object(Matching, "game/dtor_801E89E8.cpp", extab_padding=b"\x00\x00"),
            Object(Matching, "game/dtor_801E8A64.cpp", extab_padding=b"\x00\x00"),
            Object(Matching, "game/dtor_801E8AE0.cpp", extab_padding=b"\x00\x00"),
            Object(Matching, "game/dtor_801E8B70.cpp", extab_padding=b"\x00\x00"),
            Object(Matching, "game/dtor_801E8C00.cpp", extab_padding=b"\x00\x00"),
            Object(Matching, "game/dtor_801F0B58.cpp", extab_padding=b"\x00\x00"),
            Object(Matching, "game/dtor_801F2724.cpp", extab_padding=b"\x00\x00"),
            Object(Matching, "game/fn_801E9094.c"),
            Object(Matching, "game/fn_801EC3DC.c"),
            Object(Matching, "game/fn_801F0C80.c"),
            Object(Matching, "game/fn_801F6804.c"),
            Object(Matching, "game/fn_801F8E58.c"),
            Object(Matching, "game/fn_801F8FCC.c"),
            Object(Matching, "game/fn_801F93C8.c"),
            Object(Matching, "game/fn_801F98CC.c"),
            Object(Matching, "game/fn_801FBD14.c"),
            Object(Matching, "game/fn_801FBD94.c"),
            Object(Matching, "game/fn_801B76C8.cpp"),
            Object(Matching, "game/fn_801B785C.cpp"),
            Object(Matching, "game/fn_801B7894.cpp"),
            Object(Matching, "game/fn_801B78E0.cpp"),
            Object(Matching, "game/fn_801BA110.cpp", extab_padding=b""),
            Object(Matching, "game/fn_801C3108.c"),
            Object(Matching, "game/fn_801DA700.c"),
            Object(Matching, "game/x10.c"),
            Object(Matching, "game/ItemHolder_SetItem.c"),
            Object(Matching, "game/ItemHolder_Update.cpp"),
            Object(Matching, "game/fn_801EB91C.c"),
            Object(Matching, "game/EnemyRunType2_CalcSteering.c"),
            Object(Matching, "game/fn_801ECB04.c"),
            Object(Matching, "game/fn_801F5A64.cpp"),
            Object(Matching, "game/fn_801F7B2C.c"),
            Object(Matching, "game/fn_801F7B74.c"),
            Object(Matching, "game/fn_801F7CD8.cpp", extab_padding=b""),
            Object(Matching, "game/fn_801F7D50.cpp", extab_padding=b""),
            Object(Matching, "game/fn_801F9888.c"),
            Object(Matching, "game/fn_801F98E8.c"),
            Object(Matching, "game/fn_801F9F04.cpp"),
            Object(Matching, "game/fn_801F9F54.cpp"),
            Object(Matching, "game/fn_801F9FEC.cpp"),
            Object(Matching, "game/fn_801FA2E0.cpp"),
            Object(Matching, "game/fn_801FA864.cpp", extab_padding=b""),
            Object(Matching, "game/fn_801FAB20.cpp"),
            Object(Matching, "game/fn_801FAB58.cpp"),
            Object(Matching, "game/fn_801FB5FC.cpp"),
            Object(Matching, "game/fn_801FB6C0.c"),
            Object(Matching, "game/fn_801FB720.c"),
            Object(Matching, "game/fn_801FC1A8.cpp"),
        ],
    },
    {
        "lib": "game_g4",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": [
            Object(Matching, "game/Scene_80163554.cpp"),
            Object(Matching, "game/Scene_8015AE3C.cpp"),
            Object(Matching, "game/Scene_8015B698.cpp"),
            Object(Matching, "game/Scene_8015B70C.cpp"),
            Object(Matching, "game/Scene_8015BC08.cpp"),
            Object(Matching, "game/Scene_8015BE0C.cpp"),
            Object(Matching, "game/Scene_8015BED4.cpp"),
            Object(Matching, "game/Scene_801622C8.cpp"),
            Object(Matching, "game/Scene_80162B00.cpp"),
            Object(Matching, "game/Scene_801634C4.cpp"),
            Object(Matching, "game/Scene_801636B4.cpp"),
            Object(Matching, "game/Scene_80163614.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_80163804.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_8015B6D0.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_8015BE44.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_80165454.cpp"),
            Object(Matching, "game/Scene_80165BCC.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_80165E90.cpp"),
            Object(Matching, "game/Scene_801660EC.cpp", extra_cflags=["-use_lmw_stmw on"]),
            Object(Matching, "game/Scene_80166B28.cpp"),
            Object(Matching, "game/Scene_8016700C.cpp"),
            Object(Matching, "game/Sound_8016730C.cpp"),
            Object(Matching, "game/Sound_801674AC.cpp"),
            Object(Matching, "game/Rumble.cpp"),
            Object(Matching, "game/CourseMarker.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Sound_8016A2C0.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_8016AABC.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_8016ACD4.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/HsdRes_8016B0A0.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "sound/SoundMgr_Front.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "sound/SoundMgr_Weather.c", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "sound/SoundMgr_PointSetMgr.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "sound/SoundMgr_PointSetNew.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemBox_8016CC04.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/ItemBox_8016CEA0.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_8016D79C.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_8016D920.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_8016E1C0.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/Scene_8016EACC.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/DebrisBurst.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/Scene_8016FC14.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_8016FC74.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_8016FD0C.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_801704A0.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_801706C8.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/Scene_801707FC.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/LensFlare.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/LavaSplash.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            Object(Matching, "game/Scene_801709FC.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]),
            Object(Matching, "game/Scene_801734B0.cpp", extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on", "-use_lmw_stmw on"]),
            # g4-end
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
            Object(Matching, "sound/SoundObj_PlaySE_Direct.c"),
        ],
    },
    SdkLib(
        "dolphin_base",
        [
            Object(Matching, "dolphin/base/PPCArch.c"),
        ],
    ),
    SdkLib(
        "dolphin_db",
        [
            Object(Matching, "dolphin/db/db.c"),
        ],
    ),
    SdkLib(
        "dolphin_os",
        [
            Object(Matching, "dolphin/os/OS.c"),
            Object(Matching, "dolphin/os/OSAlarm.c"),
            Object(Matching, "dolphin/os/OSArena.c"),
            Object(Matching, "dolphin/os/OSAudioSystem.c"),
            Object(Matching, "dolphin/os/OSCache.c"),
            Object(Matching, "dolphin/os/OSContext.c"),
            Object(Matching, "dolphin/os/OSError.c"),
            Object(Matching, "dolphin/os/OSFont.c"),
            Object(Matching, "dolphin/os/OSInterrupt.c"),
            Object(Matching, "dolphin/os/OSLink.c"),
            Object(Matching, "dolphin/os/OSMessage.c"),
            Object(Matching, "dolphin/os/OSMemory.c"),
            Object(Matching, "dolphin/os/OSMutex.c"),
            Object(Matching, "dolphin/os/OSReboot.c"),
            Object(Matching, "dolphin/os/OSReset.c"),
            Object(Matching, "dolphin/os/OSResetSW.c"),
            Object(Matching, "dolphin/os/OSRtc.c"),
            Object(Matching, "dolphin/os/OSSemaphore.c"),
            Object(Matching, "dolphin/os/OSSync.c"),
            Object(Matching, "dolphin/os/OSThread.c"),
            Object(Matching, "dolphin/os/OSTime.c"),
        ],
        revision=1,
    ),
    SdkLib(
        "dolphin_mtx",
        [
            Object(Matching, "dolphin/mtx/mtx.c"),
            Object(Matching, "dolphin/mtx/mtxvec.c"),
            Object(Matching, "dolphin/mtx/mtx44.c"),
            Object(Matching, "dolphin/mtx/vec.c"),
            Object(Matching, "dolphin/mtx/quat.c"),
        ],
        extra_cflags=["-char signed"],
    ),
    SdkLib(
        "dolphin_vi",
        [
            Object(Matching, "dolphin/vi/vi.c"),
        ],
    ),
    SdkLib(
        "dolphin_ai",
        [
            Object(Matching, "dolphin/ai/ai.c"),
        ],
    ),
    SdkLib(
        "dolphin_ar",
        [
            Object(Matching, "dolphin/ar/ar.c"),
            Object(Matching, "dolphin/ar/arq.c"),
        ],
    ),
    SdkLib(
        "dolphin_dsp",
        [
            Object(Matching, "dolphin/dsp/dsp.c"),
            Object(Matching, "dolphin/dsp/dsp_debug.c"),
            Object(Matching, "dolphin/dsp/dsp_task.c"),
        ],
    ),
    SdkLib(
        "dolphin_si",
        [
            Object(Matching, "dolphin/si/SIBios.c"),
            Object(Matching, "dolphin/si/SISamplingRate.c"),
        ],
    ),
    SdkLib(
        "dolphin_dvd",
        [
            Object(Matching, "dolphin/dvd/dvdfs.c"),
            Object(Matching, "dolphin/dvd/dvdqueue.c"),
            Object(Matching, "dolphin/dvd/dvderror.c"),
            Object(Matching, "dolphin/dvd/dvdidutils.c"),
            Object(Matching, "dolphin/dvd/dvdFatal.c"),
            Object(Matching, "dolphin/dvd/fstload.c"),
        ],
        extra_cflags=["-char signed"],
    ),
    SdkLib(
        "dolphin_exi",
        [
            Object(Matching, "dolphin/exi/EXIBios.c", extra_cflags=["-schedule off"]),
            Object(Matching, "dolphin/exi/EXIUart.c"),
        ],
    ),
    SdkLib(
        "dolphin_gx",
        [
            Object(Matching, "dolphin/gx/GXInit.c"),
            Object(Matching, "dolphin/gx/GXFifo.c"),
            Object(Matching, "dolphin/gx/GXAttr.c"),
            Object(Matching, "dolphin/gx/GXMisc.c"),
            Object(Matching, "dolphin/gx/GXGeometry.c"),
            Object(Matching, "dolphin/gx/GXFrameBuf.c"),
            Object(Matching, "dolphin/gx/GXLight.c"),
            Object(Matching, "dolphin/gx/GXTexture.c"),
            Object(Matching, "dolphin/gx/GXBump.c"),
            Object(Matching, "dolphin/gx/GXTev.c"),
            Object(Matching, "dolphin/gx/GXPixel.c"),
            Object(Matching, "dolphin/gx/GXDisplayList.c"),
            Object(Matching, "dolphin/gx/GXTransform.c"),
            Object(Matching, "dolphin/gx/GXPerf.c"),
        ],
        revision=0,
    ),
    {
        "lib": "MSL_C",
        "mw_version": "GC/2.7",
        "cflags": cflags_msl,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "MSL_C/string.c"),
            Object(Matching, "MSL_C/GCN_mem_alloc.c", extra_cflags=["-str nopool"]),
            Object(Matching, "MSL_C/abort_exit.c"),
            Object(Matching, "MSL_C/ansi_fp.c"),
            Object(Matching, "MSL_C/arith.c"),
            Object(Matching, "MSL_C/critical_regions.gamecube.c"),
            Object(Matching, "MSL_C/ctype.c"),
            Object(Matching, "MSL_C/mem.c"),
            Object(Matching, "MSL_C/mem_funcs.c"),
            Object(Matching, "MSL_C/printf.c"),
            Object(Matching, "MSL_C/rand.c"),
            Object(Matching, "MSL_C/scanf.c"),
            Object(Matching, "MSL_C/signal.c"),
            Object(Matching, "MSL_C/strtoul.c"),
            Object(Matching, "MSL_C/float.c"),
            Object(Matching, "MSL_C/math/e_acos.c"),
            Object(Matching, "MSL_C/math/e_asin.c"),
            Object(Matching, "MSL_C/math/e_atan2.c"),
            Object(Matching, "MSL_C/math/e_exp.c"),
            Object(Matching, "MSL_C/math/e_fmod.c"),
            Object(Matching, "MSL_C/math/e_log.c"),
            Object(Matching, "MSL_C/math/e_pow.c"),
            Object(Matching, "MSL_C/math/e_rem_pio2.c"),
            Object(Matching, "MSL_C/math/k_cos.c"),
            Object(Matching, "MSL_C/math/k_rem_pio2.c"),
            Object(Matching, "MSL_C/math/k_sin.c"),
            Object(Matching, "MSL_C/math/k_tan.c"),
            Object(Matching, "MSL_C/math/s_atan.c"),
            Object(Matching, "MSL_C/math/s_copysign.c"),
            Object(Matching, "MSL_C/math/s_cos.c"),
            Object(Matching, "MSL_C/math/s_floor.c"),
            Object(Matching, "MSL_C/math/s_frexp.c"),
            Object(Matching, "MSL_C/math/s_ldexp.c"),
            Object(Matching, "MSL_C/math/s_modf.c"),
            Object(Matching, "MSL_C/math/s_sin.c"),
            Object(Matching, "MSL_C/math/s_tan.c"),
            Object(Matching, "MSL_C/math/w_acos.c"),
            Object(Matching, "MSL_C/math/w_asin.c"),
            Object(Matching, "MSL_C/math/w_atan2.c"),
            Object(Matching, "MSL_C/math/w_exp.c"),
            Object(Matching, "MSL_C/math/w_fmod.c"),
            Object(Matching, "MSL_C/math/w_log.c"),
            Object(Matching, "MSL_C/math/w_pow.c"),
            Object(Matching, "MSL_C/math_ppc.c"),
            Object(Matching, "MSL_C/Gecko_ExceptionPPC.c"),
            Object(Matching, "MSL_C/mbstring.c"),
            Object(Matching, "MSL_C/alloc.c"),
            Object(Matching, "MSL_C/wmem.c"),
            Object(Matching, "MSL_C/wctype.c"),
            Object(Matching, "MSL_C/wprintf.c"),
        ],
    },
    DolphinLib(
        "dolphin_stubs",
        [
            Object(Matching, "dolphin/amcstubs/AmcExi2Stubs.c"),
            Object(Matching, "dolphin/odenotstub/odenotstub.c"),
            Object(Matching, "dolphin/odemustubs/odemustubs.c"),
        ],
    ),
    {
        "lib": "TRK_MINNOW_DOLPHIN",
        "mw_version": "GC/2.6",
        "cflags": cflags_trk,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "TRK_MINNOW_DOLPHIN/mainloop.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/nubevent.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/nubinit.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/msg.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/msgbuf.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/serpoll.c", extra_cflags=["-sdata 8"]),
            Object(Matching, "TRK_MINNOW_DOLPHIN/usr_put.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/dispatch.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/mutex_TRK.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/notify.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/flush_cache.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/mem_TRK.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/mpc_7xx_603e.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/main_TRK.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/dolphin_trk_glue.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/targcont.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/target_options.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/UDP_Stubs.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/CircleBuffer.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/MWTrace.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/MWCriticalSection_gc.cpp"),
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


def _inject_jvs_metrics_ctor_bridge() -> None:
    """Use symbol-only ctor bridging for this EH-free three-member TU.

    The existing extab rule runs `dtk extab clean`, which rejects objects with
    no extab section. Clone the normal SJIS rule without changing compilation
    flags, then apply only the existing per-TU symbol-name bridge.
    """
    build_ninja = Path("build.ninja")
    text = build_ninja.read_text(encoding="utf-8")
    # The first configure after adding a split has no source edge yet. Ninja
    # runs SPLIT and regenerates this file before compiling the new object.
    if "JvsInputMetrics.o:" not in text:
        return
    start = text.index("rule mwcc_sjis\n")
    end = text.index("\nrule ", start + 1)
    rule = text[start:end]
    rule = rule.replace("rule mwcc_sjis\n", "rule mwcc_sjis_ctor_bridge\n", 1)
    hook = " && $python tools/postprocess_sdata2.py $out $out"
    assert hook in rule
    rule = rule.replace(hook, " && $python tools/postprocess_extab_user.py $out" + hook, 1)
    target = "build build\\GNLJ82\\src\\game\\JvsInputMetrics.o: mwcc_sjis_extab"
    if sys.platform != "win32":
        target = "build build/GNLJ82/src/game/JvsInputMetrics.o: mwcc_sjis_extab"
    assert target in text
    text = text.replace(target, target.replace("mwcc_sjis_extab", "mwcc_sjis_ctor_bridge"), 1)
    text = text[:start] + rule + "\n" + text[start:]
    build_ninja.write_text(text, encoding="utf-8")


def _inject_kart_character_data_alignment() -> None:
    """Keep this EH/BSS-free leaf TU's observed four-byte table alignment.

    MWLD symbol alignment in .comment overrides ELF section alignment. This
    TU has no common/BSS or lifetime metadata requiring that comment section.
    Only layout metadata is removed; text/data bytes and relocations stay native.
    """
    build_ninja = Path("build.ninja")
    text = build_ninja.read_text(encoding="utf-8")
    target = "build build\\GNLJ82\\src\\game\\KartCharacterParam.o: mwcc_sjis"
    if sys.platform != "win32":
        target = "build build/GNLJ82/src/game/KartCharacterParam.o: mwcc_sjis"
    if target not in text:
        return
    start = text.index("rule mwcc_sjis\n")
    end = text.index("\nrule ", start + 1)
    rule = text[start:end].replace("rule mwcc_sjis\n", "rule mwcc_sjis_kart_character\n", 1)
    hook = " && $python tools/postprocess_sdata2.py $out $out"
    assert hook in rule
    rule = rule.replace(hook, hook + " && $python tools/postprocess_data_alignment.py $out", 1)
    text = text.replace(target, target.replace("mwcc_sjis", "mwcc_sjis_kart_character"), 1)
    text = text[:start] + rule + "\n" + text[start:]
    build_ninja.write_text(text, encoding="utf-8")


def _inject_kartfx_chargeicon_data_alignment() -> None:
    """Preserve the original four-byte alignment of this owned jump table.

    The TU has only native text, one jump table and plain EH8/index12, with
    no common/BSS or weak lifetime objects. MWLD's .comment alignment would
    otherwise round the table to eight bytes. No code/data/EH bytes change.
    """
    build_ninja = Path("build.ninja")
    text = build_ninja.read_text(encoding="utf-8")
    target = "build build\\GNLJ82\\src\\game\\KartFxChargeIcon.o: mwcc_sjis_extab"
    if sys.platform != "win32":
        target = "build build/GNLJ82/src/game/KartFxChargeIcon.o: mwcc_sjis_extab"
    if target not in text:
        return
    start = text.index("rule mwcc_sjis_extab\n")
    end = text.index("\nrule ", start + 1)
    rule = text[start:end].replace("rule mwcc_sjis_extab\n", "rule mwcc_sjis_chargeicon\n", 1)
    hook = " && $python tools/postprocess_sdata2.py $out $out"
    assert hook in rule
    rule = rule.replace(hook, hook + " && $python tools/postprocess_data_alignment.py $out", 1)
    text = text.replace(target, target.replace("mwcc_sjis_extab", "mwcc_sjis_chargeicon"), 1)
    text = text[:start] + rule + "\n" + text[start:]
    build_ninja.write_text(text, encoding="utf-8")


# TUs whose owned .data (switch jump tables) sits at a four-byte boundary in
# the target. MWLD's .comment alignment would round it to eight bytes, so the
# .comment section is dropped and .data alignment pinned to 4. Text/data bytes
# and relocations stay native.
DATA_ALIGN4_TUS = [
    "game/clItemBoxManager_StepTable",
    "game/ItemUseStats",
    "game/KartItem_RenderCb_Modes",
]


def _inject_data_align4_tus() -> None:
    build_ninja = Path("build.ninja")
    text = build_ninja.read_text(encoding="utf-8")
    sep = "\\" if sys.platform == "win32" else "/"
    hook = " && $python tools/postprocess_sdata2.py $out $out"
    for base_rule in ("mwcc_sjis", "mwcc_sjis_extab"):
        new_rule = base_rule + "_align4"
        users = []
        for tu in DATA_ALIGN4_TUS:
            obj = ("build/GNLJ82/src/" + tu + ".o").replace("/", sep)
            target = "build " + obj + ": " + base_rule + " "
            if target in text:
                users.append(target)
        if not users:
            continue
        start = text.index("rule " + base_rule + "\n")
        end = text.index("\nrule ", start + 1)
        rule = text[start:end].replace("rule " + base_rule + "\n", "rule " + new_rule + "\n", 1)
        assert hook in rule
        rule = rule.replace(hook, hook + " && $python tools/postprocess_data_alignment.py $out", 1)
        for target in users:
            text = text.replace(target, target.replace(": " + base_rule + " ", ": " + new_rule + " "), 1)
        text = text[:start] + rule + "\n" + text[start:]
    build_ninja.write_text(text, encoding="utf-8")


if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
    _inject_sdata2_postprocess(config)
    _inject_jvs_metrics_ctor_bridge()
    _inject_kart_character_data_alignment()
    _inject_kartfx_chargeicon_data_alignment()
    _inject_data_align4_tus()
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
