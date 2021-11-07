#include "StartScene.h"

static void startButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);
static void CLIButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);
static void helpButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);
static void quitButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);

StartScene *createStartScene()
{
    int totalSceneElements = 5;
    SceneElement **sceneElements = malloc(totalSceneElements * sizeof(SceneElement*));
    if (!sceneElements)
    {
        return NULL;
    }
    sceneElements[0] = createTextLabel("Dictionary Menu", 0);
    sceneElements[1] = createTextButton("Command", startButtonInputHandler);
    sceneElements[2] = createTextButton("CLI", CLIButtonInputHandler);
    sceneElements[3] = createTextButton("Help", helpButtonInputHandler);
    sceneElements[4] = createTextButton("Quit", quitButtonInputHandler);

    SceneUserData *sceneUserData = malloc(sizeof(SceneUserData));
    if (!sceneUserData)
    {
        fprintf(stderr, "Unable to allocate space for scene user data\n");
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }
    sceneUserData->ID = START_SCENE;
    
    StartScene *startScene = prepareAndGenerateScene(sceneElements, totalSceneElements, sceneUserData);
    if (!startScene)
    {
        fprintf(stderr, "Unable to prepare or allocate space for start scene\n");
        free(sceneUserData);
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }

    resetFocusScene(startScene);

    return startScene;
}

static void startButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
        setSceneByIDSceneManager(sceneManager, COMMAND_SCENE);
}

static void CLIButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
        sceneManager->paused = 1;
}

static void helpButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
        setSceneByIDSceneManager(sceneManager, HELP_SCENE);
}

static void quitButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
        sceneManager->done = 1;
}