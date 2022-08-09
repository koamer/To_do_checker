FILES = source/main.cpp
CFLAGS = -Wall -Wextra  -std=c++17 -pedantic -ggdb -O1
LIBS = -lncurses -lmenu
all:
	g++ ${FILES} ${CFLAGS} -o to_do_tool ${LIBS}
