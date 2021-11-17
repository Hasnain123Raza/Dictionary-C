#include "InsertScene.h"

static void wordTextInputChangedCallback(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement);
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
    sceneElements[1] = createTextInput("Word", wordTextInputChangedCallback);
    sceneElements[2] = createTextInput("Definition", NULL);
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

static void insertButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    Dictionary **dictionary = sceneManager->userData;

    TextInput *wordTextInput = scene->sceneElements[1];
    SceneElementUserData *wordTextSceneElementUserData = wordTextInput->userData;
    TextInputUserData *wordTextInputUserData = wordTextSceneElementUserData->data;
    char *word = wordTextInputUserData->input;

    TextInput *definitionTextInput = scene->sceneElements[2];
    SceneElementUserData *definitionTextInputSceneElementUserData = definitionTextInput->userData;
    TextInputUserData *definitionTextInputData = definitionTextInputSceneElementUserData->data;
    char *definition = definitionTextInputData->input;

    if (strlen(word) != 0 && strlen(definition) != 0)
    {
        if (searchWordDictionary(*dictionary, word))
            insertDefinitionDictionary(*dictionary, word, createDefinition(definition));
        else
            insertWordDictionary(*dictionary, word, createDefinitions(createDefinition(definition)));
    }

    clearTextBufferTextLabel(scene->sceneElements[3]);
    appendTextBufferTextLabel(scene->sceneElements[3], "Successfully Inserted\n", 1);
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
        appendTextBufferTextLabel(scene->sceneElements[3], "Output\n", 2);
        setSceneByIDSceneManager(sceneManager, COMMAND_SCENE);
    }
} 