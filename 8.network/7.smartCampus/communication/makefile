# Global definitions

CC = g++
#SFLAGS = -g -shared -Wl,-soname,
CXXFLAGS = -g -Wall -ansi -pedantic
LDFLAGS = -g -pthread -ldl
# Directory structure
INC_DIR = -Iserver/ -I../inc/
CXXFLAGS += $(INC_DIR)
#LIB_DIR = ../../../lib
#LDFLAGS += -L$(LIB_DIR)
#LIB_NAME = libfeeder.so
#LDLIBS =-lPHash -lLinkedList
# all contents of current directory
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

SERVER_TARGET = server/test.out
NEXTOBJ = $(wildcard server/*.o)
OBJS += $(patsubst %.o,%.o,$(NEXTOBJ))
# Target and sources
TARGET = test
#LIB_SRCS = ../communication/comm.c
#LIB_OBJS = $(LIB_SRCS:.c=.o)
# Dependencies
all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_OBJS)
	$(CC) -I$(INC_DIR) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)
	rm event.o

include depends

depends:
	$(CC) -MM $(INC_DIR) $(OBJS:.o=.cpp) > depends

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
