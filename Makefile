CC = g++
CXXFLAGS = -o3 -Wall -Wextra -Werror -pedantic -std=c++17

#VPATH = src/ tests/

OBJS = ast.o error.o
EXEC = ast

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $^ -o $@

clean: $(EXEC) $(OBJS)
	${RM} $^

.PHONY: clean
