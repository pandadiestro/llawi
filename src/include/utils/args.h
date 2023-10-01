#include <string.h>

typedef struct {
    char io_style;
} OPT;

OPT parseArgs(int argsNum, char* argsList[]);

OPT
parseArgs(int argsNum, char* argsList[])
{
    OPT opts = {
        .io_style = 0
    };

    for (int i = 0; i < argsNum; i++) {
        if (strcmp("--bold", argsList[i]) || strcmp("-b", argsList[i])) {
            opts.io_style = 1;
        }
    }

    return opts;
}

