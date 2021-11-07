#include "TextInput.h"

static void drawHandler(SceneElement *sceneElement, int focused);
static void inputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input);

TextInput *createTextInput(char *placeholder)
{
    SceneElementUserData *sceneElementUserData = malloc(sizeof(SceneElementUserData));
    if (!sceneElementUserData)
    {
        fprintf(stderr, "Unable to allocate space for scene element user data\n");
        return NULL;
    }
    sceneElementUserData->ID = TEXT_INPUT_SCENE_ELEMENT;

    TextInputUserData *textInputUserData = malloc(sizeof(TextInputUserData));
    if (!textInputUserData)
    {
        fprintf(stderr, "Unable to allocate space for text input user data\n");
        free(sceneElementUserData);
        return NULL;
    }
    strncpy(textInputUserData->placeholder, placeholder, SCENE_ELEMENT_TEXT_LENGTH);
    textInputUserData->input[0] = '\0';
    sceneElementUserData->data = textInputUserData;

    int height = SCENE_ELEMENT_HEIGHT;
    int width = SCENE_ELEMENT_TEXT_X_PADDING + strlen(placeholder) + SCENE_ELEMENT_TEXT_X_PADDING;
    int y = 0;
    int x = 0;
    int focusable = 1;
    TextInput *textInput = createSceneElement(height, width, y, x, focusable, drawHandler, inputHandler, sceneElementUserData, sceneElementFreeUserDataHandler);
    if (!textInput)
    {
        fprintf(stderr, "Unable to allocate space for text input\n");
        free(textInputUserData);
        free(sceneElementUserData);
        return NULL;
    }

    return textInput;
}

void clearTextInput(TextInput *textInput)
{
    SceneElementUserData *sceneElementUserData = textInput->userData;
    TextInputUserData *textInputUserData = sceneElementUserData->data;
    textInputUserData->input[0] = '\0';
}

static void drawHandler(SceneElement *sceneElement, int focused)
{
    SceneElementUserData *sceneElementUserData = sceneElement->userData;
    TextInputUserData *textInputUserData = sceneElementUserData->data;

    int inputLength = strlen(textInputUserData->input);
    char *text = textInputUserData->placeholder;
    if (inputLength > 0)
        text = textInputUserData->input;

    if (focused)
    {
        wattrset(sceneElement->window, A_STANDOUT);
        box(sceneElement->window, 0, 0);
        applyAttributes(sceneElement->window, A_STANDOUT);
        putInputInWindow(sceneElement->window, text);
    }
    else
    {
        wattrset(sceneElement->window, A_NORMAL);
        box(sceneElement->window, 0, 0);
        applyAttributes(sceneElement->window, A_NORMAL);
        putInputInWindow(sceneElement->window, text);
    }
}

static void inputHandler(SceneManager *sceneManager, Scene *scene, SceneElement *sceneElement, int input)
{
    SceneElementUserData *sceneElementUserData = sceneElement->userData;
    TextInputUserData *textInputUserData = sceneElementUserData->data;

    int inputLength = strlen(textInputUserData->input);

    switch (input)
    {
        case KEY_BACKSPACE:
        {
            if (inputLength > 0)
                textInputUserData->input[inputLength - 1] = '\0';
            break;
        }

        default:
        {
            if (inputLength < SCENE_ELEMENT_INPUT_TEXT_LENGTH + 1)
            {
                textInputUserData->input[inputLength] = input;
                textInputUserData->input[inputLength + 1] = '\0';
            }
            break;
        }
    }

    clearSceneElement(sceneElement);
    drawSceneElement(sceneElement, 1);
}