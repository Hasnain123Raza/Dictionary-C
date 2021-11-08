#ifndef CORE_H
#define CORE_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct SceneElement {
    WINDOW *window;
    int focusable;
    struct SceneElement *previous;
    struct SceneElement *next;
    void *drawHandler;
    void *inputHandler;
    void *userData;
    void *freeUserDataHandler;
} SceneElement;

typedef struct {
    SceneElement **sceneElements;
    int totalSceneElements;
    SceneElement *focusedSceneElement;
    void *userData;
} Scene;

typedef struct {
    Scene **scenes;
    Scene *currentScene;
    int totalScenes;
    int paused;
    int done;
    void *userData;
} SceneManager;

typedef void (*SceneElementDrawHandler)(SceneElement*, int);
typedef void (*SceneElementInputHandler)(SceneManager*, Scene*, SceneElement*, int);
typedef void (*SceneElementFreeUserDataHandler)(SceneElement*);

#endif