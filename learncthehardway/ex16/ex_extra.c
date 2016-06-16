// include libs
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// declate struct Person and it's fields types
typedef struct {
    char *name; 
    int age;
    int height;
    int weight;
} Person;

// declate create function of type struct Person
Person Person_create(
        char *name, 
        int age, 
        int height, 
        int weight
) {
    Person who;
    who.name = name;
    who.age = age;
    who.height = height;
    who.weight=weight;
    return who;
}

void Person_print(Person who) {
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeihgt: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

typedef struct {
    float lon;
    float lat;
} Coords;

typedef struct {
    Coords coords;
    char *label;
} CoordLabel;


int main(int argc, char *argv[]) {
    // make two people structures
    Person joe = Person_create(
        "Joe Alex", 
        32, // age
        64, // height
        140 // weight
    );

    Person frank = Person_create(
        "Frank Blank",
        20, 72, 180);


    Person_print(joe);
    Person_print(frank);

    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);
    
    Coords coords;
    coords.lat = 67;
    coords.lon = 88;

    printf("We have coords, capitan: %f:%f\n", coords.lat, coords.lon);
    
    CoordLabel c_label;
    c_label.coords = coords;
    c_label.label = "Tortuga";

    printf("Capitan, seems like it's coordinates of: %s\n", c_label.label);



    return 0;
}

