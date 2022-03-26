#pragma once
#define MAX_SYMBOL 12
// typedef struct id
// {
//     int value;
//     char symbol[10];
// } id;

// typedef struct card
// {
//     id *id;
//     struct card *prev, *next;
// } card;

// typedef struct deck
// {
//     card *head;
//     unsigned int data_size;
//     unsigned int size;
//     struct deck *next, *prev;
// } deck;

// typedef struct dll_decks
// {
//     void *head;
//     unsigned int data_size;
//     unsigned int size;
// } dll_deck;

typedef struct dll_list
{
    void *value;
    struct dll_list *head;
    struct dll_list *next, *prev;
} dll_list;

// typedef struct data
// {
//     dll_list *list;
//     unsigned int size;
// } data;

typedef struct card
{
    char symbol[MAX_SYMBOL];
    int number;
    int nr_cards;
} card;