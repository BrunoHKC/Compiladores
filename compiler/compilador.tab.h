/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     ABRE_PARENTESES = 259,
     FECHA_PARENTESES = 260,
     VIRGULA = 261,
     PONTO_E_VIRGULA = 262,
     DOIS_PONTOS = 263,
     PONTO = 264,
     INTEGER = 265,
     BOOLEAN = 266,
     T_BEGIN = 267,
     T_END = 268,
     VAR = 269,
     IDENT = 270,
     NUMERO = 271,
     ATRIBUICAO = 272,
     IGUAL = 273,
     DIFERENTE = 274,
     MAIOR = 275,
     MENOR = 276,
     MAIOR_IGUAL = 277,
     MENOR_IGUAL = 278,
     MAIS = 279,
     MENOS = 280,
     MULTIPLICACAO = 281,
     DIVISAO = 282,
     READ = 283,
     WRITE = 284,
     TRUE = 285,
     FALSE = 286,
     T_LABEL = 287,
     T_TYPE = 288,
     T_ARRAY = 289,
     T_OF = 290,
     T_PROCEDURE = 291,
     T_FUNCTION = 292,
     T_GOTO = 293,
     T_IF = 294,
     T_THEN = 295,
     T_ELSE = 296,
     T_WHILE = 297,
     T_DO = 298,
     T_OR = 299,
     T_DIV = 300,
     T_AND = 301,
     T_NOT = 302
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define ABRE_PARENTESES 259
#define FECHA_PARENTESES 260
#define VIRGULA 261
#define PONTO_E_VIRGULA 262
#define DOIS_PONTOS 263
#define PONTO 264
#define INTEGER 265
#define BOOLEAN 266
#define T_BEGIN 267
#define T_END 268
#define VAR 269
#define IDENT 270
#define NUMERO 271
#define ATRIBUICAO 272
#define IGUAL 273
#define DIFERENTE 274
#define MAIOR 275
#define MENOR 276
#define MAIOR_IGUAL 277
#define MENOR_IGUAL 278
#define MAIS 279
#define MENOS 280
#define MULTIPLICACAO 281
#define DIVISAO 282
#define READ 283
#define WRITE 284
#define TRUE 285
#define FALSE 286
#define T_LABEL 287
#define T_TYPE 288
#define T_ARRAY 289
#define T_OF 290
#define T_PROCEDURE 291
#define T_FUNCTION 292
#define T_GOTO 293
#define T_IF 294
#define T_THEN 295
#define T_ELSE 296
#define T_WHILE 297
#define T_DO 298
#define T_OR 299
#define T_DIV 300
#define T_AND 301
#define T_NOT 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

