CC=g++
#CFLAGS=-Wall -std=c++11 -Ofast -DDEBUG=0 -march=native -fomit-frame-pointer
 
CFLAGS=-Wall -std=c++11 -g -DDEBUG=0
#CFLAGS=-Wall -std=c++11 -g -pg -DDEBUG=0

# Can turn off threads when compiling (in case the required libraries are not present...)
USETHREADS=true
#USETHREADS=false
# to tell the compiler that this is a multithreaded build (libraries must be present!)
LIBS=-lpthread

# taken from stack exchange!
SYS := $(shell ${CC} -dumpmachine)

RM=rm

ifneq (, $(findstring mingw, $(SYS)))
	RM=del
endif


ifneq (${USETHREADS}, true)
	LIBS=
	CFLAGS += -DNOTHREADS
endif


ifneq (, $(findstring mingw, $(SYS)))
All: lookup.h str8.h str8.o parseConfig.o lookup.o trie.o
	${CC} ${CFLAGS} -static -o str8.exe str8.o parseConfig.o lookup.o trie.o -static-libstdc++ -static-libgcc ${LIBS}
else
All: lookup.h str8.h str8.o parseConfig.o lookup.o trie.o
	${CC} ${CFLAGS} -o str8 str8.o parseConfig.o lookup.o trie.o ${LIBS}
endif

str8.o: str8.h str8.cpp constants.h lookup.h
	${CC} ${CFLAGS} -c str8.cpp

parseConfig.o: parseConfig.cpp str8.h constants.h lookup.h
	${CC} ${CFLAGS} -c parseConfig.cpp

lookup.o: lookup.cpp str8.h constants.h lookup.h
	${CC} ${CFLAGS} -c lookup.cpp

trie.o: trie.cpp trie.h
	${CC} ${CFLAGS} -c trie.cpp

clean: 
	${RM} *.o
