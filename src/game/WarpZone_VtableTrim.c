extern char lbl_80411DD0[];  /* WarpZone vtable */

void WarpZone_VtableTrim(void *self)
{
    *(char **)self = lbl_80411DD0;
}

int fn_800AA8E0(void)
{
    return 0;
}

int fn_800AA8E8(void)
{
    return 0;
}

void fn_800AA8F0(void)
{
}

int fn_800AA8F4(void)
{
    return 0;
}
