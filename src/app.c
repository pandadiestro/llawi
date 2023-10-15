#include <generate/passman.h>

int main(int argc, char* argv[]) {
    srand(time(NULL));

    OPT opts = parseArgs(argc - 1, &argv[1]);
    if (opts.key == NULL)
        die("no key was given!");

    int len = FINAL_LEN;
    char* pass = NULL;

    switch (opts.io_fn) {
    case 0:
        pass = newPermutatedSet();
        bunnyPrint(pass, opts, "Here, copy your new password!");
        savePass(pass, len, opts);
        free(pass);
        break;
    case 1:
        pass = getPass(len, opts);
        bunnyPrint(pass, opts, "Here is your password ^^");
        free(pass);
        break;
    default:
        break;
    }


    return 0;
}

