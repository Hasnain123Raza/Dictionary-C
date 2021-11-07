#include "SceneElementUtilities.h"

void sceneElementFreeUserDataHandler(SceneElement *sceneElement)
{
    if (sceneElement->userData)
    {
        SceneElementUserData *sceneElementUserData = sceneElement->userData;
        free(sceneElementUserData->data);
        free(sceneElementUserData);
    }
}

void putStringInCenter(WINDOW *window, char *string)
{
    int height, width;
    getmaxyx(window, height, width);

    mvwaddstr(window, height/2, width/2 - strlen(string)/2, string);
}

void putStringInWindow(WINDOW *window, char *string)
{
    int height, width;
    getmaxyx(window, height, width);

    int index = 0;
    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 2; x < width - 2; x++)
        {
            char currentCharacter = string[index];
            index++;
            if (currentCharacter == '\0')
                return;
            if (currentCharacter == '\n')
                break;
            
            mvwaddch(window, y, x, currentCharacter);
        }
    }
}

void putInputInWindow(WINDOW *window, char *input)
{
    int height, width;
    getmaxyx(window, height, width);

    int index = 0;
    int inputLength = strlen(input);
    if (inputLength > width - 4)    // border and padding
        index = inputLength - (width - 4);
    
    int finished = 0;
    
    wattron(window, A_UNDERLINE);
    for (int x = 2; x < width - 2; x++)
    {
        char currentCharacter = ' ';
        if (!finished)
        {
            currentCharacter = input[index];
            if (currentCharacter == '\0')
            {
                currentCharacter = ' ';
                finished = 1;
            }
            index++;
        }
        
        mvwaddch(window, height/2, x, currentCharacter);
    }
    wattroff(window, A_UNDERLINE);
}

void applyAttributes(WINDOW *window, int attributes)
{
    int height, width;
    getmaxyx(window, height, width);

    for (int row = 1; row < height - 1; row++)
        mvwchgat(window, row, 1, width - 2, attributes, 0, NULL);
}