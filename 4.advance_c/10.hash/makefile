LIB_PATH = ../../lib
INC_PATH = ../../inc
CFLAGS = -ansi -Wall -g -pedantic -Wconversion -I$(INC_PATH)

HashMapTest.out: List HashMapTest.c $(LIB_PATH)/libHash.a
	gcc $(FLAGS) -o HashMapTest.out HashMapTest.c $(LIB_PATH)/libHash.a $(LIB_PATH)/libLinkedList.a -lm

List:
	make -C../5.iterator
	
$(LIB_PATH)/libHash.a: HashMap.o $(INC_PATH)/HashMap.h
	ar -cvq libHash.a HashMap.o
	mv libHash.a $(LIB_PATH)

HashMap.o: HashMap.c
	gcc $(FLAGS) -c HashMap.c $(LIB_PATH)/libLinkedList.a -lm
	
clean:
	make -C../5.iterator
	rm HashMap.o
