run:
	bison --defines=syntax.tab.h --output=syntax.tab.c -v syntax.y
	flex lexical.l
	gcc syntax.tab.c lex.yy.c -Wall -o compiler