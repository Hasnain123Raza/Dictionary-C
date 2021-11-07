#include "SearchScene.h"

static void searchButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);
static void backButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);

SearchScene *createSearchScene()
{
    int totalSceneElements = 6;
    SceneElement **sceneElements = malloc(totalSceneElements * sizeof(SceneElement*));
    if (!sceneElements)
    {
        return NULL;
    }
    sceneElements[0] = createTextLabel("Search Menu", 0);
    sceneElements[1] = createTextInput("Word");
    sceneElements[2] = createTextInput("[Definition Index]");
    sceneElements[3] = createTextLabel("Output:\n\n", 1);
    sceneElements[4] = createTextButton("Search", searchButtonInputHandler);
    sceneElements[5] = createTextButton("Back", backButtonInputHandler);

    SceneElement *searchResultTextLabel = sceneElements[3];
    wresize(searchResultTextLabel->window, 12, 32);

    SceneUserData *sceneUserData = malloc(sizeof(SceneUserData));
    if (!sceneUserData)
    {
        fprintf(stderr, "Unable to allocate space for scene user data\n");
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }
    sceneUserData->ID = SEARCH_SCENE;
    
    SearchScene *searchScene = prepareAndGenerateScene(sceneElements, totalSceneElements, sceneUserData);
    if (!searchScene)
    {
        fprintf(stderr, "Unable to prepare or allocate space for search scene\n");
        free(sceneUserData);
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }

    resetFocusScene(searchScene);

    return searchScene;
}

static void searchButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    setTextTextLabel(scene->sceneElements[3], "Output:\n\nSearch Successful");
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