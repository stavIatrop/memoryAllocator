#include "d_list.h"
#define hash_size 8093

typedef class hash_list {

	private:

		hash_list *next;
		d_ptr pgNode;

	public:

		hash_list(d_ptr, hash_list *);
		~hash_list();
		void set_next(hash_list *);
		hash_list *get_next();
		void set_pgNode(d_ptr);
		d_ptr get_pgNode();

}HashNode;

typedef HashNode *hash_ptr;
typedef hash_ptr HashTable[hash_size];

