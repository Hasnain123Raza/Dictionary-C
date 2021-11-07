#include "SceneElement.h"

SceneElement *createSceneElement(int height, int width, int y, int x, int focusable, void *drawHandler, void *inputHandler, void *userData, void *freeUserDataHandler)
{
    SceneElement *sceneElement = malloc(sizeof(SceneElement));
    if (!sceneElement)
    {
        fprintf(stderr, "Unable to allocate space for scene element\n");
        return NULL;
    }

    WINDOW *sceneElementWindow = newwin(height, width, y, x);
    if (!sceneElementWindow)
    {
        fprintf(stderr, "Unable to allocate space for scene element window\n");
        free(sceneElement);
        return NULL;
    }

    sceneElement->window = sceneElementWindow;
    sceneElement->focusable = focusable;
    sceneElement->previous = NULL;
    sceneElement->next = NULL;
    sceneElement->drawHandler = drawHandler;
    sceneElement->inputHandler = inputHandler;
    sceneElement->userData = userData;
    sceneElement->freeUserDataHandler = freeUserDataHandler;

    return sceneElement;
}

void destroySceneElement(SceneElement *sceneElement)
{
    clearSceneElement(sceneElement);
    delwin(sceneElement->window);
    SceneElementFreeUserDataHandler sceneElementFreeUserDataHandler = sceneElement->freeUserDataHandler;
    sceneElementFreeUserDataHandler(sceneElement);
    free(sceneElement);
}



void drawSceneElement(SceneElement *sceneElement, int focused)
{
    SceneElementDrawHandler sceneElementDrawHandler = sceneElement->drawHandler;
    if (sceneElementDrawHandler)
    {
        sceneElementDrawHandler(sceneElement, focused);
        wrefresh(sceneElement->window);
    }
}

void clearSceneElement(SceneElement *sceneElement)
{
    werase(sceneElement->window);
    wrefresh(sceneElement->window);
}