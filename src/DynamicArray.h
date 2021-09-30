#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

typedef struct {
    unsigned int capacity;
    unsigned int length;

    char *value;
} DynamicArray;

typedef DynamicArray Definition;

/* Constructor and Destructor */

DynamicArray *createDynamicArray(unsigned int initialCapacity);
void destroyDynamicArray(DynamicArray *dynamicArray);

/* DynamicArray Operations */



#endif