CC = gcc
MKDIR = mkdir -p
RM = rm -rf
CFLAGS = -Werror -Wall

# Dynamically find all .c files (use find's -name for simplicity, no need for grep/|)
SOURCES := $(shell find ./Source -type f -name '*.c')

# Convert sources to objects (assumes obj/ mirrors src/ structure,
# e.g., src/commands/foo.c -> obj/commands/foo.o)
OBJECTS := $(patsubst ./Source/%.c, ./Build/obj/%.o, $(SOURCES))

# Dynamically find every .h file in './Include'
INCLUDE := $(shell find ./Include -type f -name '*.h')

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

clean:
	$(RM) Build

backup:
	bash ./Scripts/backup.bash
