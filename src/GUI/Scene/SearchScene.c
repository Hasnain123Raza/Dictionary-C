#include "SearchScene.h"

static void wordTextInputChangedCallback(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement);
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
    sceneElements[1] = createTextInput("Word", wordTextInputChangedCallback);
    sceneElements[2] = createTextInput("[Definition Index]", NULL);
    sceneElements[3] = createTextLabel("Search Results:\n\n", 1);
    sceneElements[4] = createTextButton("Search", searchButtonInputHandler);
    sceneElements[5] = createTextButton("Back", backButtonInputHandler);

    SceneElement *searchResultTextLabel = sceneElements[3];
    wresize(searchResultTextLabel->window, 12, 32);
    if (!refreshTextBufferTextLabel(searchResultTextLabel))
    {
        fprintf(stderr, "Unable to allocate space for text label text buffer\n");
        freeSceneElements(sceneElements, totalSceneElements);
        return NULL;
    }

    clearTextBufferTextLabel(searchResultTextLabel);
    appendTextBufferTextLabel(searchResultTextLabel, "Search Results:\n\n", 2);

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

static void searchButtonInputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    Dictionary **dictionary = sceneManager->userData;
    
    TextInput *wordTextInput = scene->sceneElements[1];
    SceneElementUserData *wordTextInputSceneElementUserData = wordTextInput->userData;
    TextInputUserData *wordTextInputData = wordTextInputSceneElementUserData->data;
    char *word = wordTextInputData->input;

    TextInput *definitionIndexTextInput = scene->sceneElements[2];
    SceneElementUserData *definitionIndexTextInputSceneElementUserData = definitionIndexTextInput->userData;
    TextInputUserData *definitionIndexTextInputData = definitionIndexTextInputSceneElementUserData->data;
    char *definitionIndex = definitionIndexTextInputData->input;

    TextLabel *searchResultTextLabel = scene->sceneElements[3];

    Definition *definition = NULL;
    Definitions *definitions = NULL;

    if (strlen(word) > 0)
    {
        if (strlen(definitionIndex) > 0)
        {
            definition = searchDefinitionDictionary(*dictionary, word, atoi(definitionIndex) - 1);
        }
        else
        {
            definitions = searchWordDictionary(*dictionary, word);
        }
    }

    clearTextBufferTextLabel(searchResultTextLabel);
    appendTextBufferTextLabel(searchResultTextLabel, "Search Results:\n\n", 2);

    if (definition)
    {
        char textToAppend[definition->length + 4];
        memset(textToAppend, 0, definition->length + 4);
        sprintf(textToAppend, "> %s\n", definition->value);
        appendTextBufferTextLabel(searchResultTextLabel, textToAppend, 100);
    }
    else if (definitions)
    {
        while (definitions)
        {
            char textToAppend[definitions->definition->length + 4];
            memset(textToAppend, 0, definitions->definition->length + 4);
            sprintf(textToAppend, "> %s\n", definitions->definition->value);
            appendTextBufferTextLabel(searchResultTextLabel, textToAppend, 2);
            definitions = definitions->next;
        }
    }

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
        appendTextBufferTextLabel(scene->sceneElements[3], "Search Results:\n\n", 2);
        setSceneByIDSceneManager(sceneManager, COMMAND_SCENE);
    }
}