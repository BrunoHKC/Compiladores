
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

//incializa variaveis globais
int num_vars;
int nivel_lexico = 0;
int desloc = 0;

//Pilha de deslocamentos
Stack* pilhaDeslocamentos;

//Tabela de simbolos
TabelaSimbolos ts;


#define YYSTYPE char *

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token INTEGER BOOLEAN
%token T_BEGIN T_END VAR IDENT ATRIBUICAO
%token T_LABEL T_TYPE T_ARRAY T_OF
%token T_PROCEDURE T_FUNCTION
%token T_GOTO T_IF T_THEN T_ELSE
%token T_WHILE T_DO
%token T_OR T_DIV T_AND T_NOT

%%

programa    :{
         		geraCodigo (NULL, "INPP");
             }
             PROGRAM IDENT
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
             	geraCodigo (NULL, "PARA");
             }
;

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




parte_declara_vars: VAR declara_vars PONTO_E_VIRGULA
				  | parte_declara_vars declara_vars PONTO_E_VIRGULA
				  	
;



declara_vars : { 	/* zera contador */
					num_vars = 0; 
			   }
              lista_id_var DOIS_PONTOS tipo
;

tipo        : INTEGER { atualizaTipos(&ts, num_vars, TYPE_INT); }
			| BOOLEAN { atualizaTipos(&ts, num_vars, TYPE_BOOL); }
;

lista_id_var: lista_id_var VIRGULA IDENT
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

lista_idents: lista_idents VIRGULA IDENT
            | IDENT
;


comando_composto: T_BEGIN comandos T_END

comandos: 	comando
			| comandos comando
;

comando: 	atribuicao
//			| chamada_procedimento
//			| desvio
//			| comando_condicional
//			| comando_repetitivo
;

atribuicao: variavel ATRIBUICAO expressao PONTO_E_VIRGULA;

expressao: 	expressao_simples 
			| relacao expressao_simples;

variavel: IDENT{ 
					Item* var = busca(&ts,token);
					if(var == NULL)
					{
						//TODO: gera erro
						char buff[100];
	          			snprintf(buff,100,"Variavel %s nao foi declarada",token);
						fprintf(stderr,buff);
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


   yyin=fp;
   yyparse();

   return 0;
}
