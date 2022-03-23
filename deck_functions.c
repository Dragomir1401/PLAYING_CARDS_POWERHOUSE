#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
deck *deck_create(unsigned int id_size)
{
    deck *list = malloc(sizeof(deck));
    if (!list)
        printf("Cant alloc memory for list.");

    list->head = NULL;
    list->data_size = id_size;
    list->size = 0;

    return list;
}

card *deck_get_nth_card(deck *list, unsigned int n)
{
    if (!list)
        printf("List is NULL.");

    card *aux = list->head;
    n = n % list->size;
    for (int i = 0; i < n; i++)
        aux = aux->next;

    return aux;
}

void deck_add_nth_card(deck *list, unsigned int n, const void *id)
{
    if (!list)
        printf("List is NULL.");

    card *new_node = malloc(sizeof(card));
    if (!new_node)
    {
        printf("Cant alloc memory for nodes.");
    }
    new_node->id = malloc(list->data_size);
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
        card *aux;
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

    card *aux = list->head;
    for (int i = 0; i < list->size - 1; i++)
        aux = aux->next;
    aux->next = new_node;
    new_node->next = NULL;
    new_node->prev = aux;
    list->size++;
}

card *deck_remove_nth_card(deck *list, unsigned int n)
{
    card *behind;
    if (!n)
    {
        card *removed = list->head;
        list->head = removed->next;
        list->size--;
        return removed;
    }

    if (n > list->size)
        n = list->size - 1;

    behind = deck_get_nth_card(list, n - 1);
    card *removed = behind->next;
    behind->next = removed->next;
    removed->next->prev = behind;
    list->size--;

    return removed;
}

unsigned deck_get_size(deck *list)
{

    return list->size;
}

void deck_free(deck **pp_list)
{

    int n = (*pp_list)->size;
    for (int i = 0; i < n; i++)
    {
        card *aux = deck_remove_nth_card(*pp_list, 0);
        free(aux->id);
        free(aux);
    }

    free(*pp_list);
}

void deck_print_list(deck *list)
{
    if (!list)
    {
        printf("List is NULL.");
        return;
    }

    card *aux = list->head;
    do
    {
        printf("%d %s", ((id *)aux->id)->value, ((id *)aux->id)->symbol);
        aux = aux->next;
    } while (aux);

    printf("\n");
}