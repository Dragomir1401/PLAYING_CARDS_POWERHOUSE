#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include "error_messages.h"
dll_deck *dll_deck_create(unsigned int id_size)
{
    dll_deck *list = malloc(sizeof(dll_deck));
    if (!list)
        printf("Cant alloc memory for list.");

    list->head = NULL;
    list->data_size = id_size;
    list->size = 0;

    return list;
}

deck *dll_deck_get_nth_deck(dll_deck *list, unsigned int n)
{
    if (!list)
        printf("List is NULL.");

    deck *aux = list->head;
    n = n % list->size; // wowow be careful
    for (unsigned int i = 0; i < n; i++)
        aux = aux->next;

    return aux;
}

deck *dll_deck_remove_nth_deck(dll_deck *list, unsigned int n)
{
    deck *behind;
    if (!n)
    {
        deck *removed = list->head;
        list->head = removed->next;
        list->size--;
        return removed;
    }

    if (n > list->size)
        n = list->size - 1;

    behind = dll_deck_get_nth_deck(list, n - 1);
    deck *removed = behind->next;
    behind->next = removed->next;
    if (n < list->size - 1)
        removed->next->prev = behind;
    list->size--;

    return removed;
}

void dll_deck_add_nth_deck(dll_deck *list, unsigned int n, const void *id)
{
    if (!list)
        printf("List is NULL.");
    deck *new_node = (deck *)id;
    if (!list->size)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        list->head = new_node;
        list->size++;
        return;
    }

    if (n < list->size)
    {
        deck *aux;
        if (n)
        {
            aux = list->head;
            for (unsigned int i = 0; i < n - 1; i++)
                aux = aux->next;

            new_node->next = aux->next;
            aux->next = new_node;
            new_node->prev = aux;
            new_node->next->prev = new_node;
            list->size++;
            return;
        }
        else
        {
            new_node->prev = NULL;
            new_node->next = list->head;
            list->head->prev = new_node;
            list->head = new_node;
            list->size++;
            return;
        }
    }

    deck *aux = list->head;
    for (unsigned int i = 0; i < list->size - 1; i++)
        aux = aux->next;
    aux->next = new_node;
    new_node->next = NULL;
    new_node->prev = aux;
    list->size++;
}

void dll_show_all_decks(dll_deck *list)
{
    deck *aux = list->head;
    for (unsigned int i = 0; i < list->size; i++)
    {
        printf("Deck %d:\n", i);
        card *aux1 = aux->head;
        for (unsigned int i = 0; i < aux->size; i++)
        {
            printf("\t%d %s", aux1->id->value, aux1->id->symbol);
            aux1 = aux1->next;
        }
        aux = aux->next;
    }
}

void dll_free(dll_deck **pp_list)
{
    int n = (*pp_list)->size;
    for (int i = 0; i < n; i++)
    {
        deck *aux = dll_deck_remove_nth_deck(*pp_list, 0);
        deck_free(&aux);
    }

    free(*pp_list);
}

void dll_show_deck(dll_deck *list, int n)
{
    deck *aux = list->head;
    for (unsigned int i = 0; i < list->size; i++)
    {
        if ((int)i == n)
        {
            printf("Deck %d:\n", i);
            card *aux1 = aux->head;
            for (unsigned int i = 0; i < aux->size; i++)
            {
                printf("\t%d %s", aux1->id->value, aux1->id->symbol);
                aux1 = aux1->next;
            }
        }
        aux = aux->next;
    }
}

void del_deck(dll_deck *list, unsigned int index)
{
    if (index >= list->size)
        printf(DECK_INDEX_OUT_OF_BOUNDS);
    else
    {
        deck *removed = dll_deck_remove_nth_deck(list, index);
        deck_free(&removed);
    }
}