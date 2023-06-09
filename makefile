run:
	bison --defines=syntax.tab.hpp --output=syntax.tab.cpp -Wcounterexamples -v syntax.y
	flex -o lex.yy.cpp lexical.l
	g++ -std=c++11 syntax.tab.cpp lex.yy.cpp list_tree.cpp symbol_table.cpp -Wall -o compiler