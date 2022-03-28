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
    dll_list *list_decks;
    list_decks = dll_deck_create(sizeof(card));
    char *buff = malloc(BUFFER_MAX);
    while (1)
    {
        fgets(buff, BUFFER_MAX, stdin);
        char *token = strtok(buff, "  ");

        if (!strncmp(token, "ADD_DECK", 8))
        {
            dll_list *card_deck = deck_create(sizeof(card));
            add_additional_deck(list_decks, token, card_deck);
        }
        else if (!strncmp(token, "SHOW_ALL", 8))
        {
            dll_show_all_decks(list_decks);
        }
        else if (!strncmp(token, "SHOW_DECK", 9))
        {
            token = strtok(NULL, "  ");
            unsigned int index = atoi(token);
            if (index >= dll_get_size(list_decks))
                printf(DECK_INDEX_OUT_OF_BOUNDS);
            else
                dll_show_deck(list_decks, index);
        }
        else if (!strncmp(token, "EXIT", 4))
        {
            dll_free(list_decks);
            break;
        }
        else if (!strncmp(token, "DEL_DECK", 8))
        {
            token = strtok(NULL, "  ");
            unsigned int index = atoi(token);
            del_deck(list_decks, index);
        }
        else if (!strncmp(token, "DEL_CARD", 8))
        {
            del_certain_card(list_decks, token);
        }
        else if (!strncmp(token, "ADD_CARDS", 9))
        {
            add_additional_cards(list_decks, token);
        }
        else if (!strncmp(token, "DECK_NUMBER", 11))
        {
            printf("The number of decks is %d.\n", dll_get_size(list_decks));
        }
        else if (!strncmp(token, "DECK_LEN", 8))
        {
            len_of_deck(list_decks, token);
        }
        else if (!strncmp(token, "SHUFFLE_DECK", 12))
        {
            shuffle_deck(list_decks, token);
        }
        else
        {
            printf(INVALID_COMMAND);
        }
    }
    free(buff);
    return 0;
}