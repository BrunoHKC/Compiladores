/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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
     T_LABEL = 283,
     T_TYPE = 284,
     T_ARRAY = 285,
     T_OF = 286,
     T_PROCEDURE = 287,
     T_FUNCTION = 288,
     T_GOTO = 289,
     T_IF = 290,
     T_THEN = 291,
     T_ELSE = 292,
     T_WHILE = 293,
     T_DO = 294,
     T_OR = 295,
     T_DIV = 296,
     T_AND = 297,
     T_NOT = 298
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
#define T_LABEL 283
#define T_TYPE 284
#define T_ARRAY 285
#define T_OF 286
#define T_PROCEDURE 287
#define T_FUNCTION 288
#define T_GOTO 289
#define T_IF 290
#define T_THEN 291
#define T_ELSE 292
#define T_WHILE 293
#define T_DO 294
#define T_OR 295
#define T_DIV 296
#define T_AND 297
#define T_NOT 298




/* Copy the first part of user declarations.  */
#line 6 "compilador.y"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "tabela_simbolos/tabela_simbolos.h"
#include "utils/utils.h"
#include "utils/stack.h"

enum {
	OP_IGUAL,
	OP_DIFERENTE,
	OP_MENOR,
	OP_MENOR_OU_IGUAL,
	OP_MAIOR,
	OP_MAIOR_OU_IGUAL,
	OP_SOMA,
	OP_SUBTRACAO,
	OP_MULTIPLICACAO,
	OP_DIVISAO,
	OP_DIVISAO_INTEIRA,
	OP_AND,
	OP_OR,
	OP_NOT
};


//incializa variaveis globais
int num_vars;
int nivel_lexico = 0;
int desloc = 0;
int sinal = 0;	//0: mais , 1: menos
char tokenAtual[100];
int contador_rotulo = 0;


//Pilha de deslocamentos
Stack* pilhaDeslocamentos;

//Pilha de operacoes
Stack* pilhaOperacoes;

//Pilha nivel destino e deslocamento
Stack* pilhaVarNivelDestino;
Stack* pilhaVarDeslocamentos;

//Pilha de rotulos
Stack* pilhaRotulo;

//Tabela de simbolos
TabelaSimbolos ts;

//Itens
Item* var = NULL;


#define YYSTYPE char *

char* geraRotulo()
{
	char* rotulo = (char*)malloc(4*sizeof(char));
	rotulo[0] = 'R';
	rotulo[1] = '0' + (contador_rotulo/10)%10;
	rotulo[2] = '0' + contador_rotulo%10;
	rotulo[3] = '\0';
	contador_rotulo++;
	return rotulo;
}

void geraCRVL() {
	char buff[5 + 10];
	snprintf(buff,15,"CRVL %d, %d",var->nivel, var->var.deslocamento);
    geraCodigo(NULL, buff);
}

void empilhaOperacao(int operacao)
{	
	switch(operacao)
	{
		case OP_IGUAL:
		case OP_DIFERENTE:
		case OP_AND:
		case OP_OR:
		case OP_NOT:
			break;
		case OP_MENOR:
		case OP_MENOR_OU_IGUAL:
		case OP_MAIOR:
		case OP_MAIOR_OU_IGUAL:
			break;
		case OP_SOMA:
		case OP_SUBTRACAO:
		case OP_MULTIPLICACAO:
		case OP_DIVISAO:
		case OP_DIVISAO_INTEIRA:
			break;
	}

	
	int* new_operacao = (int*)malloc(sizeof(int));
	*new_operacao = operacao;
	push(pilhaOperacoes,(void*)new_operacao);
}

void empilhaVarNivelDestino(int nd)
{
	int* new_nivel = (int*)malloc(sizeof(int));
	*new_nivel = nd;
	push(pilhaVarNivelDestino,(void*)new_nivel);
}

void empilhaVarDeslocamento(int desloc)
{
	int* new_desloc = (int*)malloc(sizeof(int));
	*new_desloc = desloc;
	push(pilhaVarDeslocamentos,(void*)new_desloc);
}

void geraOperacao() {
	int op = *(int*)pop(pilhaOperacoes);

	switch (op) {
		case OP_IGUAL: //=
			geraCodigo(NULL, "CMIG \0");
			break;
		case OP_DIFERENTE: //<>
			geraCodigo(NULL, "CMDG \0");
			break;
		case OP_MENOR: //<
			geraCodigo(NULL, "CMME \0");
			break;
		case OP_MENOR_OU_IGUAL: //<=
			geraCodigo(NULL, "CMEG \0");
			break;
		case OP_MAIOR: //>
			geraCodigo(NULL, "CMMA \0");
			break;
		case OP_MAIOR_OU_IGUAL: //>=
			geraCodigo(NULL, "CMAG \0");
			break;
		case OP_SOMA: //+
			geraCodigo(NULL, "SOMA \0");
			break;
		case OP_SUBTRACAO: //-
			geraCodigo(NULL, "SUBT \0");
			break;
		case OP_MULTIPLICACAO: //*
			geraCodigo(NULL, "MULT \0");
			break;
		case OP_DIVISAO: ///
			geraCodigo(NULL, "DIVI \0");
			break;
		case OP_AND: //&&
			geraCodigo(NULL, "CONJ \0");
			break;
		case OP_OR: //||
			geraCodigo(NULL, "DISJ \0");
			break;
		case OP_NOT: //!
			geraCodigo(NULL, "NEGA \0");
			break;
		default:
			break;
	}
}




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 362 "compilador.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   76

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNRULES -- Number of states.  */
#define YYNSTATES  96

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,    14,    15,    16,    21,    23,    25,
      29,    32,    35,    36,    41,    45,    47,    50,    51,    56,
      59,    62,    65,    66,    67,    73,    74,    77,    78,    79,
      80,    89,    90,    91,    98,   100,   104,   106,   108,   110,
     112,   114,   116,   118,   120,   121,   123,   125,   127,   131,
     134,   136,   138,   140,   144,   146,   148,   150,   154,   155,
     159,   161
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    -1,    46,     3,    15,     4,    55,     5,
       7,    47,     9,    -1,    -1,    -1,    48,    52,    49,    57,
      -1,    10,    -1,    11,    -1,    51,     7,    53,    -1,    14,
      53,    -1,    51,     7,    -1,    -1,    54,    55,     8,    50,
      -1,    55,     6,    15,    -1,    15,    -1,    56,    58,    -1,
      -1,    12,    58,    56,    13,    -1,    59,     7,    -1,    67,
       7,    -1,    63,     7,    -1,    -1,    -1,    60,    79,    61,
      17,    70,    -1,    -1,    37,    57,    -1,    -1,    -1,    -1,
      64,    35,    70,    36,    65,    57,    66,    62,    -1,    -1,
      -1,    38,    68,    70,    69,    39,    57,    -1,    74,    -1,
      74,    71,    74,    -1,    18,    -1,    19,    -1,    21,    -1,
      23,    -1,    22,    -1,    20,    -1,    24,    -1,    25,    -1,
      -1,    24,    -1,    25,    -1,    40,    -1,    74,    73,    76,
      -1,    72,    76,    -1,    26,    -1,    41,    -1,    42,    -1,
      76,    75,    77,    -1,    77,    -1,    79,    -1,    80,    -1,
       4,    70,     5,    -1,    -1,    43,    78,    77,    -1,    15,
      -1,    16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   194,   194,   194,   206,   218,   206,   245,   246,   251,
     252,   253,   257,   257,   265,   274,   285,   285,   286,   289,
     290,   291,   298,   302,   298,   321,   321,   323,   327,   341,
     323,   371,   387,   370,   422,   423,   429,   430,   431,   432,
     433,   434,   437,   438,   439,   440,   441,   442,   443,   447,
     451,   452,   453,   454,   458,   462,   467,   469,   470,   470,
     475,   493
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "ABRE_PARENTESES",
  "FECHA_PARENTESES", "VIRGULA", "PONTO_E_VIRGULA", "DOIS_PONTOS", "PONTO",
  "INTEGER", "BOOLEAN", "T_BEGIN", "T_END", "VAR", "IDENT", "NUMERO",
  "ATRIBUICAO", "IGUAL", "DIFERENTE", "MAIOR", "MENOR", "MAIOR_IGUAL",
  "MENOR_IGUAL", "MAIS", "MENOS", "MULTIPLICACAO", "DIVISAO", "T_LABEL",
  "T_TYPE", "T_ARRAY", "T_OF", "T_PROCEDURE", "T_FUNCTION", "T_GOTO",
  "T_IF", "T_THEN", "T_ELSE", "T_WHILE", "T_DO", "T_OR", "T_DIV", "T_AND",
  "T_NOT", "$accept", "programa", "@1", "bloco", "@2", "@3", "tipo",
  "parte_declara_vars_aux", "parte_declara_vars", "declara_vars", "@4",
  "lista_idents", "comando_composto_aux", "comando_composto", "comando",
  "atribuicao", "@5", "@6", "comando_condicional_else",
  "comando_condicional", "@7", "@8", "@9", "comando_repetitivo", "@10",
  "@11", "expressao", "relacao", "mais_menos_epsilon", "mais_menos_or",
  "expressao_simples", "mult_div_and", "termo", "fator", "@12", "variavel",
  "numero", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    46,    45,    48,    49,    47,    50,    50,    51,
      51,    52,    54,    53,    55,    55,    56,    56,    57,    58,
      58,    58,    60,    61,    59,    62,    62,    64,    65,    66,
      63,    68,    69,    67,    70,    70,    71,    71,    71,    71,
      71,    71,    72,    72,    72,    73,    73,    73,    74,    74,
      75,    75,    75,    76,    76,    77,    77,    77,    78,    77,
      79,    80
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     0,     0,     4,     1,     1,     3,
       2,     2,     0,     4,     3,     1,     2,     0,     4,     2,
       2,     2,     0,     0,     5,     0,     2,     0,     0,     0,
       8,     0,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     1,     1,     3,     2,
       1,     1,     1,     3,     1,     1,     1,     3,     0,     3,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    15,     0,     0,
       0,     4,    14,     0,     0,     3,    12,     0,     5,    10,
       0,    11,     0,     0,     9,    22,     6,     0,    31,    17,
       0,     0,     0,     0,     0,     7,     8,    13,    44,    22,
      19,    60,    23,    21,    44,    20,    42,    43,    32,     0,
      34,    18,    16,     0,     0,     0,    44,    61,    58,    49,
      54,    55,    56,    36,    37,    41,    38,    40,    39,    45,
      46,    47,    44,     0,    44,    28,     0,     0,     0,    50,
      51,    52,     0,    35,    48,    24,     0,    33,    57,    59,
      53,    29,    25,     0,    30,    26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    13,    14,    22,    37,    17,    18,    19,
      20,     8,    39,    26,    29,    30,    31,    53,    94,    32,
      33,    86,    92,    34,    38,    55,    48,    72,    49,    73,
      50,    82,    59,    60,    78,    61,    62
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -62
static const yytype_int8 yypact[] =
{
     -62,    15,    20,   -62,    13,    34,    29,   -62,    31,    38,
      32,   -62,   -62,    37,    35,   -62,   -62,    41,   -62,   -62,
      29,    36,    40,    14,   -62,    -3,   -62,    30,   -62,   -62,
      43,    39,    46,    21,    48,   -62,   -62,   -62,    18,   -11,
     -62,   -62,   -62,   -62,    18,   -62,   -62,   -62,   -62,    -4,
     -15,   -62,   -62,    42,    22,    23,    18,   -62,   -62,   -12,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,    18,    -4,    18,   -62,    40,    52,    -4,   -62,
     -62,   -62,    -4,    -6,   -12,   -62,    40,   -62,   -62,   -62,
     -62,   -62,    24,    40,   -62,   -62
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,    44,
     -62,    47,   -62,   -60,    25,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -43,   -62,   -62,   -62,
      -9,   -62,   -13,   -61,   -62,    45,   -62
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -28
static const yytype_int8 yytable[] =
{
      56,    54,    51,    63,    64,    65,    66,    67,    68,    69,
      70,    41,    57,    77,    79,     3,    87,    89,    69,    70,
      10,    90,    27,     4,   -27,    71,    91,    28,     5,    80,
      81,    85,   -27,    95,    71,    28,     9,    10,     6,    58,
      35,    36,    46,    47,     7,    11,    15,    12,    21,    16,
      40,   -12,    25,    43,    41,    45,    44,    88,    75,    74,
      84,    93,    76,    83,    52,    24,     0,    23,     0,     0,
       0,     0,     0,     0,     0,     0,    42
};

static const yytype_int8 yycheck[] =
{
       4,    44,    13,    18,    19,    20,    21,    22,    23,    24,
      25,    15,    16,    56,    26,     0,    76,    78,    24,    25,
       6,    82,     8,     3,    35,    40,    86,    38,    15,    41,
      42,    74,    35,    93,    40,    38,     5,     6,     4,    43,
      10,    11,    24,    25,    15,     7,     9,    15,     7,    14,
       7,    15,    12,     7,    15,     7,    35,     5,    36,    17,
      73,    37,    39,    72,    39,    21,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,    46,     0,     3,    15,     4,    15,    55,     5,
       6,     7,    15,    47,    48,     9,    14,    51,    52,    53,
      54,     7,    49,    55,    53,    12,    57,     8,    38,    58,
      59,    60,    63,    64,    67,    10,    11,    50,    68,    56,
       7,    15,    79,     7,    35,     7,    24,    25,    70,    72,
      74,    13,    58,    61,    70,    69,     4,    16,    43,    76,
      77,    79,    80,    18,    19,    20,    21,    22,    23,    24,
      25,    40,    71,    73,    17,    36,    39,    70,    78,    26,
      41,    42,    75,    74,    76,    70,    65,    57,     5,    77,
      77,    57,    66,    37,    62,    57
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 194 "compilador.y"
    {
         		geraCodigo (NULL, "INPP");
             ;}
    break;

  case 3:
#line 199 "compilador.y"
    {
             	geraCodigo (NULL, "PARA");
             ;}
    break;

  case 4:
#line 206 "compilador.y"
    { 
					nivel_lexico++;

					//Salva deslocamento anterior
					int* new_desloc = (int*)malloc(sizeof(int));
					*new_desloc = desloc;
					push(pilhaDeslocamentos,(void*)new_desloc);
				
					//Reseta deslocamento
					desloc = 0;
			  ;}
    break;

  case 5:
#line 218 "compilador.y"
    { 	/* AMEM */ 
      				char buff[5 + 10];
          			snprintf(buff,15,"AMEM %d",desloc);
          			geraCodigo (NULL, buff);
  			  ;}
    break;

  case 6:
#line 225 "compilador.y"
    { 
              	
              		//Remove simbolos
              		elimina(&ts, desloc);
              	
              		//Libera memoria
					char buff[5 + 10];
          			snprintf(buff,15,"DMEM %d",desloc);
          			geraCodigo (NULL, buff);
          		
          			//Atualiza nivel lexico
          			nivel_lexico--;
          		
          			//Recupera deslocamento anterior
          			desloc = *(int*)pop(pilhaDeslocamentos);
              ;}
    break;

  case 7:
#line 245 "compilador.y"
    { atualizaTipos(&ts, num_vars, TYPE_INT); ;}
    break;

  case 8:
#line 246 "compilador.y"
    { atualizaTipos(&ts, num_vars, TYPE_BOOL); ;}
    break;

  case 12:
#line 257 "compilador.y"
    { 	/* zera contador */
					num_vars = 0; 
			   ;}
    break;

  case 14:
#line 266 "compilador.y"
    { /* insere ultima vars na tabela de simbolos */
			  	strcpy(tokenAtual,token);
              	printf("[ASynt]\tINSERE VAR SIMPLES  %s\n",tokenAtual);
              	Item* novo_item = ItemVarSimples(tokenAtual,nivel_lexico,desloc);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
               ;}
    break;

  case 15:
#line 274 "compilador.y"
    { /* insere vars na tabela de simbolos */
				strcpy(tokenAtual,token);
            	Item* novo_item = ItemVarSimples(tokenAtual,nivel_lexico,desloc);
            	printf("[ASynt]\tINSERE VAR SIMPLES  %s\n",tokenAtual);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
            ;}
    break;

  case 22:
#line 298 "compilador.y"
    {
				printf("--Inicia atribuicao--\n");
			;}
    break;

  case 23:
#line 302 "compilador.y"
    {
				empilhaVarNivelDestino(var->nivel);
				empilhaVarDeslocamento(var->var.deslocamento);
			;}
    break;

  case 24:
#line 307 "compilador.y"
    {
				//TODO: Verifica se o tipo da expressao eh o mesmo da variavel
				
				int nivel_destino = *(int*)pop(pilhaVarNivelDestino);
				int deslocamento = *(int*)pop(pilhaVarDeslocamentos);
				char buff[5 + 10];
				snprintf(buff,15,"ARMZ %d, %d",nivel_destino,deslocamento);
				geraCodigo (NULL, buff);
				printf("--Fim atribuicao--\n");
			;}
    break;

  case 27:
#line 323 "compilador.y"
    {
						printf("--Inicio If--\n");
					;}
    break;

  case 28:
#line 327 "compilador.y"
    {
						//Cria rotulo saida e empilha
						char* rotulo_entrada_else = geraRotulo();
						
						//desvia se falso
						char buff[5 + 10];
						snprintf(buff,15,"DSVF %s",rotulo_entrada_else);
						geraCodigo (NULL, buff);

						//empilha rotulo entrada do else
						push(pilhaRotulo,rotulo_entrada_else);

					;}
    break;

  case 29:
#line 341 "compilador.y"
    {
						//Cria rotulo saida e empilha
						char* rotulo_saida_else = geraRotulo();
						
						//desvia sempre
						char buff[5 + 10];
						snprintf(buff,15,"DSVS %s",rotulo_saida_else);
						geraCodigo (NULL, buff);
				
						//recupera rotulo entrada do else
						char* rotulo_entrada_else = pop(pilhaRotulo);

						//Insere rotulo entrada else
						geraCodigo (rotulo_entrada_else, "NADA");

						push(pilhaRotulo,rotulo_saida_else);

					;}
    break;

  case 30:
#line 359 "compilador.y"
    {
						//recupera rotulo saida do else
						char* rotulo_saida_else = pop(pilhaRotulo);

						//Insere rotulo saida else
						geraCodigo (rotulo_saida_else, "NADA");
					;}
    break;

  case 31:
#line 371 "compilador.y"
    {
						printf("--Inicio while--\n");
						//Cria rotulo entrada e empilha
						char* rotulo_entrada = geraRotulo();
						printf("Rotulo entrada %s\n",rotulo_entrada);
						push(pilhaRotulo,rotulo_entrada);

						//Cria rotulo saida e empilha
						char* rotulo_saida = geraRotulo();
						printf("Rotulo saida %s\n",rotulo_saida);
						push(pilhaRotulo,rotulo_saida);

						//Insere rotulo entrada no codgo MEPA
						geraCodigo (rotulo_entrada, "NADA");
					;}
    break;

  case 32:
#line 387 "compilador.y"
    {
						//recupera rotulos
						char* rotulo_saida = pop(pilhaRotulo);
						char* rotulo_entrada = pop(pilhaRotulo);

						//desvia se falso
						char buff[5 + 10];
						snprintf(buff,15,"DSVF %s",rotulo_saida);
						geraCodigo (NULL, buff);

						//empilha rotulos
						push(pilhaRotulo,rotulo_entrada);
						push(pilhaRotulo,rotulo_saida);

					;}
    break;

  case 33:
#line 403 "compilador.y"
    {
						//recupera rotulos
						char* rotulo_saida = pop(pilhaRotulo);
						char* rotulo_entrada = pop(pilhaRotulo);
						//desvia sempre
						char buff[5 + 10];
						snprintf(buff,15,"DSVS %s",rotulo_entrada);
						geraCodigo (NULL, buff);

						//Insere rotulo saida no codgo MEPA
						geraCodigo (rotulo_saida, "NADA");
						printf("--Fim while--\n");

					;}
    break;

  case 35:
#line 424 "compilador.y"
    {
				geraOperacao();
			;}
    break;

  case 36:
#line 429 "compilador.y"
    {empilhaOperacao(OP_IGUAL);;}
    break;

  case 37:
#line 430 "compilador.y"
    {empilhaOperacao(OP_DIFERENTE);;}
    break;

  case 38:
#line 431 "compilador.y"
    {empilhaOperacao(OP_DIFERENTE);;}
    break;

  case 39:
#line 432 "compilador.y"
    {empilhaOperacao(MENOR_IGUAL);;}
    break;

  case 40:
#line 433 "compilador.y"
    {empilhaOperacao(MAIOR_IGUAL);;}
    break;

  case 41:
#line 434 "compilador.y"
    {empilhaOperacao(OP_MAIOR);;}
    break;

  case 42:
#line 437 "compilador.y"
    {sinal = 0;;}
    break;

  case 43:
#line 438 "compilador.y"
    {sinal = 1;;}
    break;

  case 44:
#line 439 "compilador.y"
    {sinal = 0;;}
    break;

  case 45:
#line 440 "compilador.y"
    {empilhaOperacao(OP_SOMA);;}
    break;

  case 46:
#line 441 "compilador.y"
    {empilhaOperacao(OP_SUBTRACAO);;}
    break;

  case 47:
#line 442 "compilador.y"
    {empilhaOperacao(OP_OR);;}
    break;

  case 48:
#line 444 "compilador.y"
    {
						geraOperacao();
					;}
    break;

  case 49:
#line 447 "compilador.y"
    {if (sinal) geraCodigo(NULL, "INVR \0");;}
    break;

  case 50:
#line 451 "compilador.y"
    {empilhaOperacao(OP_MULTIPLICACAO);;}
    break;

  case 51:
#line 452 "compilador.y"
    {empilhaOperacao(OP_DIVISAO_INTEIRA);;}
    break;

  case 52:
#line 453 "compilador.y"
    {empilhaOperacao(OP_AND);;}
    break;

  case 53:
#line 455 "compilador.y"
    {
			geraOperacao();
		;}
    break;

  case 55:
#line 463 "compilador.y"
    { 
			geraCRVL();
			//geraOperacao(); 
		;}
    break;

  case 58:
#line 470 "compilador.y"
    {empilhaOperacao(OP_NOT);;}
    break;

  case 60:
#line 476 "compilador.y"
    { 
					strcpy(tokenAtual,token);
					//Salva token atual
					var = busca(&ts,tokenAtual);
					if(var == NULL)
					{
						//gera erro
						char buff[100];
	          			snprintf(buff,100,"Erro: Variavel '%s' nao foi declarada!\n",tokenAtual);
						fprintf(stderr,"%s",buff);
						exit(1);
					}

				;}
    break;

  case 61:
#line 493 "compilador.y"
    {

			//TODO: verifica se erro semantico

			char buff[5 + 10];
			strcpy(tokenAtual,token);
			snprintf(buff,15,"CRCT %s",tokenAtual);
			geraCodigo (NULL, buff);
			;}
    break;


/* Line 1267 of yacc.c.  */
#line 2035 "compilador.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 503 "compilador.y"


int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */
	initTS(&ts);
	
	pilhaDeslocamentos = initStack();
	pilhaOperacoes = initStack();

	pilhaVarDeslocamentos = initStack();
	pilhaVarNivelDestino = initStack();

	pilhaRotulo = initStack();

   yyin=fp;
   yyparse();

   return 0;
}

