knapsack: main.o n_item.o
	c++ -o knapsack main.o n_item.o
main.o: main.cpp
	c++ -c main.cpp
n_item.o: n_item.cpp
	c++ -c n_item.cpp
n_item.o : n_item.hpp

clean:
	rm -f knapsack main.o n_item.o
