#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include "error_messages.h"
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

dll_list *dll_deck_remove_nth_deck(dll_list *list, unsigned int n)
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

    behind = dll_deck_get_nth_deck(list, n - 1);
    dll_list *removed = behind->next;
    behind->next = removed->next;
    if (n < dll_get_size(list) - 1)
        removed->next->prev = behind;
    return removed;
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

void dll_show_all_decks(dll_list *list)
{
    dll_list *aux = list->head;
    int i = 0;
    while (aux)
    {
        printf("Deck %d:\n", i);
        dll_list *aux1 = ((dll_list *)(aux->value))->head;
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

void dll_free(dll_list **pp_list)
{
    int n = dll_get_size(*pp_list);
    for (int i = 0; i < n; i++)
    {
        dll_list *aux = dll_deck_remove_nth_deck(*pp_list, 0);
        deck_free(&aux);
    }

    free(*pp_list);
}

void dll_show_deck(dll_list *list, int n)
{
    dll_list *aux = list->head;
    int i = 0;
    while (aux)
    {
        if (i == n)
        {
            printf("Deck %d:\n", i);
            dll_list *aux1 = ((dll_list *)(aux->value))->head;
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
}

void del_deck(dll_list *list, unsigned int index)
{
    if (index >= dll_get_size(list))
        printf(DECK_INDEX_OUT_OF_BOUNDS);
    else
    {
        dll_list *removed = dll_deck_remove_nth_deck(list, index);
        deck_free(&removed);
    }
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