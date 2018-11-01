CXX = g++
CXXFLAGS = -o3 -Wall -Wextra -Werror -pedantic -std=c++17

VPATH = src/read_dir/ src/tree/ #src/eval_expr

#EVAL_OBJS = eval.o eval_error.o eval_tree.o lexer.o operator.o
#EVAL_OBJS += parser.o preprocessor.o
RD_OBJS = read_dir.o rd.o
TREE_OBJS = tree_error.o
TREE_DEMO_OBJS = $(TREE_OBJS) tree_demo.o
OBJS = $(RD_OBJS) $(TREE_DEMO_OBJS) #(EVAL_OBJS)

EXEC = rd tree_demo #eval

all: $(EXEC)

rd: $(RD_OBJS) $(TREE_OBJS)
	$(CXX) $^ -o $@

tree_demo: $(TREE_DEMO_OBJS)
	$(CXX) $^ -o $@

#eval: $(EVAL_OBJS) $(TREE_OBJS)
#	$(CXX) $^ -o $@

clean: $(EXEC) $(OBJS)
	${RM} $^

.PHONY: clean
