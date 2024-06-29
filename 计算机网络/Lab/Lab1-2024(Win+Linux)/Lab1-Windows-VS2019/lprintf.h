#ifndef lprintf

#ifdef __cplusplus
extern "C" 
{
#endif

#include <stdarg.h>
#include <stdio.h>

extern FILE *log_file;
extern unsigned int get_ms(void);

size_t lprintf(const char *format, ...);
size_t __v_lprintf(const char *format, va_list arg_ptr);

#ifdef __cplusplus
}
#endif

#endif


/*
 *  call-seq:
 *     format(format_string [, arguments...] )   => string
 *     sprintf(format_string [, arguments...] )  => string
 *  
 *  Returns the string resulting from applying <i>format_string</i> to
 *  any additional arguments. Within the format string, any characters
 *  other than format sequences are copied to the result. A format
 *  sequence consists of a percent sign, followed by optional flags,
 *  width, and precision indicators, then terminated with a field type
 *  character. The field type controls how the corresponding
 *  <code>sprintf</code> argument is to be interpreted, while the flags
 *  modify that interpretation. The field type characters are listed
 *  in the table at the end of this section. The flag characters are:
 *
 *    Flag     | Applies to   | Meaning
 *    ---------+--------------+-----------------------------------------
 *    space    | bdeEfgGiouxX | Leave a space at the start of 
 *             |              | positive numbers.
 *    ---------+--------------+-----------------------------------------
 *    (digit)$ | all          | Specifies the absolute argument number
 *             |              | for this field. Absolute and relative
 *             |              | argument numbers cannot be mixed in a
 *             |              | sprintf string.
 *    ---------+--------------+-----------------------------------------
 *     #       | beEfgGoxX    | Use an alternative format. For the
 *             |              | conversions `o', `x', `X', and `b', 
 *             |              | prefix the result with ``0'', ``0x'', ``0X'',
 *             |              |  and ``0b'', respectively. For `e',
 *             |              | `E', `f', `g', and 'G', force a decimal
 *             |              | point to be added, even if no digits follow.
 *             |              | For `g' and 'G', do not remove trailing zeros.
 *    ---------+--------------+-----------------------------------------
 *    +        | bdeEfgGiouxX | Add a leading plus sign to positive numbers.
 *    ---------+--------------+-----------------------------------------
 *    -        | all          | Left-justify the result of this conversion.
 *    ---------+--------------+-----------------------------------------
 *    0 (zero) | bdeEfgGiouxX | Pad with zeros, not spaces.
 *    ---------+--------------+-----------------------------------------
 *    *        | all          | Use the next argument as the field width. 
 *             |              | If negative, left-justify the result. If the
 *             |              | asterisk is followed by a number and a dollar 
 *             |              | sign, use the indicated argument as the width.
 *
 *     
 *  The field width is an optional integer, followed optionally by a
 *  period and a precision. The width specifies the minimum number of
 *  characters that will be written to the result for this field. For
 *  numeric fields, the precision controls the number of decimal places
 *  displayed. For string fields, the precision determines the maximum
 *  number of characters to be copied from the string. (Thus, the format
 *  sequence <code>%10.10s</code> will always contribute exactly ten
 *  characters to the result.)
 *
 *  The field types are:
 *
 *      Field |  Conversion
 *      ------+--------------------------------------------------------------
 *        b   | Convert argument as a binary number.
 *        c   | Argument is the numeric code for a single character.
 *        d   | Convert argument as a decimal number.
 *        E   | Equivalent to `e', but uses an uppercase E to indicate
 *            | the exponent.
 *        e   | Convert floating point argument into exponential notation 
 *            | with one digit before the decimal point. The precision
 *            | determines the number of fractional digits (defaulting to six).
 *        f   | Convert floating point argument as [-]ddd.ddd, 
 *            |  where the precision determines the number of digits after
 *            | the decimal point.
 *        G   | Equivalent to `g', but use an uppercase `E' in exponent form.
 *        g   | Convert a floating point number using exponential form
 *            | if the exponent is less than -4 or greater than or
 *            | equal to the precision, or in d.dddd form otherwise.
 *        i   | Identical to `d'.
 *        o   | Convert argument as an octal number.
 *        p   | The valuing of argument.inspect.
 *        s   | Argument is a string to be substituted. If the format
 *            | sequence contains a precision, at most that many characters
 *            | will be copied.
 *        u   | Treat argument as an unsigned decimal number. Negative integers
 *            | are displayed as a 32 bit two's complement plus one for the
 *            | underlying architecture; that is, 2 ** 32 + n.  However, since
 *            | Ruby has no inherent limit on bits used to represent the
 *            | integer, this value is preceded by two dots (..) in order to
 *            | indicate a infinite number of leading sign bits.
 *        X   | Convert argument as a hexadecimal number using uppercase
 *            | letters. Negative numbers will be displayed with two
 *            | leading periods (representing an infinite string of
 *            | leading 'FF's.
 *        x   | Convert argument as a hexadecimal number.
 *            | Negative numbers will be displayed with two
 *            | leading periods (representing an infinite string of
 *            | leading 'ff's.
 *     
 *  Examples:
 *
 *     sprintf("%d %04x", 123, 123)               #=> "123 007b"
 *     sprintf("%08b '%4s'", 123, 123)            #=> "01111011 ' 123'"
 *     sprintf("%1$*2$s %2$d %1$s", "hello", 8)   #=> "   hello 8 hello"
 *     sprintf("%1$*2$s %2$d", "hello", -8)       #=> "hello    -8"
 *     sprintf("%+g:% g:%-g", 1.23, 1.23, 1.23)   #=> "+1.23: 1.23:1.23"
 *     sprintf("%u", -123)                        #=> "..4294967173"
 */

/*
    %M(Memory block) %M, %0M, %#0M
    0 --LEFT PAD 0 for byte value 0~15
    # -- PREFIX length: (123) 
*/
