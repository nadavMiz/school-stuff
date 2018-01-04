# Global definitions
CC=gcc
CFLAGS = -g -Wconversion -Wall -ansi -pedantic -std=gnu99
LDFLAGS = -g
# Directory structure
INC_DIR = ../../inc
CFLAGS += -I$(INC_DIR)
LIB_DIR = ../../lib
CFLAGS += -L$(LIB_DIR)
LIB_NAME = libcScheduler.so.1.0
LIB_LINK = libcScheduler.so.1

# all contents of current directory
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
# Target and sources
TARGET = TestScheduler.out
LIB_SRCS=Scheduler.c Task.c myTime.c
LIB_OBJS=$(LIB_SRCS:.c=.o)

LIB_FILE=$(LIB_DIR)/$(LIB_NAME)

# Dependencies
all: Heap $(TARGET)

Heap:
	make ../8.heap

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -libcVector.so

include depends

depends:
	$(CC) -MM -I$(INC_DIR) -fPIC $(OBJS:.o=.c) -libcVector.so > depends


commit: $(LIB_FILE) $(LIB_DIR)/$(LIB_LINK) $(LIB_DIR)/libcScheduler.so

$(LIB_FILE): $(LIB_OBJS)
	gcc -shared -Wl,-soname,$(LIB_LINK) -o $(LIB_NAME) *.o
	mv $(LIB_NAME) $(LIB_DIR)
	
$(LIB_DIR)/$(LIB_LINK):
	ln -sf $(LIB_NAME) $(LIB_DIR)/$(LIB_LINK)
	
$(LIB_DIR)/libcScheduler.so:
	ln -sf $(LIB_NAME) $(LIB_DIR)/libcScheduler.so


clean:
	-rm *.o
	-rm TestScheduler.out

run:
	./TestScheduler.out

