#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SceneElementConfigurations.h"
#include "SceneElementUtilities.h"

#include "Scene.h"
#include "SceneElement.h"

typedef SceneElement TextInput;

typedef struct {
    char placeholder[SCENE_ELEMENT_TEXT_LENGTH + 1];
    char input[SCENE_ELEMENT_INPUT_TEXT_LENGTH + 1];
} TextInputUserData;

TextInput *createTextInput(char *placeholder);
void clearTextInput(TextInput *textInput);

#endif