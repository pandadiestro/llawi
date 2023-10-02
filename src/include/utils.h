#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <config.h>

#define _XOPEN_SOURCE
#define _POSIX_C_SOURCE 200809L

void
die(const char* msg)
{
    fprintf(stderr, "%s", msg);
    exit(-1);
}

static void
swap(char* one, char* two)
{
    char tmp = *one;
    *one = *two;
    *two = tmp;
}

static int
randomFn(int limit)
{
    return rand()%(limit+1);
}

typedef struct {
    char io_style;
    char io_fn;
    char* name;
    char* home;
    char* key;
} OPT;

OPT parseArgs(int argsNum, char* argsList[]);

OPT
parseArgs(int argsNum, char* argsList[])
{
    OPT opts = {
        .io_style = 0,
        .io_fn = 0,
        .name = NULL,
        .key = NULL
    };

    opts.home = defaultPassHome;
    if (getenv("pass_home") != NULL) {
        if(strlen(getenv("pass_home")) > 1)
            opts.home  = getenv("pass_home");
    }

    for (int i = 0; i < argsNum; i++) {
        if (strcmp("--bold", argsList[i]) == 0 || strcmp("-b", argsList[i]) == 0) {
            opts.io_style = 1;
            continue;
        }

        if (strcmp("--key", argsList[i]) == 0) {
            opts.io_fn = 1;
            if (i < argsNum - 1)
                if (strlen(argsList[i + 1]) != 13)
                    die("key must be a 13 characters long string!");
                opts.key = argsList[++i];
            continue;
        }

        if (strcmp("gen", argsList[i]) == 0) {
            opts.io_fn = 0;
            if (i < argsNum - 1)
                opts.name = argsList[++i];
            continue;
        }

        if (strcmp("get", argsList[i]) == 0) {
            opts.io_fn = 1;
            if (i < argsNum - 1)
                opts.name = argsList[++i];
            continue;
        }
    }

    return opts;
}

