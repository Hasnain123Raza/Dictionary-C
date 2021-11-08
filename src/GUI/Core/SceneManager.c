#include "SceneManager.h"

SceneManager *createSceneManager(Scene *scenes[], int totalScenes)
{
    SceneManager *sceneManager = malloc(sizeof(SceneManager));
    if (!sceneManager)
    {
        fprintf(stderr, "Unable to allocate space for scene manager\n");
        return NULL;
    }

    sceneManager->scenes = scenes;
    sceneManager->currentScene = NULL;
    sceneManager->totalScenes = totalScenes;
    sceneManager->paused = 0;
    sceneManager->done = 0;
    sceneManager->userData = NULL;

    return sceneManager;
}

void destroySceneManager(SceneManager *sceneManager)
{
    for (int counter = 0; counter < sceneManager->totalScenes; counter++)
        destroyScene(sceneManager->scenes[counter]);
    
    free(sceneManager->scenes);
    free(sceneManager);
}



void setSceneSceneManager(SceneManager *sceneManager, Scene *scene)
{
    clearCurrentSceneSceneManager(sceneManager);
    resetFocusScene(scene);

    sceneManager->currentScene = scene;
    clearCurrentSceneSceneManager(sceneManager);
    drawCurrentSceneSceneManager(sceneManager);
}

void drawCurrentSceneSceneManager(SceneManager *sceneManager)
{
    if (sceneManager->currentScene)
        drawScene(sceneManager->currentScene);
}

void clearCurrentSceneSceneManager(SceneManager *sceneManager)
{
    if (sceneManager->currentScene)
        clearScene(sceneManager->currentScene);
}



void handleInputSceneManager(SceneManager *sceneManager, int input)
{
    handleInputScene(sceneManager, sceneManager->currentScene, input);
}