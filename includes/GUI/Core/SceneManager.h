#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Core.h"
#include "Scene.h"

SceneManager *createSceneManager(Scene *scenes[], int totalScenes);
void destroySceneManager(SceneManager *sceneManager);

void setSceneSceneManager(SceneManager *sceneManager, Scene *scene);
void drawCurrentSceneSceneManager(SceneManager *sceneManager);
void clearCurrentSceneSceneManager(SceneManager *sceneManager);

void handleInputSceneManager(SceneManager *sceneManager, int input);

#endif