CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Iinclude
LDLIBS = -lcheck -lsubunit -lm

SRC_DIR = src
TST_DIR = test
MAIN = main.c
SRCS = $(wildcard $(SRC_DIR)/*.c)
TSTS = $(wildcard $(TST_DIR)/*.c)

OBJ_DIR = build
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TEST_OBJS = $(patsubst $(TST_DIR)/%.c, $(OBJ_DIR)/%.test.o, $(TSTS))
DEPS = $(OBJS:.o=.d)

DIST_DIR = dist

OUT = $(DIST_DIR)/byote
TEST_OUT = $(DIST_DIR)/tests

$(OUT): $(MAIN) $(OBJS)
	@mkdir -p $(DIST_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(OBJ_DIR)/%.test.o: $(TST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(OUT)

$(TEST_OUT): $(TEST_OBJS) $(OBJS)
	@mkdir -p $(DIST_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
