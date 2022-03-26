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
            token = strtok(NULL, "  ");
            int nr_cards = atoi(token);
            for (int i = 0; i < nr_cards; i++)
            {
                card card_id;
                fgets(buff, BUFFER_MAX, stdin);
                token = strtok(buff, "  ");
                card_id.number = atoi(token);
                token = strtok(NULL, "  ");
                strcpy(card_id.symbol, token);
                deck_add_nth_card(card_deck, nr_cards, &card_id);
            }
            // dll_list *aux = card_deck->head;
            // while (aux)
            // {
            //     printf("%d %s", ((card *)(aux->value))->number, ((card *)(aux->value))->symbol);
            //     aux = aux->next;
            // }
            dll_deck_add_nth_deck(list_decks, dll_get_size(list_decks), card_deck); /// FIX
            //printf("%d\n", dll_get_size(list_decks));
            printf("The deck was succesfully created with %d cards.\n", nr_cards);
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
            dll_free(&list_decks);
            break;
        }
        else if (!strncmp(token, "DEL_DECK", 8))
        {
            token = strtok(NULL, "  ");
            unsigned int index = atoi(token);
            del_deck(list_decks, index);
        }
        else
        {
            printf(INVALID_COMMAND);
        }
    }
    free(buff);
    return 0;
}