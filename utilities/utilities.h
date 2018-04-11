//
// Created by Matteo Cardellini on 11/04/18.
//

#ifndef OS_PROJECT_UTILITIES_H
#define OS_PROJECT_UTILITIES_H

typedef struct {
    char *preemptionPath;
    char *noPreemptionPath;
    char *inputPath;
    int isHelp;
} settings;

settings getArgsSettings(int argc, char **argv);

#endif //OS_PROJECT_UTILITIES_H
