typedef unsigned long long int my_size;


typedef class d_list {		//double connected list structure

	private:

		d_list *previous;
		d_list *next;
		void *page;
		int class_size;
		unsigned char *bit_vector;

	public:

		d_list(int, d_list*, d_list*, void*);
		void set_page(void *);
		void *get_page();
		void set_prev(d_list *);
		void set_next(d_list *);
		d_list *get_prev();
		d_list *get_next();
		void flip_nth_bit(int);
		int search();
		int get_size();
		~d_list();

}d_listNode;

typedef class d_list *d_ptr;

