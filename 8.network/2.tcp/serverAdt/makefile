# Global definitions

CC = gcc
#SFLAGS = -g -shared -Wl,-soname,
CXXFLAGS = -g -Wall -ansi -pedantic -std=gnu99
# Directory structure
INC_DIR = ../inc/
CXXFLAGS += -I$(INC_DIR)
LIB_DIR = ../../../lib
LDFLAGS += -L$(LIB_DIR) 
#LIB_NAME = libfeeder.so
LDLIBS = -lcList
# all contents of current directory
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.cpp=.o)
# Target and sources
TARGET = server.out
#LIB_SRCS = ../communication/comm.c
#LIB_OBJS = $(LIB_SRCS:.c=.o)
# Dependencies
all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_OBJS)
	$(CC) -I$(INC_DIR) $(LDFLAGS) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDLIBS)

include depends

depends:
	$(CC) -MM -I$(INC_DIR) $(OBJS:.o=.cpp) > depends

commit: $(LIB_FILE).1.0

#$(LIB_FILE): $(LIB_OBJS)
#   $(CC) $(SFLAGS)$(LIB_NAME).1 -o $(LIB_NAME).1.0 $(LIB_OBJS)
#   ln -sf $(LIB_NAME).1.0 $(LIB_FILE).1
#   ln -sf $(LIB_NAME).1.0 $(LIB_FILE)
#   mv $(LIB_NAME).1.0 $(LIB_DIR)/
clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -f depends
#   -rm -f $(LIB_FILE) $(LIB_FILE).1 $(LIB_FILE).1.0

run: all
	./test

gdb: all
	gdb ./test
