
test: test/LinkedList test/HashTable test/LRU
	./test/LinkedList
	./test/HashTable
	./test/LRU

test/LinkedList: LinkedList.o test/LinkedList.c
	gcc -o $@ $^

test/HashTable: HashTable.o test/HashTable.c
	gcc -o $@ $^

test/LRU: test/LRU.c LRU.o LinkedList.o HashTable.o
	gcc -o $@ $^

LinkedList.o: LinkedList.c LinkedList.h
	gcc -o $@ -c LinkedList.c 

HashTable.o: HashTable.c HashTable.h
	gcc -o $@ -c HashTable.c 

LRU.o: LRU.c LRU.h HashTable.h LinkedList.h
	gcc -o $@ -c $<

clean:
	rm *.o test/LinkedList test/HashTable test/LRU

