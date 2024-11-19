.DEFAULT_GOAL := all

TARGET := order

SRC := src
BIN := bin
OBJ := obj

# create directories if needed
$(shell mkdir -p $(BIN))
$(shell mkdir -p $(OBJ))

EXE = $(BIN)/$(TARGET)

# lists all c files in SRC directory
SOURCES := $(wildcard $(SRC)/*.c)
# lists all object files in OBJ directory
OBJECTS := $(patsubst $(SRC)%,$(OBJ)%, $(patsubst %.c,%.o,$(SOURCES)))

INCLUDE := -I.
FLAGS := -g

CC := gcc

### TARGETS ###

run: all
	@$(EXE)

valgrind: all
	valgrind --leak-check=full $(EXE)

### general targets

all: $(OBJECTS)
	@$(CC) $(FLAGS) $(INCLUDE) $(OBJECTS) $(LIBS) -o $(EXE) 

%.o: ../$(SRC)/%.c
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rfv $(OBJ)/*
	@rm -rfv $(BIN)/*
