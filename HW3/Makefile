heapsort: main.o heap.o heapsort.o
	g++ -o main.o heap.o heapsort.o -o heapsort

main.o: main.cpp
	g++ -c main.cpp

heap.o: heap.cpp
	g++ -c heap.cpp

heapsort.o: heapsort.cpp
	g++ -c heapsort.cpp

clean:
	rm *.o heapsort
