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
    textLabelUserData->textBuffer = NULL;
    sceneElementUserData->data = textLabelUserData;
    if (!large)
        strncpy(textLabelUserData->text, text, SCENE_ELEMENT_TEXT_LENGTH);    

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

    return textLabel;
}

int refreshTextBufferTextLabel(TextLabel *textLabel)
{
    SceneElementUserData *sceneElementUserData = textLabel->userData;
    TextLabelUserData *textLabelUserData = sceneElementUserData->data;
    if (textLabelUserData->textBuffer)
        free(textLabelUserData->textBuffer);
    
    int textLabelHeight;
    int textLabelWidth;
    getmaxyx(textLabel->window, textLabelHeight, textLabelWidth);
    int textBufferSize = (textLabelHeight - 2) * (textLabelWidth - 4) + 1;

    char *textBuffer = malloc(textBufferSize * sizeof(char));
    if (!textBuffer)
    {
        fprintf(stderr, "Unable to allocate space for text buffer\n");
        return 0;
    }
    memset(textBuffer, '\0', textBufferSize);
    textLabelUserData->textBuffer = textBuffer;

    return 1;
}

void appendTextBufferTextLabel(TextLabel *textLabel, char *text, int maximumLines)
{
    SceneElementUserData *sceneElementUserData = textLabel->userData;
    TextLabelUserData *textLabelUserData = sceneElementUserData->data;
    char *textBuffer = textLabelUserData->textBuffer;

    int textLabelHeight;
    int textLabelWidth;
    getmaxyx(textLabel->window, textLabelHeight, textLabelWidth);

    int lineLength = textLabelWidth - 4;
    int totalLines = textLabelHeight - 2;
    
    int textIndex = 0;
    int bufferIndex = 0;
    int startLine = -1;
    for (int line = 0; line < totalLines; line++)
    {
        if (startLine != -1)
            if (startLine + maximumLines == line)
                break;

        for (int column = 0; column < lineLength; column++)
        {
            char currentCharacter = textBuffer[bufferIndex];
            bufferIndex++;
            if (currentCharacter == '\0')
            {
                if (startLine == -1)
                    startLine = line;
                
                char textCharacter = text[textIndex];
                if (textCharacter == '\0')
                    return;
                
                textBuffer[bufferIndex - 1] = textCharacter;
                textIndex++;

                if (textCharacter == '\n')
                    break;
            }
            else if (currentCharacter == '\n')
                break;
        }
    }
}

void clearTextBufferTextLabel(TextLabel *textLabel)
{
    SceneElementUserData *sceneElementUserData = textLabel->userData;
    TextLabelUserData *textLabelUserData = sceneElementUserData->data;

    int textLabelHeight;
    int textLabelWidth;
    getmaxyx(textLabel->window, textLabelHeight, textLabelWidth);
    int textBufferSize = (textLabelHeight - 2) * (textLabelWidth - 4) + 1;

    memset(textLabelUserData->textBuffer, '\0', textBufferSize);
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
        putStringInWindow(sceneElement->window, textLabelUserData->textBuffer);
}

static void freeUserDataHandler(SceneElement *sceneElement)
{
    SceneElementUserData *sceneElementUserData = sceneElement->userData;
    TextLabelUserData *textLabelUserData = sceneElementUserData->data;
    if (textLabelUserData->large && textLabelUserData->textBuffer)
        free(textLabelUserData->textBuffer);
    
    sceneElementFreeUserDataHandler(sceneElement);
}