#include <iostream>
#include "hash_list.h"

using namespace std;

hash_list::hash_list(d_ptr pg, hash_ptr nxt){

	next = nxt;
	pgNode = pg;

}

void hash_list::set_next(hash_ptr nxt){

	next = nxt;
}

void hash_list::set_pgNode(d_ptr pg){

	pgNode = pg;
}

hash_ptr hash_list::get_next(){

	return next;
}

d_ptr hash_list::get_pgNode(){

	return pgNode;
}

