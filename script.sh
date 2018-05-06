rm Parser.tab.h
rm Parser.tab.c
rm lex.yy.c
rm lex.yy.h
rm analizador

bison -d Parser.y
flex --header-file=lex.yy.h lexer.l

gcc lex.yy.c Parser.tab.c symbolTable.c syntaxTree.c -o analizador -ll