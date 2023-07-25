run:
	bison --defines=parser.tab.hpp --output=parser.tab.cpp -Wcounterexamples -v parser.y
	flex -o lex.yy.cpp tokens.l
	g++ -std=c++11 parser.tab.cpp lex.yy.cpp src/list_tree.cpp src/symbol_table.cpp src/semantic.cpp -Wall -o compiler