BIN_DIR = bin
INC_DIR = .
OBJ_DIR = obj
SRC_DIR = .
APP_EXE = a.out

RM := rm
MKDIR := mkdir
LOG_ERR := /dev/null

CC := g++
CFLAGS := -I$(INC_DIR) -std=c++14 -Wall -pedantic -Wextra -Werror
LDFLAGS := -lm

SRC_EXT := cpp
INC_EXT := h

SRCS := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJS := $(patsubst $(SRC_DIR)/%.$(SRC_EXT), $(OBJ_DIR)/%.o, $(SRCS))
DIRS := $(OBJ_DIR) $(BIN_DIR)

.PHONY: all dir clean check

all: dir $(BIN_DIR)/$(APP_EXE)

$(BIN_DIR)/$(APP_EXE): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT) $(INC_DIR)/%.$(INC_EXT)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	$(CC) $(CFLAGS) -o $@ -c $<

dir: $(DIRS)

$(DIRS):
	$(MKDIR) -p $@

clean:
	$(RM) -rf $(OBJ_DIR)/*.o $(BIN_DIR)/$(APP_EXE) 2>$(LOG_ERR)

check:
	cppcheck -f --std=c++14 --enable=all --check-config --inconclusive --suppress=missingIncludeSystem .
