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
    if (n >= dll_get_size(list))
        n = dll_get_size(list) - 1;
    for (unsigned int i = 0; i < n; i++)
        aux = aux->next;

    return (dll_list *)(aux->value);
}

void dll_deck_add_nth_deck(dll_list *list, unsigned int n, const void *id)
{
    if (!list)
        printf("List is NULL.");

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

void del_deck(dll_list *list, unsigned int index, int no_message)
{
    if (index >= dll_get_size(list))
        printf(DECK_INDEX_OUT_OF_BOUNDS);
    else
    {
        dll_list *removed = deck_remove_nth_card(list, index);
        deck_free(removed->value);
        free(removed);
    }
    if (!no_message)
        printf("The deck %d was successfully deleted.\n", index);
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

void add_additional_deck(dll_list *list_decks, char *token)
{
    token = strtok(NULL, "  ");
    int nr_cards = atoi(token);
    dll_list *card_deck = deck_create(sizeof(card));

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
            deck_add_nth_card(card_deck, count, &card_id);
            count++;
        }
        else
            printf(INVALID_CARD);
        free(buff);
    }

    dll_deck_add_nth_deck(list_decks, dll_get_size(list_decks), card_deck);
    printf("The deck was successfully created with %d cards.\n", nr_cards);
}

void merge_decks(dll_list *deck_list, char *token)
{
    token = strtok(NULL, "  ");
    unsigned int index_deck1 = atoi(token);

    token = strtok(NULL, "  ");
    unsigned int index_deck2 = atoi(token);
    if (index_deck1 >= dll_get_size(deck_list) || index_deck2 >= dll_get_size(deck_list))
    {
        printf(DECK_INDEX_OUT_OF_BOUNDS);
        return;
    }

    dll_list *deck1 = dll_deck_get_nth_deck(deck_list, index_deck1);
    dll_list *deck2 = dll_deck_get_nth_deck(deck_list, index_deck2);
    dll_list *new_deck;
    new_deck = deck_create(sizeof(card));

    dll_list *aux1 = deck1->head;
    dll_list *aux2 = deck2->head;

    card *card_id;
    int count = 0;
    while (aux1 && aux2)
    {
        card_id = (card *)(aux1->value);
        deck_add_nth_card(new_deck, count, card_id);
        count++;
        card_id = (card *)(aux2->value);
        deck_add_nth_card(new_deck, count, card_id);
        count++;

        aux1 = aux1->next;
        aux2 = aux2->next;
    }

    if (!aux1)
    {
        while (aux2)
        {
            card *card_id = (card *)(aux2->value);
            deck_add_nth_card(new_deck, count, card_id);
            count++;

            aux2 = aux2->next;
        }
    }

    if (!aux2)
    {
        while (aux1)
        {
            card *card_id = (card *)(aux1->value);
            deck_add_nth_card(new_deck, count, card_id);
            count++;

            aux1 = aux1->next;
        }
    }
    if (index_deck1 < index_deck2)
    {
        del_deck(deck_list, index_deck1, 1);
        del_deck(deck_list, index_deck2 - 1, 1);
    }
    else
    {
        del_deck(deck_list, index_deck2, 1);
        del_deck(deck_list, index_deck1 - 1, 1);
    }

    dll_deck_add_nth_deck(deck_list, dll_get_size(deck_list), new_deck);
    printf("The deck %d and the deck %d were successfully merged.\n", index_deck1, index_deck2);
}

void split_deck(dll_list *deck_list, char *token)
{
    token = strtok(NULL, "  ");
    unsigned int index_deck = atoi(token);

    token = strtok(NULL, "  ");
    unsigned int index_split = atoi(token);

    if (index_deck >= dll_get_size(deck_list))
    {
        printf(DECK_INDEX_OUT_OF_BOUNDS);
        return;
    }

    dll_list *deck = dll_deck_get_nth_deck(deck_list, index_deck);
    dll_list *left_deck, *right_deck;
    left_deck = deck_create(sizeof(card));
    right_deck = deck_create(sizeof(card));

    dll_list *aux = deck->head;

    card *card_id;
    unsigned int count_left = 0, i = 0, count_right = 0;
    while (aux)
    {
        if (i < index_split)
        {
            card_id = (card *)(aux->value);
            deck_add_nth_card(left_deck, count_left, card_id);
            count_left++;
        }
        else
        {
            card_id = (card *)(aux->value);
            deck_add_nth_card(right_deck, count_right, card_id);
            count_right++;
        }
        i++;
        aux = aux->next;
    }

    del_deck(deck_list, index_deck, 1);

    if (count_left)
        dll_deck_add_nth_deck(deck_list, index_deck, left_deck);
    else
        free(left_deck);

    if (count_right && count_left)
        dll_deck_add_nth_deck(deck_list, index_deck + 1, right_deck);
    else if (count_right && !count_left)
        dll_deck_add_nth_deck(deck_list, index_deck, right_deck);
    else
        free(right_deck);

    printf("The deck %d was successfully split by index %d.\n", index_deck, index_split);
}
