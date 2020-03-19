knapsack: main.o n_item.o learning.o
	c++ -o knapsack main.o n_item.o learning.o
main.o: main.cpp
	c++ -c main.cpp
n_item.o: n_item.cpp
	c++ -c n_item.cpp
n_item.o : n_item.hpp
learning.o: learning.cpp
	c++ -c -std=c++17 learning.cpp
learning.o : learning.hpp

clean:
	rm -f knapsack main.o n_item.o learning.o
