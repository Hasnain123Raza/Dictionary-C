#include "SceneUtilities.h"

static int ensureSceneElementGeneration(SceneElement *sceneElements[], int totalSceneElements);
static void adjustSceneElementWindows(SceneElement *sceneElements[], int totalSceneElements);
static int getLargestSceneElementWidth(SceneElement *sceneElements[], int totalSceneElements);
static void linkSceneElements(SceneElement *sceneElements[], int totalSceneElements);

Scene *prepareAndGenerateScene(SceneElement *sceneElements[], int totalSceneElements, void *sceneUserData)
{
    if (!ensureSceneElementGeneration(sceneElements, totalSceneElements))
    {
        fprintf(stderr, "Unable to allocate space for scene's elements\n");
        return NULL;
    }

    adjustSceneElementWindows(sceneElements, totalSceneElements);
    linkSceneElements(sceneElements, totalSceneElements);

    Scene *scene = createScene(sceneElements, totalSceneElements, sceneUserData);
    if (!scene)
    {
        fprintf(stderr, "Unable to allocate space for scene\n");
        return NULL;
    }

    return scene;
}

void freeSceneElements(SceneElement *sceneElements[], int totalSceneElements)
{
    for (int counter = 0; counter < totalSceneElements; counter++)
        if (sceneElements[counter])
            destroySceneElement(sceneElements[counter]);

    free(sceneElements);
}

static int ensureSceneElementGeneration(SceneElement *sceneElements[], int totalSceneElements)
{
    for (int counter = 0; counter < totalSceneElements; counter++)
    {
        if (!sceneElements[counter])
            return 0;
    }

    return 1;
}

static void adjustSceneElementWindows(SceneElement *sceneElements[], int totalSceneElements)
{
    int maxHeight;
    int maxWidth;
    getmaxyx(stdscr, maxHeight, maxWidth);

    int largestWidth = getLargestSceneElementWidth(sceneElements + 1, totalSceneElements - 1);
    int currentY = SCENE_TOP_Y_PADDING;
    for (int counter = 0; counter < totalSceneElements; counter++)
    {
        SceneElement *currentSceneElement = sceneElements[counter];
        int isTitleSceneElement = (counter == 0);

        int height;
        int width;
        getmaxyx(currentSceneElement->window, height, width);

        if (isTitleSceneElement)
            height = SCENE_TITLE_ELEMENT_HEIGHT;
        else
            width = largestWidth;

        wresize(currentSceneElement->window, height, width);
        mvwin(currentSceneElement->window, currentY, maxWidth/2 - width/2);

        currentY += height;
        if (isTitleSceneElement)
            currentY += SCENE_TITLE_ELEMENT_Y_PADDING;
        else
            currentY += SCENE_SCENE_ELEMENT_Y_PADDING;
    }
}

static int getLargestSceneElementWidth(SceneElement *sceneElements[], int totalSceneElements)
{
    int largestWidth = 0;
    for (int counter = 0; counter < totalSceneElements; counter++)
    {
        int placeHolder;
        int currentWidth;
        getmaxyx(sceneElements[counter]->window, placeHolder, currentWidth);

        if (currentWidth > largestWidth)
            largestWidth = currentWidth;
    }

    return largestWidth;
}

static void linkSceneElements(SceneElement *sceneElements[], int totalSceneElements)
{
    SceneElement *previouslyFocusableSceneElement = NULL;
    SceneElement *currentSceneElement = NULL;

    for (int counter = 0; counter < totalSceneElements; counter++)
    {
        currentSceneElement = sceneElements[counter];

        if (currentSceneElement->focusable)
        {
            if (previouslyFocusableSceneElement)
                previouslyFocusableSceneElement->next = currentSceneElement;
            
            currentSceneElement->previous = previouslyFocusableSceneElement;
            previouslyFocusableSceneElement = currentSceneElement;
        }
    }
}