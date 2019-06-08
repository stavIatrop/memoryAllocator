# Memory Allocator

Implementation of a simple memory allocator used as an alternative for the calls of malloc/free. The allocator is implemented by using a method called "segregated fit"(seperated storage depending on object's size). "mymalloc" , "myfree" functions are manipulating only requests for 4096 bytes memory allocation, otherwise malloc/free are called.

## mymalloc
An array of size 8 representing each of the 8 size classes (each one is power of 2) starting with 32 until 4096. Each of the 8 elements point to the head of a doubly linked list which stores the "pages" used to store objects. A "pagse" consists of 4096 bytes, is aligned to 4096 bytes(address of each "page" is multiple of 4096) and are acquired by a malloc call to the system of 1MB ("page warehouse") and, then, "slice" the 1MB to multiples of 4096. Each page is allocated to store objects of the same class size (e.g. one page that belongs to the "256" size class can store up to 16 objects).

In each node of the doubly linked list(of a specific size class) there is a bit vector indicating which positions are free to store an object (of this size class). In each "mymalloc" call, a position in a page needs to be found to store the object.If no position is free on the first page of the list, the lookup continues in the next one, and so on. (If list is used up, a new page is taken from the "page warehouse". If the "page warehouse" is empty, a new malloc call(1MB) to the sytem is taking place.) When a page with a free position is found, the page is moved to the top of the list so that future searches will be faster.

Every page is stored in a hashtable so it will be faster to find out if a page is used by a "mymalloc" call.

## myfree
There are two kind of objects that are "freed", the ones that were allocated by malloc and the ones that were allocated by mymalloc. In order to determine which one is happening, the address of the object is rounded down to multiple of 4096 and, by using the hashtable, either free (updating appropriately the bit vector) or "myfree" is called.