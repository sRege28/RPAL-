all:
	g++ -g main.cpp rp.cpp token.cpp tokenQueue.cpp Tree.cpp TreeStack.cpp parse.cpp -o p1
cl:
	rm -f*.o p1
