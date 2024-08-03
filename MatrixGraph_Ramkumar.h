
#ifndef MATRIXGRAPH_RAMKUMAR_H
#define MATRIXGRAPH_RAMKUMAR_H

#include <string>
#include <vector>

class MatrixGraph {
private:
	float** adjacencyMatrix; //2D array for matrix representation
	int rows; //Number of rows in the matrix
	int columns; //Number of columns in the matrix
	bool dir; //Check whether graph is directed or undirected
	int vertices;

public:
	MatrixGraph(int numVertices, bool directed); //Constructor
	~MatrixGraph(); //Deconstructor
	void addEdge(int start, int end); //Add edge between 2 vertices
	void addEdge(int start, int end, float weight); //Add weighted edge between 2 vertices in the graph
	void removeEdge(int start, int end); //Remove an edge between two vertices
	bool adjacent(int start, int end); //Check if there is an edge between 2 vertices
	float getEdgeWeight(int start, int end); //Get the weight of an edge between 2 graphs
	void setEdgeWeight(int start, int end, float weight); //Set the weight of the edge
	std::string toString(); //String representation of graph
	void printRaw(); //Print the raw matrix of the graph
	bool pathExists(int start, int end); //Check if there exists a path between 2 vertices
	std::vector<int> getBFSPath(int start, int end); //Method to perform BFS. Get the shortest path between 2 vertices
	std::vector<int> getDijkstraPath(int start, int end);
	std::vector<std::vector<int>> getDijkstraAll(int start);
};

#endif
