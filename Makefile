CC = gcc
MKDIR = mkdir -p
RM = rm -rf
CFLAGS = -Werror -Wall

# Dynamically find all .c files (use find's -name for simplicity, no need for grep/|)
SOURCES := $(shell find ./src -type f -name '*.c')

# Convert sources to objects (assumes obj/ mirrors src/ structure,
# e.g., src/commands/foo.c -> obj/commands/foo.o)
OBJECTS := $(patsubst ./src/%.c, ./build/obj/%.o, $(SOURCES))

# Main target to build the executable
build/bin/pato: $(OBJECTS)
	$(MKDIR) $(@D)
	$(CC) $^ -o $@ $(CFLAGS)

# Pattern rule to compile each .c to .o (creates subdirs as needed)
./build/obj/%.o: ./src/%.c
	$(MKDIR) $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

# Optional target to echo sources for debugging
list_sources:
	for FILE in $(SOURCES); do \
		echo $$FILE; \
	done

clean:
	$(RM) build

backup:
	bash ./Scripts/backup.bash
