#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#define COMMAND_MAX 50
#define BUFFER_MAX 200
#define SYMBOL_MAX 15
int main(void)
{
    //dll_deck *list_decks;
    while (1)
    {
        char buff[BUFFER_MAX];
        fgets(buff, BUFFER_MAX, stdin);
        char *token = strtok(buff, " \n");
        if (!strcmp(token, "ADD_DECK"))
        {
            deck *card_deck = deck_create(sizeof(id));
            token = strtok(NULL, " ");
            int nr_cards = atoi(token);
            //printf("%d\n", nr_cards);
            for (int i = 0; i < nr_cards; i++)
            {
                id card_id;
                fgets(buff, BUFFER_MAX, stdin);
                token = strtok(buff, " ");
                //printf("%s ", token);
                card_id.value = atoi(token);
                token = strtok(NULL, " ");
                //printf("%s\n", token);
                strcpy(card_id.symbol, token);
                deck_add_nth_card(card_deck, nr_cards, &card_id);
            }

            deck_print_list(card_deck);
        }
        else if (!strcmp(token, "EXIT"))
        {
            break;
        }
    }
    return 0;
}