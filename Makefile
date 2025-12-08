CC = gcc
MKDIR = mkdir -p
RM = rm -rf
CFLAGS = -IInclude -Werror -Wall -g
DEBUG_ARGS ?=

# Dynamically find all .c files (use find's -name for simplicity, no need for grep/|)
SOURCES := $(shell find ./Source -type f -name '*.c')

# Convert sources to objects (assumes obj/ mirrors src/ structure,
# e.g., src/commands/foo.c -> obj/commands/foo.o)
OBJECTS := $(patsubst ./Source/%.c, ./Build/obj/%.o, $(SOURCES))

# Main target to build the executable
Build/bin/none: $(OBJECTS)
	$(MKDIR) $(@D)
	$(CC) $^ -o $@ $(CFLAGS)

# Pattern rule to compile each .c to .o (creates subdirs as needed)
./Build/obj/%.o: ./Source/%.c
	$(MKDIR) $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

# Optional target to echo sources for debugging
list_sources:
	for FILE in $(SOURCES); do \
		echo $$FILE; \
	done

list_all: list_sources
	for FILE in $(shell find Include -type f -name *.h); do \
		echo $$FILE; \
	done

clean:
	$(RM) Build

backup:
	bash ./Scripts/backup.bash

debug: clean Build/bin/none
	clear && gdb --args ./Build/bin/none $(DEBUG_ARGS)
