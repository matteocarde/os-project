#include <stdio.h>
#include "utilities/utilities.h"

int main(int argc, char **argv) {


    settings argsSettings;
    argsSettings = getArgsSettings(argc, argv);

    printf("Path preemption %s\nPath nopreemption %s\nPath input %s\n", argsSettings.preemptionPath, argsSettings.noPreemptionPath, argsSettings.inputPath);

    

}