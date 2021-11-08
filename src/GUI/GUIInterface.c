#include "GUIInterface.h"

static SceneManager *sceneManager = NULL;

static int ensureSceneGeneration(Scene *scenes[], int totalScenes);
static void freeScenes(Scene *scenes[], int totalScenes);

void handleInputGUI(Dictionary *dictionary, APPLICATION_STATE* applicationState)
{
    if (!sceneManager)
    {
        sceneManager = initializeSceneManager();
        if (!sceneManager)
        {
            fprintf(stderr, "Unable to initialize scene manager\n");
            applicationState->mode = MODE_CLI;
            return;
        }
        sceneManager->userData = dictionary;
    }

    if (sceneManager->paused)
    {
        resumeGUI();
        sceneManager->paused = 0;
    }

    int input = getch();
    if (input == KEY_F(1))
    {
        sceneManager->done = 1;
    }
    else
    {
        handleInputSceneManager(sceneManager, input);
    }

    if (sceneManager->done)
    {
        applicationState->done = 1;
        terminateGUI();
    }
    else if (sceneManager->paused)
    {
        applicationState->mode = MODE_CLI;
        pauseGUI();
    }
}

SceneManager *initializeSceneManager()
{
    initscr();
    raw();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    refresh();

    int totalScenes = 6;
    Scene **scenes = malloc(totalScenes * sizeof(Scene*));
    if (!scenes)
    {
        return NULL;
    }
    scenes[0] = createStartScene();
    scenes[1] = createCommandScene();
    scenes[2] = createHelpScene();
    scenes[3] = createInsertScene();
    scenes[4] = createSearchScene();
    scenes[5] = createRemoveScene();

    if (!ensureSceneGeneration(scenes, totalScenes))
    {
        fprintf(stderr, "Unable to allocate space for scenes\n");
        freeScenes(scenes, totalScenes);
        return NULL;
    }

    SceneManager *sceneManager = createSceneManager(scenes, totalScenes);
    if (!sceneManager)
    {
        fprintf(stderr, "Unable to allocate space for scene manager\n");
        freeScenes(scenes, totalScenes);
        return NULL;
    }

    setSceneSceneManager(sceneManager, sceneManager->scenes[0]);

    return sceneManager;
}

void pauseGUI()
{
    def_prog_mode();
    endwin();
}

void resumeGUI()
{
    reset_prog_mode();
    refresh();
}

void terminateGUI()
{
    if (sceneManager)
    {
        destroySceneManager(sceneManager);
        endwin();
        sceneManager = NULL;
    }
}

static int ensureSceneGeneration(Scene *scenes[], int totalScenes)
{
    for (int counter = 0; counter < totalScenes; counter++)
    {
        if (!scenes[counter])
            return 0;
    }

    return 1;
}

static void freeScenes(Scene *scenes[], int totalScenes)
{
    for (int counter = 0; counter < totalScenes; counter++)
        if (scenes[counter])
            destroyScene(scenes[counter]);

    free(scenes);
}