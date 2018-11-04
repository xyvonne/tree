### Adapted from http://www.partow.net/programming/makefile/index.html ###

## Variables ##

# Flags #
CXX := g++
CXXFLAGS := -o3 -Wall -Wextra -Werror -pedantic -std=c++14
LDFLAGS :=

# Build directories #
BUILD := ./build
DEMO_OBJ_DIR := $(BUILD)/demo
EVAL_OBJ_DIR := $(BUILD)/eval
RD_OBJ_DIR := $(BUILD)/rd

# Targets (binary files) #
DEMO_TARGET = demo
EVAL_TARGET = eval
RD_TARGET = rd
TARGETS = $(DEMO_TARGET) $(EVAL_TARGET) $(RD_TARGET)

# Header directory #
INCLUDE := -Iinclude

# Source directories and files #
SRC := ./src
DEMO_SRC_DIR := $(SRC)/demo
EVAL_SRC_DIR := $(SRC)/eval
RD_SRC_DIR := $(SRC)/rd

TREE_SRC := $(wildcard ./src/tree/*.cc)
DEMO_SRC := $(wildcard $(DEMO_SRC_DIR)/*.cc) $(TREE_SRC)
EVAL_SRC := $(wildcard $(EVAL_SRC_DIR)/*.cc) $(TREE_SRC)
RD_SRC := $(wildcard $(RD_SRC_DIR)/*.cc) $(TREE_SRC)

# Object files #
DEMO_OBJ = $(patsubst $(DEMO_SRC_DIR)/%.cc, $(DEMO_OBJ_DIR)/%.o, $(DEMO_SRC))
EVAL_OBJ = $(patsubst $(EVAL_SRC_DIR)/%.cc, $(EVAL_OBJ_DIR)/%.o, $(EVAL_SRC))
RD_OBJ = $(patsubst $(RD_SRC_DIR)/%.cc, $(RD_OBJ_DIR)/%.o, $(RD_SRC))

## Rules ##

# Main rule #
all: build $(TARGETS)

# Make the build directories #
build:
	@mkdir -p $(DEMO_OBJ_DIR) $(EVAL_OBJ_DIR) $(RD_OBJ_DIR)

# Link the .o to make the binaries #
$(DEMO_TARGET): $(DEMO_OBJ)
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) $(LDFLAGS) -o $@ $^

$(EVAL_TARGET): $(EVAL_OBJ)
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) $(LDFLAGS) -o $@ $^

$(RD_TARGET): $(RD_OBJ)
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) $(LDFLAGS) -o $@ $^

# Compile the .o from the .cc #
$(DEMO_OBJ_DIR)/%.o: $(DEMO_SRC_DIR)/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(EVAL_OBJ_DIR)/%.o: $(EVAL_SRC_DIR)/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(RD_OBJ_DIR)/%.o: $(RD_SRC_DIR)/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

# Cleaning #
clean:
	@rm -rf $(BUILD)

mrproper: clean
	@rm -rf $(TARGETS)

# Dummy rules #
.PHONY: all build clean
