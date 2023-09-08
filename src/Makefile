GCC = gcc -Wall -Wextra -Werror
PATH = ../bin/pong

all: pong
clean: 
	rm -rf *.out *.o $(PATH)
rebuild: clean all

pong: pong.c
	$(GCC) $^ -o $(PATH) 

run: $(PATH)
	./$(PATH)