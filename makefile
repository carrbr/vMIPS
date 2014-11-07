CC=gcc
CFLAGS=-O3 -lm -fopenmp
OBJ_DIR=obj
INC_DIR=inc
SRC_DIR=src
HEADERS=$(wildcard $(INC_DIR)/*.h)
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_GCC_PROF=$(SRC:%.c=$(OBJ_DIR)/%-prof)

USER_INC_DIR=arch/inc
USER_SRC_DIR=arch/src
USER_SRC=$(wildcard $(USER_SRC_DIR)/*.c)
USER_OBJS=$(USER_SRC:$(USER_SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: vmips
		
prof: $(OBJS_GCC_PROF)
	
%-prof: %.c
	$(CC) -pg -o $@ $^ $(CFLAGS)
vmips: $(OBJS) $(USER_OBJS)
	$(CC) -o vmips $(OBJS) $(USER_OBJS) $(CFLAGS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS) -I $(INC_DIR) -I $(USER_INC_DIR)
$(OBJ_DIR)/%.o: $(USER_SRC_DIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS) -I $(INC_DIR) -I $(USER_INC_DIR)
clean:
	rm -f $(OBJS) $(USER_OBJS) $(OBJS_GCC_PROF) vmips
