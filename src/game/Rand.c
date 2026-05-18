extern unsigned short fn_80278C54(void);

#pragma exceptions on
unsigned short Rand15(void) {
    return fn_80278C54();
}
#pragma exceptions reset
