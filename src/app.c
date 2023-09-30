#include <stdio.h>
#include <time.h>
#include <generate/passgen.c>

int main(void) {
    srand(time(NULL));

    char* pass = return_gen();

    return 0;
}




