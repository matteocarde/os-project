#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv) {

    const char *const short_options = "ho:i:np";

    /* An array describing valid long options. */
    const struct option long_options[] = {
            {"help",    0, NULL, 'h'},
            {"output",  2, NULL, 'o'},
            {"output-preemption", 1, NULL, 'p'},
            {"output-no-preemption", 1, NULL, 'n'},
            {"input", 1, NULL, 'i'},
            {NULL,      0, NULL, 0}
    };

    return 0;
}