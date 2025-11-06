CPP_STD := -std=c++23
CPP_FLAG := -g -O0 -Wall $(CPP_STD)
SRC_DIR := src
MAIN_SRC := main.cpp
EXAMPLES_DIR := examples
ALL_SRC := $(SRC_DIR)/* $(EXAMPLES_DIR)/concepts/*
ARTIFACTS := main

main: $(SRC_DIR)/*
	clang++ $(SRC_DIR)/$(MAIN_SRC) $(CPP_FLAG) -o $@

.PHONY: tidy format run clean

tidy:
	clang-tidy $(ALL_SRC) -- $(CPP_STD)

format:
	clang-format -i $(ALL_SRC)

run:
	@./main

clean:
	rm -f $(ARTIFACTS)