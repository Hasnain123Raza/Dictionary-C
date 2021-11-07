#include "TextButton.h"

static void drawHandler(SceneElement *sceneElement, int focused);

TextButton *createTextButton(char *text, void *inputHandler)
{
    SceneElementUserData *sceneElementUserData = malloc(sizeof(SceneElementUserData));
    if (!sceneElementUserData)
    {
        fprintf(stderr, "Unable to allocate space for scene element user data\n");
        return NULL;
    }
    sceneElementUserData->ID = TEXT_BUTTON_SCENE_ELEMENT;

    TextButtonUserData *textButtonUserData = malloc(sizeof(TextButtonUserData));
    if (!textButtonUserData)
    {
        fprintf(stderr, "Unable to allocate space for text button user data\n");
        free(sceneElementUserData);
        return NULL;
    }
    strncpy(textButtonUserData->text, text, SCENE_ELEMENT_TEXT_LENGTH);
    sceneElementUserData->data = textButtonUserData;

    int height = SCENE_ELEMENT_HEIGHT;
    int width = SCENE_ELEMENT_TEXT_X_PADDING + strlen(text) + SCENE_ELEMENT_TEXT_X_PADDING;
    int y = 0;
    int x = 0;
    int focusable = 1;
    TextButton *textButton = createSceneElement(height, width, y, x, focusable, drawHandler, inputHandler, sceneElementUserData, sceneElementFreeUserDataHandler);
    if (!textButton)
    {
        fprintf(stderr, "Unable to allocate space for text button\n");
        free(textButtonUserData);
        free(sceneElementUserData);
        return NULL;
    }

    return textButton;
}

static void drawHandler(SceneElement *sceneElement, int focused)
{
    SceneElementUserData *sceneElementUserData = sceneElement->userData;
    TextButtonUserData *textButtonUserData = sceneElementUserData->data;

    if (focused)
    {
        wattrset(sceneElement->window, A_STANDOUT);
        box(sceneElement->window, 0, 0);
        applyAttributes(sceneElement->window, A_STANDOUT);
        putStringInCenter(sceneElement->window, textButtonUserData->text);
    }
    else
    {
        wattrset(sceneElement->window, A_NORMAL);
        box(sceneElement->window, 0, 0);
        applyAttributes(sceneElement->window, A_NORMAL);
        putStringInCenter(sceneElement->window, textButtonUserData->text);
    }
}