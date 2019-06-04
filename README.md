# Memory Allocator

Implementation of a simple memory allocator used as an alternative for the calls of malloc/free. The allocator is implemented by using a method called "segregated fit"(seperated storage depending on object's size). "mymalloc" , "myfree" functions are manipulating only requests for 4096 bytes memory allocation, otherwise malloc/free are called.

## mymalloc
An array of size 8 representing each of the 8 size classes (each one is power of 2) starting with 32 until 4096. Each of the 8 elements point to the head of a doubly linked list which stores the "pages" used to store objects. A "page" consists of 4096 bytes, is aligned to 4096 bytes(address of each "page" is multiple of 4096) and are acquired by a malloc call to the system of 1MB and, then, "slice" the 1MB to multiples of 4096.