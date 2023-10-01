#include <generate/passgen.h>

int main(int argc, char* argv[]) {
    srand(time(NULL));

    OPT opts = parseArgs(argc - 1, &argv[1]);
    char* pass = newPermutatedSet();

    printBunny(pass, opts);
    return 0;
}

