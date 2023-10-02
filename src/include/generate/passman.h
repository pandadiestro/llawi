#include <utils.h>

#define rounds 13
#define FINAL_LEN sizeof(CHARSET_SPECIAL) + sizeof(CHARSET_ALPHANUM) - 2
#define PRINT_BOLD(str) printf("\033[1m%s\033[0m", str)

const char CHARSET_ALPHANUM[] = "abcdefghijklmnopqrstuvwxyz0123456789";
const char CHARSET_SPECIAL[]  = " #$%&/()=[]{}";

const int perm[] = {24, 19, 10, 15, 37, 29, 2, 16, 28, 25, 3, 33, 14, 39, 41, 45, 34, 6, 5, 9, 0, 32, 17, 20, 7, 43, 23, 21, 27, 13, 47, 4, 36, 46, 11, 22, 26, 35, 18, 31, 42, 8, 30, 48, 40, 38, 12, 44, 1};

void bunnyPrint(char* pass, OPT opts, char* msg);
int genNew(OPT opts);
char* decrypt(char* str, int len, OPT opts);

static char* getCharsetFinal(void);
static char* newPermutatedSet(void);
static void substitute(char* str, int len);
static char* substituteAndPermute(char* str, int len, OPT opts);
static char* permutate(char* str, const int perm[], int len, const unsigned char way);

static char*
getCharsetFinal(void)
{
    char* finalSet = malloc(FINAL_LEN);

    memcpy(finalSet, CHARSET_ALPHANUM, sizeof(CHARSET_ALPHANUM) - 1);
    memcpy(finalSet + sizeof(CHARSET_ALPHANUM) - 1, CHARSET_SPECIAL, sizeof(CHARSET_SPECIAL) - 1);

    return finalSet;
}

void
bunnyPrint(char* str, OPT opts, char* msg)
{
    char* bunny = "\n\
  /)/) \n\
 (˶•༝•) \n\
୭(づ\033[0m";

    fprintf(stderr, "\n\033[38;2;255;208;182;1m\t%s\n", msg);
    fprintf(stderr, "%s", bunny);
    fprintf(stderr, "\033[31m>>\033[0m");
    switch(opts.io_style) {
    case 0:
        printf("%s", str);
        break;
    case 1:
        PRINT_BOLD(str);
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


static char*
permutate(char* str, const int perm[], int len, const unsigned char way)
{
    int* deperm = calloc(len, sizeof(int));
    char* newStr = calloc(len, sizeof(char));

    switch (way) {
    case 0:
        for (int i = 0; i < len; i++)
            newStr[i] = str[perm[i]];
        break;
    case 1:
        for (int i = 0; i < len; i++) {
            deperm[perm[i]] = i;
        }
        for (int i = 0; i < len; i++)
            newStr[i] = str[deperm[i]];
        break;
    default:
        for (int i = 0; i < len; i++)
            newStr[i] = str[perm[i]];
        break;
    }

    free(deperm);
    return newStr;
}

static char*
substituteAndPermute(char* str, int len, OPT opts)
{
    for (int i = 0; i < rounds; i++) {
        for (int j = 0; j < len; j++) {
            str[j] ^= opts.key[i];
        }
        str = permutate(str, perm, len, 0);
    }

    return str;
}

char*
decrypt(char* str, int len, OPT opts)
{
    for (int i = 0; i < rounds; i++) {
        str = permutate(str, perm, len, 1);
        for (int j = 0; j < len; j++) {
            str[j] ^= opts.key[i];
        }
    }

    return str;
}

int
savePass(char* pass, int len, OPT opts)
{
    int locSize = strlen(opts.name) + strlen(opts.home) + 2;
    char* fileLocation = (char*) calloc(locSize, sizeof(char));
    char* separator = "/";

    strcpy(fileLocation, opts.home);
    strcpy(fileLocation + strlen(opts.home), separator);
    strcpy(fileLocation + strlen(opts.home) + 1, opts.name);

    FILE* passFile = fopen(fileLocation, "wb");
    if (passFile == NULL) {
        fclose(passFile);
        die("error with file opening");
    }

    pass = substituteAndPermute(pass, len, opts);
    fwrite(pass, len, 1, passFile);
    fclose(passFile);
    free(fileLocation);
    return 0;
}

char*
getPass(int len, OPT opts)
{
    int locSize = strlen(opts.name) + strlen(opts.home) + 2;
    char* fileLocation = (char*) calloc(locSize, sizeof(char));
    char* separator = "/";

    strcpy(fileLocation, opts.home);
    strcpy(fileLocation + strlen(opts.home), separator);
    strcpy(fileLocation + strlen(opts.home) + 1, opts.name);

    FILE* passFile = fopen(fileLocation, "rb");
    if (passFile == NULL) {
        fclose(passFile);
        die("error with file opening");
    }

    char* pass = calloc(len, sizeof(char));
    fread(pass, len, 1, passFile);
    pass = decrypt(pass, len, opts);

    fclose(passFile);
    free(fileLocation);

    return pass;
}

