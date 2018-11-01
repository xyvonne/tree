CC = g++
CXXFLAGS = -o3 -Wall -Wextra -Werror -pedantic -std=c++17

VPATH = src/demo src/error/ src/evalexpr src/read_dir/ src/tree/

OBJS = error.o read_dir.o demo.o
EXEC = demo

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $^ -o $@

clean: $(EXEC) $(OBJS)
	${RM} $^

.PHONY: clean
