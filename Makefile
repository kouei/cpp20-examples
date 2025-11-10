SHELL := /bin/bash -O globstar

CPP_STD := -std=c++23
CPP_FLAG := -g -O0 -Wall $(CPP_STD)

SRC_DIR := src
main: $(SRC_DIR)/*
	clang++ $(SRC_DIR)/main.cpp $(CPP_FLAG) -o $@

.PHONY: tidy tidy-all format format-all run clean

EXAMPLES_DIR := examples
ALL_SRC := $(SRC_DIR)/*.cpp $(SRC_DIR)/*.hpp $(shell ls $(EXAMPLES_DIR)/**/*.cpp) $(shell ls $(EXAMPLES_DIR)/**/*.hpp)

tidy:
	@clang-tidy $(SRC_DIR)/*.cpp $(SRC_DIR)/*.hpp -- $(CPP_STD)

tidy-all:
	@clang-tidy $(ALL_SRC) -- $(CPP_STD)

format:
	@clang-format -i $(SRC_DIR)/*.cpp $(SRC_DIR)/*.hpp

format-all:
	@clang-format -i $(ALL_SRC)

run:
	@./main

ARTIFACTS := main
clean:
	rm -f $(ARTIFACTS)