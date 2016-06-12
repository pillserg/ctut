#include <stdio.h>


void print_names(int *ages, char *names[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s is %d\n", names[i], ages[i]);
    }
}


int main(int argc, char *argv[]) {
    // creates two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);

    //first way using indexing
    for(int i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }

    printf("---\n");

    // setup pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // Second way of using pointers

    for (int i=0; i < count; i++) {
        printf("%s is %d years old.\n",
                *( cur_name+i ), *(cur_age+i));
     }

    printf("---\n");

    // third way with pointers in stupid complex way
    for (cur_name = names, cur_age = ages;
            (cur_age - ages) < count;
            cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }


    printf("--- extra stuff \n");
     
    for (int i = count - 1; 0 <= i; i--) {
        printf("%s is %d yo\n", names[i], ages[i]);
    }
    printf("---\n");
    
    cur_age = ages;
    cur_name = names;
    printf("Pointers reuse\n"); 
    for (int i=0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
    }

    printf("---\n");

    printf("Pointers backward \n"); 
    for (int i = count - 1; 0 <= i; i--) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
    }

    printf("---\n");

    printf("Mutable pointers backwards: \n");

    for (
            cur_age = ages + count - 1, cur_name = names + count - 1;
            (cur_age - ages) >= 0;
            cur_age--, cur_name--
        ) {
        printf("%s at %p is %d at %p\n",
                *cur_name, cur_name,
                *cur_age, cur_age);
    }

    printf("printloop with func\n");

    print_names(&ages, &names, count);
    return 0;
}
