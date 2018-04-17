#include <stdio.h>
#include "utilities/utilities.h"
#include "libs/csvparser.h"

int main(int argc, char **argv) {


    settings argsSettings;
    argsSettings = getArgsSettings(argc, argv);

    printf("Path preemption %s\nPath nopreemption %s\nPath input %s\n", argsSettings.preemptionPath,
           argsSettings.noPreemptionPath, argsSettings.inputPath);

    CsvParser *preemptionParser = CsvParser_new(argsSettings.preemptionPath, ",", 0);
    CsvRow *row;
    CsvRow *header;
    row = CsvParser_getRow(preemptionParser);
    if (row == NULL) {
        printf("%s\n", CsvParser_getErrorMessage(preemptionParser));
        return 1;
    }

    while ((row = CsvParser_getRow(preemptionParser))) {
        printf("NEW LINE:\n");
        char **rowFields = CsvParser_getFields(row);
        for (int i = 0; i < CsvParser_getNumFields(row); i++) {
            printf("FIELD: %s\n", rowFields[i]);
        }
        CsvParser_destroy_row(row);
    }
    CsvParser_destroy(preemptionParser);

}