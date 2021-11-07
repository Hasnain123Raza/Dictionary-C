#ifndef GUI_INTERFACE_H
#define GUI_INTERFACE_H

#include <stdio.h>

#include "BinarySearchTree.h"
#include "Common.h"

#include "SceneManager.h"
#include "Scene.h"
#include "SceneElement.h"

#include "SceneElementInterface.h"
#include "SceneInterface.h"

void handleInputGUI(Dictionary *dictionary, APPLICATION_STATE* applicationState);

SceneManager *initializeSceneManager();
void pauseGUI();
void resumeGUI();
void terminateGUI();

#endif