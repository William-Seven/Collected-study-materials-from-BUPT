%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
int step = 0; // 用于计数产生式的顺序
%}

%token NUM
%start E

%%

E : E '+' T    { printf("(%d) E → E + T\n", ++step); }
  | E '-' T    { printf("(%d) E → E - T\n", ++step); }
  | T          { printf("(%d) E → T\n", ++step); }
  ;

T : T '*' F    { printf("(%d) T → T * F\n", ++step); }
  | T '/' F    { printf("(%d) T → T / F\n", ++step); }
  | F          { printf("(%d) T → F\n", ++step); }
  ;

F : '(' E ')'  { printf("(%d) F → (E)\n", ++step); }
  | NUM        { printf("(%d) F → num\n", ++step); }
  ;

%%

int main() {
    printf("Enter an expression ending with $:\n");
    if (yyparse() == 0) {
        printf("\033[32mAccept!\033[0m\n");  // 绿色输出
    } else {
        printf("\033[31mReject!\033[0m\n");  // 红色输出
    }
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
