#include <stdio.h>
#include "function_prototypes.h"


typedef struct node {

	long long test1;
long long test2;
long long test3;
long long test4;
long long test5;
long long test6;
long long test7;
long long test8;
	int code;
	struct node *next;
}ListNode;

typedef ListNode *NodePtr;


void InsertNewLastNode(int c, NodePtr *N ) {


	NodePtr L, temp;
	L = (NodePtr)mymalloc(sizeof(ListNode));
	L->code = c;
	L->next = NULL;

	if( *N == NULL) //empty list
		*N = L;
	else {
		temp = *N;
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = L;
	}

}

void DeleteLastNode(NodePtr *N) {

	NodePtr current, previous;

	if (*N != NULL) {	//non-empty list
		if((*N)->next == NULL){	//one element only
			myfree(*N);
			*N = NULL;
		}
		else {

			previous = *N;
			current = (*N)->next;
			while(current->next != NULL) {
				previous = current;
				current = current->next;
			}
			previous->next = NULL;
			myfree(current);
		}
	}

}

void PrintList(NodePtr N){

	NodePtr temp;
	temp = N;
	printf("(");
	while(temp != NULL) {

		printf(" %d", temp->code);
		temp = temp->next;
		if (temp != NULL)
			printf(",");
	}
	printf(" )\n");
}

NodePtr ListSearch(NodePtr N, int c) {
	NodePtr temp;
	temp = N;
	while(temp != NULL ){

		if(temp->code == c)
			return temp;
		temp = temp->next;
	}
	return temp;
}

void DeleteNode(NodePtr *N, NodePtr delnode){

	NodePtr current, previous;

	if((*N) == delnode){
		(*N) = (*N)->next;
		myfree(delnode);
		return;
	}
	previous = *N;
	current = (*N)->next;
	while(current != delnode) {
		previous = current;
		current = current->next;
	}
	previous->next = current->next;
	myfree(delnode);
}


int main(void) {

	NodePtr Head;
	Head = NULL;
	printf("%lu\n",sizeof(int));
	PrintList(Head);
	int i;
	for(i = 0; i < 10000; i++){
		InsertNewLastNode(i, &Head);
	}
	PrintList(Head);

	NodePtr del;
	for(i = 1; i <= 9999; i+=2){
		del = ListSearch(Head,i);
		if(del != NULL)
			DeleteNode(&Head, del);
	}
	PrintList(Head);
	for(i = 1; i <=9999; i+=2){
		InsertNewLastNode(i, &Head);

	}
	PrintList(Head);

	for(i = 1; i <=9999; i+=2){
		DeleteLastNode(&Head);
	}
	PrintList(Head);
}
