
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
int nivel_lexico = -1;
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
          			snprintf(buff,15,"AMEM %d",desloc);
          			geraCodigo (NULL, buff);

					if(nivel_lexico == 0)
					{					
						char* rotulo_pula_subrotinas = geraRotulo();
						snprintf(buff,15,"DSVS %s",rotulo_pula_subrotinas);
						geraCodigo (NULL, buff);

						push(pilhaRotulo,rotulo_pula_subrotinas);
					}
  			  }

			  parte_declara_subrotinas
			  {
					if(nivel_lexico == 0)
					{
						char* rotulo_pula_subrotinas = pop(pilhaRotulo);
						geraCodigo (rotulo_pula_subrotinas, "NADA");
					}
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
              	printf("[ASynt]\tINSERE VAR SIMPLES %s nl= %d, desloc = %d\n",token,nivel_lexico,desloc);
              	Item* novo_item = ItemVarSimples(token,nivel_lexico,desloc);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
               }
            | IDENT { /* insere vars na tabela de simbolos */
            	Item* novo_item = ItemVarSimples(token,nivel_lexico,desloc);
            	printf("[ASynt]\tINSERE VAR SIMPLES %s nl= %d, desloc = %d\n",token,nivel_lexico,desloc);
              	insere(&ts,novo_item);
              	desloc++;
              	num_vars++;
            }
;


//Regra 11: parte declaracoes de sub-rotinas 	
parte_declara_subrotinas:
				            |declara_procedimento PONTO_E_VIRGULA parte_declara_subrotinas
//			            	| declara_funcao PONTO_E_VIRGULA parte_declara_subrotinas
;

//Regra 12: declaracao de procedimento
declara_procedimento:
			{
				printf("--Inicio declara procedimento--\n");
			}
            T_PROCEDURE IDENT
            {
                Item* procedimento = busca(&ts, token);

                if (!procedimento) {
                    proced = geraProcedimento(token, nivel_lexico+1);
                    
                    char* label = geraRotulo();
					strcpy(proced->proc.rotulo,label);

                    sprintf(buff, "ENPR %d", nivel_lexico+1);
                    geraCodigo(proced->proc.rotulo, buff);
                }
				else
				{
					snprintf(buff,100,"Erro: o procedimento '%s' ja foi declarado!\n",token);
					yyerror(buff);
					exit(1);
				}
            }
            parametros_formais PONTO_E_VIRGULA
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


            }
            bloco_subrotina
;

bloco_subrotina: 
            {
				push(pilhaSubRotinas,proced);
            } 
            bloco
			{
				proced = pop(pilhaSubRotinas);
				sprintf(buff, "RTPR %d, %d", proced->nivel, proced->proc.n);	
				geraCodigo(NULL, buff);
				proced = NULL;
			}
;

chamada_procedimento:
            {
				printf("--Chamada procedimento com parametros--\n");
                if (!var) {
                    yyerror("Procedimento nao declarado.");
                    exit(1);
                }
                proced = var;
				proced->proc.n = 0;
                count_param = 0;
            }
            ABRE_PARENTESES lista_expressoes
            {
                sprintf(buff, "CHPR %s, %d", proced->proc.rotulo, nivel_lexico);
                geraCodigo(NULL, buff);
                proced = NULL;
            }
            FECHA_PARENTESES
			| ABRE_PARENTESES FECHA_PARENTESES
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
            }
            |
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
            }
;

/*
declara_funcao: 
            T_FUNCTION identificador
            {
                temporary = find(symbols_table, yytext);

                if (!temporary) {
                    funct = newFunction(0, yytext, nvl_lex);
                    geraRotulo(str_tmp);
                    strcpy(funct->item.func.label, str_tmp);

                    geraRotulo(str_tmp);
                    strcpy(funct->item.func.label_f, str_tmp);

                    sprintf(str_tmp,"ENPR %d", nvl_lex);
                    geraCodigo(funct->item.func.label, str_tmp);
                } else {
                    funct = temporary;
                    geraCodigo(funct->item.func.label_f, "NADA");
                }
            }
            parametros_formais 
            {
                funct->item.func.num_param = parameters->size;
                offset = - 4;
                i_index = parameters->size - 1;
                funct->item.func.parameters = (variable*)malloc(sizeof(variable)*parameters->size);
                push(symbols_table, funct);
                
                while (parameters->size) {
                    temporary = pop(parameters);
                    temporary->item.simple.offset = offset;
                    push(symbols_table, newVariable(0, temporary->name, nvl_lex, offset, temporary->item.simple.parameter));
                    offset--;
                    funct->item.func.parameters[i_index] = temporary->item.simple;
                    i_index--;
                }
                parameters->size = 0;
                offset = 0;
            }
            DOIS_PONTOS tipo
            {
                int j;
                if (!strcmp(yytext, "boolean")) {
                    for (j = symbols_table->size - 1; j >= 0; j--) {
                        if (symbols_table->head[j].category == FUNCTION_TP) {
                            symbols_table->head[j].item.func.offset = - 4 - symbols_table->head[j].item.func.num_param;
                            symbols_table->head[j].item.func.type = 8;
                            break;
                        }
                    }
                } else {
                    for (j = symbols_table->size - 1; j >= 0; j--) {
                        if (symbols_table->head[j].category == FUNCTION_TP) {
                            symbols_table->head[j].item.func.offset = - 4 - symbols_table->head[j].item.func.num_param;
                            symbols_table->head[j].item.func.type = 7;
                            break;
                        }
                    }
                }
            } PONTO_E_VIRGULA 
            bloco
;


chamada_funcao:
            identificador
            {
                call_flag = 1;
                if (!temporary) {
                    yyerror("funcao nao declarada.");
                    exit(1);
                }
                geraCodigo(NULL, "AMEM 1");
                funct = temporary;
                parameters->size = 0;
                count_param = 0;
            }
            ABRE_PARENTESES lista_expressoes
            { 	
                sprintf(str_tmp, "CHPR %s, %d", funct->item.func.label, nvl_lex);
                geraCodigo(NULL, str_tmp);
                funct = NULL;
                call_flag = 0;
            }
            FECHA_PARENTESES
;
*/

//Regra 14: parametros formais
parametros_formais:
            | ABRE_PARENTESES secao_parametros_formais parametros_formais_aux FECHA_PARENTESES
;

parametros_formais_aux:
            | PONTO_E_VIRGULA secao_parametros_formais parametros_formais_aux
;

//Regra 15: secao_parametros_formais
secao_parametros_formais: 
            lista_idents
            {
				/*
                for (i_index = 0; i_index < aux->size; i_index++) {
                    temporary = &(aux->head[i_index]);
                    temporary->item.simple.parameter = VALUE_TP;
                    push(parameters, temporary);
                }
                aux->size = 0;
				*/
            }
            DOIS_PONTOS tipo
            | VAR lista_idents
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
            }
            DOIS_PONTOS tipo
;




//Regra 16: comando composto
comando_composto_aux: comando_composto_aux comando PONTO_E_VIRGULA | ;
comando_composto: T_BEGIN comando PONTO_E_VIRGULA comando_composto_aux T_END;

//Regra 17 e 18: comando (omitido comando sem rotulo)
comando: 	atribuicao_ou_chama_procedimento
			| leitura
			| escrita
			| comando_repetitivo
			| comando_condicional
//			| chamada_funcao
;

atribuicao_ou_chama_procedimento:
	identificador atribuicao_ou_chama_procedimento_aux;

atribuicao_ou_chama_procedimento_aux:
	atribuicao
	| chamada_procedimento;

//Regra 19:
atribuicao	: 
			{
				printf("--Inicia atribuicao--\n");
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
lista_expressoes	:
					lista_expressoes VIRGULA expressao
					{
						if (write) {
							geraCodigo(NULL, "IMPR");
						}
					}
					| expressao
					{
						if (write) {
							geraCodigo(NULL, "IMPR");
						}
					}
					;

//Regra 25: expressao
expressao: 	
			expressao_simples 
			| expressao_simples relacao expressao_simples 
			{
				geraOperacao();            
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
variavel	: 	identificador
				{
					if(var == NULL)
					{
						//gera erro
	          			snprintf(buff,100,"Erro: variavel '%s' nao foi declarada!\n",token);
						yyerror(buff);
						exit(1);
					}
				};

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
					var = busca(&ts,token);
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

	pilhaSubRotinas = initStack();
	pilhaParametros = initStack();

   yyin=fp;
   yyparse();

   return 0;
}
