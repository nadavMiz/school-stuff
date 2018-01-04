# Global definitions
CC=g++
CFLAGS = -g -Wconversion -Wall -ansi -pedantic

# all contents of current directory
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
# Target and sources
TARGET = test.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(SHARED_OBJ)

include depends

depends:
	$(CC) -MM -I$(INC_DIR) -fPIC $(OBJS:.o=.cpp) > depends


clean:
	-rm *.o
	-rm $(TARGET)
	-rm depends

run:
	./$(TARGET)

