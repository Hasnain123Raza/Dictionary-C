#ifndef SCENE_UTILITIES_H
#define SCENE_UTILITIES_H

#include <ncurses.h>
#include <string.h>

#include "Core.h"
#include "SceneElementInterface.h"
#include "SceneConfigurations.h"

typedef struct {
    SceneID ID;
} SceneUserData;

Scene *prepareAndGenerateScene(SceneElement *sceneElements[], int totalSceneElements, void *sceneUserData);
void freeSceneElements(SceneElement *sceneElements[], int totalSceneElements);

#endif