#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include "error_messages.h"
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
    dll_list *to_delete = NULL;
    dll_list *aux = list->head;
    unsigned int i = 0;
    while (aux)
    {
        if (i == index_deck)
        {
            dll_list *aux1 = ((dll_list *)(aux->value));
            if (index_deck > dll_get_size(aux1) && !to_delete)
            {
                printf(CARD_INDEX_OUT_OF_BOUNDS);
                return;
            }
            dll_list *removed = deck_remove_nth_card(aux1, index_card);
            free(removed->value);
            free(removed);

            if (!dll_get_size(aux1))
            {
                to_delete = aux1;
            }
        }

        i++;
        aux = aux->next;
    }
    del_deck(to_delete, index_deck);
}
