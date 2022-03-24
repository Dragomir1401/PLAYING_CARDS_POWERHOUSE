#pragma once
typedef struct id
{
    int value;
    char symbol[10];
} id;

typedef struct card
{
    id *id;
    struct card *prev, *next;
} card;

typedef struct deck
{
    card *head;
    unsigned int data_size;
    unsigned int size;
    struct deck *next, *prev;
} deck;

typedef struct dll_decks
{

    deck *head;
    unsigned int data_size;
    unsigned int size;
} dll_deck;