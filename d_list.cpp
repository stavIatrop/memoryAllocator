#include <iostream>
#include <cstdlib>
#include "d_list.h"

using namespace std;

d_list::d_list(int n, d_list* prev, d_list* nxt, void* pg) {

	class_size = n;
	page = pg;
	previous = prev;
	next = nxt;
	if ( class_size == 4096 || class_size == 2048 || class_size == 1024  ) {
		bit_vector = (unsigned char *)malloc(sizeof(char));
		bit_vector[0] = 0x00;
	}else {
		bit_vector = (unsigned char *)malloc( (4096/(8*class_size)) *sizeof(char));
		int i;
		for( i = 0; i < (4096/(8*class_size)); i++)
			bit_vector[i] = 0x00;
	}

}

void d_listNode::set_page(void *pg){
	page = pg;
}

void * d_listNode::get_page(){
	return page;
}

void d_listNode::set_prev(d_ptr ptr){

	previous = ptr;
}

void d_listNode::set_next(d_ptr ptr){

	next = ptr;
}

d_ptr d_listNode::get_next(){

	return next;
}

d_ptr d_listNode::get_prev() {

	return previous;
}

int d_listNode::get_size(){
	return class_size;
}

void d_listNode::flip_nth_bit(int n){

	if (n <= 8)
		bit_vector[0] ^= 1 << (n - 1);
	else if (n <= 16)
		bit_vector[1] ^= 1 << (n - 8 - 1);
	else if (n <= 24)
		bit_vector[2] ^= 1 << (n - 16 - 1);
	else if (n <= 32)
		bit_vector[3] ^= 1 << (n - 24 - 1);
	else if (n <= 40)
		bit_vector[4] ^= 1 << (n - 32 - 1);
	else if (n <= 48)
		bit_vector[5] ^= 1 << (n - 40 - 1);
	else if (n <= 56)
		bit_vector[6] ^= 1 << (n - 48 - 1);
	else if (n <= 64)
		bit_vector[7] ^= 1 << (n - 56 - 1);
	else if (n <= 72)
		bit_vector[8] ^= 1 << (n - 64 - 1);
	else if (n <= 80)
		bit_vector[9] ^= 1 << (n - 72 - 1);
	else if (n <= 88)
		bit_vector[10] ^= 1 << (n - 80 - 1);
	else if (n <= 96)
		bit_vector[11] ^= 1 << (n - 88 - 1);
	else if (n <= 104)
		bit_vector[12] ^= 1 << (n - 96 - 1);
	else if (n <= 112)
		bit_vector[13] ^= 1 << (n - 104 - 1);
	else if (n <= 120)
		bit_vector[14] ^= 1 << (n - 112 - 1);
	else
		bit_vector[15] ^= 1 << (n - 120 - 1);

}



int d_listNode::search() {	//search for available position and return it, if there isn't one, return 0

	int position, i, j;

	if(class_size == 4096) {

		if( bit_vector[0] == 0x01) { 	//no available space
			return 0;
		}else{
			return 1;
		}
	}else if(class_size == 2048) {

		if( bit_vector[0] == 0x03) {	//no available space
			return 0;
		}else{
			for (i = 0; i < 2; i++) {
				if ( ( (bit_vector[0] >> i ) & 0x01) == 0x00 ) {
					position = i + 1;
					return position;
				}
			}
		}
	}else if(class_size == 1024){

		if (bit_vector[0] == 0x0F) {	//no available space
			return 0;
		}else {

			for (i = 0; i < 4; i++) {

				if ( ( (bit_vector[0] >> i ) & 0x01) == 0x00 ) {
					position = i + 1;
					return position;
				}
			}
		}
	}else {

		position = 0;

		for(j = 0; j < 4096/(8*class_size); j++) {

			if (bit_vector[j] == 0xFF) {	//no available space
				position += 8;
			}else {
				for (i = 0; i < 8; i++) {

					if ( ( (bit_vector[j] >> i ) & 0x01) == 0x00 ) {
						position = position + i + 1;
						return position;
					}
				}
			}
		}
		return 0;	//no available space;
	}

}

