#include "Scene.h"

Scene *createScene(SceneElement *sceneElements[], int totalSceneElements, void *userData)
{
    Scene *scene = malloc(sizeof(Scene));
    if (!scene)
    {
        fprintf(stderr, "Unable to allocate space for scene\n");
        return NULL;
    }

    scene->sceneElements = sceneElements;
    scene->totalSceneElements = totalSceneElements;
    scene->focusedSceneElement = NULL;
    scene->userData = userData;

    return scene;
}

void destroyScene(Scene *scene)
{
    for (int counter = 0; counter < scene->totalSceneElements; counter++)
        destroySceneElement(scene->sceneElements[counter]);
    
    free(scene->sceneElements);
    free(scene->userData);
    free(scene);
}



void setFocusScene(Scene *scene, SceneElement *sceneElement)
{
    if (scene->focusedSceneElement)
    {
        clearSceneElement(scene->focusedSceneElement);
        drawSceneElement(scene->focusedSceneElement, 0);
    }
    
    scene->focusedSceneElement = sceneElement;
    clearSceneElement(sceneElement);
    drawSceneElement(sceneElement, 1);
}

void resetFocusScene(Scene *scene)
{
    for (int counter = 0; counter < scene->totalSceneElements; counter++)
    {
        SceneElement *sceneElement = scene->sceneElements[counter];
        if (sceneElement->focusable)
        {
            scene->focusedSceneElement = sceneElement;
            return;
        }
    }
}

void drawScene(Scene *scene)
{
    for (int counter = 0; counter < scene->totalSceneElements; counter++)
    {
        SceneElement *currentSceneElement = scene->sceneElements[counter];
        drawSceneElement(currentSceneElement, scene->focusedSceneElement == currentSceneElement);
    }        
}

void clearScene(Scene *scene)
{
    for (int counter = 0; counter < scene->totalSceneElements; counter++)
        clearSceneElement(scene->sceneElements[counter]);
}



void handleInputScene(SceneManager *sceneManager, Scene *scene, int input)
{
    SceneElement *sceneElement = scene->focusedSceneElement;
    if (!sceneElement)
        return;

    switch (input)
    {
        case KEY_UP:
            {
                if (sceneElement->previous)
                    setFocusScene(scene, sceneElement->previous);
            }
            break;

        case KEY_DOWN:
            {
                if (sceneElement->next)
                    setFocusScene(scene, sceneElement->next);
            }
            break;

        default:
            {
                SceneElementInputHandler sceneElementInputHandler = sceneElement->inputHandler;
                sceneElementInputHandler(sceneManager, scene, sceneElement, input);
            }
            break;
    }
}