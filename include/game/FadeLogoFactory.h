#ifndef GAME_FADELOGO_FACTORY_H
#define GAME_FADELOGO_FACTORY_H

/*
 * Fading logo task (0x8020E2D8..0x8020F220).
 *
 *   PopupRoot (vtable lbl_8048ECF8, inline) -> PopupTask (vtable lbl_8048ED10, inline)
 *     FadeLogoScene (vtable FadeLogoScene_vtable_804ECAA8): owns a task list holding one FadeLogo.
 *     FadeTaskBase (vtable FadeTaskBase_vtable_804ECB1C) -> FadeLogo (vtable FadeLogo_vtable_804ECB04).
 *   TaskListBase (vtable lbl_804ECAC0) -> TaskListImpl (vtable lbl_804ECB44).
 */

#include "game/FlowScene.h"

#include "game/types/PopupRoot.h"

#include "game/types/PopupTask.h"

#include "game/types/TaskNode.h"

#include "game/types/TaskIter.h"

/* count + sentinel node {prev = last, next = first}. */
#include "game/types/TaskEntriesBase.h"

#include "game/types/TaskEntriesMid.h"

#include "game/types/TaskEntries.h"

struct TaskListBase {
    virtual ~TaskListBase();
    virtual void Update() = 0;
    virtual void Draw() = 0;
    TaskEntries entries;
    TaskListBase() {}
    void KillAll();
    bool Add(PopupTask *task, int delay);
};

#include "game/types/TaskListImpl.h"

#include "game/types/FadeLogoScene.h"

#endif
