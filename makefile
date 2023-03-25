run:
	bison --defines=syntax.tab.h --output=syntax.tab.c -v syntax.y
	flex lexical.l
	g++ -std=c++11 syntax.tab.c lex.yy.c list_tree.c list_tree.cpp -Wall -o compiler