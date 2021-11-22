#ifndef SCENE_ELEMENT_UTILITIES_H
#define SCENE_ELEMENT_UTILITIES_H

#include <ncurses.h>
#include <string.h>

#include "Core.h"
#include "SceneElementConfigurations.h"

typedef struct {
    SceneElementID ID;
    void *data;
} SceneElementUserData;

void sceneElementFreeUserDataHandler(SceneElement *sceneElement);

void putStringInCenter(WINDOW *window, char *string);
void putStringInWindow(WINDOW *window, char *string);
void putInputInWindow(WINDOW *window, char *input);
void applyAttributes(WINDOW *window, int attributes);

#endif