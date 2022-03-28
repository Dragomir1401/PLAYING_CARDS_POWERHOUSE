#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include "error_messages.h"
#define BUFFER_MAX 200

dll_list *dll_deck_create()
{
    dll_list *list = malloc(sizeof(dll_list));
    if (!list)
        printf("Cant alloc memory for list.");
    list->head = NULL;
    return list;
}

dll_list *dll_deck_get_nth_deck(dll_list *list, unsigned int n)
{
    if (!list)
        printf("List is NULL.");

    dll_list *aux = list->head;
    n = n % dll_get_size(list); // wowow be careful
    for (unsigned int i = 0; i < n; i++)
        aux = aux->next;

    return aux;
}

void dll_deck_add_nth_deck(dll_list *list, unsigned int n, const void *id)
{
    if (!list)
        printf("List is NULL.");
    // dll_list *new_node = (dll_list *)id;

    dll_list *new_node = malloc(sizeof(dll_list));
    if (!new_node)
    {
        printf("Cant alloc memory for nodes.");
    }
    new_node->value = malloc(sizeof(dll_list));
    if (!new_node->value)
    {
        printf("Cant alloc memory for nodes id.");
    }
    memcpy(new_node->value, id, sizeof(dll_list));
    dll_list *to_free = (dll_list *)(id);
    free(to_free);
    general_add_node(list, new_node, n);
}

void dll_show_all_decks(dll_list *list)
{
    dll_list *aux = list->head;
    int i = 0;
    while (aux)
    {
        dll_list *aux1 = ((dll_list *)(aux->value))->head;
        dll_list *checker = ((dll_list *)(aux->value));
        if (dll_get_size(checker))
            printf("Deck %d:\n", i);
        card *aux2;
        while (aux1)
        {
            aux2 = (card *)(aux1->value);
            printf("\t%d %s", aux2->number, aux2->symbol);
            aux1 = aux1->next;
        }
        i++;
        aux = aux->next;
    }
}

void dll_free(dll_list *pp_list)
{
    int n = dll_get_size(pp_list);
    for (int i = 0; i < n; i++)
    {
        dll_list *aux = deck_remove_nth_card(pp_list, 0);
        deck_free(aux->value);
        free(aux);
    }
    free(pp_list);
}

void deck_free(dll_list *pp_list)
{

    int n = dll_get_size(pp_list);
    for (int i = 0; i < n; i++)
    {
        dll_list *aux = deck_remove_nth_card(pp_list, 0);
        free(aux->value);
        free(aux);
    }
    free(pp_list);
}

unsigned int dll_get_size(dll_list *list)
{
    dll_list *aux = list->head;
    int i = 0;
    while (aux)
    {
        i++;
        aux = aux->next;
    }
    return i;
}

void dll_show_deck(dll_list *list, int n)
{
    dll_list *aux = list->head;
    int i = 0;
    while (aux)
    {
        if (i == n)
        {
            dll_list *aux1 = ((dll_list *)(aux->value))->head;
            dll_list *checker = ((dll_list *)(aux->value));
            if (dll_get_size(checker))
                printf("Deck %d:\n", i);
            card *aux2;
            while (aux1)
            {
                aux2 = (card *)(aux1->value);
                printf("\t%d %s", aux2->number, aux2->symbol);
                aux1 = aux1->next;
            }
        }
        i++;
        aux = aux->next;
    }
}

void del_deck(dll_list *list, unsigned int index)
{
    if (index >= dll_get_size(list))
        printf(DECK_INDEX_OUT_OF_BOUNDS);
    else
    {
        dll_list *removed = deck_remove_nth_card(list, index);
        deck_free(removed->value);
        free(removed);
    }
}

void general_add_node(dll_list *list, dll_list *new_node, unsigned int n)
{
    if (!dll_get_size(list))
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        list->head = new_node;
        return;
    }

    if (n < dll_get_size(list))
    {
        dll_list *aux;
        if (n)
        {
            aux = list->head;
            for (unsigned int i = 0; i < n - 1; i++)
                aux = aux->next;

            new_node->next = aux->next;
            aux->next = new_node;
            new_node->prev = aux;
            new_node->next->prev = new_node;
            return;
        }
        else
        {
            new_node->prev = NULL;
            new_node->next = list->head;
            ((dll_list *)list->head)->prev = new_node;
            list->head = new_node;
            return;
        }
    }

    dll_list *aux = list->head;
    for (unsigned int i = 0; i < dll_get_size(list) - 1; i++)
        aux = aux->next;
    aux->next = new_node;
    new_node->next = NULL;
    new_node->prev = aux;
}

void add_additional_deck(dll_list *list_decks, char *token, dll_list *card_deck)
{
    token = strtok(NULL, "  ");
    int nr_cards = atoi(token);

    card card_id;
    int count = 0;
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

    dll_deck_add_nth_deck(list_decks, dll_get_size(list_decks), card_deck);
    printf("The deck was succesfully created with %d cards.\n", nr_cards);
}