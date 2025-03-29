CC = clang
CFLAGS = -ansi 

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin
LIB_DIR = lib
TESTS_DIR = tests

CCONTAINERS_LIB = $(LIB_DIR)/libccontainers.so

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

TESTS_SRC_FILES = $(wildcard $(TESTS_DIR)/*.c)
TESTS_BIN_FILES = $(patsubst $(TESTS_DIR)/%.c, $(BIN_DIR)/%, $(TESTS_SRC_FILES))

MAIN_SRC = main.c
MAIN_BIN = $(BIN_DIR)/main

all: $(MAIN_BIN) $(CCONTAINERS_LIB) $(TESTS_BIN_FILES)

run: $(MAIN_BIN)
	@./$<

$(MAIN_BIN): $(CCONTAINERS_LIB) $(MAIN_SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I./$(INC_DIR) -L./$(LIB_DIR) $^ -o $@

$(CCONTAINERS_LIB): $(OBJ_FILES)
	@mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@

ccontainers: $(CCONTAINERS_LIB)

run_tests: $(TESTS_BIN_FILES)
	@for test in $^; do ./$$test; done

$(BIN_DIR)/%: $(CCONTAINERS_LIB) $(TESTS_DIR)/%.c 
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I./$(INC_DIR) -L./$(LIB_DIR) $^ -o $@

clean:
	@rm -rf $(BUILD_DIR)

clean_all: clean
	@rm -rf $(LIB_DIR)
	@rm $(TESTS_BIN_FILES)
	@rm -rf $(BIN_DIR)

.PHONY: all run ccontainers run_tests clean clean_all