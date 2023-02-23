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
char buff[100];	//buffer
int contador_rotulo = 0;
int write = 0;
int count_param = 0;


//Pilha de deslocamentos
Stack* pilhaDeslocamentos;

//Pilha de operacoes
Stack* pilhaOperacoes;

//Pilha de rotulos
Stack* pilhaRotulo;

//Pilha das sub-rotinas
Stack* pilhaSubRotinas;
Stack* pilhaParametros;


//Tabela de simbolos
TabelaSimbolos ts;

//Itens
Item* func = NULL;
Item* proced = NULL;
Item* var = NULL;
Item* varAtribuida = NULL;


#define YYSTYPE char *

Item* geraProcedimento(char* identificador, int nivel)
{
	//Cria item
	Item* new_item = (Item*)malloc(sizeof(Item));
	
	//Aloca espaco para o identificador
	new_item->identificador = (char*)malloc(100*sizeof(char));

	//Preenche campos
	strcpy(new_item->identificador,identificador);
	new_item->categoria = CAT_PROCEDIM;
	new_item->nivel = nivel;

	return new_item;
}

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


void geraCarregaValor(Item* variavel)
{
	//se variavel simples
	if(variavel->categoria == CAT_PARAM_FORMAL_SIMPLES)
	{
		if(variavel->param.passagem == REFERENCIA)
		{
			//Se eh um parametro por referencia
			sprintf(buff, "CRVI %d, %d", variavel->nivel, variavel->param.deslocamento);
		}
		else
		{
			//Se eh um parametro por valor
			sprintf(buff, "CRVL %d, %d", variavel->nivel, variavel->param.deslocamento);
		}	
	}
	else
	{
		sprintf(buff, "CRVL %d, %d", variavel->nivel, variavel->var.deslocamento);
	}

	geraCodigo(NULL,buff);
}

void geraArmazenaValor(Item* variavel)
{
	if(variavel->categoria == CAT_PARAM_FORMAL_SIMPLES)
	{
		if(variavel->param.passagem == REFERENCIA)
		{
			//Se eh um parametro por referencia
			sprintf(buff, "ARMI %d, %d", variavel->nivel, variavel->param.deslocamento);
		}
		else
		{
			//Se eh um parametro por valor
			sprintf(buff, "ARMZ %d, %d", variavel->nivel, variavel->param.deslocamento);
		}	
	}
	else
	{
		sprintf(buff, "ARMZ %d, %d", variavel->nivel, variavel->var.deslocamento);
	}
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
#line 421 "compilador.tab.c"

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
#define YYLAST   112

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNRULES -- Number of states.  */
#define YYNSTATES  159

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    14,    15,    16,    17,    24,    26,
      28,    32,    35,    36,    39,    40,    45,    49,    51,    52,
      56,    57,    58,    59,    68,    69,    72,    73,    74,    80,
      83,    84,    85,    90,    91,    95,    96,   101,   102,   108,
     112,   113,   119,   121,   123,   125,   127,   129,   132,   134,
     136,   137,   141,   142,   143,   151,   152,   156,   157,   162,
     166,   168,   169,   172,   173,   174,   175,   184,   185,   186,
     193,   197,   199,   201,   205,   207,   209,   211,   213,   215,
     217,   219,   221,   222,   224,   226,   228,   232,   235,   237,
     239,   241,   245,   247,   249,   251,   253,   255,   259,   262,
     264,   266
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    -1,    50,     3,    15,     4,    60,     5,
       7,    51,     9,    -1,    -1,    -1,    -1,    52,    57,    53,
      61,    54,    77,    -1,    10,    -1,    11,    -1,    56,     7,
      58,    -1,    14,    58,    -1,    -1,    56,     7,    -1,    -1,
      59,    60,     8,    55,    -1,    60,     6,    15,    -1,    15,
      -1,    -1,    62,     7,    61,    -1,    -1,    -1,    -1,    63,
      36,    15,    64,    71,     7,    65,    66,    -1,    -1,    67,
      51,    -1,    -1,    -1,    69,     4,    98,    70,     5,    -1,
       4,     5,    -1,    -1,    -1,     4,    73,    72,     5,    -1,
      -1,     7,    73,    72,    -1,    -1,    60,    74,     8,    55,
      -1,    -1,    14,    60,    75,     8,    55,    -1,    76,    78,
       7,    -1,    -1,    12,    78,     7,    76,    13,    -1,    79,
      -1,    83,    -1,    88,    -1,    95,    -1,    91,    -1,   109,
      80,    -1,    81,    -1,    68,    -1,    -1,    82,    17,    99,
      -1,    -1,    -1,    28,     4,    84,   107,    85,    86,     5,
      -1,    -1,     6,    87,   107,    -1,    -1,    29,     4,    89,
       5,    -1,    89,     6,    99,    -1,    99,    -1,    -1,    41,
      77,    -1,    -1,    -1,    -1,    92,    39,    99,    40,    93,
      77,    94,    90,    -1,    -1,    -1,    42,    96,    99,    97,
      43,    77,    -1,    98,     6,    99,    -1,    99,    -1,   103,
      -1,   103,   100,   103,    -1,    18,    -1,    19,    -1,    21,
      -1,    23,    -1,    22,    -1,    20,    -1,    24,    -1,    25,
      -1,    -1,    24,    -1,    25,    -1,    44,    -1,   103,   102,
     105,    -1,   101,   105,    -1,    26,    -1,    45,    -1,    46,
      -1,   105,   104,   106,    -1,   106,    -1,   107,    -1,   108,
      -1,    30,    -1,    31,    -1,     4,    99,     5,    -1,    47,
     106,    -1,   109,    -1,    16,    -1,    15,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   246,   246,   246,   258,   268,   285,   258,   316,   317,
     322,   323,   324,   325,   330,   330,   338,   346,   357,   358,
     364,   368,   388,   364,   414,   414,   427,   438,   427,   444,
     459,   564,   565,   568,   569,   575,   574,   587,   586,   605,
     605,   606,   609,   610,   611,   612,   613,   618,   621,   622,
     626,   626,   664,   664,   663,   671,   670,   672,   677,   681,
     685,   693,   693,   695,   699,   713,   695,   743,   759,   742,
     792,   798,   808,   809,   815,   816,   817,   818,   819,   820,
     823,   824,   825,   826,   827,   828,   829,   833,   837,   838,
     839,   840,   844,   848,   852,   853,   859,   866,   867,   874,
     886,   896
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
  "MENOR_IGUAL", "MAIS", "MENOS", "MULTIPLICACAO", "DIVISAO", "READ",
  "WRITE", "TRUE", "FALSE", "T_LABEL", "T_TYPE", "T_ARRAY", "T_OF",
  "T_PROCEDURE", "T_FUNCTION", "T_GOTO", "T_IF", "T_THEN", "T_ELSE",
  "T_WHILE", "T_DO", "T_OR", "T_DIV", "T_AND", "T_NOT", "$accept",
  "programa", "@1", "bloco", "@2", "@3", "@4", "tipo",
  "parte_declara_vars_aux", "parte_declara_vars", "declara_vars", "@5",
  "lista_idents", "parte_declara_subrotinas", "declara_procedimento", "@6",
  "@7", "@8", "bloco_subrotina", "@9", "chamada_procedimento", "@10",
  "@11", "parametros_formais", "parametros_formais_aux",
  "secao_parametros_formais", "@12", "@13", "comando_composto_aux",
  "comando_composto", "comando", "atribuicao_ou_chama_procedimento",
  "atribuicao_ou_chama_procedimento_aux", "atribuicao", "@14", "leitura",
  "@15", "@16", "parametros_letura", "@17", "escrita", "parametros_write",
  "comando_condicional_else", "comando_condicional", "@18", "@19", "@20",
  "comando_repetitivo", "@21", "@22", "lista_expressoes", "expressao",
  "relacao", "mais_menos_epsilon", "mais_menos_or", "expressao_simples",
  "mult_div_and", "termo", "fator", "variavel", "numero", "identificador", 0
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
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    50,    49,    52,    53,    54,    51,    55,    55,
      56,    56,    57,    57,    59,    58,    60,    60,    61,    61,
      63,    64,    65,    62,    67,    66,    69,    70,    68,    68,
      68,    71,    71,    72,    72,    74,    73,    75,    73,    76,
      76,    77,    78,    78,    78,    78,    78,    79,    80,    80,
      82,    81,    84,    85,    83,    87,    86,    86,    88,    89,
      89,    90,    90,    92,    93,    94,    91,    96,    97,    95,
      98,    98,    99,    99,   100,   100,   100,   100,   100,   100,
     101,   101,   101,   102,   102,   102,   103,   103,   104,   104,
     104,   105,   105,   106,   106,   106,   106,   106,   106,   107,
     108,   109
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     0,     0,     0,     6,     1,     1,
       3,     2,     0,     2,     0,     4,     3,     1,     0,     3,
       0,     0,     0,     8,     0,     2,     0,     0,     5,     2,
       0,     0,     4,     0,     3,     0,     4,     0,     5,     3,
       0,     5,     1,     1,     1,     1,     1,     2,     1,     1,
       0,     3,     0,     0,     7,     0,     3,     0,     4,     3,
       1,     0,     2,     0,     0,     0,     8,     0,     0,     6,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     1,     3,     2,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     3,     2,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    17,     0,     0,
       0,     4,    16,     0,    12,     3,    14,     0,     5,    11,
       0,    13,    18,     0,    10,     6,     0,     0,     0,     0,
      18,     0,     8,     9,    15,    63,     7,    19,    21,   101,
       0,     0,    67,     0,    42,    43,    44,    46,     0,    45,
      30,    31,    52,    82,    82,    40,    82,     0,    49,     0,
      47,    48,     0,     0,     0,     0,    80,    81,     0,    60,
       0,    72,    68,    63,     0,    29,    82,    82,     0,    35,
      33,    22,    53,    99,    58,    82,    82,   100,    95,    96,
       0,    87,    92,    93,    94,    74,    75,    79,    76,    78,
      77,    83,    84,    85,    82,     0,     0,    41,     0,    64,
      27,    71,    51,    37,     0,     0,     0,    24,    57,    59,
       0,    98,    88,    89,    90,     0,    73,    86,     0,    39,
       0,    82,     0,     0,     0,    33,    32,    23,     4,    55,
       0,    97,    91,    69,    65,    70,    28,     0,    36,    34,
      25,     0,    54,    61,    38,    56,     0,    66,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    13,    14,    22,    29,    34,    17,    18,
      19,    20,    79,    25,    26,    27,    51,   117,   137,   138,
      58,    59,   132,    64,   116,    80,   114,   133,    73,    36,
      43,    44,    60,    61,    62,    45,    65,   118,   140,   151,
      46,    68,   157,    47,    48,   130,   153,    49,    54,   106,
     110,    69,   104,    70,   105,    71,   125,    91,    92,    93,
      94,    83
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -120
static const yytype_int8 yypact[] =
{
    -120,    29,    35,  -120,    39,    59,    49,  -120,     1,    58,
      51,  -120,  -120,    61,    53,  -120,  -120,    64,  -120,  -120,
      49,    60,    32,     7,  -120,  -120,    66,    40,    11,    65,
      32,    67,  -120,  -120,  -120,    -1,  -120,  -120,  -120,  -120,
      75,    76,  -120,    74,  -120,  -120,  -120,  -120,    44,  -120,
      13,    80,  -120,    33,    33,  -120,    33,    82,  -120,    81,
    -120,  -120,    71,    45,    83,    77,  -120,  -120,    56,  -120,
       4,    25,  -120,    -3,    54,  -120,    33,    33,    49,    85,
      86,  -120,  -120,  -120,  -120,    33,    33,  -120,  -120,  -120,
       4,    10,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,    33,     4,    46,  -120,    88,  -120,
      90,  -120,  -120,    85,    89,    45,    93,  -120,    94,  -120,
      96,  -120,  -120,  -120,  -120,     4,    28,    10,    65,  -120,
      65,    33,    97,    91,    11,    86,  -120,  -120,  -120,  -120,
      98,  -120,  -120,  -120,  -120,  -120,  -120,    11,  -120,  -120,
    -120,    77,  -120,    63,  -120,  -120,    65,  -120,  -120
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -120,  -120,  -120,   -33,  -120,  -120,  -120,  -116,  -120,  -120,
      87,  -120,    -4,    79,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,   -29,    -8,  -120,  -120,  -120,  -119,
      37,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,   -53,  -120,  -120,  -120,     8,  -120,     6,   -85,   -65,
    -120,   -31
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -51
static const yytype_int16 yytable[] =
{
      82,    72,     8,    74,    50,   121,     9,    10,    86,   143,
     107,   144,    39,    10,    39,    28,    23,    57,   148,    39,
      87,    32,    33,   111,   112,    40,    41,    40,    41,     3,
     -50,   154,   119,   120,    88,    89,   122,   158,     4,    42,
     142,    42,    50,    95,    96,    97,    98,    99,   100,   101,
     102,    90,   101,   102,     5,   123,   124,    66,    67,    78,
       7,    84,    85,     6,     7,    11,    12,    16,   -20,   103,
      15,    21,   103,    30,   113,   -14,    31,    35,   145,    52,
      53,    55,    38,    56,    63,    76,   155,    75,    77,   128,
      81,    10,    39,   115,   109,   129,   131,   134,   136,   147,
     139,   141,   146,   152,   156,   150,   149,   135,    24,    37,
     108,   127,   126
};

static const yytype_uint8 yycheck[] =
{
      65,    54,     6,    56,    35,    90,     5,     6,     4,   128,
      13,   130,    15,     6,    15,     8,    20,     4,   134,    15,
      16,    10,    11,    76,    77,    28,    29,    28,    29,     0,
      17,   147,    85,    86,    30,    31,    26,   156,     3,    42,
     125,    42,    73,    18,    19,    20,    21,    22,    23,    24,
      25,    47,    24,    25,    15,    45,    46,    24,    25,    14,
      15,     5,     6,     4,    15,     7,    15,    14,    36,    44,
       9,     7,    44,     7,    78,    15,    36,    12,   131,     4,
       4,     7,    15,    39,     4,     4,   151,     5,    17,    43,
       7,     6,    15,     7,    40,     7,     6,     8,     5,     8,
       6,     5,     5,     5,    41,   138,   135,   115,    21,    30,
      73,   105,   104
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    49,    50,     0,     3,    15,     4,    15,    60,     5,
       6,     7,    15,    51,    52,     9,    14,    56,    57,    58,
      59,     7,    53,    60,    58,    61,    62,    63,     8,    54,
       7,    36,    10,    11,    55,    12,    77,    61,    15,    15,
      28,    29,    42,    78,    79,    83,    88,    91,    92,    95,
     109,    64,     4,     4,    96,     7,    39,     4,    68,    69,
      80,    81,    82,     4,    71,    84,    24,    25,    89,    99,
     101,   103,    99,    76,    99,     5,     4,    17,    14,    60,
      73,     7,   107,   109,     5,     6,     4,    16,    30,    31,
      47,   105,   106,   107,   108,    18,    19,    20,    21,    22,
      23,    24,    25,    44,   100,   102,    97,    13,    78,    40,
      98,    99,    99,    60,    74,     7,    72,    65,    85,    99,
      99,   106,    26,    45,    46,   104,   103,   105,    43,     7,
      93,     6,    70,    75,     8,    73,     5,    66,    67,     6,
      86,     5,   106,    77,    77,    99,     5,     8,    55,    72,
      51,    87,     5,    94,    55,   107,    41,    90,    77
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
#line 246 "compilador.y"
    {
         		geraCodigo (NULL, "INPP");
             ;}
    break;

  case 3:
#line 251 "compilador.y"
    {
             	geraCodigo (NULL, "PARA");
             ;}
    break;

  case 4:
#line 258 "compilador.y"
    { 
					//Salva deslocamento anterior
					int* new_desloc = (int*)malloc(sizeof(int));
					*new_desloc = desloc;
					push(pilhaDeslocamentos,(void*)new_desloc);
				
					//Reseta deslocamento
					desloc = 0;
			  ;}
    break;

  case 5:
#line 268 "compilador.y"
    { 	/* AMEM */ 
          			snprintf(buff,15,"AMEM %d",desloc);
          			geraCodigo (NULL, buff);

					if(nivel_lexico == 0)
					{					
						char* rotulo_pula_subrotinas = geraRotulo();
						snprintf(buff,15,"DSVS %s",rotulo_pula_subrotinas);
						geraCodigo (NULL, buff);

						push(pilhaRotulo,rotulo_pula_subrotinas);
					}

					nivel_lexico++;
  			  ;}
    break;

  case 6:
#line 285 "compilador.y"
    {
					//Atualiza nivel lexico
          			nivel_lexico--;

					if(nivel_lexico == 0)
					{
						char* rotulo_pula_subrotinas = pop(pilhaRotulo);
						geraCodigo (rotulo_pula_subrotinas, "NADA");
					}
			  ;}
    break;

  case 7:
#line 298 "compilador.y"
    {

              		//Remove simbolos
              		elimina(&ts, desloc);
              	
              		//Libera memoria
					char buff[5 + 10];
          			snprintf(buff,15,"DMEM %d",desloc);
          			geraCodigo (NULL, buff);

					
          			//Recupera deslocamento anterior
          			desloc = *(int*)pop(pilhaDeslocamentos);
              ;}
    break;

  case 8:
#line 316 "compilador.y"
    { atualizaTipos(&ts, num_vars, TYPE_INT); ;}
    break;

  case 9:
#line 317 "compilador.y"
    { atualizaTipos(&ts, num_vars, TYPE_BOOL); ;}
    break;

  case 14:
#line 330 "compilador.y"
    { 	/* zera contador */
					num_vars = 0; 
			   	;}
    break;

  case 16:
#line 339 "compilador.y"
    { /* insere ultima vars na tabela de simbolos */
              	printf("[ASynt]\tINSERE VAR SIMPLES %s nl= %d, desloc = %d\n",token,nivel_lexico,desloc);
              	Item* novo_item = ItemVarSimples(token,nivel_lexico,desloc);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
               ;}
    break;

  case 17:
#line 346 "compilador.y"
    { /* insere vars na tabela de simbolos */
            	Item* novo_item = ItemVarSimples(token,nivel_lexico,desloc);
            	printf("[ASynt]\tINSERE VAR SIMPLES %s nl= %d, desloc = %d\n",token,nivel_lexico,desloc);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
            ;}
    break;

  case 20:
#line 364 "compilador.y"
    {
				printf("--Inicio declara procedimento--\n");
			;}
    break;

  case 21:
#line 368 "compilador.y"
    {
                Item* procedimento = busca(&ts, token);

                if (!procedimento) {
                    proced = geraProcedimento(token, nivel_lexico);
                    
                    char* label = geraRotulo();
					strcpy(proced->proc.rotulo,label);

                    sprintf(buff, "ENPR %d", nivel_lexico);
                    geraCodigo(proced->proc.rotulo, buff);
                }
				else
				{
					snprintf(buff,100,"Erro: o procedimento '%s' ja foi declarado!\n",token);
					yyerror(buff);
					exit(1);
				}
            ;}
    break;

  case 22:
#line 388 "compilador.y"
    {
                proced->proc.n = pilhaParametros->size;
                int offset = - 4;
                proced->proc.parametros = (ParametroFormal*)malloc(sizeof(ParametroFormal)*proced->proc.n);
                insere(&ts, proced);
				printf("Inseriu procedimento na tabela de simbolos\n");
                
				for(int i = 0; i < proced->proc.n; i++)
				{
                    Item* tmp = (Item*)pop(pilhaParametros);

                    tmp->param.deslocamento = offset;
                    //insere(&ts, ItemVarSimples(tokenAtual,nivel_lexico,offset);
					
					//newVariable(0, temporary->name, nivel_lexico, offset, temporary->item.simple.parameter));
                    offset++;
                    //proced->proc.parametros[i] = (*tmp);
                    
                }


            ;}
    break;

  case 24:
#line 414 "compilador.y"
    {
				push(pilhaSubRotinas,proced);
            ;}
    break;

  case 25:
#line 418 "compilador.y"
    {
				proced = pop(pilhaSubRotinas);
				sprintf(buff, "RTPR %d, %d", proced->nivel, proced->proc.n);	
				geraCodigo(NULL, buff);
				proced = NULL;
			;}
    break;

  case 26:
#line 427 "compilador.y"
    {
				printf("--Chamada procedimento com parametros--\n");
                if (!var) {
                    yyerror("Procedimento nao declarado.");
                    exit(1);
                }
                proced = var;
				proced->proc.n = 0;
                count_param = 0;
            ;}
    break;

  case 27:
#line 438 "compilador.y"
    {
                sprintf(buff, "CHPR %s, %d", proced->proc.rotulo, nivel_lexico);
                geraCodigo(NULL, buff);
                proced = NULL;
            ;}
    break;

  case 29:
#line 445 "compilador.y"
    {
				printf("--Chamada procedimento sem parametro com parenteses--\n");
                if (!var) {
                    yyerror("Procedimento nao declarado.");
                    exit(1);
                }
                proced = var;
                proced->proc.n = 0;

                sprintf(buff, "CHPR %s, %d", proced->proc.rotulo, nivel_lexico);
                geraCodigo(NULL, buff);
                proced = NULL;
            ;}
    break;

  case 30:
#line 459 "compilador.y"
    {
				printf("--Chamada procedimento sem parenteses--\n");
                if (!var) {
                    yyerror("Procedimento nao declarado.");
                    exit(1);
                }
                proced = var;
                proced->proc.n = 0;

                sprintf(buff, "CHPR %s, %d", proced->proc.rotulo, nivel_lexico);
                geraCodigo(NULL, buff);
                proced = NULL;
            ;}
    break;

  case 35:
#line 575 "compilador.y"
    {
				/*
                for (i_index = 0; i_index < aux->size; i_index++) {
                    temporary = &(aux->head[i_index]);
                    temporary->item.simple.parameter = VALUE_TP;
                    push(parameters, temporary);
                }
                aux->size = 0;
				*/
            ;}
    break;

  case 37:
#line 587 "compilador.y"
    {
				/*
                for (i_index = 0; i_index < aux->size; i_index++) {
                    temporary = &(aux->head[i_index]);
                    temporary->item.simple.parameter = REFERENCE_TP;
                    temporary->nvl_lex = nvl_lex;
                    push(parameters, temporary);
                }
                aux->size = 0;
				*/
            ;}
    break;

  case 50:
#line 626 "compilador.y"
    {
				printf("--Inicia atribuicao--\n");
				varAtribuida = var;
			;}
    break;

  case 51:
#line 631 "compilador.y"
    {
				//TODO: Verifica se o tipo da expressao eh o mesmo da variavel
				
				if(varAtribuida->categoria == CAT_PARAM_FORMAL_SIMPLES)
				{
					if(varAtribuida->param.passagem == REFERENCIA)
					{
						//Se eh um parametro por referencia
						char buff[5 + 10];
						sprintf(buff, "ARMI %d, %d", varAtribuida->nivel, varAtribuida->param.deslocamento);
                    	geraCodigo(NULL, buff);
					}
					else
					{
						//Se eh um parametro por valor
						char buff[5 + 10];
						sprintf(buff, "ARMZ %d, %d", varAtribuida->nivel, varAtribuida->param.deslocamento);
                    	geraCodigo(NULL, buff);
					}	
				}
				else
				{
					char buff[5 + 10];
					sprintf(buff, "ARMZ %d, %d", varAtribuida->nivel, varAtribuida->var.deslocamento);
					geraCodigo(NULL, buff);
				}
				printf("--Fim atribuicao--\n");
			;}
    break;

  case 52:
#line 664 "compilador.y"
    {geraCodigo(NULL, "LEIT");;}
    break;

  case 53:
#line 664 "compilador.y"
    { geraArmazenaValor(var);;}
    break;

  case 55:
#line 671 "compilador.y"
    {geraCodigo(NULL, "LEIT");;}
    break;

  case 56:
#line 671 "compilador.y"
    {geraArmazenaValor(var);;}
    break;

  case 59:
#line 682 "compilador.y"
    {
						geraCodigo(NULL, "IMPR");
					;}
    break;

  case 60:
#line 686 "compilador.y"
    {
						geraCodigo(NULL, "IMPR");
					;}
    break;

  case 63:
#line 695 "compilador.y"
    {
						printf("--Inicio If--\n");
					;}
    break;

  case 64:
#line 699 "compilador.y"
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

  case 65:
#line 713 "compilador.y"
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

  case 66:
#line 731 "compilador.y"
    {
						//recupera rotulo saida do else
						char* rotulo_saida_else = pop(pilhaRotulo);

						//Insere rotulo saida else
						geraCodigo (rotulo_saida_else, "NADA");
					;}
    break;

  case 67:
#line 743 "compilador.y"
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

  case 68:
#line 759 "compilador.y"
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

  case 69:
#line 775 "compilador.y"
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

  case 70:
#line 793 "compilador.y"
    {
						if (write) {
							geraCodigo(NULL, "IMPR");
						}
					;}
    break;

  case 71:
#line 799 "compilador.y"
    {
						if (write) {
							geraCodigo(NULL, "IMPR");
						}
					;}
    break;

  case 73:
#line 810 "compilador.y"
    {
				geraOperacao();            
			;}
    break;

  case 74:
#line 815 "compilador.y"
    {empilhaOperacao(OP_IGUAL);;}
    break;

  case 75:
#line 816 "compilador.y"
    {empilhaOperacao(OP_DIFERENTE);;}
    break;

  case 76:
#line 817 "compilador.y"
    {empilhaOperacao(OP_DIFERENTE);;}
    break;

  case 77:
#line 818 "compilador.y"
    {empilhaOperacao(MENOR_IGUAL);;}
    break;

  case 78:
#line 819 "compilador.y"
    {empilhaOperacao(MAIOR_IGUAL);;}
    break;

  case 79:
#line 820 "compilador.y"
    {empilhaOperacao(OP_MAIOR);;}
    break;

  case 80:
#line 823 "compilador.y"
    {sinal = 0;;}
    break;

  case 81:
#line 824 "compilador.y"
    {sinal = 1;;}
    break;

  case 82:
#line 825 "compilador.y"
    {sinal = 0;;}
    break;

  case 83:
#line 826 "compilador.y"
    {empilhaOperacao(OP_SOMA);;}
    break;

  case 84:
#line 827 "compilador.y"
    {empilhaOperacao(OP_SUBTRACAO);;}
    break;

  case 85:
#line 828 "compilador.y"
    {empilhaOperacao(OP_OR);;}
    break;

  case 86:
#line 830 "compilador.y"
    {
						geraOperacao();
					;}
    break;

  case 87:
#line 833 "compilador.y"
    {if (sinal) geraCodigo(NULL, "INVR \0");;}
    break;

  case 88:
#line 837 "compilador.y"
    {empilhaOperacao(OP_MULTIPLICACAO);;}
    break;

  case 89:
#line 838 "compilador.y"
    {empilhaOperacao(OP_DIVISAO_INTEIRA);;}
    break;

  case 90:
#line 839 "compilador.y"
    {empilhaOperacao(OP_AND);;}
    break;

  case 91:
#line 841 "compilador.y"
    {
			geraOperacao();
		;}
    break;

  case 93:
#line 849 "compilador.y"
    { 
			geraCarregaValor(var);
		;}
    break;

  case 95:
#line 854 "compilador.y"
    {
			char buff[5 + 10];
			sprintf(buff, "CRCT 1");
			geraCodigo(NULL, buff);
		;}
    break;

  case 96:
#line 860 "compilador.y"
    {
			char buff[5 + 10];
			sprintf(buff, "CRCT 0");
			geraCodigo(NULL, buff);
		;}
    break;

  case 98:
#line 868 "compilador.y"
    {
			geraCodigo(NULL, "NEGA");
		;}
    break;

  case 99:
#line 875 "compilador.y"
    {
					if(var == NULL)
					{
						//gera erro
	          			snprintf(buff,100,"Erro: variavel '%s' nao foi declarada!\n",token);
						yyerror(buff);
						exit(1);
					}
				;}
    break;

  case 100:
#line 886 "compilador.y"
    {

			//TODO: verifica se erro semantico

			char buff[5 + 10];
			strcpy(tokenAtual,token);
			snprintf(buff,15,"CRCT %s",tokenAtual);
			geraCodigo (NULL, buff);
			;}
    break;

  case 101:
#line 897 "compilador.y"
    { 
					var = busca(&ts,token);
				;}
    break;


/* Line 1267 of yacc.c.  */
#line 2420 "compilador.tab.c"
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


#line 901 "compilador.y"


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

	pilhaRotulo = initStack();

	pilhaSubRotinas = initStack();
	pilhaParametros = initStack();

   yyin=fp;
   yyparse();

   return 0;
}

