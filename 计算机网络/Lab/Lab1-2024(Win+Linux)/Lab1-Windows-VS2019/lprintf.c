
#ifdef _WIN32

#ifndef	_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <windows.h>

#else
#define __int64 long long
#endif

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "lprintf.h"

FILE *log_file = NULL;

#define bool int
#define true 1
#define false 0

#define MAX_WIDTH (10 * 1024)

static unsigned long skip_to(const char *format) {
    unsigned long i;
    for (i = 0; format[i] && format[i] != '%'; ++i);
    return i;
}

#define tee_output(buf, len) do { \
    fwrite(buf, 1, len, stdout); \
	if (log_file)                    \
        fwrite(buf, 1, len, log_file); \
} while (0)

static size_t output(const char *str, size_t len)
{
	static bool sol = true; /* start of line */
	unsigned int ms, n;
	char timestamp[32];
	const char *head, *tail, *end = str + len;

	for (head = tail = str; tail < end; head = tail) {
		while (tail < end && *tail++ != '\n');
		if (sol) {
			ms = get_ms();
			n = sprintf(timestamp, "%03d.%03d ", ms / 1000, ms % 1000);
			tee_output(timestamp, n);
		}
		tee_output(head, tail - head);
		sol = tail[-1] == '\n';
	}
	return len;
}

static size_t write_pad(size_t len, int pad_ch) 
{
    const char *pad;
    size_t n;

    if ((int)len <= 0) 
        return 0;

    if (pad_ch == '0')
        pad = "0000000000000000";
    else
        pad = "                ";

    for (n = 0; len > 15; len -= 16, n += 16) 
        output(pad, 16);

    if (len > 0) 
        n += output(pad, len); 

    return n;
}

static size_t int64_str(char *s, size_t size, unsigned __int64 i, int base, char upcase)
{
    char *p;
    unsigned int j = 0;
    
    s[--size] = 0; 
    
    p = s + size;
    
    if (base == 0 || base > 36) 
        base = 10;
    
    j = 0;
    if (i == 0) {
        *(--p) = '0';
        j = 1;
    }
    
    while (p > s && i != 0) {
        p--;
        *p = (char)(i % base + '0');
        if (*p > '9') 
            *p += (upcase ? 'A' : 'a') - '9' - 1;
        i /= base;
        j++;
    }

    memmove(s, p, j + 1);

    return j;
}

#define F_SIGN    0x0001
#define F_UPCASE  0x0002
#define F_HASH    0x0004
#define F_LEFT    0x0008
#define F_SPACE   0x0010
#define F_PLUS    0x0020
#define F_DOT     0x0040

static size_t output_string(
   const char *str, size_t size, size_t prefix_len, 
   size_t width, size_t precision, 
   int flag, char pad, char precision_pad)
{
    const char *prefix;
    size_t len = 0;
 
    if (width == 0 && precision == 0) {
        output(str, size); 
        return size;
    }
    
    prefix = str;
    
    if (prefix_len) {
        str += prefix_len;
        size -= prefix_len;
        width -= prefix_len;
    }
     
    /* These are the cases for 1234 or "1234" respectively:
        %.6u -> "001234"
        %6u  -> "  1234"
        %06u -> "001234"
        %-6u -> "1234  "
        %.6s -> "1234"
        %6s  -> "  1234"
        %06s -> "  1234"
        %-6s -> "1234  "
        %6.5u -> " 01234"
        %6.5s -> "  1234"
        In this code, for %6.5s, 6 is width, 5 is precision.
        flag_dot means there was a '.' and precision is set.
        flag_left means there was a '-'.
        sz is 4 (strlen("1234")).
        pad will be '0' for %06u, ' ' otherwise.
        precision_pad is '0' for %u, ' ' for %s.
    */
    
    if ((flag & F_DOT) && width == 0) 
        width = precision;
    
    if (!(flag & F_DOT)) 
        precision = size;

    /* do left-side padding with spaces */
    if (!(flag & F_LEFT) && pad == ' ') 
        len += write_pad(width - precision, ' ');
    
    if (prefix_len) {
        output(prefix, prefix_len);
        len += prefix_len;
    }

    /* do left-side padding with '0' */
    if (!(flag & F_LEFT) && pad == '0') 
        len += write_pad(width - precision, '0');
    
    /* do precision padding */
    len += write_pad(precision - size, precision_pad);
    
    /* write actual string */
    output(str, size); 
    len += size;

    /* do right-side padding */
    if (flag & F_LEFT) 
        len += write_pad(width - precision, pad);

    return len;
}

static size_t output_integer(
    unsigned __int64 num, int opt_long, char type, 
    size_t width, size_t precision, 
    int flag, int base, char *prefix, char pad)
{
    char buf[128], *s;
    size_t sz, prefix_len, n;
    bool is_negative;

    if (precision > width) 
        width = precision;
    
    s = buf + 1;
    if (type == 'p') {
        if (num == 0) {
            s = "(nil)";
            return output_string(s, strlen(s), 0, width, precision, flag, ' ', ' ');
        } 
    } 

    strcpy(s, prefix);
    sz = strlen(s);
    prefix_len = sz;
     
    is_negative = false;
    if (flag & F_SIGN) {
        if ((signed __int64)num < 0) {
            num = -(signed __int64)num;
            is_negative = true;
        }
    } 
    
    if (opt_long == 1)
        num &= (unsigned long)-1;
    else if (opt_long == 0)
        num &= (unsigned int)-1;
    else if (opt_long == -1) 
        num &= 0xffff;
    else if (opt_long == -2) 
        num &= 0xff;

    n = int64_str(s + sz, sizeof(buf) - sz - 1, num, base, flag & F_UPCASE);

    /* When 0 is printed with an explicit precision 0, the output is empty. */
    if ((flag & F_DOT) && n == 1 && s[sz] == '0') {
        if (precision == 0 || prefix_len > 0) 
            sz = 0;
        prefix_len = 0;
    } else 
        sz += n;
    
    if (is_negative) {
        prefix_len = 1;
        *(--s) = '-';
        sz++;
    } else if ((flag & F_SIGN) && (flag & (F_PLUS | F_SPACE))) {
        prefix_len = 1;
        *(--s) = (flag & F_PLUS) ? '+' : ' ';
        sz++;
    } 

    if (precision > 0)
        pad = ' ';

    if (sz - prefix_len > precision)
        precision = sz - prefix_len;

    return output_string(s, sz, prefix_len, width, precision, flag, pad, '0');
}

static size_t output_double(double d, 
    char type, size_t width, size_t precision, int flag, int pad)
{
    char fmt[64], buf[256], *s, *p;
    size_t prefix_len = 0, sz;

    if (width == 0) 
        width = 1;
    if (!(flag & F_DOT)) 
        precision = 6;
    if (d < 0.0) 
        prefix_len = 1;

    s = buf + 1;
    
    sprintf(fmt, "%%%zd.%zd%c", width, precision, type);
    sprintf(s, fmt, d);
    
    for (p = s; *p == ' '; p++);

    for (;;) {
        *s = *p;
        if (*p == '\0')
            break;
        s++;
        p++;
    } 
    s = buf + 1;
    sz = strlen(s);

    if ((flag & (F_PLUS | F_SPACE)) && d >= 0) {
        prefix_len = 1;
        *(--s) = (flag & F_PLUS) ? '+' : ' ';
        sz++;
    }
    
    if ((flag & F_HASH) && type == 'f' && strchr(s, '.') == NULL) 
        s[sz++] = '.';
    
    if (width < sz) 
        width = sz;
    flag &= ~F_DOT;
   
    return output_string(s, sz, prefix_len, width, precision, flag, pad, '0');
}

/*
   %M  (Memory block)  %M, %0M, %#0M
       0 -- LEFT PAD 0 for byte value 0~15
       # -- PREFIX length: (123) 
*/

static size_t output_memory_block(const unsigned char *ptr, int n, size_t width,
				  size_t precision, int flag, int pad)
{
    static const char *char_set = "0123456789abcdef";
    char str[256], *s;
    size_t len = 0;
    
    if (ptr == NULL) 
        return output_string("(null)", 6, 0, width, precision, flag, pad, ' ');

    s = str; 
    if (flag & F_HASH) 
        s += sprintf(s, "(%d) ", n);

    if (n > (sizeof(str) - 32) / 3) 
        width = precision = 0;
        
    while (n > 0) {
        if (pad != '0' && *ptr < 0x10) 
            *s++ = char_set[*ptr];
        else {
            *s++ = char_set[*ptr / 16];
            *s++ = char_set[*ptr % 16];
        }

        n--;
        if (n > 0)
            *s++ = ' ';

        ptr++;
        if (s - str > sizeof(str) - 4) {
            len += output_string(str, s - str, 0, width, precision, flag, pad, ' ');
            s = str;
        }
    }

    if (s != str) 
        len += output_string(str, s - str, 0, width, precision, flag, pad, ' ');

    return len;
}

size_t __v_lprintf(const char *format, va_list arg_ptr)
{
    size_t len = 0, l;
    signed int n;
    int err = errno;
    char *s;
    unsigned char *ptr;
    int flag;
    char ch, pad;
    
    signed int opt_long;

    unsigned int base;
    size_t width, precision;
    
    __int64 num;
    char *prefix;

    while (*format) {
        
        n = skip_to(format);
        if (n) {
            output(format, n); 
            len += n;
            format += n;
        }
        
        if (*format != '%') 
            continue;
        
        pad = ' ';
        flag = 0;
        opt_long = 0;
        prefix = "";
        
        width = 0;
        precision = 0;
        num = 0;
        
        ++format;
        
next_option:
        switch (ch = *format++) {
        case 0:
            return -1;
            break;
            
        /* FLAGS */
        case '#':
            flag |= F_HASH;
            goto next_option;

        case 'h':
            --opt_long;
            goto next_option;
            
        case 'q':     
        case 'L':
            ++opt_long;
        case 'z':
        case 'l':
            ++opt_long;
            goto next_option;
            
        case '-':
            flag |= F_LEFT;
            goto next_option;
            
        case ' ':
            flag |= F_SPACE;
            goto next_option;
            
        case '+':
            flag |= F_PLUS;
            goto next_option;
            
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (flag & F_DOT) 
                return -1;
            width = strtoul(format - 1, (char **)&s, 10);
            if (width > MAX_WIDTH) 
                return -1;
            if (ch == '0' && !(flag & F_LEFT)) 
                pad = '0';
            format = s;
            goto next_option;
            
        case '*': 
            if ((n = va_arg(arg_ptr, int)) < 0) {
                flag |= F_LEFT;
                n = -n;
            }
            if ((width = (unsigned long)n) > MAX_WIDTH) 
                return -1;
            goto next_option; 
            
        case '.':
            flag |= F_DOT;
            if (*format == '*') {
                n = va_arg(arg_ptr, int);
                ++format;
            } else {
                n = strtol(format, (char**)&s, 10);
                format = s;
            }
            precision = n < 0 ? 0 : n;
            if (precision > MAX_WIDTH) 
                return -1;
            goto next_option;
            
        /* print a char or % */
        case 'c':
            ch = (char)va_arg(arg_ptr, int);
        case '%':
            output(&ch, 1); 
            ++len;
            break;
                       
        /* print a string */
        case 'm':
        case 's':
            s = ch == 'm' ? strerror(err) : va_arg(arg_ptr, char *);
            if (s == NULL) 
                s = "(null)";
            l = strlen(s);
            if ((flag & F_DOT) && l > precision) 
                l = precision;
            flag &= ~F_DOT;
            len += output_string(s, l, 0, width, 0, flag, ' ', ' ');
            break;
             
        /* print an integer value */
        case 'b':
            base = 2;
            goto print_num;
            
        case 'p':
            prefix = "0x";
            opt_long = sizeof(void *) / sizeof(long);
        case 'X':
            if (ch == 'X')
                flag |= F_UPCASE;
        case 'x':
            base = 16;
            if (flag & F_HASH) 
                prefix = ch == 'X' ? "0X" : "0x";
            goto print_num;
            
        case 'd':
        case 'i': 
            flag |= F_SIGN;
        case 'u':
            base = 10;
            goto print_num;
            
        case 'o':
            base = 8;
            if (flag & F_HASH) 
                prefix = "0";
print_num:
            if (opt_long > 0) {
                if (opt_long > 1)
                    num = va_arg(arg_ptr, __int64);
                else
                    num = (__int64)va_arg(arg_ptr, long);
            } else 
                num = (__int64)va_arg(arg_ptr, int);

            len += output_integer(num, opt_long, ch, 
                width, precision, flag, base, prefix, pad);
            break;
  
        /* print a floating point value */
        case 'g':
        case 'F':  
        case 'f':
        case 'e':
        case 'E':
            len += output_double(va_arg(arg_ptr, double), ch, 
                width, precision, flag, pad);
            break;

        /* print a memory block */
        case 'M': 
            ptr = va_arg(arg_ptr, unsigned char *);
            len += output_memory_block(ptr, va_arg(arg_ptr, int), 
                width, precision, flag, pad); 
            break; 

        default:
            break;
        }
    }
    return len;
}

size_t lprintf(const char *format, ...)
{
    size_t n;
    va_list arg_ptr;

    va_start(arg_ptr, format);
	n = __v_lprintf(format, arg_ptr);
    va_end(arg_ptr);

    return n;
}

#if 0

int main()
{
	lprintf("Hellll %03d\n", 1289);
	lprintf("sadfasfasfsadf [[%#M]]\n", "\033\071", 3);
	lprintf("SSSSSSSSSSSSSSSSSSSSSSSSS\n");
	getchar();
}

#endif
