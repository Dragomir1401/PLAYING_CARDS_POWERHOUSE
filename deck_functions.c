#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"

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
            list->head->prev = new_node;
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
    removed->next->prev = behind;

    return removed;
}

void deck_free(dll_list **pp_list)
{

    int n = dll_get_size(*pp_list);
    for (int i = 0; i < n; i++)
    {
        dll_list *aux = deck_remove_nth_card(*pp_list, 0);
        free(aux->value);
        free(aux);
    }

    free(*pp_list);
}
