%option yylineno
%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int yycolumn = 1, char_cnt = 0;
int start_line, start_column;
int prev_yylineno;

#define YY_USER_ACTION                                                   \
  start_line = prev_yylineno; start_column = yycolumn;                   \
  char_cnt += yyleng;                                                    \
  if (yylineno == prev_yylineno) yycolumn += yyleng;                     \
  else {                                                                 \
    for (yycolumn = 1; yytext[yyleng - yycolumn] != '\n'; ++yycolumn) {} \
    prev_yylineno = yylineno;                                            \
  }

void record_token(const char *type, const char *text);
void print_statistics();

#define MAX_TOKENS 1000
char *token_names[] = {"EOF", "error", "identifier", "keyword", "punctuator", 
                       "integer constant", "floating constant", "char constant", 
                       "string literal"};
int token_counts[MAX_TOKENS] = {0};
char *token_types[MAX_TOKENS];
int token_type_count = 0;

void record_token(const char *type, const char *text) {
    for (int i = 0; i < token_type_count; i++) {
        if (strcmp(token_types[i], type) == 0) {
            token_counts[i]++;
            printf("%d:%d: <%s, %s>\n", start_line, start_column, type, text);
            return;
        }
    }
    token_types[token_type_count] = strdup(type);
    token_counts[token_type_count++] = 1;
    printf("%d:%d: <%s, %s>\n", start_line, start_column, type, text);
}

void print_statistics() {
    int sum = 0;
    for (int i = 0; i < token_type_count; i++) {
        printf("\n%-10d %s", token_counts[i], token_types[i]);
        sum += token_counts[i];
    }
    printf("\ntotal: %d tokens, %d characters, %d lines\n", sum, char_cnt, start_line);
}
%}

ws [ \f\n\r\t\v]
prep "#"[^\n]*
line_comment \/\/[^\n]*
block_comment \/\*([^*]|\*+[^*/])*\*+\/
keyword auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while|_Alignas|_Alignof|_Atomic|_Bool|_Complex|_Generic|_Imaginary|_Noreturn|_Static_assert|_Thread_local
letter [a-zA-Z]
l [_a-zA-Z]
d [0-9]
hexd [0-9a-fA-F]
octd [0-7]
ucn \\u{hexd}{4}|\\U{hexd}{8}
identifier ({l}|{ucn})({l}|{d}|{ucn})*
punctuator ("{"|"}"|"["|"]"|"("|")"|";"|":"|"..."|"?"|"."|"->"|"~"|"!"|"+"|"-"|"*"|"/"|"%"|"^"|"&"|"|"|"="|"+="|"-="|"*="|"/="|"%="|"^="|"&="|"|="|"=="|"!="|"<"|">"|"<="|">="|"&&"|"||"|"<<"|">>"|"<<="|">>="|"++"|"--"|","|")")
unsigned_suffix u|U
long_suffix l|L|ll|LL
int_suffix {unsigned_suffix}{long_suffix}?|{long_suffix}{unsigned_suffix}?
decimal_int (0|[1-9]{d}*{int_suffix}?)
octal_int 0{octd}+{int_suffix}?
hex_int (0x|0X){hexd}+{int_suffix}?
float_suffix f|F|l|L
decimal_exp (e|E)[+-]?{d}+
decimal_float ({d}+\.{d}+|{d}*\.{d}+|{d}+\.{d}*)({decimal_exp})?{float_suffix}?
hex_exp (p|P)[+-]?{d}+
hex_float (0x|0X)(({hexd}*\.{hexd}+)|({hexd}+\.?)){hex_exp}{float_suffix}?
escape_sequence \\([abfnrtv'"?]|{octd}{1,3}|x[hexd]+)|{ucn}
c_char [^'\\\n]|{escape_sequence}
valid_char_constant (L|u|U|u8)?\'{c_char}\'
s_char [^"\\\n]|{escape_sequence}
string_literal (L|u|U|u8)?\"([^"\\\n]|{escape_sequence})*\"

incomplete_comment \/\*([^*]*)
invalid_octal 0[89]
invalid_char_constant (L|u|U|u8)?\'[^']{2,}\'
incomplete_exp ({d}+\.{d}*|{d}*\.{d}+|{d}+\.{d}*){float_suffix}?(e|E)[+-]?(\s|;)

%%

{ws}|{prep}|{line_comment}|{block_comment} {}   // 对于合法的块注释，跳过

{incomplete_comment} {
    record_token("error", "Unterminated block comment");
    while (input() != '\n') ; // 跳过第二行，从第三行开始词法分析
}

{invalid_octal} {
    record_token("error", "invalid octal"); // 记录为错误
}

{invalid_char_constant} {
    record_token("error", "Invalid character constant");
}

{incomplete_exp} {
    record_token("error", "Incomplete exponent part");
}

{keyword} { 
    record_token("keyword", yytext); 
}

{identifier} { 
    record_token("identifier", yytext); 
}

{punctuator} { 
    record_token("punctuator", yytext); 
}

{decimal_int}|{octal_int}|{hex_int} { 
    record_token("integer constant", yytext);
}

{decimal_float}|{hex_float} {
    record_token("floating constant", yytext); 
}

{valid_char_constant} { 
    record_token("char constant", yytext); 
}

{string_literal} { 
    record_token("string literal", yytext); 
}

. { 
    record_token("error", yytext); 
}

%%
int main(int argc, char **argv) {
    FILE *fin;
    prev_yylineno = 0;
    if (argc > 1) {
        fin = fopen(argv[1], "r");
        if (fin == NULL) {
            perror("cannot open file");
            return 1;
        }
        yyset_in(fin);
    }

    int token;
    while ((token = yylex()) != 0) {}

    print_statistics();
    
    if (fin) {
        fclose(fin);
    }
    return 0;
}
