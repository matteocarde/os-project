//
// Created by Matteo Cardellini on 11/04/18.
//

#include <stdbool.h>
#include <ntsid.h>
#include "../structures/TaskList.h"

#ifndef OS_PROJECT_UTILITIES_H
#define OS_PROJECT_UTILITIES_H

typedef struct {
    char *preemptionPath;
    char *noPreemptionPath;
    FILE* preemptionFile;
    FILE* noPreemptionFile;
    char *inputPath;
    int isHelp;
} programArgs_t;

typedef struct {
    programArgs_t programArgs;
    bool isPreemptive;
    TaskList* taskList;
    int threadId;
    pthread_mutex_t* mutex;
} threadArgs_t;

programArgs_t getArgsSettings(int argc, char **argv);

TaskList *getTaskListFromCSV(char *inputFile);

#endif //OS_PROJECT_UTILITIES_H
