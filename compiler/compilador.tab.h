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
     ATRIBUICAO = 271,
     IGUAL = 272,
     DIFERENTE = 273,
     MAIOR = 274,
     MENOR = 275,
     MAIOR_IGUAL = 276,
     MENOR_IGUAL = 277,
     MAIS = 278,
     MENOS = 279,
     MULTIPLICACAO = 280,
     DIVISAO = 281,
     T_LABEL = 282,
     T_TYPE = 283,
     T_ARRAY = 284,
     T_OF = 285,
     T_PROCEDURE = 286,
     T_FUNCTION = 287,
     T_GOTO = 288,
     T_IF = 289,
     T_THEN = 290,
     T_ELSE = 291,
     T_WHILE = 292,
     T_DO = 293,
     T_OR = 294,
     T_DIV = 295,
     T_AND = 296,
     T_NOT = 297
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
#define ATRIBUICAO 271
#define IGUAL 272
#define DIFERENTE 273
#define MAIOR 274
#define MENOR 275
#define MAIOR_IGUAL 276
#define MENOR_IGUAL 277
#define MAIS 278
#define MENOS 279
#define MULTIPLICACAO 280
#define DIVISAO 281
#define T_LABEL 282
#define T_TYPE 283
#define T_ARRAY 284
#define T_OF 285
#define T_PROCEDURE 286
#define T_FUNCTION 287
#define T_GOTO 288
#define T_IF 289
#define T_THEN 290
#define T_ELSE 291
#define T_WHILE 292
#define T_DO 293
#define T_OR 294
#define T_DIV 295
#define T_AND 296
#define T_NOT 297




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

