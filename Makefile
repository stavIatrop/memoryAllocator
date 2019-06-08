OBJS     = d_list.o functions.o hash_list.o allocator.o main.o
SOURCE	 = d_list.cpp functions.cpp hash_list.cpp allocator.cpp main.c
HEADER	 = d_list.h hash_list.h functions_prototypes.h
OUT	 = allocator
CPP	 = g++
FLAGS	 = -c

all: $(OBJS)
	$(CPP) $(OBJS) -o $(OUT)

main.o: main.c function_prototypes.h d_list.h hash_list.h
	$(CPP) $(FLAGS) main.c

d_list.o: d_list.cpp d_list.h
	$(CPP) $(FLAGS) d_list.cpp

functions.o: functions.cpp hash_list.h d_list.h
	$(CPP) $(FLAGS) functions.cpp

hash_list.o: hash_list.cpp hash_list.h d_list.h
	$(CPP) $(FLAGS) hash_list.cpp

allocator.o: allocator.cpp function_prototypes.h hash_list.h d_list.h
	$(CPP) $(FLAGS) allocator.cpp
clean:
	rm -f $(OBJS) $(OUT)
