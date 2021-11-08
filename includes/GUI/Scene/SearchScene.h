#ifndef SEARCH_SCENE_H
#define SEARCH_SCENE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DynamicArray.h"
#include "SinglyLinkedList.h"
#include "BinarySearchTree.h"

#include "SceneManagerInterface.h"
#include "SceneConfigurations.h"
#include "SceneUtilities.h"

#include "SceneManager.h"
#include "Scene.h"

typedef Scene SearchScene;

SearchScene *createSearchScene();

#endif