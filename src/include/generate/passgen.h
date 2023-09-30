#include <stdlib.h>
#include <string.h>

#define CHARSET_ALPHANUM "abcdefghijklmnopqrstuvwxyz0123456789"
#define CHARSET_SPECIAL  " #$%&/()=[]{}"
#define len sizeof(CHARSET_SPECIAL) + sizeof(CHARSET_ALPHANUM) - 2

#define LEN 8

static void swap(char* one, char* two) {
    char tmp = *one;
    *one = *two;
    *two = tmp;
}

char* getCharsetFinal() {
    char* final = malloc(len);

    memcpy(final, CHARSET_ALPHANUM, sizeof(CHARSET_ALPHANUM) - 1);
    memcpy(final + sizeof(CHARSET_ALPHANUM) - 1, CHARSET_SPECIAL, sizeof(CHARSET_SPECIAL) - 1);

    return final;
}

int randomFn(int limit) {
    return rand()%(limit+1);
}

void printBunny(char* pass) {
    char* bunny = "\n\
  /)/) \n\
 (˶•༝•) \n\
୭(づ<[";

    fprintf(stderr, "%s\033[1m %s \033[0m]>", bunny, pass);
}

char* return_gen() {
    char* chars = getCharsetFinal();
    for (int i = 0; i < len; i++) {
        swap(&chars[i], &chars[randomFn(len-1)]);
    }

    printBunny(chars);

    return chars;
}


