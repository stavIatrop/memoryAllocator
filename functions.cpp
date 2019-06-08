#include <iostream>
#include <cstdlib>
#include "function_prototypes.h"

using namespace std;


int round_up(size_t cbytes){

        if (cbytes <= 32)
                return 32;
        else if (cbytes <= 64)
                return 64;
        else if (cbytes <= 128)
                return 128;
        else if (cbytes <= 256)
                return 256;
        else if (cbytes <= 512)
                return 512;
        else if (cbytes <= 1024)
                return 1024;
        else if (cbytes <= 2048)
                return 2048;
        else if (cbytes <= 4096)
                return 4096;
        else
                return cbytes;
}

void *get_Page(){

	static void *cur = NULL;
	static void *end = NULL;
	void *res;

	if (cur == end) {
		cur = malloc(1024*1024);
		my_size cast;
		cast = (my_size)cur;	//cast pointer
		if (cast % 4096 == 0){
			end = (char*)cur + 1024*1024;
		}else {
			//round up to greater multiple

			cur =  (char*)(((cast/4096) + 1) * 4096);

			end = (char*)cur + 1020*1024;
		}
	}
	res = cur;
	cur = (char*)cur + 4096;

	return res;
}

int decide_index_in_array(size_t c_size){

	switch(c_size){

		case 4096:
			return 7;
			break;
		case 2048:
			return 6;
			break;
		case 1024:
			return 5;
			break;
		case 512:
			return 4;
			break;
		case 256:
			return 3;
			break;
		case 128:
			return 2;
			break;
		case 64:
			return 1;
			break;
		case 32:
			return 0;
		default:
			break;
	}
}


int hash_function(my_size i){

	return i % hash_size;

}

void hash_insert(HashTable T1, d_ptr pgN, void *pg){
	static bool flag = 0;
	if (flag == 0){

		flag = 1;
		int i;
		for (i = 0; i < hash_size; i++){
			T1[i] = NULL;
		}
	}
	int index = hash_function( ( my_size)pg );

	hash_ptr current;

	if ( T1[index] == NULL ){
		T1[index] = new HashNode(pgN, NULL);
	}else{
		current = T1[index];
		T1[index] = new HashNode(pgN, current);
	}


}

int check_hash(HashTable T1, void *add){

	int rest, n;
	rest = (my_size)add % 4096;
	void *start = (char *)add - rest;

	int index = hash_function((my_size)start);

	hash_ptr current = T1[index];

	while(current != NULL){

		if(current->get_pgNode()->get_page() == start ) {
								//(pg - start)/ class_size = n - 1
			n = ( (my_size)add - (my_size)start ) / ( current->get_pgNode()->get_size() ) + 1;

			current->get_pgNode()->flip_nth_bit(n);
			return 1;
		}else{
			current = current->get_next();			//search next node in hash_list
		}
	}
	return 0;

}

