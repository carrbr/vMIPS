CC=gcc
CFLAGS=-O3 -lm -Wall -Wpedantic -Werror
CFLAGS_TEST=-g -Wall -Wpedantic -Werror
OBJ_DIR=obj
DEBUG_OBJ_DIR=debug_obj
INC_DIR=inc
SRC_DIR=src
UNIT_TEST_DIR=test/unit

HEADERS=$(wildcard $(INC_DIR)/*.h)
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_GCC_PROF=$(SRC:%.c=$(OBJ_DIR)/%-prof)

USER_INC_DIR=arch/inc
USER_SRC_DIR=arch/src
USER_SRC=$(wildcard $(USER_SRC_DIR)/*.c)
USER_OBJS=$(USER_SRC:$(USER_SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_INC_DIR_FIXTURE=test/unity/extras/fixture/src
TEST_INC_DIR=test/unity/src

# not ideal but it works for now
DEBUG_OBJS=$(DEBUG_OBJ_DIR)/hardware.o $(DEBUG_OBJ_DIR)/instrs.o $(DEBUG_OBJ_DIR)/arch.o $(DEBUG_OBJ_DIR)/debug.o
TEST_OBJS=$(DEBUG_OBJ_DIR)/test_runner.o \
		$(DEBUG_OBJ_DIR)/arch_test.o \
		$(DEBUG_OBJ_DIR)/test_helper.o \
		$(DEBUG_OBJ_DIR)/alu_logical_test.o \
		$(DEBUG_OBJ_DIR)/alu_shift_test.o \
		$(DEBUG_OBJ_DIR)/alu_arithmetic_test.o

UNITY_DIR=test/unity
UNITY_OBJS=$(DEBUG_OBJ_DIR)/unity.o $(DEBUG_OBJ_DIR)/unity_fixture.o

all: vmips
test: vmips_test
		
prof: $(OBJS_GCC_PROF)
	
%-prof: %.c
	$(CC) -pg -o $@ $^ $(CFLAGS)
vmips: $(OBJS) $(USER_OBJS)
	$(CC) -o vmips $(OBJS) $(USER_OBJS) $(FLAGS)
vmips_test: $(DEBUG_OBJS) $(TEST_OBJS)
	cd $(UNITY_DIR) && $(MAKE) 
	cd ..
	cd ..
	$(CC) -o vmips_test $(TEST_OBJS) $(DEBUG_OBJS) $(UNITY_OBJS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS) -I $(INC_DIR) -I $(USER_INC_DIR)
$(OBJ_DIR)/%.o: $(USER_SRC_DIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS) -I $(INC_DIR) -I $(USER_INC_DIR)
#{$(SRC_DIR)\}.c{$(DEBUG_OBJ_DIR)\}.obj:
$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS_TEST) -I $(INC_DIR) -I $(USER_INC_DIR)
#{$(USER_SRC_DIR)\}.c{$(DEBUG_OBJ_DIR)\}.obj:
$(DEBUG_OBJ_DIR)/%.o: $(USER_SRC_DIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS_TEST) -I $(INC_DIR) -I $(USER_INC_DIR)
$(DEBUG_OBJ_DIR)/%.o: $(UNIT_TEST_DIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS_TEST) -I $(INC_DIR) -I $(USER_INC_DIR) -I $(TEST_INC_DIR) -I $(TEST_INC_DIR_FIXTURE)
clean:
	rm -f $(OBJS) $(DEBUG_OBJ_DIR)/*.o $(USER_OBJS) $(OBJS_GCC_PROF) vmips vmips_test
