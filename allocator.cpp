#include <iostream>
#include <cstdlib>
#include <cmath>
#include "function_prototypes.h"

using namespace std;
HashTable T;

void *mymalloc(size_t cbytes){

	static d_ptr *size_classes  = new d_ptr[8];
	static bool first = 0;

	if (first == 0){

		first = 1;
		int i;
		for ( i = 0; i < 8; i++){
			size_classes[i] = NULL;
		}
	}
	int c_size = round_up(cbytes);	//class_size
	if (c_size > 4096){
		return malloc(cbytes);
	}
	int j;
	j = decide_index_in_array(c_size);
	void *pg;
	d_ptr current;

	if (size_classes[j] == NULL) {

		pg = get_Page();
		size_classes[j] = new d_listNode(c_size, NULL, NULL, pg);

		//Page hashing

		hash_insert(T, size_classes[j], pg);


		size_classes[j]->flip_nth_bit(1);
		return size_classes[j]->get_page();		//return address of requested space to user (little indian)

	}else{

		current = size_classes[j];
		int pos;
		while(current != NULL) {		//check nodes of list

			pos = current->search();
			if ( pos == 0)  				//if there is no available position in node,
				current = current->get_next();	//move to next node
			else{
				//if node found with free position in the bit vector isn't the first one
				if (current->get_prev() != NULL){
						//if node found with free position in the bit vector is the last node of the list
					if(current->get_next() == NULL){

						current->get_prev()->set_next(NULL);
						current->set_next(size_classes[j]);
						current->set_prev(NULL);
						size_classes[j]->set_prev(current);
						size_classes[j] =current;

					}else{	//if node found with free position in the bit vector is a middle one

						current->get_prev()->set_next(current->get_next());
						current->get_next()->set_prev(current->get_prev());
						current->set_next(size_classes[j]);
						current->set_prev(NULL);
						size_classes[j]->set_prev(current);
						size_classes[j] =current;

					}
				}
				current->flip_nth_bit(pos);	//else set the pos-th bit to 1
				return (char *)current->get_page() + (pos - 1)*current->get_size();		//and return address
			}
		}
		//No available space in the list, new node needs to be constructed
		current = size_classes[j];
		pg = get_Page();

		size_classes[j] = new d_listNode(c_size, NULL, current, pg);
		current->set_prev(size_classes[j]);

		//Page hashing

		hash_insert(T, size_classes[j], pg);
		size_classes[j]->flip_nth_bit(1);
		return size_classes[j]->get_page();
	}


}


void myfree(void *add){

	if (check_hash(T, add) == 0)	//if the page address isn't stored in hashtable, call free

		free(add);

}
