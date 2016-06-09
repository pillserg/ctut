/*
 * Program for evaluating face values.
 * Released under Vegas Public Licence.
 * (c)2016 The Colledge BlackJack Team
 */
#include <stdio.h>
#include <stdlib.h>

int main() {
    char card_name[3] = {'b'};
    int count = 0;

    while (card_name[0] != 'X') {
        puts("Enter the card name: ");
        scanf("%2s", card_name);
        int val = 0;
        
        switch(card_name[0]){
            case 'K': case 'Q': case 'J':
                val = 10;
                break;
            case 'A':
                val = 11;
                break;
            default:
                val = atoi(card_name);
        }
        if (val < 1 || val > 11) {
            puts("Wrong card");
            continue;
        } else {
            printf("The card value is: %i\n", val);
        }

        if (3 <= val && val <= 6) {
            count++;
        } else if (10 <= val) {
            count--;
        }
        printf("Current count: %i\n", count);
    }
    puts("Buy");
    return 0;
}
