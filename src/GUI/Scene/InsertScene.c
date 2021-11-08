#include "InsertScene.h"

static void insertButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);
static void backButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);

InsertScene *createInsertScene()
{
    int totalSceneElements = 6;
    SceneElement **sceneElements = malloc(totalSceneElements * sizeof(SceneElement*));
    if (!sceneElements)
    {
        return NULL;
    }
    sceneElements[0] = createTextLabel("Insert Menu", 0);
    sceneElements[1] = createTextInput("Word");
    sceneElements[2] = createTextInput("Definition");
    sceneElements[3] = createTextLabel("Output:\n\n", 1);
    sceneElements[4] = createTextButton("Insert", insertButtonInputHandler);
    sceneElements[5] = createTextButton("Back", backButtonInputHandler);

    SceneElement *insertStatusTextLabel = sceneElements[3];
    wresize(insertStatusTextLabel->window, 12, 32);
    if (!refreshTextBufferTextLabel(insertStatusTextLabel))
    {
        fprintf(stderr, "Unable to allocate space for text label text buffer\n");
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }

    clearTextBufferTextLabel(insertStatusTextLabel);
    appendTextBufferTextLabel(insertStatusTextLabel, "Output:\n\n", 2);

    SceneUserData *sceneUserData = malloc(sizeof(SceneUserData));
    if (!sceneUserData)
    {
        fprintf(stderr, "Unable to allocate space for scene user data\n");
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }
    sceneUserData->ID = INSERT_SCENE;
    
    InsertScene *insertScene = prepareAndGenerateScene(sceneElements, totalSceneElements, sceneUserData);
    if (!insertScene)
    {
        fprintf(stderr, "Unable to prepare or allocate space for insert scene\n");
        free(sceneUserData);
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }

    resetFocusScene(insertScene);

    return insertScene;
}

static void insertButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    clearTextBufferTextLabel(scene->sceneElements[3]);
    appendTextBufferTextLabel(scene->sceneElements[3], "Output:\n\n", 2);
    drawSceneElement(scene->sceneElements[3], scene->focusedSceneElement == scene->sceneElements[3]);
}

static void backButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
    {
        clearTextInput(scene->sceneElements[1]);
        clearTextInput(scene->sceneElements[2]);
        clearTextBufferTextLabel(scene->sceneElements[3]);
        appendTextBufferTextLabel(scene->sceneElements[3], "Output:\n\n", 2);
        setSceneByIDSceneManager(sceneManager, COMMAND_SCENE);
    }
} 