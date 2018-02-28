# Global definitions
CC=gcc
CFLAGS = -g -Wconversion -Wall -ansi -pedantic -std=gnu99 -m32
LDFLAGS = -g
# Directory structure
INC_DIR = ../inc
CFLAGS += -I$(INC_DIR)
LIB_DIR = ../../../lib
CFLAGS += -L$(LIB_DIR)
SHARED_OBJ = -lcZlog4c

# all contents of current directory
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
# Target and sources
TARGET = controllerMain.out
LOG_FILE = ../log/controller.log

LIB_FILE=$(LIB_DIR)/$(LIB_NAME)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -pthread $(SHARED_OBJ)

include depends

depends:
	$(CC) $(CFLAGS) -MM -I$(INC_DIR) -fPIC $(OBJS:.o=.c) > depends

clean:
	-rm *.o
	-rm controllerMain.out

run:
	-rm $(LOG_FILE)
	./controllerMain.out

