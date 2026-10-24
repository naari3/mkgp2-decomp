/*
 * 0x8015B6D0..0x8015B70C: factory for the scene built by fn_8015AFCC.
 * Real C++ new-expression for the DELETEPOINTER extab action; mangled
 * names are bridged in tools/extab_user_renames.json.
 */

struct Scene8015AFCC {
    char _opaque[0x104];
    Scene8015AFCC();
};

#pragma exceptions on

extern "C" Scene8015AFCC *fn_8015B6D0(void) {
    return new Scene8015AFCC;
}

#pragma exceptions reset
