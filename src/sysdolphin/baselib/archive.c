// mkgp2's archive.c: HSD_ArchiveParse lives elsewhere in this build, and the
// TU has extra helpers that are not in melee. Names of the non-melee
// functions are guesses from their behavior.
#include "archive.h"

#include <Runtime/platform.h>

#include "memory.h"
#include <string.h>

char* HSD_ArchiveGetPublicName(HSD_Archive* archive, int index)
{
    if (index < 0 || archive->header.nb_public <= (u32) index) {
        return NULL;
    }

    return archive->symbols + archive->public_info[index].symbol;
}

void* HSD_ArchiveGetPublicAddress(HSD_Archive* archive, const char* symbols)
{
    u32 i;

    for (i = 0; i < archive->header.nb_public; i++) {
        int comparison =
            strcmp(archive->symbols + archive->public_info[i].symbol, symbols);

        if (comparison == 0) {
            // If both strings are equal, we've found the node
            return archive->data + archive->public_info[i].offset;
        }
    }

    return NULL;
}

u8* HSD_ArchiveTakeData(HSD_Archive* archive)
{
    u8* data;

    if (archive == NULL) {
        return NULL;
    }
    data = archive->data;
    archive->data = NULL;
    return data;
}

void HSD_ArchiveFree(HSD_Archive* archive)
{
    if (archive == NULL) {
        return;
    }
    if (!(archive->flags & HSD_ARCHIVE_DONT_FREE)) {
        if (archive->data != NULL) {
            HSD_Free(archive->data);
        }
        if (archive->reloc_info != NULL) {
            HSD_Free(archive->reloc_info);
        }
        if (archive->public_info != NULL) {
            HSD_Free(archive->public_info);
        }
        if (archive->extern_info != NULL) {
            HSD_Free(archive->extern_info);
        }
        if (archive->symbols != NULL) {
            HSD_Free(archive->symbols);
        }
        if (archive->name != NULL) {
            HSD_Free(archive->name);
        }
    }
    HSD_Free(archive);
}
