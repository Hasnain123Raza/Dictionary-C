#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SceneElementConfigurations.h"
#include "SceneElementUtilities.h"

#include "Scene.h"
#include "SceneElement.h"

typedef SceneElement TextLabel;

typedef struct {
    int large;
    char text[SCENE_ELEMENT_TEXT_LENGTH + 1];
    char *textBuffer;
} TextLabelUserData;

TextLabel *createTextLabel(char *text, int large);
int refreshTextBufferTextLabel(TextLabel *textLabel);
void appendTextBufferTextLabel(TextLabel *textLabel, char *text, int maximumLines);
void clearTextBufferTextLabel(TextLabel *textLabel);

#endif