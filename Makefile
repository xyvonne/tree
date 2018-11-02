CXX = g++
CXXFLAGS = -o3 -Wall -Wextra -Werror -pedantic -std=c++14

VPATH = src/rd/ src/tree/ #src/eval

#EVAL_OBJS = eval.o eval_ast.o eval_error.o
#EVAL_OBJS += lexer.o operator.o parser.o preprocessor.o
DEMO_OBJS = $(TREE_OBJS) demo.o
RD_OBJS = rd.o reader.o
TREE_OBJS = tree_error.o
OBJS = $(DEMO_OBJS) $(RD_OBJS) #(EVAL_OBJS)

EXEC = demo rd #eval

all: $(EXEC)

rd: $(RD_OBJS) $(TREE_OBJS)
	$(CXX) $^ -o $@

demo: $(DEMO_OBJS)
	$(CXX) $^ -o $@

#eval: $(EVAL_OBJS) $(TREE_OBJS)
#	$(CXX) $^ -o $@

clean: $(EXEC) $(OBJS)
	${RM} $^

.PHONY: clean
