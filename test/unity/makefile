CC=gcc
CFLAGS_TEST=-g -Wall -Wpedantic -Werror
SRC_DIR=src
OBJ_DIR=../../obj
DEBUG_OBJ_DIR=../../debug_obj
FIXTURE_DIR=extras/fixture/src

# not ideal but it works for now
DEBUG_OBJS=$(DEBUG_OBJ_DIR)/unity.o $(DEBUG_OBJ_DIR)/unity_fixture.o

test: $(DEBUG_OBJS)
	echo $(DEBUG_OBJS)

$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS_TEST) -c -o $@ $^
$(DEBUG_OBJ_DIR)/%.o: $(FIXTURE_DIR)/%.c
	$(CC) $(CFLAGS_TEST) -c -o $@ $^ -I $(SRC_DIR)
