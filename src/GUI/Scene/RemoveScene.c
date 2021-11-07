#include "RemoveScene.h"

static void removeButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);
static void backButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);

RemoveScene *createRemoveScene()
{
    int totalSceneElements = 6;
    SceneElement **sceneElements = malloc(totalSceneElements * sizeof(SceneElement*));
    if (!sceneElements)
    {
        return NULL;
    }
    sceneElements[0] = createTextLabel("Remove Menu", 0);
    sceneElements[1] = createTextInput("Word");
    sceneElements[2] = createTextInput("[Definition Index]");
    sceneElements[3] = createTextLabel("Output:\n\n", 1);
    sceneElements[4] = createTextButton("Remove", removeButtonInputHandler);
    sceneElements[5] = createTextButton("Back", backButtonInputHandler);

    SceneElement *removeStatusTextLabel = sceneElements[3];
    wresize(removeStatusTextLabel->window, 12, 32);

    SceneUserData *sceneUserData = malloc(sizeof(SceneUserData));
    if (!sceneUserData)
    {
        fprintf(stderr, "Unable to allocate space for scene user data\n");
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }
    sceneUserData->ID = REMOVE_SCENE;
    
    RemoveScene *removeScene = prepareAndGenerateScene(sceneElements, totalSceneElements, sceneUserData);
    if (!removeScene)
    {
        fprintf(stderr, "Unable to prepare or allocate space for remove scene\n");
        free(sceneUserData);
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }

    resetFocusScene(removeScene);

    return removeScene;
}

static void removeButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    setTextTextLabel(scene->sceneElements[3], "Output:\n\nRemove Successful");
    drawSceneElement(scene->sceneElements[3], scene->focusedSceneElement == scene->sceneElements[3]);
}

static void backButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
    {
        clearTextInput(scene->sceneElements[1]);
        clearTextInput(scene->sceneElements[2]);
        setTextTextLabel(scene->sceneElements[3], "Output:\n\n");
        setSceneByIDSceneManager(sceneManager, COMMAND_SCENE);
    }
}