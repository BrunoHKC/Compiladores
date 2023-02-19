
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
char tokenAtual[100];
int contador_rotulo = 0;
int write = 0;


//Pilha de deslocamentos
Stack* pilhaDeslocamentos;

//Pilha de operacoes
Stack* pilhaOperacoes;

//Pilha de rotulos
Stack* pilhaRotulo;

//Tabela de simbolos
TabelaSimbolos ts;

//Itens
Item* var = NULL;
Item* varAtribuida = NULL;


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
%token READ WRITE TRUE FALSE
%token T_LABEL T_TYPE T_ARRAY T_OF
%token T_PROCEDURE T_FUNCTION
%token T_GOTO T_IF T_THEN T_ELSE
%token T_WHILE T_DO
%token T_OR T_DIV T_AND T_NOT

%nonassoc T_ELSE
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

			  parte_declara_subrotinas

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
parte_declara_vars		: //epsilon 
						| parte_declara_vars_aux PONTO_E_VIRGULA;


//Regra 9: declaracao de variaveis
declara_vars 	:
				{ 	/* zera contador */
					num_vars = 0; 
			   	}
              	lista_idents DOIS_PONTOS tipo
;


//Regra 10: lista de identificadores
lista_idents: lista_idents VIRGULA IDENT
              { /* insere ultima vars na tabela de simbolos */
			  	strcpy(tokenAtual,token);
              	printf("[ASynt]\tINSERE VAR SIMPLES  %s\n",tokenAtual);
              	Item* novo_item = ItemVarSimples(tokenAtual,nivel_lexico,desloc);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
               }
            | IDENT { /* insere vars na tabela de simbolos */
				strcpy(tokenAtual,token);
            	Item* novo_item = ItemVarSimples(tokenAtual,nivel_lexico,desloc);
            	printf("[ASynt]\tINSERE VAR SIMPLES  %s\n",tokenAtual);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
            }
;

//Regra 11: parte declaracoes de sub-rotinas
parte_declara_subrotinas: 	//epsilon
							| parte_declara_subrotinas daclara_procedimento
//							| parte_declara_subrotinas declara_funcao
							;

//Regra 12: declaracao de procedimento
daclara_procedimento: T_PROCEDURE 

//Regra 16: comando composto
comando_composto_aux: comando_composto_aux comando PONTO_E_VIRGULA | ;
comando_composto: T_BEGIN comando PONTO_E_VIRGULA comando_composto_aux T_END;

//Regra 17 e 18: comando (omitido comando sem rotulo)
comando: 	atribuicao
			| leitura
			| escrita
			| comando_repetitivo
			| comando_condicional
//			| chamada_procedimento
//			| chamada_funcao
;

//Regra 19:
atribuicao	: 
			{
				printf("--Inicia atribuicao--\n");
			}
			variavel
			{
				varAtribuida = var;
			}
			ATRIBUICAO expressao
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
			}
			;


leitura:
            READ
            ABRE_PARENTESES read_section FECHA_PARENTESES
;

read_section:
            {
                geraCodigo(NULL, "LEIT");
            }
            variavel
            {
				if(var->categoria == CAT_PARAM_FORMAL_SIMPLES)
				{
					if(var->param.passagem == REFERENCIA)
					{
						//Se eh um parametro por referencia
						char buff[5 + 10];
						sprintf(buff, "ARMI %d, %d", var->nivel, var->param.deslocamento);
                    	geraCodigo(NULL, buff);
					}
					else
					{
						//Se eh um parametro por valor
						char buff[5 + 10];
						sprintf(buff, "ARMZ %d, %d", var->nivel, var->param.deslocamento);
                    	geraCodigo(NULL, buff);
					}	
				}
				else
				{
					char buff[5 + 10];
					sprintf(buff, "ARMZ %d, %d", var->nivel, var->var.deslocamento);
					geraCodigo(NULL, buff);
				}
            }
            read_section_lp
;

read_section_lp:
            | VIRGULA read_section
;

escrita:
            WRITE
            {
                write = 1;
            }
            ABRE_PARENTESES expressao FECHA_PARENTESES
            {
                write = 0;
            }
;

//Regra 22: comando condcional
comando_condicional_else : | T_ELSE comando_composto;
comando_condicional	: 
					{
						printf("--Inicio If--\n");
					}
					T_IF expressao T_THEN
					{
						//Cria rotulo saida e empilha
						char* rotulo_entrada_else = geraRotulo();
						
						//desvia se falso
						char buff[5 + 10];
						snprintf(buff,15,"DSVF %s",rotulo_entrada_else);
						geraCodigo (NULL, buff);

						//empilha rotulo entrada do else
						push(pilhaRotulo,rotulo_entrada_else);

					}
					comando_composto
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

					} comando_condicional_else
					{
						//recupera rotulo saida do else
						char* rotulo_saida_else = pop(pilhaRotulo);

						//Insere rotulo saida else
						geraCodigo (rotulo_saida_else, "NADA");
					}
					;


//Regra 23: comando repetitivo
comando_repetitivo	: T_WHILE
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
					}
					expressao 
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

					}
					T_DO comando_composto
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

					};

//Regra 24: lista expressoes
/*
lista_expressoes_aux: 
					| VIRGULA expressao lista_expressoes_aux;
lista_expressoes	: expressao lista_expressoes_aux;
*/

//Regra 25: expressao
expressao: 	

			expressao_simples 
			{
                if (write) {
                    geraCodigo(NULL, "IMPR");
                }
            }
			| expressao_simples relacao expressao_simples 
			{
				geraOperacao();

			    if (write) {
                    geraCodigo(NULL, "IMPR");
                }
            
			};

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
					| {sinal = 0;};
mais_menos_or	: MAIS {empilhaOperacao(OP_SOMA);}
				| MENOS {empilhaOperacao(OP_SUBTRACAO);}
				| T_OR {empilhaOperacao(OP_OR);};
expressao_simples	: expressao_simples mais_menos_or termo 
					{
						geraOperacao();
					}
					| mais_menos_epsilon termo {if (sinal) geraCodigo(NULL, "INVR \0");};
					

//Regra 28: termo
mult_div_and	: MULTIPLICACAO {empilhaOperacao(OP_MULTIPLICACAO);} 
				| T_DIV {empilhaOperacao(OP_DIVISAO_INTEIRA);}
				| T_AND {empilhaOperacao(OP_AND);};
termo	: termo mult_div_and fator 
		{
			geraOperacao();
		}
		| fator;


//Regra 29: fator
fator: 	variavel 
		{ 
			if(var->categoria == CAT_PARAM_FORMAL_SIMPLES)
			{
				if(var->param.passagem == REFERENCIA)
				{
					//Se eh um parametro por referencia
					char buff[5 + 10];
					sprintf(buff, "CRVI %d, %d", var->nivel, var->param.deslocamento);
					geraCodigo(NULL, buff);
				}
				else
				{
					//Se eh um parametro por valor ou variavel simples
					char buff[5 + 10];
					sprintf(buff, "CRVL %d, %d", var->nivel, var->param.deslocamento);
					geraCodigo(NULL, buff);
				}
			}
			else
			{
				//Se eh um parametro por valor ou variavel simples
				char buff[5 + 10];
				sprintf(buff, "CRVL %d, %d", var->nivel, var->param.deslocamento);
				geraCodigo(NULL, buff);
			}
		}
		| numero
		| TRUE 
		{
			char buff[5 + 10];
			sprintf(buff, "CRCT 1");
			geraCodigo(NULL, buff);
		}
		| FALSE
		{
			char buff[5 + 10];
			sprintf(buff, "CRCT 0");
			geraCodigo(NULL, buff);
		}
//		| chamada_funcao
		| ABRE_PARENTESES expressao FECHA_PARENTESES
		| T_NOT fator
		{
			geraCodigo(NULL, "NEGA");
		};


//Regra 30: variavel
variavel	: 
				identificador
//				| identificador lista_expressoes
			;

//Regra 32: Numero
numero: NUMERO {

			//TODO: verifica se erro semantico

			char buff[5 + 10];
			strcpy(tokenAtual,token);
			snprintf(buff,15,"CRCT %s",tokenAtual);
			geraCodigo (NULL, buff);
			};

identificador: IDENT
				{ 
					strcpy(tokenAtual,token);
					//Salva token atual
					var = busca(&ts,tokenAtual);
					if(var == NULL)
					{
						//gera erro
						char buff[100];
	          			snprintf(buff,100,"Erro: identificador '%s' nao existe!\n",tokenAtual);
						yyerror(buff);
						exit(1);
					}

				}

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

	pilhaRotulo = initStack();

   yyin=fp;
   yyparse();

   return 0;
}
