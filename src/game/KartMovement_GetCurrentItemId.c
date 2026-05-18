typedef struct KartMovement KartMovement;

/* Returns the "current item id" cached at KartMovement+0x2C0.
 * Note: this field is stale after the item is used. For live item state,
 * read KM+0x340 -> ItemSlotEntry+0x34 (ItemSlotEntry: +0x2C=state, +0x34=itemId). */
int KartMovement_GetCurrentItemId(KartMovement *km) {
    return *(int *)((char *)km + 0x2c0);
}
