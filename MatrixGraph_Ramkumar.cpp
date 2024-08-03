/*
Author: Samyukta Ramkumar

Date: 04/19/2024

Description: This project is going to build directed & undirected weighted graphs then search
them using Dijkstra’s algorithm to find best paths between nodes.

*/

#include "MatrixGraph_Ramkumar.h"
#include "Queue_Ramkumar.hpp"
#include "minmaxheap_ramkumar.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <iostream>
#include <queue>
#include <iomanip>
#include <sstream>
#include <algorithm>

MatrixGraph::MatrixGraph(int vertices, bool isDirected) : rows(vertices), columns(vertices) {
	dir = isDirected; //To check for directed or undirected

	//Dynamic memory allocation for matrix
	adjacencyMatrix = new float*[vertices];
	for(int i = 0; i < vertices; ++i) {
		adjacencyMatrix[i] = new float[vertices];

		//Initialize all elements of the matrix to 0.00
		for(int j = 0; j < vertices; ++j) {
			adjacencyMatrix[i][j] = 0.00;
		}
	}
}

//Deconstructor Method
MatrixGraph::~MatrixGraph() {
    for(int i = 0; i < rows; ++i) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}

//This method is used to add an edge between two vertices in the graph (unweighted)
void MatrixGraph::addEdge(int start, int end) {
	if (dir) { //If the graph is directed
		adjacencyMatrix[start - 1][end - 1] = 1; //Add a directed edge from the start vertex to the end vertex
	}
	else { //If the graph is undirected
		adjacencyMatrix[start - 1][end - 1] = 1; //Add an undirected edge from the start vertex to the end
		adjacencyMatrix[end - 1][start - 1] = 1; //Add an undirected edge from the end vertex to the start
	}
}

//Method to add an edge between two vertices in the graph (weighted)
void MatrixGraph::addEdge(int start, int end, float weight) {
    if (dir) {
        adjacencyMatrix[start - 1][end - 1] = weight;
    } else {
        adjacencyMatrix[start - 1][end - 1] = weight;
        adjacencyMatrix[end - 1][start - 1] = weight;
    }
}

//Method to remove an edge between two verices in the graph
void MatrixGraph::removeEdge(int start, int end) {
	//Setting the weight to 0
	adjacencyMatrix[start][end] = 0;
	if (dir) {
		adjacencyMatrix[start - 1][end - 1] = 0; //Remove directed edge from start to end
	}
	else {
		adjacencyMatrix[start - 1][end - 1] = 0; //Remove undirected edge from start to end
		adjacencyMatrix[end - 1][start - 1] = 0; //Remove undirected edge from end to start
	}
}

//This method checks if 2 vertices are adjacent to each other
bool MatrixGraph::adjacent(int start, int end) {
    if (start < 1 || start > rows || end < 1 || end > columns) {
        //Check if the vertices are within the valid range
        return false;
    }

    if (dir) { //If the graph is directed
        return adjacencyMatrix[start - 1][end - 1] != 0.0;
    } else { //If the graph is undirected
        //Check both directions and return true if any edge exists
        return adjacencyMatrix[start - 1][end - 1] != 0.0 || adjacencyMatrix[end - 1][start - 1] != 0.0;
    }
}

//Get the weight of an edge from a start to end vertex
float MatrixGraph::getEdgeWeight(int start, int end) {
    if (dir) { //If the graph is directed
        return adjacencyMatrix[start - 1][end - 1];
    } else { //If the graph is undirected
        //Check both directions and return the non-zero weight
        if (adjacencyMatrix[start - 1][end - 1] != 0.0) {
            return adjacencyMatrix[start - 1][end - 1];
        } else {
            return adjacencyMatrix[end - 1][start - 1];
        }
    }
}

//Set the weight of the edge
void MatrixGraph::setEdgeWeight(int start, int end, float weight) {
	adjacencyMatrix[start][end] = weight;
}

//This method is used to print the string representation of the graph
std::string MatrixGraph::toString() {
	std::ostringstream oss;

	for(int i = 0; i < rows; ++i) {
		oss << "[" << std::setw(2) << i + 1 << "]:";

		bool firstEdge = true;
		for(int j = 0; j < columns; ++j) {
			if(adjacencyMatrix[i][j] != 0) {
				if(firstEdge) {
					oss << "-->";
					firstEdge = false;
				} else {
					oss << "-->";
				}
				oss << "[" << std::setw(2) << i + 1 << "," << std::setw(2) << j + 1 << "::" << std::fixed << std::setprecision(2) << std::setw(6) << adjacencyMatrix[i][j] << "]";
			}
		}
		oss << std::endl;
	}

	std::string result = oss.str(); //Converts the output to string format

	std::cout << result; //Prints the string representation

	return result; //Return string representaion of the graph
}

//This method is used to print the raw adjacency matrix of the graph
void MatrixGraph::printRaw() {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < columns; j++) {
			std::cout << std::setw(7) << std::fixed << std::setprecision(2) << adjacencyMatrix[i][j]; //Prints each of the elements in the matrix with fixed spacing
		}
		std::cout << std::endl;
	}
}

//Method to check if a path exists
bool MatrixGraph::pathExists(int start, int end) {
	std::vector<int> path = getBFSPath(start, end);
	return path.empty() == false;
}

//This method finds the path between a start and end vertex using BFS search
std::vector<int> MatrixGraph::getBFSPath(int start, int end) {
	std::vector<int> path; //Vector to store the path between two vertices

	//Array to keep track of visited vertices
	bool* visited = new bool[rows];
	for (int i = 0; i < rows; ++i) {
		visited[i] = false;
	}

	//Array to keep track of parent vertices to reconstruct the path
	int* parent = new int[rows];
	for (int i = 0; i < rows; ++i) {
		parent[i] = -1;
	}

	//Queue for BFS traversal
	std::queue<int> q;
	q.push(start); //Enqueue the starting vertex
	visited[start] = true; //Mark the starting vertex as visited

	//BFS traversal loop
	while (!q.empty()) {
		int current = q.front(); //Get the current vertex from the queue
		q.pop(); //Dequeue the current vertex

		//If the current vertex is the end vertex, reconstruct the shortest path
		if (current == end) {
			//Reconstruct the shortest path using parent vertices
			int node = end;
			while (node != -1) {
				path.push_back(node);
				node = parent[node];
			}
			std::reverse(path.begin(), path.end()); //Reverse the path to get it in the correct order
			delete[] visited;
			delete[] parent;
			return path; //Return the path
		}

		//Traverse all adjacent vertices of the current vertex
		for (int i = 0; i < rows; ++i) {
			if (adjacencyMatrix[current][i] != 0 && !visited[i]) {
				q.push(i);
				visited[i] = true;
				parent[i] = current;
			}
		}
	}

	delete[] visited;
	delete[] parent;
	return path; //Return an empty path if no path exists
}

//This method uses the dijkstra algorithm to find the shortest path between 2 vertices
std::vector<int> MatrixGraph::getDijkstraPath(int start, int end) {
	std::vector<int> path; //Vector to store the shortest path between two vertices

	if (start < 0 || start >= rows || end < 0 || end >= rows) {
		return path;  //If input is invalid, return empty path
	}

	if (start == end) {
        path.push_back(start);
        return path;
    }

	//Priority queue to keep track of distances from the start vertex to each vertex
	MinHeap<DistanceVertexPair> priorityQueue(rows);

	//Array to keep track of distances from the start vertex to each vertex
	float* distance = new float[rows];
	for (int i = 0; i < rows; ++i) {
		distance[i] = std::numeric_limits<float>::infinity();
	}

	//Initialize distance of start vertex to 0
	distance[start] = 0;

	//Enqueue the distance to the start vertex
	priorityQueue.enqueue({0.0f, start});

	//Array to keep track of parent vertices to reconstruct the shortest path
	int** parent = new int*[rows];
	for (int i = 0; i < rows; ++i) {
	    parent[i] = new int[rows];
	    for (int j = 0; j < rows; ++j) {
	        parent[i][j] = -1; //Initialize all parent vertices to -1
	    }
	}

	//Dijkstra's algorithm
	while (!priorityQueue.isEmpty()) {
		//Get the vertex with the minimum distance from the priority queue
		auto minPair = priorityQueue.peek();
		priorityQueue.dequeue();

		int vertex = minPair.vertex;
		float dist = minPair.distance;

		//If the current vertex is the destination vertex, break out of the loop
		if (vertex == end) {
			break;
		}

		//If the distance of the current vertex is greater than the extracted distance, continue to the next iteration
		if (dist > distance[vertex]) {
			continue;
		}

		//Update distances for adjacent vertices
		for (int j = 0; j < rows; ++j) {
			if (adjacencyMatrix[vertex][j] != 0 && distance[vertex] + adjacencyMatrix[vertex][j] < distance[j]) {
				distance[j] = distance[vertex] + adjacencyMatrix[vertex][j];
				priorityQueue.enqueue({distance[j], j});
				parent[j][0] = vertex;
			}
		}
	}

	if (distance[end] == std::numeric_limits<float>::infinity()) {
	    if (parent[end][0] == -1) {
	        //If there is no path from start to end, return an empty path
	        delete[] distance;
	        for (int i = 0; i < rows; ++i) {
	        	delete[] parent[i];
	        }
	        delete[] parent;
	        return path;
	    } else {
	    	delete[] distance;
	    	for (int i = 0; i < rows; ++i) {
	    		delete[] parent[i];
	    	}
	    	delete[] parent;
	    	return path;
	    }
	}
	int node = end;
	while (node != -1) {
		path.push_back(node);
		node = parent[node][0];
	}
	std::reverse(path.begin(), path.end()); //Reverse the path to get it in the correct order

	//Free memory
	delete[] distance;
	for (int i = 0; i < rows; ++i) {
		delete[] parent[i];
	}
	delete[] parent;


	return path;
}

//This method returns the paths to all vertices from a certain start vertex
std::vector<std::vector<int>> MatrixGraph::getDijkstraAll(int start) {
    std::vector<std::vector<int>> allPaths;

    for (int i = 0; i < rows; ++i) {
        std::vector<int> path = getDijkstraPath(start, i); //Get the shortest path from the starting vertex to the current vertex i
        allPaths.push_back(path); //Push the obtained path to the vector of all paths
    }

    return allPaths; //Return the vector that contains all the paths from the start vertex to all other vertices
}
