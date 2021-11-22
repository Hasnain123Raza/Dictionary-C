#ifndef COMMAND_SCENE_H
#define COMMAND_SCENE_H

#include <stdio.h>
#include <stdlib.h>

#include "SceneManagerInterface.h"
#include "SceneConfigurations.h"
#include "SceneUtilities.h"

#include "SceneManager.h"
#include "Scene.h"

typedef Scene CommandScene;

CommandScene *createCommandScene();

#endif