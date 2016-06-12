#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: You need some arguments.\n");
        return 1;
    }
    char letter;
    int curr_arg = 1;
    do {
        for (int i = 0; letter=argv[curr_arg][i], letter != '\0'; i++) {
            switch(letter <= 'A' && letter <= 'Z' ? letter + 32 : letter){
                case 'a': case 'e': case 'i':
                case 'o': case 'u': case 'y':
                    printf("%d: %c\n", i, letter);
                    break;
                default:
                    printf("%d: %c is not a vowel\n", i, letter);
            }
        }
        printf("\n");
        curr_arg++;
    }
    while (curr_arg < argc);

    return 0;
}
