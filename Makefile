CC=g++
CFLAGS=-Wall -std=c++11 -Ofast -DDEBUG=0 -fomit-frame-pointer

SEQLIBPATH=/usr/local/src/SeqLib/SeqLib
# nosigncompare b/c of seqlib. 
#CFLAGS=-Wall -std=c++11 -g -DDEBUG=1 -Wno-sign-compare

USE_THREADS=true
#USETHREADS=false

USE_SEQ_LIB=true
#USE_SEQ_LIB=false

INCLUDES=

# taken from stack exchange!
SYS := $(shell ${CC} -dumpmachine)
RM=rm

ifneq (, $(findstring mingw, $(SYS)))
	RM=del
endif

# to tell the compiler that this is a multithreaded build (libraries must be present!)
LIBS:=-lpthread
ifneq ($(USE_THREADS), true)
	LIBS:=
	CFLAGS += -DNOTHREADS
endif

ifeq (${USE_SEQ_LIB}, true)
	LIBS := ${SEQLIBPATH}/bin/libseqlib.a ${SEQLIBPATH}/bin/libbwa.a  ${SEQLIBPATH}/bin/libhts.a ${LIBS} -lm -lz
	INCLUDES= -I${SEQLIBPATH} -I${SEQLIBPATH}/htslib 
	CFLAGS += -DSEQLIB
endif

# turn on named semaphores (OSX only)
ifneq (, $(findstring apple, $(SYS)))
	CFLAGS += -DOSX
endif




ifneq (, $(findstring mingw, $(SYS)))
All: lookup.h str8.h str8.o parseConfig.o lookup.o trie.o
	${CC} ${CFLAGS} ${INCLUDES} -static -o str8rzr.exe str8.o parseConfig.o lookup.o trie.o -static-libstdc++ -static-libgcc ${LIBS}
else
All: lookup.h str8.h str8.o parseConfig.o lookup.o trie.o
	${CC} ${CFLAGS} ${INCLUDES} -o str8rzr str8.o parseConfig.o lookup.o trie.o ${LIBS}
endif

str8.o: str8.h str8.cpp constants.h lookup.h
	${CC} ${CFLAGS} ${INCLUDES} -c str8.cpp

parseConfig.o: parseConfig.cpp str8.h constants.h lookup.h
	${CC} ${CFLAGS} -c parseConfig.cpp

lookup.o: lookup.cpp str8.h constants.h lookup.h
	${CC} ${CFLAGS} -c lookup.cpp

trie.o: trie.cpp trie.h
	${CC} ${CFLAGS} -c trie.cpp

clean: 
	${RM} *.o
