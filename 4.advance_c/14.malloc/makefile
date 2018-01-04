# Global definitions
CC=gcc
CFLAGS = -g -Wconversion -Wall -ansi -pedantic -std=gnu99
LDFLAGS = -g
# Directory structure
INC_DIR = ../../inc
CFLAGS += -I$(INC_DIR)
LIB_DIR = ../../lib
CFLAGS += -L$(LIB_DIR)

# all contents of current directory
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
# Target and sources
TARGET = testMyalloc.out
LIB_SRCS= myalloc.c testMyalloc.c
LIB_OBJS=$(LIB_SRCS:.c=.o)

LIB_FILE=$(LIB_DIR)/$(LIB_NAME)

# Dependencies
all: Heap $(TARGET)

Heap:
	make ../8.heap

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

include depends

depends:
	$(CC) -MM -I$(INC_DIR) -fPIC $(OBJS:.o=.c) > depends


clean:
	-rm *.o
	-rm testMyalloc.out

run:
	./testMyalloc.out

