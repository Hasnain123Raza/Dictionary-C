#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#define INITIAL_DEFINITION_CAPACITY 64

typedef struct {
    unsigned int capacity;
    unsigned int length;

    char *value;
} DynamicArray;

typedef DynamicArray Definition;

/* Constructor and Destructor */

Definition *createDefinition(char *definition);
void destroyDefinition(Definition *definition);

/* Definition Operations */

int growDefinition(Definition *defintion);

#endif