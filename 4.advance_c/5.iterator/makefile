# Global definitions
CC=gcc
CFLAGS = -g -Wconversion -Wall -pedantic -ansi
LDFLAGS = -g

# Directory structure
INC_DIR = ../../inc
CFLAGS += -I$(INC_DIR)
LIB_DIR = ../../lib
LIB_NAME = libcList.so.1.0

# all contents of current directory
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
# Target and sources
TARGET = doubleLinkedListMain.out
LIB_SRCS=doubleLinkedList.c ListIteratorFuncs.c
LIB_OBJS=$(LIB_SRCS:.c=.o)

LIB_FILE=$(LIB_DIR)/$(LIB_NAME)

# Dependencies
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -fPIC -o $(TARGET) $(OBJS)

include depends

depends:
	$(CC) -MM -I$(INC_DIR) -fPIC $(OBJS:.o=.c) > depends

dynamic:
	ar -cvq libList.a *.o
	mv libList.a $(LIB_DIR)

commit: $(LIB_FILE) ../../lib/libcList.so.1 ../../lib/libcList.so

$(LIB_FILE): $(LIB_OBJS)
	gcc -shared -Wl,-soname,libcList.so.1 -fPIC -o $(LIB_NAME) *.o
	mv $(LIB_NAME) ../../lib

../../lib/libcList.so.1:
	ln -sf $(LIB_NAME) ../../lib/libcList.so.1
	
../../lib/libcList.so:
	ln -sf $(LIB_NAME) ../../lib/libcList.so

clean:
	-rm *.o
	-rm doubleLinkedListMain.out

run:
	./doubleLinkedListMain.out

