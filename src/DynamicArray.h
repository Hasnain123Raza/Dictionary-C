#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

typedef struct {
    unsigned int capacity;
    unsigned int length;

    char *value;
} DynamicArray;

#endif