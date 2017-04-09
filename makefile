IDIR=include
CC=g++ -std=c++11
C=gcc -std=c99
CFLAGS=-g

ODIR=obj
SRCDIR=src

clt:	$(SRCDIR)/tools/clt.c $(ODIR)/c-cc-interface.o $(ODIR)/backend.o $(SRCDIR)/sql-compiler/grammar.y $(SRCDIR)/sql-compiler/lexer.l
	bison -o $(SRCDIR)/sql-compiler/gen/grammar.tab.c -d $(SRCDIR)/sql-compiler/grammar.y
	mv $(SRCDIR)/sql-compiler/gen/grammar.tab.h $(IDIR)/sql-compiler/gen/grammar.tab.h
	flex $(SRCDIR)/sql-compiler/lexer.l
	mv lex.yy.c $(SRCDIR)/sql-compiler/gen/lexer.yy.c
	$(C) $(CFLAGS) -o clt $(SRCDIR)/tools/clt.c $(ODIR)/backend.o $(ODIR)/c-cc-interface.o $(SRCDIR)/sql-compiler/gen/grammar.tab.c $(SRCDIR)/sql-compiler/gen/lexer.yy.c -lfl -lstdc++ -lboost_system -lboost_filesystem

$(ODIR)/c-cc-interface.o:	$(SRCDIR)/sql-compiler/c-cc-interface.cc $(IDIR)/sql-compiler/c-cc-interface.h
	$(CC) $(CFLAGS) -o $(ODIR)/c-cc-interface.o -c $(SRCDIR)/sql-compiler/c-cc-interface.cc

$(ODIR)/backend.o: $(SRCDIR)/backend/backend.cc $(IDIR)/backend/backend.h
	$(CC) $(CFLAGS) -o $(ODIR)/backend.o -c $(SRCDIR)/backend/backend.cc

clean:
	rm -f $(ODIR)/*.o
	rm clt
	rm $(SRCDIR)/sql-compiler/gen/*.*
	rm $(IDIR)/sql-compiler/gen/*.*