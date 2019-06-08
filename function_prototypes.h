#include "hash_list.h"

int round_up(size_t );
void *get_Page();
int decide_index_in_array(size_t );
int hash_function(my_size);
void hash_insert(HashTable , d_ptr , void *);
void *mymalloc(size_t );
int check_hash(HashTable , void *);
void myfree(void *);

