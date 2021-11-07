#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SceneElementConfigurations.h"
#include "SceneElementUtilities.h"

#include "Scene.h"
#include "SceneElement.h"

typedef SceneElement TextButton;

typedef struct {
    char text[SCENE_ELEMENT_TEXT_LENGTH + 1];
} TextButtonUserData;

TextButton *createTextButton(char *text, void *inputHandler);

#endif