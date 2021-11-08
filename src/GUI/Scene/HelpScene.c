#include "HelpScene.h"

static void backButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);

HelpScene *createHelpScene()
{
    char helpText[] = "This is a dictionary program.\n\n"
    "To interact with the dictionary, please navigate to the Command menu by selecting the command button.\n"
    "You can interact with the dictionary by inserting, searching, or removing words.\n\n"
    "You can use the CLI button to continue the program in command line interface mode";

    int totalSceneElements = 3;
    SceneElement **sceneElements = malloc(totalSceneElements * sizeof(SceneElement*));
    if (!sceneElements)
    {
        return NULL;
    }
    sceneElements[0] = createTextLabel("Help Menu", 0);
    sceneElements[1] = createTextLabel(helpText, 1);
    sceneElements[2] = createTextButton("Back", backButtonInputHandler);

    SceneElement *helpTextLabel = sceneElements[1];
    wresize(helpTextLabel->window, 16, 48);
    if (!refreshTextBufferTextLabel(helpTextLabel))
    {
        fprintf(stderr, "Unable to allocate space for text label text buffer\n");
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }

    clearTextBufferTextLabel(helpTextLabel);
    appendTextBufferTextLabel(helpTextLabel, helpText, 100);

    SceneUserData *sceneUserData = malloc(sizeof(SceneUserData));
    if (!sceneUserData)
    {
        fprintf(stderr, "Unable to allocate space for scene user data\n");
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }
    sceneUserData->ID = HELP_SCENE;
    
    HelpScene *helpScene = prepareAndGenerateScene(sceneElements, totalSceneElements, sceneUserData);
    if (!helpScene)
    {
        fprintf(stderr, "Unable to prepare or allocate space for help scene\n");
        free(sceneUserData);
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }

    resetFocusScene(helpScene);

    return helpScene;
}

static void backButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
        setSceneByIDSceneManager(sceneManager, START_SCENE);
}