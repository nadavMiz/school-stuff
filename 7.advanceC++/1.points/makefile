
FLAGS = -pedantic -Wall -Wconversion -ansi
LDFLAGS = -lm

C_TARGET = points.out
C_PLUS_TARGET = solution.out

all: $(C_TARGET) $(C_PLUS_TARGET)

$(C_TARGET): points.o
	gcc points.o -o $(C_TARGET) $(LDFLAGS)

points.o:
	gcc $(FLAGS) -std=gnu99 -c points.c $(LDFLAGS) 
	
$(C_PLUS_TARGET): points_jul_17.o
	g++ points_jul_17.o -o $(C_PLUS_TARGET) $(LDFLAGS)
	
points_jul_17.o:
	g++ -c points_jul_17.cpp $(LDFLAGS)
	
clean:
	rm $(C_PLUS_TARGET) 
	rm $(C_TARGET) 
	rm *.o
