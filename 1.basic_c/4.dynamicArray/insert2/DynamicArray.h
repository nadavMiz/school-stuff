#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
typedef int* intptr;

struct DynamicArray{
	int capacity;
	int noe; // number of elements
	intptr* array;
};

typedef struct DynamicArray DynamicArray;

int insert(struct DynamicArray* dynamicArray, intptr element);
int insertAtN (DynamicArray* DA, intptr element, int index);
intptr find(DynamicArray* DA, int element);
int delete(DynamicArray* DA, int searchNum);
struct DynamicArray* create(int capacity);
void destroy(struct DynamicArray* dynamicArray);
#endif
