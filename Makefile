
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

all: dijkstra

dijkstra: MatrixGraph_Ramkumar.o Ramkumar_TestGraph.o
	$(CXX) $(CXXFLAGS) -o dijkstra MatrixGraph_Ramkumar.o Ramkumar_TestGraph.o

MatrixGraph_Ramkumar.o: MatrixGraph_Ramkumar.cpp MatrixGraph_Ramkumar.h
	$(CXX) $(CXXFLAGS) -c MatrixGraph_Ramkumar.cpp

Ramkumar_TestGraph.o: Ramkumar_TestGraph.cpp MatrixGraph_Ramkumar.h
	$(CXX) $(CXXFLAGS) -c Ramkumar_TestGraph.cpp

clean:
	rm -f *.o dijkstra