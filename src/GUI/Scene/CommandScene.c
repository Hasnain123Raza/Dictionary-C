#include "CommandScene.h"

static void insertButtonHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);
static void searchButtonHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);
static void removeButtonHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);
static void backButtonHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);

CommandScene *createCommandScene()
{
    int totalSceneElements = 5;
    SceneElement **sceneElements = malloc(totalSceneElements * sizeof(SceneElement*));
    if (!sceneElements)
    {
        return NULL;
    }
    sceneElements[0] = createTextLabel("Command Menu", 0);
    sceneElements[1] = createTextButton("Insert", insertButtonHandler);
    sceneElements[2] = createTextButton("Search", searchButtonHandler);
    sceneElements[3] = createTextButton("Remove", removeButtonHandler);
    sceneElements[4] = createTextButton("Back", backButtonHandler);

    SceneUserData *sceneUserData = malloc(sizeof(SceneUserData));
    if (!sceneUserData)
    {
        fprintf(stderr, "Unable to allocate space for scene user data\n");
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }
    sceneUserData->ID = COMMAND_SCENE;
    
    CommandScene *commandScene = prepareAndGenerateScene(sceneElements, totalSceneElements, sceneUserData);
    if (!commandScene)
    {
        fprintf(stderr, "Unable to prepare or allocate space for command scene\n");
        free(sceneUserData);
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }

    resetFocusScene(commandScene);

    return commandScene;
}

static void insertButtonHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
        setSceneByIDSceneManager(sceneManager, INSERT_SCENE);
}

static void searchButtonHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
        setSceneByIDSceneManager(sceneManager, SEARCH_SCENE);
}

static void removeButtonHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
        setSceneByIDSceneManager(sceneManager, REMOVE_SCENE);
}

static void backButtonHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
        setSceneByIDSceneManager(sceneManager, START_SCENE);
}