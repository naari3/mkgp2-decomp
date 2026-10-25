#include <wprintf.h>

#include <ansi_fp.h>
#include <mbstring.h>
#include <wmem.h>
#include <wscanf.h>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <locale>
#include <cstdarg>
#include <cstddef>
#include <va_list>

extern unsigned short __wctype_map[256];
#define iswupper(c) ((c < 0x100) ? (int)(__wctype_map[c] & 0x80) : 0)
#define iswdigit(c) ((c < 0x100) ? (int)(__wctype_map[c] & 0x10) : 0)

#define LDBL_MANT_DIG 53

#define TARGET_FLOAT_BITS 64
#define TARGET_FLOAT_BYTES (TARGET_FLOAT_BITS / 8)
#define TARGET_FLOAT_MAX_EXP LDBL_MAX_EXP
#define TARGET_FLOAT_MANT_DIG LDBL_MANT_DIG
#define TARGET_FLOAT_IMPLICIT_J_BIT 1
#define TARGET_FLOAT_MANT_BITS (TARGET_FLOAT_MANT_DIG - TARGET_FLOAT_IMPLICIT_J_BIT)
#define TARGET_FLOAT_EXP_BITS (TARGET_FLOAT_BITS - TARGET_FLOAT_MANT_BITS - 1)

enum justification_options { left_justification, right_justification, zero_fill };

enum sign_options { only_minus, sign_always, space_holder };

enum argument_options {
    normal_argument,
    char_argument,
    short_argument,
    long_argument,
    long_long_argument,
    long_double_argument,
    wchar_argument,

    intmax_argument,
    size_t_argument,
    ptrdiff_argument,
};

typedef struct {
    unsigned char justification_options;
    unsigned char sign_options;
    unsigned char precision_specified;
    unsigned char alternate_form;
    unsigned char argument_options;
    wchar_t conversion_char;
    int field_width;
    int precision;
} print_format;

extern void __msl_runtime_constraint_violation_s(const char* msg, void* ptr, int error);

static const wchar_t* parse_format(const wchar_t* format_string, va_list* arg, print_format* format) {
    print_format f;
    const wchar_t* s = format_string;
    wchar_t c;
    int flag_found;
    f.justification_options = right_justification;
    f.sign_options = only_minus;
    f.precision_specified = 0;
    f.alternate_form = 0;
    f.argument_options = normal_argument;
    f.field_width = 0;
    f.precision = 0;

    if ((c = *++s) == '%') {
        f.conversion_char = c;
        *format = f;
        return s + 1;
    }

    while (1) {
        flag_found = 1;

        switch (c) {
        case '-':
            f.justification_options = left_justification;
            break;
        case '+':
            f.sign_options = sign_always;
            break;
        case ' ':
            if (f.sign_options != sign_always) {
                f.sign_options = space_holder;
            }
            break;
        case '#':
            f.alternate_form = 1;
            break;
        case '0':
            if (f.justification_options != left_justification) {
                f.justification_options = zero_fill;
            }
            break;
        default:
            flag_found = 0;
            break;
        }

        if (flag_found) {
            c = *++s;
        } else {
            break;
        }
    }

    if (c == '*') {
        if ((f.field_width = va_arg(*arg, int)) < 0) {
            f.justification_options = left_justification;
            f.field_width = -f.field_width;
        }

        c = *++s;
    } else {
        while (iswdigit(c)) {
            f.field_width = f.field_width * 10 + (c - '0');
            c = *++s;
        }
    }

    if (f.field_width > 509) {
        f.conversion_char = 0xFFFF;
        *format = f;
        return s + 1;
    }

    if (c == '.') {
        f.precision_specified = 1;

        if ((c = *++s) == '*') {
            if ((f.precision = va_arg(*arg, int)) < 0) {
                f.precision_specified = 0;
            }

            c = *++s;
        } else {
            while (iswdigit(c))
            {
                f.precision = f.precision * 10 + (c - '0');
                c = *++s;
            }
        }
    }

    flag_found = 1;

    switch (c) {
    case 'h':
        f.argument_options = short_argument;

        if (s[1] == 'h') {
            f.argument_options = char_argument;
            c = *++s;
        }

        break;

    case 'l':
        f.argument_options = long_argument;

        if (s[1] == 'l') {
            f.argument_options = long_long_argument;
            c = *++s;
        }
        break;
    case 'L':
        f.argument_options = long_double_argument;
        break;
    default:
        flag_found = 0;
        break;
    }

    if (flag_found) {
        c = *++s;
    }

    switch (f.conversion_char = c) {
    case 'd':
    case 'i':
    case 'u':
    case 'o':
    case 'x':
    case 'X':
        if (f.argument_options == long_double_argument) {
            f.argument_options = 4;
        }

        if (!f.precision_specified) {
            f.precision = 1;
        } else if (f.justification_options == zero_fill) {
            f.justification_options = right_justification;
        }
        break;

    case 'f':
    case 'F':
        if (f.argument_options == short_argument ||
            f.argument_options == long_long_argument)
        {
            f.conversion_char = 0xFFFF;
            break;
        }

        if (!f.precision_specified) {
            f.precision = 6;
        }
        break;

    case 'g':
    case 'G':
        if (!f.precision) {
            f.precision = 1;
        }

    case 'e':
    case 'E':
        if (f.argument_options == short_argument ||
            f.argument_options == long_long_argument || f.argument_options == char_argument)
        {
            f.conversion_char = 0xFFFF;
            break;
        }

        if (!f.precision_specified) {
            f.precision = 6;
        }
        break;

    case 'p':
        f.argument_options = long_argument;
        f.alternate_form = 1;
        f.conversion_char = 'x';
        f.precision = 8;
        break;

    case 'c':
        if (f.argument_options == long_argument) {
            f.argument_options = wchar_argument;
        } else {
            if (f.precision_specified || f.argument_options != normal_argument) {
                f.conversion_char = 0xFFFF;
            }
        }

        break;

    case 's':
        if (f.argument_options == long_argument) {
            f.argument_options = wchar_argument;
        } else {
            if (f.argument_options != normal_argument) {
                f.conversion_char = 0xFFFF;
            }
        }

        break;

    case 'n':
        if (f.argument_options == long_double_argument) {
            f.argument_options = 0x4;
        }

        break;

    default:
        f.conversion_char = 0xFFFF;
        break;
    }

    *format = f;
    return s + 1;
}

static wchar_t* long2str(signed long num, wchar_t* buff, print_format format) {
    unsigned long unsigned_num, base;
    wchar_t* p;
    int n, digits;
    int minus = 0;
    unsigned_num = num;
    minus = 0;

    p = buff;
    *--p = 0;
    digits = 0;

    if (!num && !format.precision && !(format.alternate_form && format.conversion_char == 'o')) {
        return p;
    }

    switch (format.conversion_char) {
    case 'd':
    case 'i':
        base = 10;

        if (num < 0) {
            unsigned_num = -unsigned_num;

            minus = 1;
        }
        break;

    case 'o':
        base = 8;
        format.sign_options = only_minus;
        break;

    case 'u':
        base = 10;
        format.sign_options = only_minus;
        break;

    case 'x':
    case 'X':
        base = 16;
        format.sign_options = only_minus;
        break;
    }

    do {
        n = unsigned_num % base;
        unsigned_num /= base;

        if (n < 10) {
            n += '0';
        } else {
            n -= 10;

            if (format.conversion_char == 'x') {
                n += 'a';
            } else {
                n += 'A';
            }
        }

        *--p = n;
        ++digits;
    } while (unsigned_num != 0);

    if (base == 8 && format.alternate_form && *p != '0') {
        *--p = '0';
        ++digits;
    }

    if (format.justification_options == zero_fill) {
        format.precision = format.field_width;

        if (minus || format.sign_options != only_minus)
            --format.precision;

        if (base == 16 && format.alternate_form)
            format.precision -= 2;
    }

    if (buff - p + format.precision > 509)
        return 0;

    while (digits < format.precision) {
        *--p = '0';
        ++digits;
    }

    if (base == 16 && format.alternate_form) {
        *--p = format.conversion_char;
        *--p = '0';
    }

    if (minus) {
        *--p = '-';
    } else if (format.sign_options == sign_always) {
        *--p = '+';
    } else if (format.sign_options == space_holder) {
        *--p = ' ';
    }

    return p;
}

static wchar_t* longlong2str(signed long long num, wchar_t* pBuf, print_format fmt) {
    unsigned long long unsigned_num, base;
    wchar_t* p;
    int n, digits;
    int minus = 0;
    unsigned_num = num;
    minus = 0;
    p = pBuf;
    *--p = 0;
    digits = 0;

    if (!num && !fmt.precision && !(fmt.alternate_form && fmt.conversion_char == 'o')) {
        return p;
    }

    switch (fmt.conversion_char) {
    case 'd':
    case 'i':
        base = 10;

        if (num < 0) {
            unsigned_num = -unsigned_num;

            minus = 1;
        }
        break;
    case 'o':
        base = 8;
        fmt.sign_options = only_minus;
        break;
    case 'u':
        base = 10;
        fmt.sign_options = only_minus;
        break;
    case 'x':
    case 'X':
        base = 16;
        fmt.sign_options = only_minus;
        break;
    }

    do {
        n = unsigned_num % base;
        unsigned_num /= base;

        if (n < 10) {
            n += '0';
        } else {
            n -= 10;
            if (fmt.conversion_char == 'x') {
                n += 'a';
            } else {
                n += 'A';
            }
        }

        *--p = n;
        ++digits;
    } while (unsigned_num != 0);

    if (base == 8 && fmt.alternate_form && *p != '0') {
        *--p = '0';
        ++digits;
    }

    if (fmt.justification_options == zero_fill) {
        fmt.precision = fmt.field_width;

        if (minus || fmt.sign_options != only_minus) {
            --fmt.precision;
        }

        if (base == 16 && fmt.alternate_form) {
            fmt.precision -= 2;
        }
    }

    if (pBuf - p + fmt.precision > 509) {
        return 0;
    }

    while (digits < fmt.precision) {
        *--p = '0';
        ++digits;
    }

    if (base == 16 && fmt.alternate_form) {
        *--p = fmt.conversion_char;
        *--p = '0';
    }

    if (minus) {
        *--p = '-';
    } else if (fmt.sign_options == sign_always) {
        *--p = '+';
    } else if (fmt.sign_options == space_holder) {
        *--p = ' ';
    }

    return p;
}


static void round_decimal(decimal* dec, int new_length) {
    char c;
    char* p;
    int carry;

    if (new_length < 0) {
    return_zero:
        dec->exp = 0;
        dec->sig.length = 1;
        *dec->sig.text = '0';
        return;
    }

    if (new_length >= dec->sig.length) {
        return;
    }

    p = (char*)dec->sig.text + new_length + 1;
    c = *--p - '0';

    if (c == 5) {
        char* q = &((char*)dec->sig.text)[dec->sig.length];

        while (--q > p && *q == '0')
            ;
        carry = q == p ? p[-1] & 1 : 1;
    } else {
        carry = c > 5;
    }

    while (new_length != 0) {
        c = *--p - '0' + carry;

        if ((carry = (c > 9)) != 0 || c == 0) {
            --new_length;
        } else {
            *p = c + '0';
            break;
        }
    }

    if (carry != 0) {
        dec->exp += 1;
        dec->sig.length = 1;
        *dec->sig.text = '1';
        return;
    } else if (new_length == 0) {
        goto return_zero;
    }

    dec->sig.length = new_length;
}

static wchar_t* float2str(long double num, wchar_t* buff, print_format format) {
    wchar_t out_buf[0x100];
    decimal dec;
    decform form;
    wchar_t* p;
    char* p2;
    wchar_t c;
    char* p3;
    unsigned char* q;
    int n, digits, sign;
    int int_digits, frac_digits;
    int radix_marker;
    int used_bytes;

    radix_marker = '.';

    if (format.precision > 509) {
        return 0;
    }

    form.style = 0;
    form.digits = 0x20;
    __num2dec(&form, num, &dec);
    p3 = (char*)dec.sig.text + dec.sig.length;

    while (dec.sig.length > 1 && *--p3 == '0') {
        --dec.sig.length;
        ++dec.exp;
    }

    switch (*dec.sig.text) {
    case '0':
        dec.exp = 0;
        break;
    case 'I':
        if (num < 0) {
            c = format.conversion_char;
            p = buff - 5;

            if (iswupper(c)) {
                wcscpy(p, L"-INF");
            } else {
                wcscpy(p, L"-inf");
            }
        } else {
            c = format.conversion_char;
            p = buff - 4;
            if (iswupper(c)) {
                wcscpy(p, L"INF");
            } else {
                wcscpy(p, L"inf");
            }
        }

        return p;

    case 'N':
        p = buff - 4;
        wcscpy(p, L"NaN");
        return p;
    }

    dec.exp += (dec.sig.length - 1);

    p2 = (char*)&out_buf + sizeof(out_buf);
    *--p2 = 0;

    switch (format.conversion_char) {
    case 'g':
    case 'G':

        if (dec.sig.length > format.precision) {
            round_decimal(&dec, format.precision);
        }

        if (dec.exp < -4 || dec.exp >= format.precision) {
            if (format.alternate_form) {
                --format.precision;
            } else {
                format.precision = dec.sig.length - 1;
            }

            if (format.conversion_char == 'g') {
                format.conversion_char = 'e';
            } else {
                format.conversion_char = 'E';
            }

            goto e_format;
        }

        if (format.alternate_form) {
            format.precision -= dec.exp + 1;
        } else {
            if ((format.precision = dec.sig.length - (dec.exp + 1)) < 0) {
                format.precision = 0;
            }
        }

        goto f_format;

    case 'e':
    case 'E':
    e_format:

        if (dec.sig.length > format.precision + 1) {
            round_decimal(&dec, format.precision + 1);
        }

        n = dec.exp;
        sign = '+';

        if (n < 0) {
            n = -n;
            sign = '-';
        }

        for (digits = 0; n || digits < 2; ++digits) {
            *--p2 = n % 10 + '0';
            n /= 10;
        }

        *--p2 = sign;
        *--p2 = format.conversion_char;

        used_bytes = (intptr_t)out_buf - (intptr_t)p2;
        if (used_bytes + format.precision > 0x1FD) {
            return NULL;
        }

        if (dec.sig.length < format.precision + 1) {
            for (n = format.precision + 1 - dec.sig.length + 1; --n;) {
                *--p2 = '0';
            }
        }

        for (n = dec.sig.length, q = (unsigned char*)dec.sig.text + dec.sig.length; --n;) {
            *--p2 = *--q;
        }

        if (format.precision || format.alternate_form) {
            *--p2 = radix_marker;
        }

        *--p2 = *dec.sig.text;

        if (dec.sign)
            *--p2 = '-';
        else if (format.sign_options == sign_always)
            *--p2 = '+';
        else if (format.sign_options == space_holder)
            *--p2 = ' ';

        break;

    case 'f':
    case 'F':
    f_format:

        if ((frac_digits = -dec.exp + dec.sig.length - 1) < 0)
            frac_digits = 0;

        if (frac_digits > format.precision) {
            round_decimal(&dec, dec.sig.length - (frac_digits - format.precision));

            if ((frac_digits = -dec.exp + dec.sig.length - 1) < 0)
                frac_digits = 0;
        }

        if ((int_digits = dec.exp + 1) < 0)
            int_digits = 0;

        if (int_digits + frac_digits > 509)
            return 0;

        q = (unsigned char*)dec.sig.text + dec.sig.length;

        for (digits = 0; digits < (format.precision - frac_digits); ++digits)
            *--p2 = '0';

        for (digits = 0; digits < frac_digits && digits < dec.sig.length; ++digits)
            *--p2 = *--q;

        for (; digits < frac_digits; ++digits)
            *--p2 = '0';

        if (format.precision || format.alternate_form)
            *--p2 = radix_marker;

        if (int_digits) {
            for (digits = 0; digits < int_digits - dec.sig.length; ++digits) {
                *--p2 = '0';
            }

            for (; digits < int_digits; ++digits) {
                *--p2 = *--q;
            }
        } else {
            *--p2 = '0';
        }

        if (dec.sign) {
            *--p2 = '-';
        } else if (format.sign_options == sign_always) {
            *--p2 = '+';
        } else if (format.sign_options == space_holder) {
            *--p2 = ' ';
        }

        break;
    }

    p = buff - strlen((char*)p2) - 1;
    mbstowcs(p, p2, strlen((char*)p2));

    return p;
}

int __wpformatter(void* (*write_proc)(void*, const wchar_t*, size_t),
                         void* proc_data, const wchar_t* fmt,
                         va_list args) {
    int num_chars, chars_written, field_width;
    const wchar_t* format_ptr;
    const wchar_t* curr_format;
    print_format format;
    signed long long_num;
    signed long long long_long_num;
    long double long_double_num;
    wchar_t buff[512];
    wchar_t* buff_ptr;
    const wchar_t* string_end;
    wchar_t fill_char = ' ';

    format_ptr = fmt;
    chars_written = 0;

    while (*format_ptr) {
        if (!(curr_format = wcschr(format_ptr, L'%'))) {
            num_chars = wcslen(format_ptr);
            chars_written += num_chars;

            if (num_chars && !(*write_proc)(proc_data, format_ptr, num_chars)) {
                return -1;
            }

            break;
        }

        num_chars = curr_format - format_ptr;
        chars_written += num_chars;

        if (num_chars && !(*write_proc)(proc_data, format_ptr, num_chars)) {
            return -1;
        }

        format_ptr = curr_format;
        format_ptr = parse_format(format_ptr, (va_list*)&args, &format);

        switch (format.conversion_char) {
        case 'd':
        case 'i':
            if (format.argument_options == long_argument) {
                long_num = va_arg(args, signed long);
            } else if (format.argument_options == long_long_argument) {
                long_long_num = va_arg(args, signed long long);
            } else {
                long_num = va_arg(args, int);
            }

            if (format.argument_options == short_argument) {
                long_num = (signed short)long_num;
            }

            if (format.argument_options == long_long_argument)
            {
                if (!(buff_ptr = longlong2str(long_long_num, buff + 512, format))) {
                    goto conversion_error;
                }
            } else {
                if (!(buff_ptr = long2str(long_num, buff + 512, format))) {
                    goto conversion_error;
                }
            }

            num_chars = buff + 512 - 1 - buff_ptr;
            break;

        case 'o':
        case 'u':
        case 'x':
        case 'X':
            if (format.argument_options == long_argument) {
                long_num = va_arg(args, unsigned long);
            } else if (format.argument_options == long_long_argument) {
                long_long_num = va_arg(args, signed long long);
            }
            else {
                long_num = va_arg(args, unsigned int);
            }

            if (format.argument_options == short_argument) {
                long_num = (unsigned short)long_num;
            }

            if ((format.argument_options == long_long_argument))
            {
                if (!(buff_ptr = longlong2str(long_long_num, buff + 512, format))) {
                    goto conversion_error;
                }
            } else {
                if (!(buff_ptr = long2str(long_num, buff + 512, format))) {
                    goto conversion_error;
                }
            }

            num_chars = buff + 512 - 1 - buff_ptr;
            break;

        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
            if (format.argument_options == long_double_argument) {
                long_double_num = va_arg(args, long double);
            } else {
                long_double_num = va_arg(args, double);
            }

            if (!(buff_ptr = float2str(long_double_num, buff + 512, format))) {
                goto conversion_error;
            }

            num_chars = buff + 512 - 1 - buff_ptr;
            break;

        case 's':
            if (format.argument_options == wchar_argument) {
                buff_ptr = va_arg(args, wchar_t*);

                if (buff_ptr == NULL) {
                    buff_ptr = L"";
                }

                if (format.alternate_form) {
                    num_chars = (unsigned char)*buff_ptr++;

                    if (format.precision_specified && num_chars > format.precision) {
                        num_chars = format.precision;
                    }
                } else if (format.precision_specified) {
                    num_chars = format.precision;

                    if ((string_end = wmemchr(buff_ptr, 0, num_chars)) != 0) {
                        num_chars = string_end - buff_ptr;
                    }

                } else {
                    num_chars = wcslen(buff_ptr);
                }

                break;
            } else {
                const char* wcs_ptr = (const char*)va_arg(args, wchar_t*);

                if (wcs_ptr == NULL) {
                    wcs_ptr = "";
                }

                if (format.alternate_form) {
                    num_chars = (unsigned char)*buff_ptr;

                    if (format.precision_specified && num_chars > format.precision) {
                        num_chars = format.precision;
                    }
                } else if (format.precision_specified) {
                    num_chars = format.precision;

                    if ((string_end = memchr(wcs_ptr, 0, num_chars)) != 0) {
                        num_chars = (intptr_t)string_end - (intptr_t)wcs_ptr;
                    }
                } else {
                    num_chars = strlen(wcs_ptr);
                }

                if ((num_chars = mbstowcs(buff, wcs_ptr, num_chars)) < 0) {
                    goto conversion_error;
                }

                buff_ptr = buff;
            }

            break;

        case 'n':

            buff_ptr = va_arg(args, wchar_t*);

            switch (format.argument_options) {
            case normal_argument:
                *(int*)buff_ptr = chars_written;
                break;
            case short_argument:
                *(signed short*)buff_ptr = chars_written;
                break;
            case long_argument:
                *(signed long*)buff_ptr = chars_written;
                break;
            case long_long_argument:
                *(signed long long*)buff_ptr = chars_written;
                break;
            }

            continue;

        case 'c':
            buff_ptr = buff;
            if (format.argument_options == wchar_argument) {
                *buff_ptr = va_arg(args, long);
                num_chars = 1;
            } else {
                char s;
                s = va_arg(args, int);
                num_chars = mbtowc(buff_ptr, &s, 1);
            }
            break;

        case '%':
            buff_ptr = buff;
            *buff_ptr = '%';
            num_chars = 1;
            break;

        case 0xFFFF:
        default:
        conversion_error:
            num_chars = wcslen(curr_format);
            chars_written += num_chars;

            if (num_chars && !(*write_proc)(proc_data, curr_format, num_chars)) {
                return -1;
            }

            return chars_written;
            break;
        }

        field_width = num_chars;

        if (format.justification_options != left_justification) {
            fill_char = (format.justification_options == zero_fill) ? L'0' : L' ';

            if (((*buff_ptr == '+') || (*buff_ptr == '-') || (*buff_ptr == ' ')) &&
                (fill_char == '0'))
            {
                if ((*write_proc)(proc_data, buff_ptr, 1) == 0) {
                    return -1;
                }

                ++buff_ptr;
                num_chars--;
            }

            while (field_width < format.field_width) {
                if ((*write_proc)(proc_data, (wchar_t*)&fill_char, 1) == 0) {
                    return -1;
                }

                ++field_width;
            }
        }

        if (num_chars && !(*write_proc)(proc_data, buff_ptr, num_chars)) {
            return -1;
        }

        if (format.justification_options == left_justification) {
            while (field_width < format.field_width) {
                wchar_t blank = L' ';

                if ((*write_proc)(proc_data, (wchar_t*)&blank, 1) == 0) {
                    return -1;
                }

                ++field_width;
            }
        }

        chars_written += field_width;
    }

    return chars_written;
}

static int __wStringWrite(wString* dst, const void* data, size_t len) {
    const __OutStrCtrl* osc = data;
    size_t cur_len = dst->field_0x8;
    size_t var_r7 = dst->field_0x4;
    size_t write_cnt = cur_len + len <= var_r7 ? len : var_r7 - cur_len;
    wmemcpy(dst->buffer + cur_len, (const wchar_t*)osc, write_cnt);
    dst->field_0x8 += write_cnt;
}

int vswprintf(wchar_t* s, size_t n, const wchar_t* format, va_list arg) {
    int count;
    __OutStrCtrl osc;

    osc.WCharStr = s;
    osc.MaxCharCount = n;
    osc.CharsWritten = 0;
    count = __wpformatter((void* (*)(void*, const wchar_t*, size_t))__wStringWrite, &osc, format, arg);

    if (count >= 0) {
        if (count < n) {
            s[count] = 0;
        } else {
            s[n - 1] = 0;
            count = -1;
        }
    }

    return count;
}
