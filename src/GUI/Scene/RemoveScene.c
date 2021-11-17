#include "RemoveScene.h"

static void wordTextInputChangedCallback(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement);
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
    sceneElements[1] = createTextInput("Word", wordTextInputChangedCallback);
    sceneElements[2] = createTextInput("[Definition Index]", NULL);
    sceneElements[3] = createTextLabel("Output:\n\n", 1);
    sceneElements[4] = createTextButton("Remove", removeButtonInputHandler);
    sceneElements[5] = createTextButton("Back", backButtonInputHandler);

    SceneElement *removeStatusTextLabel = sceneElements[3];
    wresize(removeStatusTextLabel->window, 12, 32);
    if (!refreshTextBufferTextLabel(removeStatusTextLabel))
    {
        fprintf(stderr, "Unable to allocate space for text label text buffer\n");
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }

    clearTextBufferTextLabel(removeStatusTextLabel);
    appendTextBufferTextLabel(removeStatusTextLabel, "Output:\n\n", 2);

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

static void wordTextInputChangedCallback(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement)
{
    Dictionary **dictionary = sceneManager->userData;

    TextInput *wordTextInput = scene->sceneElements[1];
    SceneElementUserData *wordTextSceneElementUserData = wordTextInput->userData;
    TextInputUserData *wordTextInputUserData = wordTextSceneElementUserData->data;
    char *word = wordTextInputUserData->input;

    int totalMatches = 0;
    char *words[8];
    if (strlen(word) > 0)
        totalMatches = getMatchesDictionary(*dictionary, word, words, 8);
    
    if (totalMatches == 0)
    {
        clearTextBufferTextLabel(scene->sceneElements[3]);
        appendTextBufferTextLabel(scene->sceneElements[3], "No matches found\n", 1);
    }
    else
    {
        clearTextBufferTextLabel(scene->sceneElements[3]);
        appendTextBufferTextLabel(scene->sceneElements[3], "Matches:\n", 1);
        for (int i = 0; i < totalMatches; i++)
        {
            char buffer[strlen(words[i]) + 1];
            strcpy(buffer, words[i]);
            buffer[strlen(words[i])] = '\n';
            appendTextBufferTextLabel(scene->sceneElements[3], buffer, 1);
        }
    }

    clearSceneElement(scene->sceneElements[3]);
    drawSceneElement(scene->sceneElements[3], scene->focusedSceneElement == scene->sceneElements[3]);
}

static void removeButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    Dictionary **dictionary = sceneManager->userData;

    TextInput *wordTextInput = scene->sceneElements[1];
    SceneElementUserData *wordTextSceneElementUserData = wordTextInput->userData;
    TextInputUserData *wordTextInputData = wordTextSceneElementUserData->data;
    char *word = wordTextInputData->input;

    TextInput *definitionIndexTextInput = scene->sceneElements[2];
    SceneElementUserData *definitionIndexTextInputSceneElementUserData = definitionIndexTextInput->userData;
    TextInputUserData *definitionIndexTextInputData = definitionIndexTextInputSceneElementUserData->data;
    char *definitionIndex = definitionIndexTextInputData->input;

    if (strlen(word) != 0)
    {
        if (strlen(definitionIndex) == 0)
        {
            *dictionary = removeWordDictionary(*dictionary, word);
        }
        else
        {
            *dictionary = removeDefinitionDictionary(*dictionary, word, atoi(definitionIndex) - 1);
        }
    }

    clearTextBufferTextLabel(scene->sceneElements[3]);
    appendTextBufferTextLabel(scene->sceneElements[3], "Removed Successfully\n", 1);
    clearSceneElement(scene->sceneElements[3]);
    drawSceneElement(scene->sceneElements[3], scene->focusedSceneElement == scene->sceneElements[3]);
}

static void backButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    if (input == 10)
    {
        clearTextInput(scene->sceneElements[1]);
        clearTextInput(scene->sceneElements[2]);
        clearTextBufferTextLabel(scene->sceneElements[3]);
        appendTextBufferTextLabel(scene->sceneElements[3], "Output\n", 1);
        setSceneByIDSceneManager(sceneManager, COMMAND_SCENE);
    }
}