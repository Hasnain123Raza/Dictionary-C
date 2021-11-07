#include <stdio.h>

#include "Initializer.h"
#include "CLIInterface.h"
#include "Common.h"

int main(int argc, char *argv[])
{
    Dictionary *dictionary = initialize(argc, argv);
    if (!dictionary)
    {
        exit(EXIT_FAILURE);
    }

    APPLICATION_STATE state = { MODE_CLI, 0 };

    while (!state.done)
    {
        if (state.mode == MODE_CLI)
        {
            handleInputCLI(dictionary, &state);
        }
    }

    destroyDictionary(dictionary);

    exit(EXIT_SUCCESS);
}