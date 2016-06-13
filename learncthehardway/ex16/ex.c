// include libs
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// declate struct Person and it's fields types
struct Person {
    char *name; 
    int age;
    int height;
    int weight;
};

// declate create function of type struct Person
struct Person *Person_create(
        char *name, 
        int age, 
        int height, 
        int weight
) {
    // allocate mem for new struct based on it's size,
    // store pointer to it in temp var
    struct Person *who = malloc(sizeof(struct Person));
    // assert malloc returned valid pointer
    assert(who != NULL);

    // set struct fields through it's fields
    // copy name (includes mem allocation for string copy
    who->name = strdup(name);
    who->age = age;
    // another way of accesing struct fields
    (*who).height = height;
    who->weight=weight;
    // return pointer for newly created struct Person
    return who;
}

// declare function for freeng person mem
void Person_destroy(struct Person *who) {
    // assert pointer is valid
    assert(who != NULL);
    // free name string memory
    free(who->name);
    // free struct memory
    free(who);
}

// declare func to print struct
void Person_print(struct Person *who) {
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeihgt: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[]) {
    // make two people structures
    struct Person *joe = Person_create(
        "Joe Alex", 
        32, // age
        64, // height
        140 // weight
    );

    struct Person *frank = Person_create(
        "Frank Blank",
        20, 72, 180);


    // print them out and where they are in memory
    printf("Joe is at mem location: %p:\n", (void *) joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", (void *) frank);
    Person_print(frank);

    // make everyone age 20 tears and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);

    // destroy them both so we clean up
    Person_destroy(joe);
    Person_destroy(frank);

    return 0;
}

