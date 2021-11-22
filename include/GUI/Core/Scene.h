#ifndef SCENE_H
#define SCENE_H

#include "Core.h"
#include "SceneElement.h"

Scene *createScene(SceneElement *sceneElements[], int totalSceneElements, void *userData);
void destroyScene(Scene *scene);

void setFocusScene(Scene *scene, SceneElement *sceneElement);
void resetFocusScene(Scene *scene);
void drawScene(Scene *scene);
void clearScene(Scene *scene);

void handleInputScene(SceneManager *sceneManager, Scene *scene, int input);

#endif