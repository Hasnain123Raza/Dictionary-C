#ifndef COMMON_H
#define COMMON_H

typedef enum {
    MODE_CLI,
    MODE_GUI
} MODE;

typedef struct {
    MODE mode;
    int done;
} APPLICATION_STATE;

#endif