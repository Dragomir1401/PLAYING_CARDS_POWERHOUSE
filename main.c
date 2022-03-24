#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include "error_messages.h"
#define COMMAND_MAX 50
#define BUFFER_MAX 200
#define SYMBOL_MAX 15
int main(void)
{
    dll_deck *list_decks;
    list_decks = dll_deck_create(sizeof(card));
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
            for (int i = 0; i < nr_cards; i++)
            {
                id card_id;
                fgets(buff, BUFFER_MAX, stdin);
                token = strtok(buff, " ");
                card_id.value = atoi(token);
                token = strtok(NULL, " ");
                strcpy(card_id.symbol, token);
                deck_add_nth_card(card_deck, nr_cards, &card_id);
            }
            dll_deck_add_nth_deck(list_decks, list_decks->size, card_deck);
            printf("The deck was succesfully created with %d cards.\n", nr_cards);
        }
        else if (!strcmp(token, "SHOW_ALL"))
        {
            dll_show_all_decks(list_decks);
        }
        else if (!strcmp(token, "SHOW_DECK"))
        {
            token = strtok(NULL, " ");
            unsigned int index = atoi(token);
            if (index >= list_decks->size)
                printf(DECK_INDEX_OUT_OF_BOUNDS);
            else
                dll_show_deck(list_decks, index);
        }
        else if (!strcmp(token, "EXIT"))
        {
            dll_free(&list_decks);
            break;
        }
        else if (!strcmp(token, "DEL_DECK"))
        {
            token = strtok(NULL, " ");
            unsigned int index = atoi(token);
            del_deck(list_decks, index);
        }

        else
        {
            printf(INVALID_COMMAND);
        }
    }
    return 0;
}