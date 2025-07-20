/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_NEW_PASCC_TAB_H_INCLUDED
# define YY_YY_NEW_PASCC_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT_NUM = 258,
     REAL_NUM = 259,
     CHAR = 260,
     BOO_LEAN = 261,
     STRING = 262,
     BASIC_TYPE = 263,
     IDENTIFIER = 264,
     ARRAY = 265,
     BEGIN_ = 266,
     BREAK = 267,
     CASE = 268,
     CONST = 269,
     CONTINUE = 270,
     DO = 271,
     DOWNTO = 272,
     ELSE = 273,
     END = 274,
     FOR = 275,
     FUNCTION = 276,
     IF = 277,
     NOT = 278,
     OF = 279,
     PROCEDURE = 280,
     PROGRAM = 281,
     RECORD = 282,
     THEN = 283,
     TO = 284,
     VAR = 285,
     WHILE = 286,
     READ = 287,
     READLN = 288,
     WRITE = 289,
     WRITELN = 290,
     DOT = 291,
     TYPE = 292,
     STD_FUNC = 293,
     ASSIGN = 294,
     EQUAL = 295,
     PLUS = 296,
     MINUS = 297,
     ADDING_OP = 298,
     MULTI_OP = 299,
     REL_OP = 300,
     COMMA = 301,
     COLON = 302,
     SEMICOLON = 303,
     RANGE = 304,
     LPAREN = 305,
     RPAREN = 306,
     LBRACKET = 307,
     RBRACKET = 308
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 43 "NEW_PASCC.y"

    class TokenInfo* token_info;
    class ASTNode* ast;


/* Line 2058 of yacc.c  */
#line 116 "NEW_PASCC.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (ASTNode** rootPtr);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_NEW_PASCC_TAB_H_INCLUDED  */
