#ifndef SCENE_ELEMENT_H
#define SCENE_ELEMENT_H

#include "Core.h"

SceneElement *createSceneElement(int height, int width, int y, int x, int focusable, void *drawHandler, void *inputHandler, void *userData, void *freeUserDataHandler);
void destroySceneElement(SceneElement *sceneElement);

void drawSceneElement(SceneElement *sceneElement, int focused);
void clearSceneElement(SceneElement *sceneElement);

#endif