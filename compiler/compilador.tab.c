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
     T_FORWARD = 293,
     T_GOTO = 294,
     T_IF = 295,
     T_THEN = 296,
     T_ELSE = 297,
     T_WHILE = 298,
     T_DO = 299,
     T_OR = 300,
     T_DIV = 301,
     T_AND = 302,
     T_NOT = 303,
     LOWER_THAN_ELSE = 304
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
#define T_FORWARD 293
#define T_GOTO 294
#define T_IF 295
#define T_THEN 296
#define T_ELSE 297
#define T_WHILE 298
#define T_DO 299
#define T_OR 300
#define T_DIV 301
#define T_AND 302
#define T_NOT 303
#define LOWER_THAN_ELSE 304




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
int num_param = 0;
int* contaParametro;
int nivel_lexico = 0;
int desloc = 0;
int sinal = 0;	//0: mais , 1: menos
char tokenAtual[100];
char buff[100];	//buffer
int contador_rotulo = 0;
int write = 0;

int declarandoParametros = 0;
int declarandoFuncao = 0;
int chamando_subrotina = 0;
int subrotinaDeclarada = 0;


//Pilha de deslocamentos
Stack* pilhaDeslocamentos;

//Pilha de operacoes
Stack* pilhaOperacoes;

//Pilha de rotulos
Stack* pilhaRotulo;

//Pilha das sub-rotinas
Stack* pilhaSubRotinas;
Stack* pilhaParametros;
Stack* pilhaContaParametros;

//Pilha variaveisAtribuicao
Stack* pilhaVariaveisAtribuicao;

//Tabela de simbolos
TabelaSimbolos ts;

//Itens
Item* func = NULL;
Item* proced = NULL;
Item* var = NULL;
Item* varAtribuida = NULL;


#define YYSTYPE char *

Item* geraFuncao(char* identificador, int nivel)
{
	//Cria item
	Item* new_item = (Item*)malloc(sizeof(Item));
	
	//Aloca espaco para o identificador
	new_item->identificador = (char*)malloc(100*sizeof(char));

	//Preenche campos
	strcpy(new_item->identificador,identificador);
	new_item->categoria = CAT_FUNCAO;
	new_item->nivel = nivel;
	new_item->proc.implemented = 0;

	return new_item;
}

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
	new_item->proc.implemented = 0;

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
			if(chamando_subrotina && proced->proc.parametros[*contaParametro].passagem)
				//Se a variavel eh um argumento e eh passado por referencia
				sprintf(buff, "CREN %d, %d", variavel->nivel, variavel->param.deslocamento);
			else
				//Se eh um parametro por valor
				sprintf(buff, "CRVL %d, %d", variavel->nivel, variavel->param.deslocamento);
		}	
	}
	else
	{
		if(variavel->categoria == CAT_VARIAVEL)
			if(chamando_subrotina && proced->proc.parametros[*contaParametro].passagem)
				//Se a variavel eh um argumento e eh passado por referencia
				sprintf(buff, "CREN %d, %d", variavel->nivel, variavel->param.deslocamento);
			else
				sprintf(buff, "CRVL %d, %d", variavel->nivel, variavel->var.deslocamento);
		else
			sprintf(buff, "CRVL %d, %d", variavel->nivel,  - variavel->proc.n);
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
		if(variavel->categoria == CAT_VARIAVEL)
			sprintf(buff, "ARMZ %d, %d", variavel->nivel, variavel->var.deslocamento);
		else
			sprintf(buff, "ARMZ %d, %d", variavel->nivel, -4 -variavel->proc.n);
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

Item* criaParametro(char* identificador,int nl,PassagemTipo tipoPassagem)
{
	Item* novoParametro = (Item*)malloc(sizeof(Item));
	novoParametro->identificador = (char*)malloc(100*sizeof(char));

	//Preenche campos
	strcpy(novoParametro->identificador,identificador);
	novoParametro->categoria = CAT_PARAM_FORMAL_SIMPLES;
	novoParametro->nivel = nl;
	novoParametro->param.passagem = tipoPassagem;

	return novoParametro;
}

void atualizaDeslocamentoParametros(Stack* pilha)
{
	Stack* aux = initStack();
	int size = pilha->size;
	while(pilha->size > 0)
	{
		//retra os parametros atualizando o deslocamento
		Item* parametro = pop(pilha);
		parametro->param.deslocamento = -4 - ((size - pilha->size) - 1);
		push(aux,parametro);
	}
	while(aux->size > 0)
	{
		//devolve para a pilha original
		push(pilha,pop(aux));
	}
	return;
}


void atualizaTiposParametros(Stack* pilha,int qtd,VarTipo tipo)
{
	Stack* aux = initStack();
	while(qtd > 0)
	{
		//retra os parametros atualizando o tipo
		qtd--;
		Item* parametro = pop(pilha);
		parametro->param.tipo = tipo;
		push(aux,parametro);
	}
	while(aux->size > 0)
	{
		//devolve para a pilha original
		push(pilha,pop(aux));
	}
	return;
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
#line 519 "compilador.tab.c"

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
#define YYLAST   148

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  80
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNRULES -- Number of states.  */
#define YYNSTATES  193

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

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
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    14,    15,    16,    17,    24,    26,
      28,    32,    35,    36,    39,    40,    45,    49,    51,    52,
      56,    60,    62,    63,    66,    67,    68,    69,    78,    79,
      80,    81,    82,    83,    96,    97,   100,   101,   103,   107,
     108,   113,   114,   115,   120,   121,   122,   123,   130,   131,
     135,   139,   141,   145,   147,   148,   153,   154,   160,   164,
     165,   171,   173,   175,   177,   179,   180,   183,   185,   188,
     190,   192,   193,   197,   199,   200,   201,   205,   206,   207,
     215,   216,   220,   221,   226,   230,   232,   233,   236,   238,
     239,   240,   241,   250,   251,   252,   259,   261,   265,   267,
     269,   271,   273,   275,   277,   279,   281,   282,   284,   286,
     288,   292,   295,   297,   299,   301,   305,   307,   309,   311,
     313,   315,   319,   322,   324,   326
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      51,     0,    -1,    -1,    52,     3,    15,     4,    62,     5,
       7,    53,     9,    -1,    -1,    -1,    -1,    54,    59,    55,
      63,    56,    93,    -1,    10,    -1,    11,    -1,    58,     7,
      60,    -1,    14,    60,    -1,    -1,    58,     7,    -1,    -1,
      61,    62,     8,    57,    -1,    62,     6,    15,    -1,    15,
      -1,    -1,    66,     7,    63,    -1,    70,     7,    63,    -1,
      38,    -1,    -1,    65,    76,    -1,    -1,    -1,    -1,    67,
      36,    15,    68,    83,     7,    69,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    37,    15,    72,    83,     8,    73,
      57,    74,     7,    75,    64,    -1,    -1,    77,    53,    -1,
      -1,   119,    -1,    78,     6,   119,    -1,    -1,    80,     4,
      78,     5,    -1,    -1,    -1,    82,     4,    78,     5,    -1,
      -1,    -1,    -1,    84,     4,    85,    89,    86,     5,    -1,
      -1,     7,    89,    86,    -1,    87,     6,    15,    -1,    15,
      -1,    88,     6,    15,    -1,    15,    -1,    -1,    90,    87,
       8,    57,    -1,    -1,    14,    91,    88,     8,    57,    -1,
      92,    94,     7,    -1,    -1,    12,    94,     7,    92,    13,
      -1,    96,    -1,   103,    -1,   108,    -1,   116,    -1,    -1,
      95,   112,    -1,    93,    -1,   129,    97,    -1,   101,    -1,
      79,    -1,    -1,    15,    99,   100,    -1,    81,    -1,    -1,
      -1,   102,    17,   119,    -1,    -1,    -1,    28,     4,   104,
     127,   105,   106,     5,    -1,    -1,     6,   107,   127,    -1,
      -1,    29,     4,   109,     5,    -1,   109,     6,   119,    -1,
     119,    -1,    -1,   111,    94,    -1,    49,    -1,    -1,    -1,
      -1,   113,    40,   119,    41,   114,    94,   115,   110,    -1,
      -1,    -1,    43,   117,   119,   118,    44,    94,    -1,   123,
      -1,   123,   120,   123,    -1,    18,    -1,    19,    -1,    21,
      -1,    23,    -1,    22,    -1,    20,    -1,    24,    -1,    25,
      -1,    -1,    24,    -1,    25,    -1,    45,    -1,   123,   122,
     125,    -1,   121,   125,    -1,    26,    -1,    46,    -1,    47,
      -1,   125,   124,   126,    -1,   126,    -1,    98,    -1,   128,
      -1,    30,    -1,    31,    -1,     4,   119,     5,    -1,    48,
     126,    -1,   129,    -1,    16,    -1,    15,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   341,   341,   341,   353,   363,   380,   353,   409,   418,
     431,   432,   433,   434,   439,   439,   447,   455,   466,   467,
     468,   474,   484,   484,   497,   501,   529,   497,   547,   551,
     574,   574,   575,   547,   594,   594,   613,   613,   614,   617,
     617,   668,   694,   694,   745,   747,   749,   747,   759,   760,
     764,   770,   778,   784,   793,   793,   798,   797,   808,   808,
     809,   812,   813,   814,   815,   816,   816,   817,   821,   824,
     825,   830,   829,   836,   838,   854,   854,   878,   878,   877,
     885,   884,   886,   890,   894,   899,   908,   908,   909,   911,
     915,   928,   911,   959,   975,   958,  1007,  1008,  1014,  1015,
    1016,  1017,  1018,  1019,  1022,  1023,  1024,  1025,  1026,  1027,
    1028,  1032,  1036,  1037,  1038,  1039,  1043,  1047,  1048,  1049,
    1055,  1061,  1062,  1069,  1081,  1090
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
  "T_PROCEDURE", "T_FUNCTION", "T_FORWARD", "T_GOTO", "T_IF", "T_THEN",
  "T_ELSE", "T_WHILE", "T_DO", "T_OR", "T_DIV", "T_AND", "T_NOT",
  "LOWER_THAN_ELSE", "$accept", "programa", "@1", "bloco", "@2", "@3",
  "@4", "tipo", "parte_declara_vars_aux", "parte_declara_vars",
  "declara_vars", "@5", "lista_idents", "parte_declara_subrotinas",
  "foward_ou_bloco", "@6", "declara_procedimento", "@7", "@8", "@9",
  "declara_funcao", "@10", "@11", "@12", "@13", "@14", "bloco_subrotina",
  "@15", "lista_parametros", "chamada_procedimento", "@16",
  "chamada_funcao", "@17", "parametros_formais", "@18", "@19",
  "parametros_formais_aux", "lista_parametros_valor",
  "lista_parametros_referencia", "secao_parametros_formais", "@20", "@21",
  "comando_composto_aux", "comando_composto", "comando", "@22",
  "atribuicao_ou_chama_procedimento",
  "atribuicao_ou_chama_procedimento_aux", "variavel_ou_chamada_funcao",
  "@23", "variavel_ou_chamada_funcao_aux", "atribuicao", "@24", "leitura",
  "@25", "@26", "parametros_letura", "@27", "escrita", "parametros_write",
  "comando_condicional_else", "@28", "comando_condicional", "@29", "@30",
  "@31", "comando_repetitivo", "@32", "@33", "expressao", "relacao",
  "mais_menos_epsilon", "mais_menos_or", "expressao_simples",
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    52,    51,    54,    55,    56,    53,    57,    57,
      58,    58,    59,    59,    61,    60,    62,    62,    63,    63,
      63,    64,    65,    64,    67,    68,    69,    66,    71,    72,
      73,    74,    75,    70,    77,    76,    78,    78,    78,    80,
      79,    79,    82,    81,    83,    84,    85,    83,    86,    86,
      87,    87,    88,    88,    90,    89,    91,    89,    92,    92,
      93,    94,    94,    94,    94,    95,    94,    94,    96,    97,
      97,    99,    98,   100,   100,   102,   101,   104,   105,   103,
     107,   106,   106,   108,   109,   109,   111,   110,   110,   113,
     114,   115,   112,   117,   118,   116,   119,   119,   120,   120,
     120,   120,   120,   120,   121,   121,   121,   122,   122,   122,
     123,   123,   124,   124,   124,   125,   125,   126,   126,   126,
     126,   126,   126,   127,   128,   129
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     0,     0,     0,     6,     1,     1,
       3,     2,     0,     2,     0,     4,     3,     1,     0,     3,
       3,     1,     0,     2,     0,     0,     0,     8,     0,     0,
       0,     0,     0,    12,     0,     2,     0,     1,     3,     0,
       4,     0,     0,     4,     0,     0,     0,     6,     0,     3,
       3,     1,     3,     1,     0,     4,     0,     5,     3,     0,
       5,     1,     1,     1,     1,     0,     2,     1,     2,     1,
       1,     0,     3,     1,     0,     0,     3,     0,     0,     7,
       0,     3,     0,     4,     3,     1,     0,     2,     1,     0,
       0,     0,     8,     0,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     1,     1,
       3,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     3,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    17,     0,     0,
       0,     4,    16,     0,    12,     3,    14,     0,     5,    11,
       0,    13,    18,     0,    10,     6,     0,     0,     0,     0,
       0,     0,    18,     0,    18,     0,     8,     9,    15,    65,
       7,    19,    25,    20,    29,   125,     0,     0,    93,    67,
       0,    89,    61,    62,    63,    64,    41,    44,    44,    77,
     106,   106,    59,    66,     0,    70,     0,    68,    69,     0,
       0,     0,     0,     0,   104,   105,     0,    85,     0,    96,
      94,    65,   106,   106,   106,    26,    46,    30,    78,   123,
      83,   106,   106,    71,   124,   119,   120,     0,   117,   111,
     116,   118,    98,    99,   103,   100,   102,   101,   107,   108,
     109,   106,     0,     0,    60,     0,     0,     0,    37,    76,
      22,    54,     0,    82,    84,     0,    74,   122,   112,   113,
     114,     0,    97,   110,    65,    58,    90,    40,   106,    21,
      27,    34,    56,    48,     0,    31,    80,     0,   121,    73,
       0,    72,   115,    95,    65,    38,    23,     4,     0,    54,
       0,    51,     0,     0,     0,    79,   106,    91,    35,    53,
       0,    48,    47,     0,     0,    32,    81,     0,    86,     0,
       0,    49,    50,    55,    22,    43,    88,    92,    65,    52,
      57,    33,    87
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    13,    14,    22,    31,    38,    17,    18,
      19,    20,     8,    25,   140,   141,    26,    27,    57,   120,
      28,    29,    58,   122,   163,   184,   156,   157,   117,    65,
      66,   149,   150,    70,    71,   121,   160,   162,   170,   143,
     144,   158,    81,    49,    50,    51,    52,    67,    98,   126,
     151,    68,    69,    53,    73,   123,   147,   164,    54,    76,
     187,   188,    63,    64,   154,   178,    55,    61,   113,   118,
     111,    78,   112,    79,   131,    99,   100,    88,   101,    56
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -119
static const yytype_int8 yypact[] =
{
    -119,    18,    22,  -119,    36,    51,    66,  -119,     2,    30,
      67,  -119,  -119,    52,    70,  -119,  -119,    76,  -119,  -119,
      66,    72,    11,    37,  -119,  -119,    78,    50,    81,    54,
      49,    77,    11,    79,    11,    80,  -119,  -119,  -119,     7,
    -119,  -119,  -119,  -119,  -119,  -119,    89,    92,  -119,  -119,
      90,  -119,  -119,  -119,  -119,  -119,     6,    94,    94,  -119,
      47,    47,  -119,  -119,    59,  -119,    96,  -119,  -119,    84,
      95,    99,    97,    91,  -119,  -119,    69,  -119,     1,    45,
    -119,    -1,    47,    33,    47,  -119,  -119,  -119,  -119,  -119,
    -119,    47,    47,  -119,  -119,  -119,  -119,     1,  -119,   -17,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,    47,     1,    60,  -119,   101,    68,    71,  -119,  -119,
      74,   100,    49,   104,  -119,   106,   109,  -119,  -119,  -119,
    -119,     1,    -4,   -17,     7,  -119,  -119,  -119,    47,  -119,
    -119,  -119,  -119,   108,   102,  -119,  -119,   111,  -119,  -119,
     114,  -119,  -119,  -119,     7,  -119,  -119,  -119,   105,   100,
     116,  -119,    38,   112,    91,  -119,    33,  -119,  -119,  -119,
      46,   108,  -119,   107,    49,  -119,  -119,    73,    75,   110,
      49,  -119,  -119,  -119,    74,  -119,  -119,  -119,     7,  -119,
    -119,  -119,  -119
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -119,  -119,  -119,   -34,  -119,  -119,  -119,  -118,  -119,  -119,
     113,  -119,   115,   -19,   -57,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,   -40,  -119,
    -119,  -119,  -119,    82,  -119,  -119,   -43,  -119,  -119,   -30,
    -119,  -119,  -119,   117,   -81,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,   -58,
    -119,  -119,  -119,    19,  -119,    20,   -91,   -33,  -119,   -72
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -76
static const yytype_int16 yytable[] =
{
     115,    89,    77,    80,   145,    92,   127,     9,    10,   128,
     -39,    39,   114,    41,    45,    43,    93,    94,     3,    39,
     108,   109,    45,   -75,   116,     4,   119,    46,    47,   129,
     130,    95,    96,   124,   125,    46,    47,    11,   -36,   -36,
     152,   110,    48,    10,   173,    30,   174,   -24,   -28,    97,
      48,     5,   179,   153,   180,     6,   183,    74,    75,    36,
      37,    15,   190,   102,   103,   104,   105,   106,   107,   108,
     109,    74,    75,   167,    90,    91,   137,   138,   185,   138,
     155,     7,    12,    21,    16,    32,    33,   -14,    34,    39,
     110,    35,    89,    59,    42,    44,    60,    62,   -45,    82,
      83,    84,    85,    86,   134,    87,    45,   192,   135,   136,
     146,   148,   139,   -42,   142,   159,   165,   161,   166,   175,
     169,   172,   182,   168,   186,   189,   177,   191,   181,   171,
     132,   176,   133,     0,    24,    23,     0,     0,     0,     0,
      72,     0,     0,     0,     0,     0,     0,     0,    40
};

static const yytype_int16 yycheck[] =
{
      81,    73,    60,    61,   122,     4,    97,     5,     6,    26,
       4,    12,    13,    32,    15,    34,    15,    16,     0,    12,
      24,    25,    15,    17,    82,     3,    84,    28,    29,    46,
      47,    30,    31,    91,    92,    28,    29,     7,     5,     6,
     131,    45,    43,     6,     6,     8,     8,    36,    37,    48,
      43,    15,     6,   134,     8,     4,   174,    24,    25,    10,
      11,     9,   180,    18,    19,    20,    21,    22,    23,    24,
      25,    24,    25,   154,     5,     6,     5,     6,     5,     6,
     138,    15,    15,     7,    14,     7,    36,    15,     7,    12,
      45,    37,   164,     4,    15,    15,     4,     7,     4,    40,
       4,    17,     7,     4,    44,     8,    15,   188,     7,    41,
       6,     5,    38,     4,    14,     7,     5,    15,     4,     7,
      15,     5,    15,   157,    49,    15,   166,   184,   171,   159,
     111,   164,   112,    -1,    21,    20,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    51,    52,     0,     3,    15,     4,    15,    62,     5,
       6,     7,    15,    53,    54,     9,    14,    58,    59,    60,
      61,     7,    55,    62,    60,    63,    66,    67,    70,    71,
       8,    56,     7,    36,     7,    37,    10,    11,    57,    12,
      93,    63,    15,    63,    15,    15,    28,    29,    43,    93,
      94,    95,    96,   103,   108,   116,   129,    68,    72,     4,
       4,   117,     7,   112,   113,    79,    80,    97,   101,   102,
      83,    84,    83,   104,    24,    25,   109,   119,   121,   123,
     119,    92,    40,     4,    17,     7,     4,     8,   127,   129,
       5,     6,     4,    15,    16,    30,    31,    48,    98,   125,
     126,   128,    18,    19,    20,    21,    22,    23,    24,    25,
      45,   120,   122,   118,    13,    94,   119,    78,   119,   119,
      69,    85,    73,   105,   119,   119,    99,   126,    26,    46,
      47,   124,   123,   125,    44,     7,    41,     5,     6,    38,
      64,    65,    14,    89,    90,    57,     6,   106,     5,    81,
      82,   100,   126,    94,   114,   119,    76,    77,    91,     7,
      86,    15,    87,    74,   107,     5,     4,    94,    53,    15,
      88,    89,     5,     6,     8,     7,   127,    78,   115,     6,
       8,    86,    15,    57,    75,     5,    49,   110,   111,    15,
      57,    64,    94
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
#line 341 "compilador.y"
    {
         		geraCodigo (NULL, "INPP");
             ;}
    break;

  case 3:
#line 346 "compilador.y"
    {
             	geraCodigo (NULL, "PARA");
             ;}
    break;

  case 4:
#line 353 "compilador.y"
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
#line 363 "compilador.y"
    { 	/* AMEM */ 
          			sprintf(buff,"AMEM %d",desloc);
          			geraCodigo (NULL, buff);

					if(nivel_lexico == 0)
					{					
						char* rotulo_pula_subrotinas = geraRotulo();
						sprintf(buff,"DSVS %s",rotulo_pula_subrotinas);
						geraCodigo (NULL, buff);

						push(pilhaRotulo,rotulo_pula_subrotinas);
					}

					nivel_lexico++;
  			  ;}
    break;

  case 6:
#line 380 "compilador.y"
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
#line 393 "compilador.y"
    {
              		//Remove simbolos
              		elimina(&ts, desloc);
              	
              		//Libera memoria
          			sprintf(buff,"DMEM %d",desloc);
          			geraCodigo (NULL, buff);

					
          			//Recupera deslocamento anterior
          			desloc = *(int*)pop(pilhaDeslocamentos);
              ;}
    break;

  case 8:
#line 410 "compilador.y"
    { 
				if(declarandoFuncao)
					proced->proc.tipo = TYPE_INT;
				else if(!declarandoParametros)
					atualizaTipos(&ts, num_vars, TYPE_INT); 
				else
					atualizaTiposParametros(pilhaParametros,num_param,TYPE_INT);
			;}
    break;

  case 9:
#line 419 "compilador.y"
    { 
				if(declarandoFuncao)
					proced->proc.tipo = TYPE_BOOL;
				else if(!declarandoParametros)
					atualizaTipos(&ts, num_vars, TYPE_BOOL);
				else
					atualizaTiposParametros(pilhaParametros,num_param,TYPE_BOOL);
			;}
    break;

  case 14:
#line 439 "compilador.y"
    { 	/* zera contador */
					num_vars = 0; 
			   	;}
    break;

  case 16:
#line 448 "compilador.y"
    { /* insere ultima vars na tabela de simbolos */
              	printf("[ASynt]\tINSERE VAR SIMPLES %s nl= %d, desloc = %d\n",token,nivel_lexico,desloc);
              	Item* novo_item = ItemVarSimples(token,nivel_lexico,desloc);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
               ;}
    break;

  case 17:
#line 455 "compilador.y"
    { /* insere vars na tabela de simbolos */
            	Item* novo_item = ItemVarSimples(token,nivel_lexico,desloc);
            	printf("[ASynt]\tINSERE VAR SIMPLES %s nl= %d, desloc = %d\n",token,nivel_lexico,desloc);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
            ;}
    break;

  case 21:
#line 475 "compilador.y"
    {
					if(subrotinaDeclarada)
					{
						sprintf(buff,"Erro: o procedimento/funcao '%s' ja foi declarado!\n",proced->identificador);
						yyerror(buff);
						exit(1);
					}
				;}
    break;

  case 22:
#line 484 "compilador.y"
    {
					//indica que a funcao ja foi implementada
					proced->proc.implemented = 1;
					//codigo entra procediemnto
					sprintf(buff, "ENPR %d", nivel_lexico);
                    geraCodigo(proced->proc.rotulo, buff);
				;}
    break;

  case 24:
#line 497 "compilador.y"
    {
				printf("--Inicio declara procedimento--\n");
			;}
    break;

  case 25:
#line 501 "compilador.y"
    {
				subrotinaDeclarada = 0;
                Item* procedimento = busca(&ts, token);

				//Se procedimento nao declarado
                if (!procedimento) {
					//decara e insere na tabela
                    proced = geraProcedimento(token, nivel_lexico);
                    
                    char* label = geraRotulo();
					strcpy(proced->proc.rotulo,label);
                }
				else if(procedimento->proc.implemented)
				{
					//procedimento ja implementado e esta sendo declarado novamente
					sprintf(buff,"Erro: o procedimento '%s' ja foi implementado!\n",token);
					yyerror(buff);
					exit(1);
				}
				else
				{
					//flag que indica que a funcao ja foi declarada com foward
					subrotinaDeclarada = 1;
					proced = procedimento;
				}
				
            ;}
    break;

  case 26:
#line 529 "compilador.y"
    {
				proced->proc.n = pilhaParametros->size;
				proced->proc.parametros = malloc(sizeof(ParametroFormal)*proced->proc.n);
                insere(&ts, proced);
                
				for(int i = 0; i < proced->proc.n; i++)
				{
                    Item* tmp = (Item*)pop(pilhaParametros);
					insere(&ts, tmp);
					proced->proc.parametros[proced->proc.n - i] = tmp->param;
                }
            ;}
    break;

  case 28:
#line 547 "compilador.y"
    {
				printf("--Inicio declara funcao--\n");
			;}
    break;

  case 29:
#line 551 "compilador.y"
    {
				subrotinaDeclarada = 0;
                Item* procedimento = busca(&ts, token);

                if (!procedimento) {
                    proced = geraFuncao(token, nivel_lexico);
                    
                    char* label = geraRotulo();
					strcpy(proced->proc.rotulo,label);
                }
				else if(procedimento->proc.implemented)
				{
					sprintf(buff,"Erro: a funcao '%s' ja foi declarado!\n",token);
					yyerror(buff);
					exit(1);
				}
				else
				{
					//flag que indica que a funcao ja foi declarada com foward
					subrotinaDeclarada = 1;
					proced = procedimento;
				}
            ;}
    break;

  case 30:
#line 574 "compilador.y"
    {declarandoFuncao = 1;;}
    break;

  case 31:
#line 574 "compilador.y"
    {declarandoFuncao = 0;;}
    break;

  case 32:
#line 575 "compilador.y"
    {
				if(!subrotinaDeclarada)
				{
					proced->proc.n = pilhaParametros->size;
					proced->proc.parametros = malloc(sizeof(ParametroFormal)*proced->proc.n);
					insere(&ts, proced);

					for(int i = 0; i < proced->proc.n; i++)
					{
						Item* tmp = (Item*)pop(pilhaParametros);
						insere(&ts, tmp);
						proced->proc.parametros[proced->proc.n - i] = tmp->param;
					}
				}
            ;}
    break;

  case 34:
#line 594 "compilador.y"
    {
				push(pilhaSubRotinas,proced);
            ;}
    break;

  case 35:
#line 598 "compilador.y"
    {
				//gera codigo retorna procedmento
				proced = pop(pilhaSubRotinas);
				proced = busca(&ts,proced->identificador);
				sprintf(buff, "RTPR %d, %d", proced->nivel, proced->proc.n);	
				geraCodigo(NULL, buff);

				//retira parametros da tabela de simbolos
				elimina(&ts,proced->proc.n);

				proced = NULL;
			;}
    break;

  case 37:
#line 613 "compilador.y"
    { *contaParametro = *contaParametro + 1;;}
    break;

  case 38:
#line 614 "compilador.y"
    { *contaParametro = *contaParametro + 1;;}
    break;

  case 39:
#line 617 "compilador.y"
    {
				printf("--Chamada procedimento com parametros--\n");
                if (!var) {
                    yyerror("Erro: Procedimento/funcao nao declarado.");
                    exit(1);
                }
				if(var->categoria != CAT_PROCEDIM && var->categoria != CAT_FUNCAO)
				{
					sprintf(buff,"Erro: o token %s nao faz referencia a uma funcao nem a um procedimento\n",var->identificador);
					yyerror(buff);
                    exit(1);
				}

                proced = var;
				//se eh um procedimento, aloca espaco para valor de retorno
				if(proced->categoria == CAT_FUNCAO)
				{
					geraCodigo(NULL, "AMEM 1");
				}

				//salva procedimento anterior
				push(pilhaSubRotinas,proced);
				//empilha contagem de parametros anterior
				push(pilhaContaParametros,contaParametro);
				//cria uma nova contagem do 0
				contaParametro = malloc(sizeof(int));
				*contaParametro = 0;
				//empilha parametros
				chamando_subrotina = 1;

            ;}
    break;

  case 40:
#line 649 "compilador.y"
    {
				chamando_subrotina = 0;
				//recupera procedimento
				proced = pop(pilhaSubRotinas);
				//Verifica se a quantidade de parametros batem
				if(*contaParametro != proced->proc.n)
				{
					sprintf(buff,"Erro: a funcao/procedimento %s utiliza %d parametros mas foi passado %d\n",proced->identificador,proced->proc.n,*contaParametro);
					yyerror(buff);
                    exit(1);
				}
				//recupera contador anterior
				contaParametro = pop(pilhaContaParametros);
				//gera codigo chama procedimento
                sprintf(buff, "CHPR %s, %d", proced->proc.rotulo, nivel_lexico);
                geraCodigo(NULL, buff);
                proced = NULL;
            ;}
    break;

  case 41:
#line 668 "compilador.y"
    {
				printf("--Chamada procedimento sem parenteses--\n");
                if (!var) {
                    yyerror("Erro: Procedimento nao declarado.");
                    exit(1);
                }
				if(var->categoria != CAT_PROCEDIM && var->categoria != CAT_FUNCAO)
				{
					sprintf(buff,"Erro: o token %s nao faz referencia a uma funcao nem a um procedimento\n",token);
					yyerror(buff);
                    exit(1);
				}
                proced = var;
				//se eh um procedimento, aloca espaco para valor de retorno
				if(proced->categoria == CAT_FUNCAO)
				{
					geraCodigo(NULL, "AMEM 1");
				}

                sprintf(buff, "CHPR %s, %d", proced->proc.rotulo, nivel_lexico);
                geraCodigo(NULL, buff);
                proced = NULL;
            ;}
    break;

  case 42:
#line 694 "compilador.y"
    {
				printf("--Chamada funcao com parametros--\n");
                if (!var) {
                    yyerror("Erro: funcao nao declarada.");
                    exit(1);
                }

				if(var->categoria != CAT_FUNCAO)
				{
					sprintf(buff,"Erro: o token %s nao faz referencia a uma funcao\n",var->identificador);
					yyerror(buff);
                    exit(1);
				}

                proced = var;
				geraCodigo(NULL, "AMEM 1");
				
				//salva procedimento anterior
				push(pilhaSubRotinas,proced);
				//empilha contagem de parametros anterior
				push(pilhaContaParametros,contaParametro);
				//cria uma nova contagem do 0
				contaParametro = malloc(sizeof(int));
				*contaParametro = 0;
				//empilha parametros
				chamando_subrotina = 1;
            ;}
    break;

  case 43:
#line 722 "compilador.y"
    {
				chamando_subrotina = 0;
				//recupera procedimento
				proced = pop(pilhaSubRotinas);
				//Verifica se a quantidade de parametros batem
				if(*contaParametro != proced->proc.n)
				{
					sprintf(buff,"Erro: a funcao/procedimento %s utiliza %d parametros mas foi passado %d\n",proced->identificador,proced->proc.n,*contaParametro);
					yyerror(buff);
                    exit(1);
				}
				//recupera contador anterior
				contaParametro = pop(pilhaContaParametros);
				//gera codigo chama procedimento

                sprintf(buff, "CHPR %s, %d", proced->proc.rotulo, nivel_lexico);
                geraCodigo(NULL, buff);
                proced = NULL;
				printf("--fim chamada funcao com parametros--\n");
            ;}
    break;

  case 45:
#line 747 "compilador.y"
    { 
				printf("Inicio parametros formais\n");
				declarandoParametros = 1; ;}
    break;

  case 46:
#line 749 "compilador.y"
    { emptyStack(pilhaParametros); ;}
    break;

  case 47:
#line 751 "compilador.y"
    {
				//corrige deslocamentos
				atualizaDeslocamentoParametros(pilhaParametros);
				declarandoParametros = 0;
				printf("fim parametros formais \n");
			;}
    break;

  case 50:
#line 765 "compilador.y"
    {
							num_param++;
							Item* parametroValor = criaParametro(token,nivel_lexico,PARAMETRO);
							push(pilhaParametros,parametroValor);
						;}
    break;

  case 51:
#line 771 "compilador.y"
    {
							num_param++;
							Item* parametroValor = criaParametro(token,nivel_lexico,PARAMETRO);
							push(pilhaParametros,parametroValor);
						;}
    break;

  case 52:
#line 779 "compilador.y"
    {
							num_param++;
							Item* parametroReferencia = criaParametro(token,nivel_lexico,REFERENCIA);
							push(pilhaParametros,parametroReferencia);
						;}
    break;

  case 53:
#line 785 "compilador.y"
    {
							num_param++;
							Item* parametroReferencia = criaParametro(token,nivel_lexico,REFERENCIA);
							push(pilhaParametros,parametroReferencia);
						;}
    break;

  case 54:
#line 793 "compilador.y"
    {
				num_param = 0;
			;}
    break;

  case 56:
#line 798 "compilador.y"
    {
				num_param = 0;
			;}
    break;

  case 65:
#line 816 "compilador.y"
    {printf("comando - comando condicional\n");;}
    break;

  case 71:
#line 830 "compilador.y"
    {
		var = busca(&ts,token);
	;}
    break;

  case 74:
#line 838 "compilador.y"
    {
		if(var == NULL)
		{
			//gera erro
			sprintf(buff,"Erro: variavel '%s' nao foi declarada!\n",token);
			yyerror(buff);
			exit(1);
		}
		//carrega valor variavel
		geraCarregaValor(var);
	;}
    break;

  case 75:
#line 854 "compilador.y"
    {
				printf("--Inicia atribuicao--\n");
				if(!var)
				{
					//gera erro
					sprintf(buff,"Erro: variavel nao foi declarada!\n");
					yyerror(buff);
					exit(1);
				}
				varAtribuida = var;
				push(pilhaVariaveisAtribuicao,var);
			;}
    break;

  case 76:
#line 867 "compilador.y"
    {
				//TODO: Verifica se o tipo da expressao eh o mesmo da variavel
				varAtribuida = pop(pilhaVariaveisAtribuicao);
				geraArmazenaValor(varAtribuida);
				printf("--Fim atribuicao--\n");
			;}
    break;

  case 77:
#line 878 "compilador.y"
    {geraCodigo(NULL, "LEIT");;}
    break;

  case 78:
#line 878 "compilador.y"
    { geraArmazenaValor(var);;}
    break;

  case 80:
#line 885 "compilador.y"
    {geraCodigo(NULL, "LEIT");;}
    break;

  case 81:
#line 885 "compilador.y"
    {geraArmazenaValor(var);;}
    break;

  case 84:
#line 895 "compilador.y"
    {
						printf("virgula expressao ");
						geraCodigo(NULL, "IMPR");
					;}
    break;

  case 85:
#line 900 "compilador.y"
    {
						printf(" expressao ");
						geraCodigo(NULL, "IMPR");
					;}
    break;

  case 86:
#line 908 "compilador.y"
    {printf("inicio comando else\n");;}
    break;

  case 87:
#line 908 "compilador.y"
    {printf("fim comando else\n");;}
    break;

  case 89:
#line 911 "compilador.y"
    {
						printf("--Inicio If--\n");
					;}
    break;

  case 90:
#line 915 "compilador.y"
    {
						//Cria rotulo saida e empilha
						char* rotulo_entrada_else = geraRotulo();
						
						//desvia se falso
						sprintf(buff,"DSVF %s",rotulo_entrada_else);
						geraCodigo (NULL, buff);

						//empilha rotulo entrada do else
						push(pilhaRotulo,rotulo_entrada_else);

					;}
    break;

  case 91:
#line 928 "compilador.y"
    {
						//Cria rotulo saida e empilha
						char* rotulo_saida_else = geraRotulo();
						
						//desvia sempre
						sprintf(buff,"DSVS %s",rotulo_saida_else);
						geraCodigo (NULL, buff);
				
						//recupera rotulo entrada do else
						char* rotulo_entrada_else = pop(pilhaRotulo);

						//Insere rotulo entrada else
						geraCodigo (rotulo_entrada_else, "NADA");

						push(pilhaRotulo,rotulo_saida_else);

					;}
    break;

  case 92:
#line 945 "compilador.y"
    {
						//recupera rotulo saida do else
						char* rotulo_saida_else = pop(pilhaRotulo);

						//Insere rotulo saida else
						geraCodigo (rotulo_saida_else, "NADA");

						printf("--Fim If--\n");
					;}
    break;

  case 93:
#line 959 "compilador.y"
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

  case 94:
#line 975 "compilador.y"
    {
						//recupera rotulos
						char* rotulo_saida = pop(pilhaRotulo);
						char* rotulo_entrada = pop(pilhaRotulo);

						//desvia se falso
						sprintf(buff,"DSVF %s",rotulo_saida);
						geraCodigo (NULL, buff);

						//empilha rotulos
						push(pilhaRotulo,rotulo_entrada);
						push(pilhaRotulo,rotulo_saida);

					;}
    break;

  case 95:
#line 990 "compilador.y"
    {
						//recupera rotulos
						char* rotulo_saida = pop(pilhaRotulo);
						char* rotulo_entrada = pop(pilhaRotulo);
						//desvia sempre
						sprintf(buff,"DSVS %s",rotulo_entrada);
						geraCodigo (NULL, buff);

						//Insere rotulo saida no codgo MEPA
						geraCodigo (rotulo_saida, "NADA");
						printf("--Fim while--\n");

					;}
    break;

  case 97:
#line 1009 "compilador.y"
    {
				geraOperacao();            
			;}
    break;

  case 98:
#line 1014 "compilador.y"
    {empilhaOperacao(OP_IGUAL);;}
    break;

  case 99:
#line 1015 "compilador.y"
    {empilhaOperacao(OP_DIFERENTE);;}
    break;

  case 100:
#line 1016 "compilador.y"
    {empilhaOperacao(OP_DIFERENTE);;}
    break;

  case 101:
#line 1017 "compilador.y"
    {empilhaOperacao(MENOR_IGUAL);;}
    break;

  case 102:
#line 1018 "compilador.y"
    {empilhaOperacao(MAIOR_IGUAL);;}
    break;

  case 103:
#line 1019 "compilador.y"
    {empilhaOperacao(OP_MAIOR);;}
    break;

  case 104:
#line 1022 "compilador.y"
    {sinal = 0;;}
    break;

  case 105:
#line 1023 "compilador.y"
    {sinal = 1;;}
    break;

  case 106:
#line 1024 "compilador.y"
    {sinal = 0;;}
    break;

  case 107:
#line 1025 "compilador.y"
    {empilhaOperacao(OP_SOMA);;}
    break;

  case 108:
#line 1026 "compilador.y"
    {empilhaOperacao(OP_SUBTRACAO);;}
    break;

  case 109:
#line 1027 "compilador.y"
    {empilhaOperacao(OP_OR);;}
    break;

  case 110:
#line 1029 "compilador.y"
    {
						geraOperacao();
					;}
    break;

  case 111:
#line 1032 "compilador.y"
    {if (sinal) geraCodigo(NULL, "INVR \0");;}
    break;

  case 112:
#line 1036 "compilador.y"
    {empilhaOperacao(OP_MULTIPLICACAO);;}
    break;

  case 113:
#line 1037 "compilador.y"
    {empilhaOperacao(OP_DIVISAO_INTEIRA);;}
    break;

  case 114:
#line 1038 "compilador.y"
    {empilhaOperacao(OP_AND);;}
    break;

  case 115:
#line 1040 "compilador.y"
    {
			geraOperacao();
		;}
    break;

  case 119:
#line 1050 "compilador.y"
    {
			char buff[5 + 10];
			sprintf(buff, "CRCT 1");
			geraCodigo(NULL, buff);
		;}
    break;

  case 120:
#line 1056 "compilador.y"
    {
			char buff[5 + 10];
			sprintf(buff, "CRCT 0");
			geraCodigo(NULL, buff);
		;}
    break;

  case 122:
#line 1063 "compilador.y"
    {
			geraCodigo(NULL, "NEGA");
		;}
    break;

  case 123:
#line 1070 "compilador.y"
    {
					if(var == NULL)
					{
						//gera erro
	          			sprintf(buff,"Erro: variavel '%s' nao foi declarada!\n",token);
						yyerror(buff);
						exit(1);
					}
				;}
    break;

  case 124:
#line 1081 "compilador.y"
    {

			//TODO: verifica se erro semantico

			strcpy(tokenAtual,token);
			sprintf(buff,"CRCT %s",tokenAtual);
			geraCodigo (NULL, buff);
			;}
    break;

  case 125:
#line 1091 "compilador.y"
    { 
					var = busca(&ts,token);
				;}
    break;


/* Line 1267 of yacc.c.  */
#line 2791 "compilador.tab.c"
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


#line 1095 "compilador.y"


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
	pilhaContaParametros = initStack();

	pilhaVariaveisAtribuicao = initStack();

   yyin=fp;
   yyparse();

   return 0;
}

