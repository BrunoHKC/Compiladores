#include "utils.h"


Item* ItemVarSimples(char* identificador,int nivel,int deslocamento)
{
	//Cria item
	Item* new_item = (Item*)malloc(sizeof(Item));
	
	//Preenche campos
	new_item->identificador = identificador;
	new_item->categoria = CAT_VARIAVEL;
	new_item->nivel = nivel;
	new_item->var.deslocamento = deslocamento;
	
	return new_item;
}
