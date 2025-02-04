
CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -pedantic -g
SRC_DIR = src/ds
BUILD_DIR = build
OUT_DIR = bin/tests
TEST_SRC = test/ds

# Create necessary directories
$(BUILD_DIR) $(OUT_DIR):
	mkdir -p $@

# Compile object files
$(BUILD_DIR)/zroc_array.o: $(SRC_DIR)/zroc_array.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/zroc_dynArray.o: $(SRC_DIR)/zroc_dynArray.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/zroc_stack.o: $(SRC_DIR)/zroc_stack.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link tests with compiled objects
$(OUT_DIR)/test_ds_array: $(TEST_SRC)/test_zroc_array.c $(BUILD_DIR)/zroc_array.o | $(OUT_DIR)
	$(CC) $(CFLAGS) $< $(BUILD_DIR)/zroc_array.o -o $@

$(OUT_DIR)/test_ds_dynArray: $(TEST_SRC)/test_zroc_dynArray.c $(BUILD_DIR)/zroc_dynArray.o | $(OUT_DIR)
	$(CC) $(CFLAGS) $< $(BUILD_DIR)/zroc_dynArray.o -o $@

$(OUT_DIR)/test_ds_stack: $(TEST_SRC)/test_zroc_stack.c $(BUILD_DIR)/zroc_stack.o | $(OUT_DIR)
	$(CC) $(CFLAGS) $< $(BUILD_DIR)/zroc_stack.o -o $@

run_test_ds_array: $(OUT_DIR)/test_ds_array
	$(OUT_DIR)/test_ds_array

run_test_ds_dynArray: $(OUT_DIR)/test_ds_dynArray
	$(OUT_DIR)/test_ds_dynArray

run_test_ds_stack: $(OUT_DIR)/test_ds_stack
	$(OUT_DIR)/test_ds_stack

clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR)

