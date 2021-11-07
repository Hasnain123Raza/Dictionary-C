#include "TextLabel.h"

static void drawHandler(SceneElement *sceneElement, int focused);
static void freeUserDataHandler(SceneElement *sceneElement);

TextLabel *createTextLabel(char *text, int large)
{
    SceneElementUserData *sceneElementUserData = malloc(sizeof(SceneElementUserData));
    if (!sceneElementUserData)
    {
        fprintf(stderr, "Unable to allocate space for scene element user data\n");
        return NULL;
    }
    sceneElementUserData->ID = TEXT_LABEL_SCENE_ELEMENT;

    TextLabelUserData *textLabelUserData = malloc(sizeof(TextLabelUserData));
    if (!textLabelUserData)
    {
        fprintf(stderr, "Unable to allocate space for text label user data\n");
        free(sceneElementUserData);
        return NULL;
    }
    textLabelUserData->large = large;
    textLabelUserData->largeText = NULL;
    sceneElementUserData->data = textLabelUserData;

    int height = SCENE_ELEMENT_HEIGHT;
    int width = SCENE_ELEMENT_TEXT_X_PADDING + strlen(text) + SCENE_ELEMENT_TEXT_X_PADDING;
    int y = 0;
    int x = 0;
    int focusable = 0;
    TextLabel *textLabel = createSceneElement(height, width, y, x, focusable, drawHandler, NULL, sceneElementUserData, freeUserDataHandler);
    if (!textLabel)
    {
        fprintf(stderr, "Unable to allocate space for text label\n");
        free(textLabelUserData);
        free(sceneElementUserData);
        return NULL;
    }

    setTextTextLabel(textLabel, text);
    return textLabel;
}

void setTextTextLabel(TextLabel *textLabel, char *text)
{
    SceneElementUserData *sceneElementUserData = textLabel->userData;
    TextLabelUserData *textLabelUserData = sceneElementUserData->data;
    if (textLabelUserData->large)
    {
        if (textLabelUserData->largeText)
            free(textLabelUserData->largeText);
        
        int textSize = strlen(text) + 1;
        char *largeText = malloc(textSize * sizeof(char));
        strncpy(largeText, text, textSize);
        textLabelUserData->largeText = largeText;
    }
    else
    {
        strncpy(textLabelUserData->text, text, SCENE_ELEMENT_TEXT_LENGTH);
    }
}

static void drawHandler(SceneElement *sceneElement, int focused)
{
    wattrset(sceneElement->window, A_NORMAL);
    box(sceneElement->window, 0, 0);
    applyAttributes(sceneElement->window, A_NORMAL);
    SceneElementUserData *sceneElementUserData = sceneElement->userData;
    TextLabelUserData *textLabelUserData = sceneElementUserData->data;
    if (!textLabelUserData->large)
        putStringInCenter(sceneElement->window, textLabelUserData->text);
    else
        putStringInWindow(sceneElement->window, textLabelUserData->largeText);
}

static void freeUserDataHandler(SceneElement *sceneElement)
{
    SceneElementUserData *sceneElementUserData = sceneElement->userData;
    TextLabelUserData *textLabelUserData = sceneElementUserData->data;
    if (textLabelUserData->large)
        free(textLabelUserData->largeText);
    
    sceneElementFreeUserDataHandler(sceneElement);
}