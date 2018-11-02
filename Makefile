CXX = g++
CXXFLAGS = -o3 -Wall -Wextra -Werror -pedantic -std=c++14

VPATH = src/eval src/rd/ src/tree/

DEMO_OBJS = demo.o
EVAL_OBJS = eval.o eval_error.o lexer.o operator.o parser.o preprocessor.o
RD_OBJS = rd.o reader.o
TREE_OBJS = tree_error.o
OBJS = $(DEMO_OBJS) $(EVAL_OBJS) $(RD_OBJS) $(TREE_OBJS)

EXECS = demo eval rd

all: $(EXECS)

demo: $(DEMO_OBJS) $(TREE_OBJS)
	$(CXX) $^ -o $@

eval: $(EVAL_OBJS) $(TREE_OBJS)
	$(CXX) $^ -o $@

rd: $(RD_OBJS) $(TREE_OBJS)
	$(CXX) $^ -o $@

clean: $(EXECS) $(OBJS)
	${RM} $^

.PHONY: clean
