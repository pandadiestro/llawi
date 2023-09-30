#include <stdio.h>
#include <time.h>
#include <generate/passgen.c>

int main(void) {
    srand(time(NULL));

    char* pass = return_gen();

    for (int i = 0; i < len; i++)
        printf("%c", pass[i]);
    printf("\n");
    return 0;
}




