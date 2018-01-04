#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

struct DynamicArray{
	int capacity;
	int index;
	int* array;
};

int insert(struct DynamicArray* dynamicArray, int element);
struct DynamicArray* create(int capacity);
void destroy(struct DynamicArray* dynamicArray);
#endif
