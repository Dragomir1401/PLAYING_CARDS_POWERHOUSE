#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include "error_messages.h"
#define BUFFER_MAX 200

dll_list *deck_create()
{
    dll_list *list = malloc(sizeof(dll_list));
    if (!list)
        printf("Cant alloc memory for list.");
    list->head = NULL;
    return list;
}

dll_list *deck_get_nth_card(dll_list *list, unsigned int n)
{
    if (!list)
        printf("List is NULL.");

    dll_list *aux = list->head;
    n = n % dll_get_size(list);
    for (unsigned int i = 0; i < n; i++)
        aux = aux->next;

    return aux;
}

void deck_add_nth_card(dll_list *list, unsigned int n, const void *id)
{
    if (!list)
        printf("List is NULL.");

    dll_list *new_node = malloc(sizeof(dll_list));
    if (!new_node)
    {
        printf("Cant alloc memory for nodes.");
    }
    new_node->value = malloc(sizeof(card));
    if (!new_node->value)
    {
        printf("Cant alloc memory for nodes id.");
    }
    memcpy(new_node->value, id, sizeof(card));

    general_add_node(list, new_node, n);
}

dll_list *deck_remove_nth_card(dll_list *list, unsigned int n)
{
    dll_list *behind;
    if (!n)
    {
        dll_list *removed = list->head;
        list->head = removed->next;
        return removed;
    }

    if (n > dll_get_size(list))
        n = dll_get_size(list) - 1;

    behind = deck_get_nth_card(list, n - 1);
    dll_list *removed = behind->next;
    behind->next = removed->next;
    if (n < dll_get_size(list) - 1)
        removed->next->prev = behind;

    return removed;
}

void del_card(dll_list *list, unsigned int index_deck, unsigned int index_card)
{
    if (index_deck > dll_get_size(list))
    {
        printf(DECK_INDEX_OUT_OF_BOUNDS);
        return;
    }

    dll_list *aux = list->head;
    unsigned int i = 0, delete = 0;
    while (aux)
    {
        if (i == index_deck)
        {
            dll_list *aux1 = ((dll_list *)(aux->value));
            if (index_deck > dll_get_size(aux1) && !delete)
            {
                printf(CARD_INDEX_OUT_OF_BOUNDS);
                return;
            }
            dll_list *removed = deck_remove_nth_card(aux1, index_card);
            free(removed->value);
            free(removed);

            if (!dll_get_size(aux1))
                delete = 1;
        }

        i++;
        aux = aux->next;
    }
    if (delete)
        del_deck(list, index_deck);
}

int card_is_valid(card card)
{
    int valid = 0;
    if (!strncmp(card.symbol, "SPADES", 6))
        valid = 1;
    if (!strncmp(card.symbol, "HEART", 5))
        valid = 1;
    if (!strncmp(card.symbol, "CLUB", 4))
        valid = 1;
    if (!strncmp(card.symbol, "DIAMONDS", 8))
        valid = 1;
    if (card.number > 14 || card.number < 0)
        valid = 0;
    return valid;
}

void del_certain_card(dll_list *list_decks, char *token)
{
    token = strtok(NULL, "  ");
    unsigned int index_deck = atoi(token);
    token = strtok(NULL, "  ");
    unsigned int index_card = atoi(token);
    del_card(list_decks, index_deck, index_card);
    printf("The card was successfully deleted from deck %d.\n", index_deck);
}

void add_additional_cards(dll_list *deck_list, char *token)
{
    token = strtok(NULL, "  ");
    unsigned int index_deck = atoi(token);
    token = strtok(NULL, "  ");
    unsigned int nr_cards = atoi(token);

    dll_list *card_deck = dll_deck_get_nth_deck(deck_list, index_deck);
    card card_id;
    unsigned int count = 0;
    while (count < nr_cards)
    {
        char *buff = malloc(BUFFER_MAX);
        fgets(buff, BUFFER_MAX, stdin);
        token = strtok(buff, "  ");
        card_id.number = atoi(token);
        token = strtok(NULL, "  ");
        strcpy(card_id.symbol, token);
        if (card_is_valid(card_id))
        {
            deck_add_nth_card(card_deck, nr_cards, &card_id);
            count++;
        }
        else
            printf(INVALID_CARD);
        free(buff);
    }
}