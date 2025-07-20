%option case-insensitive
%option noyywrap
%option yylineno
%{
#include "NEW_PASCC.tab.h"
#include "ast.h"
#include <string.h>
#include <stdlib.h>

int yycolumn = 1; // 用于记录列号

// 将 yytext 存储在输出记号的 value 中
void to_str();
// 将 yytext 转为 int 存储在输出记号的 value 中
void to_int();
// 将 yytext 转为 double 存储在输出记号的 value 中
void to_real();
// 将 yytext 转为 char 存储在输出记号的 value 中
void to_char();
// 将 yytext 转为 bool 存储在输出记号的 value 中
void to_bool();

extern "C"
{
    // int yywrap();
    int yylex();
    void yyerror(const char *s);
}

// 错误报告
#define MAX_MSG 256
char err_msg[MAX_MSG];
void yyerror(const char *msg) {
	fprintf(stderr, "error: %s\n", msg);
}

// 括号匹配辅助
#define MAX_STACK 1000
char char_stk[MAX_STACK];
int line_stk[MAX_STACK];
int top = 0;
void stk_push(char ch) {
	if (top == MAX_STACK) {
		yyerror("Bracket stack overflow");
	} else {
		line_stk[top] = yylineno;
		char_stk[top++] = ch;
	}
}
char char_stk_pop() {
	if (top <= 0) {
		return '\0';
	} else {
		return char_stk[--top];
	}
}
int match(char top, char now) {
	return (top == '(' && now == ')') ||
			(top == '[' && now == ']') ||
			(top == '{' && now == '}');
}
void remain_stk() {
	if (top != 0) {
		for (int i = 0; i < top; i++) {
			sprintf(err_msg, "Line %d: Unmatched opening bracket '%c'", line_stk[i], char_stk[i]);
			yyerror(err_msg);
		}
	}
}
%}


delim                   [ ]
ws                      {delim}+
DIGIT                   [0-9]
DIGITS                  {DIGIT}+
FRACTION                (\.{DIGITS})
LETTER                  [a-zA-Z]

/* 关键字 */
ARRAY                   "array"
BEGIN_                  "begin"
BREAK                   "break"
CASE                    "case"
CONST                   "const"
CONTINUE                "continue"
DO                      "do"
DOWNTO                  "downto"
ELSE                    "else"
END                     "end"
FOR                     "for"
FUNCTION                "function"
IF                      "if"
NOT                     "not"
OF                      "of"
PROGRAM                 "program"
PROCEDURE               "procedure"
RECORD                  "record"
THEN                    "then"
TO                      "to"
VAR                     "var"
WHILE                   "while"
READ                    "read"
READLN                  "readln"
WRITE                   "write"
WRITELN                 "writeln"
TYPE                    "type"

/* 库函数 */
STD_FUNC                ("ord"|"chr"|"pred"|"succ"|"round"|"trunc"|"abs"|"sqr"|"sqrt"|"sin"|"cos"|"arctan"|"exp"|"ln"|"odd"|"eof"|"eoln")

/* 运算符 */
ASSIGN                  ":="
EQUAL                   "="
PLUS                    "+"
MINUS                   "-"
ADDING_OP               "or"
MULTI_OP                ("*"|"/"|"div"|"mod"|"and")
REL_OP                  ("<>"|"<"|"<="|">"|">=")
DOT                     "."
COMMA                   ","
COLON                   ":"
SEMICOLON               ";"
RANGE                   ".."
LPAREN                  "("
RPAREN                  ")"
LBRACKET                "["
RBRACKET                "]"

/* 类型 */
INT_NUM                 {DIGITS}
REAL_NUM                {DIGITS}{FRACTION}
CHAR                    ('[^'\n]')
STRING                  (\'([^\\\'\n]|(\\.)){2,}\')
BOOLEAN                 ("true"|"false")
BASIC_TYPE              ("integer"|"real"|"boolean"|"char"|"string")

/* 标识符 */
IDENTIFIER              ({LETTER}|[_])({LETTER}|{DIGIT}|[_])*

/* 注释 */
ANNO_1                  (\{[^}]*\})      
ANNO_2                  ("//"[^\n]*)

%%

{ARRAY}               { to_str(); return ARRAY; }
{BEGIN_}               { to_str(); return BEGIN_; }
{BREAK}               { to_str(); return BREAK; }
{CASE}                { to_str(); return CASE; }
{CONST}               { to_str(); return CONST; }
{CONTINUE}            { to_str(); return CONTINUE; }
{DO}                  { to_str(); return DO; }
{DOWNTO}              { to_str(); return DOWNTO; }
{ELSE}                { to_str(); return ELSE; }
{END}                 { to_str(); return END; }
{FOR}                 { to_str(); return FOR; }
{FUNCTION}            { to_str(); return FUNCTION; }
{IF}                  { to_str(); return IF; }
{NOT}                 { to_str(); return NOT; }
{OF}                  { to_str(); return OF; }
{PROCEDURE}           { to_str(); return PROCEDURE; }
{PROGRAM}             { to_str(); return PROGRAM; }
{RECORD}              { to_str(); return RECORD; }
{THEN}                { to_str(); return THEN; }
{TO}                  { to_str(); return TO; }
{VAR}                 { to_str(); return VAR; }
{WHILE}               { to_str(); return WHILE; }
{WRITE}               { to_str(); return WRITE; }
{WRITELN}             { to_str(); return WRITELN; }
{READ}                { to_str(); return READ; }
{READLN}              { to_str(); return READLN; }
{TYPE}                { to_str(); return TYPE; }

{STD_FUNC}            { to_str(); return STD_FUNC; }

{ASSIGN}              { to_str(); return ASSIGN; }
{EQUAL}               { to_str(); return EQUAL; }
{PLUS}                { to_str(); return PLUS; }
{MINUS}               { to_str(); return MINUS; }
{ADDING_OP}           { to_str(); return ADDING_OP; }
{MULTI_OP}            { to_str(); return MULTI_OP; }
{REL_OP}              { to_str(); return REL_OP; }
{DOT}                 { to_str(); return DOT; }
{COMMA}               { to_str(); return COMMA; }
{COLON}               { to_str(); return COLON; }
{SEMICOLON}           { to_str(); return SEMICOLON; }
{RANGE}               { to_str(); return RANGE; }
{LPAREN}              { stk_push('('); to_str(); return LPAREN; }
{RPAREN}              { char top = char_stk_pop();
                        if (!match(top, ')')) {
                            sprintf(err_msg, "Line %d: Bracket mismatch between '%c' and ')'", yylineno, top == '\0' ? '#' : top);
                            yyerror(err_msg);
                        }
                        to_str(); return RPAREN; }
{LBRACKET}            { stk_push('['); to_str(); return LBRACKET; }
{RBRACKET}            { char top = char_stk_pop();
                        if (!match(top, ']')) {
                            sprintf(err_msg, "Line %d: Bracket mismatch between '%c' and ']'", yylineno, top == '\0' ? '#' : top);
                            yyerror(err_msg);
                        }
                        to_str(); return RBRACKET; }

{INT_NUM}             { to_int(); return INT_NUM; }
{REAL_NUM}            { to_real(); return REAL_NUM; }
{CHAR}                { to_char(); return CHAR; }
{STRING}              { to_str(); return STRING; }
{BOOLEAN}             { to_bool(); return BOO_LEAN; }
{BASIC_TYPE}          { to_str(); return BASIC_TYPE; }

{IDENTIFIER}          { to_str(); return IDENTIFIER; }

{ANNO_1}              { /* 忽略块注释 */ }
{ANNO_2}              { /* 忽略行注释 */ }

"\t"                    { yycolumn += 4; }
"\n"                    { yycolumn = 1; }
{ws}                    { yycolumn += yyleng; }

{DIGIT}+{LETTER}+({LETTER}|{DIGIT})* {
    // 非法标识符
    sprintf(err_msg, "Line %d: Invalid identifier '%s', identifiers cannot start with a digit", yylineno, yytext);
    yyerror(err_msg);
}
{DIGIT}+\.{DIGIT}+\.{DIGIT}+ {
    // 多小数点
    sprintf(err_msg, "Line %d: Invalid number format '%s'", yylineno, yytext);
    yyerror(err_msg);
}
[^\x00-\x7F]+           {
    // 非ASCII字符
    sprintf(err_msg, "Line %d: Invalid non-ASCII character(s): '%s'", yylineno, yytext);
    yyerror(err_msg);
}

.                       { printf("Unknown character: %s\n", yytext); }

%%

// 将 yytext 存储在输出记号的 value 中
void to_str() 
{
   printf("Recognized string: '%s' (Line: %d, Column: %d)\n", yytext, yylineno, yycolumn);
    yylval.token_info = new TokenInfo();
    yylval.token_info->type = STRING_;
    yylval.token_info->string_value = strdup(yytext);
    yylval.token_info->line_no = yylineno;
    yylval.token_info->column_no = yycolumn;

    // 更新列号
    yycolumn += yyleng;
}

// 将 yytext 转为 int 存储在输出记号的 value 中
void to_int() 
{
   printf("Recognized integer: %d (Line: %d, Column: %d)\n", atoi(yytext), yylineno, yycolumn);
    yylval.token_info = new TokenInfo();
    yylval.token_info->type = INTEGER;
    yylval.token_info->value.int_value = atoi(yytext);
    yylval.token_info->line_no = yylineno;
    yylval.token_info->column_no = yycolumn;

    // 更新列号
    yycolumn += yyleng;
}

// 将 yytext 转为 double 存储在输出记号的 value 中
void to_real()
{
   printf("Recognized real number: %f (Line: %d, Column: %d)\n", atof(yytext), yylineno, yycolumn);
    yylval.token_info = new TokenInfo();
    yylval.token_info->type = REAL;
    yylval.token_info->value.real_value = atof(yytext);
    yylval.token_info->line_no = yylineno;
    yylval.token_info->column_no = yycolumn;

    // 更新列号
    yycolumn += yyleng;
}

// 将 yytext 转为 char 存储在输出记号的 value 中
void to_char()
{
   printf("Recognized character: '%c' (Line: %d, Column: %d)\n", yytext[1], yylineno, yycolumn);
    yylval.token_info = new TokenInfo();
    yylval.token_info->type = CHAR_;
    yylval.token_info->value.char_value = yytext[1];
    yylval.token_info->line_no = yylineno;
    yylval.token_info->column_no = yycolumn;

    // 更新列号
    yycolumn += yyleng;
}

// 将 yytext 转为 bool 存储在输出记号的 value 中
void to_bool()
{
    printf("Recognized boolean: %s (Line: %d, Column: %d)\n", yytext, yylineno, yycolumn);  
    yylval.token_info = new TokenInfo();
    yylval.token_info->type = BOOLEAN_;
    yylval.token_info->value.bool_value = (yytext[0] == 'T' || yytext[0] == 't');
    // cout<<yylval.token_info->value.bool_value<<endl;
    yylval.token_info->line_no = yylineno;
    yylval.token_info->column_no = yycolumn;

    // 更新列号
    yycolumn += yyleng;
}

// int yywrap()
// {
//     return 1;
// }

// int main() {
// 	while (yylex()) {}
//	remain_stk();
//	return 0;
//}