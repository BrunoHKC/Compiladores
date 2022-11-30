 # -------------------------------------------------------------------
 #            Arquivo: Makefile
 # -------------------------------------------------------------------
 #              Autor: Bruno Müller Junior
 #               Data: 08/2007
 #      Atualizado em: [09/08/2020, 19h:01m]
 #
 # -------------------------------------------------------------------

$DEPURA=1

compilador: lex.yy.c compilador.tab.c compilador.o compilador.h tabela_simbolos/tabela_simbolos.c tabela_simbolos/tabela_simbolos.h utils/utils.h utils/utils.c utils/stack.c utils/stack.h
	gcc lex.yy.c compilador.tab.c tabela_simbolos/tabela_simbolos.c utils/utils.c utils/stack.c compilador.o -o compilador -ll -ly -lc

lex.yy.c: compilador.l compilador.h
	flex compilador.l

compilador.tab.c: compilador.y compilador.h
	bison compilador.y -d -v

compilador.o : compilador.h compiladorF.c
	gcc -c compiladorF.c -o compilador.o
	

clean :
	rm -f compilador.tab.* lex.yy.c compilador.o compilador
	
test:
	python testes/testAll.py
