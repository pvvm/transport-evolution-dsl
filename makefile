run:
	bison --defines=syntax.tab.hpp --output=syntax.tab.cpp -v syntax.y
	flex -o lex.yy.cpp lexical.l
	g++ -std=c++11 syntax.tab.cpp lex.yy.cpp list_tree.cpp -Wall -o compiler