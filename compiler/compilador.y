
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
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

//Pilha de deslocamentos
Stack* pilhaDeslocamentos;

//Pilha de operacoes
Stack* pilhaOperacoes;

//Pilha nivel destino e deslocamento
Stack* pilhaVarNivelDestino;
Stack* pilhaVarDeslocamentos;

//Tabela de simbolos
TabelaSimbolos ts;

//Itens
Item* var = NULL;


#define YYSTYPE char *


void geraCRVL() {
	char buff[5 + 10];
	snprintf(buff,15,"CRVL %d, %d",var->nivel, var->var.deslocamento);
    geraCodigo(NULL, buff);
}

void empilhaOperacao(int operacao)
{
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


%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token INTEGER BOOLEAN
%token T_BEGIN T_END VAR IDENT NUMERO
%token ATRIBUICAO
%token IGUAL DIFERENTE MAIOR MENOR MAIOR_IGUAL MENOR_IGUAL
%token MAIS MENOS MULTIPLICACAO DIVISAO
%token T_LABEL T_TYPE T_ARRAY T_OF
%token T_PROCEDURE T_FUNCTION
%token T_GOTO T_IF T_THEN T_ELSE
%token T_WHILE T_DO
%token T_OR T_DIV T_AND T_NOT

%%


//Regra 1: programa
programa    :{
         		geraCodigo (NULL, "INPP");
             }
             PROGRAM IDENT
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
             	geraCodigo (NULL, "PARA");
             }
;


//Regra 2: bloco
bloco       : { 
					nivel_lexico++;

					//Salva deslocamento anterior
					int* new_desloc = (int*)malloc(sizeof(int));
					*new_desloc = desloc;
					push(pilhaDeslocamentos,(void*)new_desloc);
				
					//Reseta deslocamento
					desloc = 0;
			  }
              parte_declara_vars
              { 	/* AMEM */ 
      				char buff[5 + 10];
          			snprintf(buff,15,"AMEM %d",desloc);
          			geraCodigo (NULL, buff);
  			  }

              comando_composto
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
              }
              ;


//Regra 6: tipo
tipo        : INTEGER { atualizaTipos(&ts, num_vars, TYPE_INT); }
			| BOOLEAN { atualizaTipos(&ts, num_vars, TYPE_BOOL); }
;


//Regra 8: parte de declaracoes de variaveis
parte_declara_vars_aux	: parte_declara_vars_aux PONTO_E_VIRGULA declara_vars
						| VAR declara_vars;
parte_declara_vars		: parte_declara_vars_aux PONTO_E_VIRGULA;


//Regra 9: declaracao de variaveis
declara_vars : { 	/* zera contador */
					num_vars = 0; 
			   }
              lista_idents DOIS_PONTOS tipo
;


//Regra 10: lista de identificadores
lista_idents: lista_idents VIRGULA IDENT
              { /* insere ultima vars na tabela de simbolos */
              	printf("[ASynt]\tINSERE VAR SIMPLES  %s\n",token);
              	Item* novo_item = ItemVarSimples(token,nivel_lexico,desloc);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
               }
            | IDENT { /* insere vars na tabela de simbolos */
            	Item* novo_item = ItemVarSimples(token,nivel_lexico,desloc);
            	printf("[ASynt]\tINSERE VAR SIMPLES  %s\n",token);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
            }
;

//Regra 16: comando composto
comando_composto_aux: comando_composto_aux comando PONTO_E_VIRGULA | ;
comando_composto: T_BEGIN comando  PONTO_E_VIRGULA comando_composto_aux T_END;

//Regra 17 e 18: comando (omitido comando sem rotulo)
comando: 	atribuicao
//			| chamada_procedimento
//			| desvio
//			| comando_condicional
//			| comando_repetitivo
;

//Regra 19:
atribuicao	: variavel
			{
				empilhaVarNivelDestino(var->nivel);
				empilhaVarDeslocamento(var->var.deslocamento);
			}
			ATRIBUICAO expressao
			{
				int nivel_destino = *(int*)pop(pilhaVarNivelDestino);
				int deslocamento = *(int*)pop(pilhaVarDeslocamentos);
				char buff[5 + 10];
				snprintf(buff,15,"ARMZ %d, %d",nivel_destino,deslocamento);
				geraCodigo (NULL, buff);
			};

//Regra 25: lista de expressoes
lista_expressoes: lista_expressoes VIRGULA expressao| expressao;

//Regra 25: expressao
expressao: 	expressao_simples 
			| expressao_simples relacao expressao_simples {geraOperacao();};

//Regra 26: relacao
relacao: 	IGUAL {empilhaOperacao(OP_IGUAL);}
			| DIFERENTE {empilhaOperacao(OP_DIFERENTE);}
			| MENOR {empilhaOperacao(OP_DIFERENTE);}
			| MENOR_IGUAL {empilhaOperacao(MENOR_IGUAL);}
			| MAIOR_IGUAL {empilhaOperacao(MAIOR_IGUAL);}
			| MAIOR {empilhaOperacao(OP_MAIOR);};

//Regra 27: expressao simples
mais_menos_epsilon	: MAIS {sinal = 0;}
					| MENOS {sinal = 1;}
					| ;
mais_menos_or	: MAIS {empilhaOperacao(OP_SOMA);}
				| MENOS {empilhaOperacao(OP_SUBTRACAO);}
				| T_OR {empilhaOperacao(OP_OR);};
expressao_simples	: expressao_simples mais_menos_or termo {geraOperacao();}
					| mais_menos_epsilon termo {if (sinal) geraCodigo(NULL, "INVR \0");};
					

//Regra 28: termo
mult_div_and	: MULTIPLICACAO {empilhaOperacao(OP_MULTIPLICACAO);} 
				| T_DIV {empilhaOperacao(OP_DIVISAO_INTEIRA);}
				| T_AND {empilhaOperacao(OP_AND);};
termo	: termo mult_div_and fator {geraOperacao();}
		| fator;


//Regra 29: fator
fator: 	variavel 
		{ 
			geraCRVL();
			geraOperacao(); 
		}
		| numero
//		| chamada_funcao
		| ABRE_PARENTESES expressao FECHA_PARENTESES
		| T_NOT {empilhaOperacao(OP_NOT);} fator;


//Regra 30: variavel
variavel	: IDENT
				{ 
					var = busca(&ts,token);
					if(var == NULL)
					{
						//gera erro
						char buff[100];
	          			snprintf(buff,100,"Variavel %s nao foi declarada",token);
						fprintf(stderr,"%s",buff);
						exit(1);
					}

				}
			| IDENT 
				{ 
					var = busca(&ts,token);
					if(var == NULL)
					{
						//gera erro
						char buff[100];
	          			snprintf(buff,100,"Variavel %s nao foi declarada",token);
						fprintf(stderr,"%s",buff);
						exit(1);
					}

				} 
			lista_expressoes;

//Regra 32: Numero
numero: NUMERO {
			char buff[5 + 10];
			snprintf(buff,15,"CRCT %s",token);
			geraCodigo (NULL, buff);
			};

%%

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

   yyin=fp;
   yyparse();

   return 0;
}
