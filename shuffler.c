#include <stdio.h>


int main(){
    char cards[] = "JQK";
    char a_card = cards[2];
    puts(cards);
    printf(" %c \n", a_card);
    cards[2] = cards[1];
    puts(cards);
    cards[1] = cards[0];
    puts(cards);
    cards[0] = cards[2];
    puts(cards);
    cards[2] = cards[1];
    puts(cards);
    cards[1] = a_card;
    puts(cards);
    return 0;
}
