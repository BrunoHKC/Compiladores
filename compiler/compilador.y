
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
	printf("Atualiando deslocamentos\n");
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
		printf("qtd %d, size %d\n",qtd,pilha->size);
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
					//Salva deslocamento anterior
					int* new_desloc = (int*)malloc(sizeof(int));
					*new_desloc = desloc;
					push(pilhaDeslocamentos,(void*)new_desloc);
				
					//Reseta deslocamento
					desloc = 0;
			  }
              parte_declara_vars
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
  			  }

			  parte_declara_subrotinas
			  {
					//Atualiza nivel lexico
          			nivel_lexico--;

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
          			sprintf(buff,"DMEM %d",desloc);
          			geraCodigo (NULL, buff);

					
          			//Recupera deslocamento anterior
          			desloc = *(int*)pop(pilhaDeslocamentos);
              }
              ;


//Regra 6: tipo
tipo        : INTEGER 
			{ 
				if(declarandoFuncao)
					proced->proc.tipo = TYPE_INT;
				else if(!declarandoParametros)
					atualizaTipos(&ts, num_vars, TYPE_INT); 
				else
					atualizaTiposParametros(pilhaParametros,num_param,TYPE_INT);
			}
			| BOOLEAN 
			{ 
				if(declarandoFuncao)
					proced->proc.tipo = TYPE_BOOL;
				else if(!declarandoParametros)
					atualizaTipos(&ts, num_vars, TYPE_BOOL);
				else
					atualizaTiposParametros(pilhaParametros,num_param,TYPE_BOOL);
			}
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
			            	| declara_funcao PONTO_E_VIRGULA parte_declara_subrotinas
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
                    proced = geraProcedimento(token, nivel_lexico);
                    
                    char* label = geraRotulo();
					strcpy(proced->proc.rotulo,label);

                    sprintf(buff, "ENPR %d", nivel_lexico);
                    geraCodigo(proced->proc.rotulo, buff);
                }
				else
				{
					sprintf(buff,"Erro: o procedimento '%s' ja foi declarado!\n",token);
					yyerror(buff);
					exit(1);
				}
            }
            parametros_formais PONTO_E_VIRGULA
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
            bloco_subrotina
;


//Regra 13: declara_procedimento
declara_funcao: 
            {
				printf("--Inicio declara funcao--\n");
			}
            T_FUNCTION IDENT
            {
                Item* procedimento = busca(&ts, token);

                if (!procedimento) {
                    proced = geraFuncao(token, nivel_lexico);
                    
                    char* label = geraRotulo();
					strcpy(proced->proc.rotulo,label);

                    sprintf(buff, "ENPR %d", nivel_lexico);
                    geraCodigo(proced->proc.rotulo, buff);
                }
				else
				{
					sprintf(buff,"Erro: o procedimento '%s' ja foi declarado!\n",token);
					yyerror(buff);
					exit(1);
				}
            }
            parametros_formais DOIS_PONTOS {declarandoFuncao = 1;}tipo{declarandoFuncao = 0;} PONTO_E_VIRGULA
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
            bloco_subrotina
;

bloco_subrotina: 
            {
				printf("---Empilha Procedimento %s nl %d n %d\n",proced->identificador,proced->nivel, proced->proc.n);
				push(pilhaSubRotinas,proced);
            } 
            bloco
			{
				//gera codigo retorna procedmento
				proced = pop(pilhaSubRotinas);
				proced = busca(&ts,proced->identificador);
				sprintf(buff, "RTPR %d, %d", proced->nivel, proced->proc.n);	
				geraCodigo(NULL, buff);

				//retira parametros da tabela de simbolos
				elimina(&ts,proced->proc.n);

				proced = NULL;
			}
;


lista_parametros: 	| expressao { *contaParametro = *contaParametro + 1;}
					| lista_parametros VIRGULA expressao { *contaParametro = *contaParametro + 1;} ;

chamada_procedimento:
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

            }
            ABRE_PARENTESES lista_parametros FECHA_PARENTESES
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
            }
            |
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
            }
;

chamada_funcao:
				{
				printf("--Chamada funcao com parametros--\n");
                if (!var) {
                    yyerror("Erro: funcao nao declarada.");
                    exit(1);
                }

				printf("categoria do token %s eh %d\n",var->identificador,var->categoria);
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
            }
            ABRE_PARENTESES lista_parametros FECHA_PARENTESES
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
            }
			;

//Regra 14: parametros formais
parametros_formais:
            | 
			{ 
				printf("Inicio parametrosformais\n");
				declarandoParametros = 1; } ABRE_PARENTESES { emptyStack(pilhaParametros); }
			secao_parametros_formais parametros_formais_aux FECHA_PARENTESES
			{
				//corrige deslocamentos
				atualizaDeslocamentoParametros(pilhaParametros);
				declarandoParametros = 0;
				printf("fim parametros formais %d \n",declarandoParametros);
			}
;

parametros_formais_aux:
            | PONTO_E_VIRGULA secao_parametros_formais parametros_formais_aux
;

//Regra 15: secao_parametros_formais
lista_parametros_valor: lista_parametros_valor VIRGULA IDENT
						{
							num_param++;
							Item* parametroValor = criaParametro(token,nivel_lexico,PARAMETRO);
							push(pilhaParametros,parametroValor);
						}
						| IDENT
						{
							num_param++;
							Item* parametroValor = criaParametro(token,nivel_lexico,PARAMETRO);
							push(pilhaParametros,parametroValor);
						};

lista_parametros_referencia:
						lista_parametros_referencia VIRGULA IDENT
						{
							num_param++;
							Item* parametroReferencia = criaParametro(token,nivel_lexico,REFERENCIA);
							push(pilhaParametros,parametroReferencia);
						}
						| IDENT
						{
							num_param++;
							Item* parametroReferencia = criaParametro(token,nivel_lexico,REFERENCIA);
							push(pilhaParametros,parametroReferencia);
						}
						;

secao_parametros_formais: 
			{
				num_param = 0;
				printf("Parametros formais valor\n");
			}
			lista_parametros_valor DOIS_PONTOS tipo 
            | VAR 
			{
				num_param = 0;
				printf("Parametros formais referencia\n");
			}
			lista_parametros_referencia DOIS_PONTOS tipo
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
;

atribuicao_ou_chama_procedimento:
	identificador atribuicao_ou_chama_procedimento_aux;

atribuicao_ou_chama_procedimento_aux:
	atribuicao
	| chamada_procedimento;


variavel_ou_chamada_funcao:
	IDENT
	{
		var = busca(&ts,token);
	}
	variavel_ou_chamada_funcao_aux;

variavel_ou_chamada_funcao_aux:
	chamada_funcao
	| 
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
	}
	;


//Regra 19:
atribuicao	: 
			{
				printf("--Inicia atribuicao--\n");
				varAtribuida = var;
			}
			ATRIBUICAO expressao
			{
				//TODO: Verifica se o tipo da expressao eh o mesmo da variavel
				geraArmazenaValor(varAtribuida);
				printf("--Fim atribuicao--\n");
			}
			;


leitura:
            READ ABRE_PARENTESES 
			{geraCodigo(NULL, "LEIT");} variavel { geraArmazenaValor(var);}
			parametros_letura FECHA_PARENTESES
;


parametros_letura:
					VIRGULA 
					{geraCodigo(NULL, "LEIT");} variavel {geraArmazenaValor(var);}
					|
;


escrita:
            WRITE ABRE_PARENTESES parametros_write FECHA_PARENTESES
;

parametros_write:
					parametros_write VIRGULA expressao
					{
						geraCodigo(NULL, "IMPR");
					}
					| expressao
					{
						geraCodigo(NULL, "IMPR");
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
						sprintf(buff,"DSVF %s",rotulo_entrada_else);
						geraCodigo (NULL, buff);

						//empilha rotulo entrada do else
						push(pilhaRotulo,rotulo_entrada_else);

					}
					comando_composto
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
						sprintf(buff,"DSVF %s",rotulo_saida);
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
						sprintf(buff,"DSVS %s",rotulo_entrada);
						geraCodigo (NULL, buff);

						//Insere rotulo saida no codgo MEPA
						geraCodigo (rotulo_saida, "NADA");
						printf("--Fim while--\n");

					};


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
fator: 	variavel_ou_chamada_funcao
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
	          			sprintf(buff,"Erro: variavel '%s' nao foi declarada!\n",token);
						yyerror(buff);
						exit(1);
					}
				};

//Regra 32: Numero
numero: NUMERO {

			//TODO: verifica se erro semantico

			strcpy(tokenAtual,token);
			sprintf(buff,"CRCT %s",tokenAtual);
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
	pilhaContaParametros = initStack();

   yyin=fp;
   yyparse();

   return 0;
}
