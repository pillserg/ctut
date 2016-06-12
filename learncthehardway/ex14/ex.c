#include <stdio.h>
#include <ctype.h>
#include <string.h>


// forward declarations
void print_letters(int argc, char arg[]);


void print_arguments(int argc, char *argv[]) {
    for (int i = 1; i< argc; i++) {
        print_letters(strlen(argv[i]), argv[i]);
    }
}

void print_letters(int argc, char arg[]) {
    char ch = 0;
    for (int i = 0; ch = arg[i], i < argc; i++) {
        int can_print_it = isalpha(ch) || isblank(ch);
        if (can_print_it) {
            printf("'%c' == %d ", ch, ch);
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    print_arguments(argc, argv);
    return 0;
}
