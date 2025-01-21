%option yylineno
%option noyywrap
%{
#include "parser.tab.h"
%}

%%

[0-9]+         { yylval = atoi(yytext); return NUM; }
"+"            { return '+'; }
"-"            { return '-'; }
"*"            { return '*'; }
"/"            { return '/'; }
"("            { return '('; }
")"            { return ')'; }
"$"            { return 0; }
[ \t\n]        ;
.              { printf("Unknown character: %s\n", yytext); }

%%
