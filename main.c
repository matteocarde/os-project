#include <stdio.h>
#include <string.h>
#include "utilities/utilities.h"
#include "libs/csvparser.h"

int main(int argc, char **argv) {


    settings argsSettings;
    argsSettings = getArgsSettings(argc, argv);

    printf("Path preemption %s\nPath nopreemption %s\nPath input %s\n", argsSettings.preemptionPath,
           argsSettings.noPreemptionPath, argsSettings.inputPath);

    CsvParser *preemptionParser = CsvParser_new(argsSettings.inputPath, ",", 0);
    CsvRow *row;


    //TODO: Check if file exists !!!

    do {
        row = CsvParser_getRow(preemptionParser);
        if (row == NULL) {
            break;
        }

        char **rowFields = CsvParser_getFields(row);
        printf("%s,%s,%s\n", rowFields[0], rowFields[1], rowFields[2]);
        CsvParser_destroy_row(row);
    }while (row);

    CsvParser_destroy(preemptionParser);

}