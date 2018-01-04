# Global definitions
CC=gcc
CFLAGS = -Wconversion -Wall -ansi -pedantic -std=gnu99 -m32
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
TARGET = testHashMap.out
LIB_SRCS= HashMap.c
LIB_OBJS=$(LIB_SRCS:.c=.o)
LIB_NAME = libcHash.so.1.0
LIB_LINK = libcHash.so.1

LIB_FILE=$(LIB_DIR)/$(LIB_NAME)

# Dependencies
all: Heap $(TARGET)

Heap:
	make ../../04.advance_c/8.heap

$(TARGET): $(OBJS)
	

include depends

depends:
	$(CC) -MM -I$(INC_DIR) -fPIC $(OBJS:.o=.c) > depends

commit: $(LIB_FILE) $(LIB_DIR)/$(LIB_LINK) $(LIB_DIR)/libcHash.so

$(LIB_FILE): $(LIB_OBJS)
	gcc $(CFLAGS) -shared -Wl,-soname,$(LIB_LINK) -o $(LIB_NAME) *.o 
	mv $(LIB_NAME) $(LIB_DIR)
	
dynamic:
	ar -cvq libHash.a *.o
	mv libHash.a $(LIB_DIR)
	
$(LIB_DIR)/$(LIB_LINK):
	ln -sf $(LIB_NAME) $(LIB_DIR)/$(LIB_LINK)
	
$(LIB_DIR)/libcHash.so:
	ln -sf $(LIB_NAME) $(LIB_DIR)/libcHash.so

clean:
	-rm *.o
	-rm testHashMap.out

run:
	./testHashMap.out

