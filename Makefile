CC := $(shell command -v clang >/dev/null 2>&1 && echo clang || (command -v gcc >/dev/null 2>&1 && echo gcc))
CFLAGS ?= -Wall -Wextra -O3

all: clean compile

compile:
ifeq ($(CC),)
	@echo "Error: Cannot find gcc or clang."
	@echo "Suggestion: make CC=<compiler path>"
else
	$(CC) $(CFLAGS) sudoku-solver.c -o solver
endif

clean:
	$(RM) solver*