#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

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

dll_deck *dll_deck_get_nth_card(dll_deck *list, unsigned int n)
{
    if (!list)
        printf("List is NULL.");

    deck *aux = list->head;
    n = n % list->size;
    for (int i = 0; i < n; i++)
        aux = aux->next;

    return aux;
}

void dll_deck_add_nth_card(dll_deck *list, unsigned int n, const void *id)
{
    // To finish this
    if (!list)
        printf("List is NULL.");

    deck *new_node = deck_create(sizeof(card));
    if (!new_node)
    {
        printf("Cant alloc memory for nodes.");
    }
    new_node. //?? = malloc(list->data_size);
        if (!new_node->id)
    {
        printf("Cant alloc memory for nodes id.");
    }
    memcpy(new_node->id, id, list->data_size);

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
            for (int i = 0; i < n - 1; i++)
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
    for (int i = 0; i < list->size - 1; i++)
        aux = aux->next;
    aux->next = new_node;
    new_node->next = NULL;
    new_node->prev = aux;
    list->size++;
}
