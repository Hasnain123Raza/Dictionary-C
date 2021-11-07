#include "SceneManagerInterface.h"

void setSceneByIDSceneManager(SceneManager *sceneManager, SceneID sceneID)
{
    for (int counter = 0; counter < sceneManager->totalScenes; counter++)
    {
        Scene *currentScene = sceneManager->scenes[counter];
        SceneUserData *sceneUserData = currentScene->userData;
        if (sceneUserData->ID == sceneID)
        {
            setSceneSceneManager(sceneManager, currentScene);
            return;
        }
    }
}