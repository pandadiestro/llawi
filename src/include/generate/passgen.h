#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include <utils/args.h>


#define CHARSET_ALPHANUM "abcdefghijklmnopqrstuvwxyz0123456789"
#define CHARSET_SPECIAL  " #$%&/()=[]{}"
#define FINAL_LEN sizeof(CHARSET_SPECIAL) + sizeof(CHARSET_ALPHANUM) - 2
#define PRINT_BOLD(str) printf("\033[1m%s\033[0m", str)

#define LEN 8


void printBunny(char* pass, OPT opts);
int genNew(OPT opts);

static void swap(char* one, char* two);
static int randomFn(int limit);
static char* getCharsetFinal(void);
static char* newPermutatedSet(void);

static void
swap(char* one, char* two)
{
    char tmp = *one;
    *one = *two;
    *two = tmp;
}

static char*
getCharsetFinal(void)
{
    char* final = malloc(FINAL_LEN);

    memcpy(final, CHARSET_ALPHANUM, sizeof(CHARSET_ALPHANUM) - 1);
    memcpy(final + sizeof(CHARSET_ALPHANUM) - 1, CHARSET_SPECIAL, sizeof(CHARSET_SPECIAL) - 1);

    return final;
}

static int
randomFn(int limit)
{
    return rand()%(limit+1);
}

void
printBunny(char* pass, OPT opts)
{
    char* bunny = "\033[38;2;255;208;182;1m\n\
    Here, copy your new password: \n\
    \n\
  /)/) \n\
 (˶•༝•) \n\
୭(づ\033[0m";

    fprintf(stderr, "%s", bunny);
    switch(opts.io_style) {
    case 0:
        printf("\033[31m>>\033[0m%s\033[31m<<\033[0m\n", pass);
        break;
    case 1:
        PRINT_BOLD(pass);
        break;
    }
}

static char*
newPermutatedSet(void)
{
    char* chars = getCharsetFinal();
    for (size_t i = 0; i < FINAL_LEN; i++)
        swap(&chars[i], &chars[randomFn(FINAL_LEN-1)]);
    return chars;
}

int
genNew(OPT opts)
{
    char* newPass = newPermutatedSet();
    /*
     * This is being printed to stderr, the password should also be outputed
     * to stdout for posterior pipe to xclip
     * */
    printBunny(newPass, opts);
    return 0;
}

