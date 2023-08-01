CC = g++
CFLAGS = -Wall -I lib
NAME = main

# Finds files matching wildcard recursively
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

DEPS = $(call rwildcard,lib/,*.h)
LIB = $(call rwildcard,lib/,*.cpp)
SRC = $(call rwildcard,src/,*.cpp)

OBJ = $(patsubst %.cpp,%.o, $(SRC) $(LIB))


RM = rm -f
MKDIR = mkdir -p

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: $(OBJ)
	$(CC) -o bin/$(NAME) $^ $(CFLAGS)

run: make
	@./bin/$(NAME)

.PHONY: clean

clean:
	@ $(RM) bin/* $(OBJ) $(RME)
