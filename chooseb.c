#include <stdio.h>

void display_array(int array[], int size){
    for (int i=0; i<size; i++){
        printf("%i ", array[i]);
    }
    printf("\n");
}



int main(){
    int contestants[] = {1, 2, 3};
    int *choice = contestants;
    contestants[0] = 2;
    display_array(contestants, 3);
    
    contestants[1] = contestants[2];

    display_array(contestants, 3);
    contestants[2] = *choice;

    display_array(choice, 3);
    printf("I'm going to pick contestant number %i\n", contestants[2]);
    
    display_array(contestants, 3);
    
    return 0;
}
