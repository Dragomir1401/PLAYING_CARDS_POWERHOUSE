#include "structures.h"
deck *deck_create(unsigned int id_size);
card *deck_get_nth_card(deck *list, unsigned int n);
void deck_add_nth_card(deck *list, unsigned int n, const void *id);
card *deck_remove_nth_card(deck *list, unsigned int n);
unsigned int deck_get_size(deck *list);
void deck_free(deck **pp_list);
void deck_print_list(deck *list);
deck *dll_deck_create(unsigned int id_size);
deck *dll_deck_get_nth_card(dll_deck *list, unsigned int n);
void dll_deck_add_nth_card(dll_deck *list, unsigned int n, const void *id);