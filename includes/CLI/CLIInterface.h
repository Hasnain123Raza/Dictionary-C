#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include <stdio.h>

#include "Commands.h"
#include "Common.h"
#include "FileUtility.h"

void handleInputCLI(Dictionary *dictionary, APPLICATION_STATE* applicationState);

#endif