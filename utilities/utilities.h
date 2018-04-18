//
// Created by Matteo Cardellini on 11/04/18.
//

#include "../structures/TaskList.h"

#ifndef OS_PROJECT_UTILITIES_H
#define OS_PROJECT_UTILITIES_H

typedef struct {
    char *preemptionPath;
    char *noPreemptionPath;
    char *inputPath;
    int isHelp;
} settings;

settings getArgsSettings(int argc, char **argv);

TaskList *getTaskListFromCSV(char *inputFile);

#endif //OS_PROJECT_UTILITIES_H
