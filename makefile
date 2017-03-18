IDIR=include
CC=g++ -std=c++11
CFLAGS=-g

ODIR=obj
SRCDIR=src

clt:	$(SRCDIR)/tools/clt.cc $(ODIR)/backend.o $(ODIR)/parser.o
	$(CC) $(CFLAGS) -o clt $(SRCDIR)/tools/clt.cc $(ODIR)/backend.o $(ODIR)/parser.o

$(ODIR)/parser.o: $(SRCDIR)/sql-compiler/parser.cc $(IDIR)/sql-compiler/parser.h
	$(CC) $(CFLAGS) -o $(ODIR)/parser.o -c $(SRCDIR)/sql-compiler/parser.cc

$(ODIR)/backend.o: $(SRCDIR)/backend/backend.cc $(IDIR)/backend/backend.h
	$(CC) $(CFLAGS) -o $(ODIR)/backend.o -c $(SRCDIR)/backend/backend.cc

clean:
	rm -f $(ODIR)/*.o
	rm clt