FILES = source/main.cpp
CFLAGS = -Wall -Wextra  -std=c++17 -pedantic -ggdb -O1
LIBS = -lncurses -lmenu

build:
	-g++ ${FILES} ${CFLAGS} -o to_do_tool ${LIBS} 
	rm to_do_tool

test:
	-g++ ${FILES} ${CFLAGS} -o to_do_tool ${LIBS}
	./to_do_tool .
	rm to_do_tool

realase:
	-g++ ${FILES} ${CFLAGS} -o to_do_tool ${LIBS}
	
clean:
	rm to_do_tool
