CC = g++
CXXFLAGS = -o3 -Wall -Wextra -Werror -pedantic -std=c++17

VPATH = src/ tests/

OBJS = tree.o error.o
EXEC = tree

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $^ -o $@

clean: $(EXEC) $(OBJS)
	${RM} $^

.PHONY: clean
