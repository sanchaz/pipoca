ID=pipoca
EXT=.pip
VER=1a

.SUFFIXES: $(EXT) .asm
LOADLIBS=-L$(LIB) -lcomp # -lfl
CC=gcc
CFLAGS=-g -DYYDEBUG -I$(LIB)
#CFLAGS=-O2 -I$(LIB)
LEX=flex
LFLAGS=-l
YACC=byacc
YFLAGS=-dv
NASM=nasm -felf

BID=$(ID)-$(VER)
LIB=./lib/
BIN=$(ID)
RUN=runtime/lib$(ID).a

all: $(BIN) $(RUN)

%:%.asm
	$(NASM) $*.asm
	$(LD) $*.o -Lruntime -l$(ID) -o $@

$(EXT).asm:
	$(ID) $<

BASE= y.tab.o lex.yy.o
$(ID): $(BASE) code.o lib/libcomp.a
	$(LINK.c) -o $@ $^ $(LOADLIBS)

full: all trans gram interp java c++
java:
	cd java; $(MAKE) $(MFLAGS)
c++:
	cd c++; $(MAKE) $(MFLAGS)
trans: $(BASE) trans.o lib/libcomp.a
	$(LINK.c) -o $@ $^ $(LOADLIBS)

gram: lex.yy.o gram.o lib/libcomp.a
	$(LINK.c) -o $@ $^ $(LOADLIBS)

interp: $(BASE) interp.o lib/libcomp.a
	$(LINK.c) -o $@ $^ $(LOADLIBS)

lib/libcomp.a: lib/node.o lib/tabid.o lib/main.o
	ar crs	$@ $?

$(RUN): runtime/lib.o runtime/linux.o runtime/sys.o
	ar crs	$@ $?

runtime/%.o:runtime/%.asm
	$(NASM) $<

ver.c: Makefile
	echo "char *version = \"" $(VER) "\";" > $@

lex.yy.c: $(ID).l y.tab.c
	$(LEX) $(LFLAGS) $<

y.tab.c: $(ID).y
	$(YACC) $(YFLAGS) $<

examples: $(ID) $(RUN)
	cp $< $@
	cd $@;for i in *$(EXT);do $(MAKE) $(MFLAGS) -f ../Makefile `basename $$i $(EXT)`;done

clean:
	rm -f *.o core a.out $(BIN) y.tab.* lex.yy.* y.output *.asm trans interp
	cd examples; for i in *$(EXT); do rm -f `basename $$i $(EXT)`; done

backup: clean
	PWD=`pwd`; CWD=`basename $$PWD`; cd ..; tar cf - $$CWD | gzip -9 > $@/$(BID).tgz

.PHONY: all clean backup examples java c++
