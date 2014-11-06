CC=gcc
CFLAGS=-O3 -lm -fopenmp
OBJ_DIR=obj
INC_DIR=inc
SRC_DIR=src
HEADERS=$(wildcard $(INC_DIR)/*.h)
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_GCC_PROF=$(SRC:%.c=$(OBJ_DIR)/%-prof)

USER_INC=mips

all: vmips
		
prof: $(OBJS_GCC_PROF)
	
%-prof: %.c
	$(CC) -pg -o $@ $^ $(CFLAGS)
vmips: $(OBJS)
	$(CC) -o vmips $(OBJS) $(CFLAGS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS) -I $(INC_DIR) -I $(USER_INC)
clean:
	rm -f $(OBJS) $(OBJS_GCC_PROF) vmips
