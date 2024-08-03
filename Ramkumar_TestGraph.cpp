#include "MatrixGraph_Ramkumar.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <limits>

int main(int argc, char* argv[])
{
 	if (argc < 3) { //Checks if the number of command line arguments is less than 3
 		std::cerr << "Usage: " << argv[0] << " {-u|-w} <file> [-ud]" << std::endl;
 		return 1; //Return error code
 	}

	//Checks if the second argument states whether the graph is weighted or unweighted
	bool weighted = (std::string(argv[1])) == "-w";
	//Getting flename
	std::string filename = argv[2];

	bool isUndirected = false; //Checks for undirected
	//Iterate through the additional arguments
 	if (argc > 3) {
 		for (int i = 3; i < argc; i++) {
 			if (std::string(argv[i]) == "-ud") {
 				isUndirected = true;
 				break;
 			}
 		}
 	}

	//Menu for the user to choose action to be performed from
	int option = 1;
	while(option != 0) {
		std::cout << "Welcome to the Graph tester!\n";
		std::cout << "1) Print the graph\n";
		std::cout << "2) Find a BFS path\n";
		std::cout << "3) Find a Single Dijkstra Path\n";
		std::cout << "4) Find all Dijkstra Paths from a start\n";
		std::cout << "5) Start a file\n";
		std::cout << "6) Add a BFS path to the file\n";
		std::cout << "7) Add single Dijkstra Path to file\n";
		std::cout << "8) Add all Dijkstra Paths from a start\n";
		std::cout << "0) Quit\n";
		std::cin >> option;

		switch(option) {
		case 1: {
			std::ifstream file(filename); //Opens file
			if (!file.is_open()) { //Checks to see if file has been opened
				std::cerr << "Failed to open file." << std::endl; //Provides error message if file has not been successfully opened
				return 1;
			}

			int vertices, edges;
			file >> vertices >> edges; //Reads number of edges and vertices from the file

			MatrixGraph graph(vertices, !isUndirected); //Create a directed matricgraph with specified number of vertices
			int start, end;
			float weight;
			for (int i = 0; i < edges; i++) { //Iterate through evere edge
				file >> start >> end;
				if(weighted) {
					file >> weight;
					graph.addEdge(start, end, weight);
				}
				else {
					graph.addEdge(start, end); //Add unweighted edge to graph
				}
			}
			file.close();
			graph.toString(); //Generate the string representation of the graph
			break;
		}

		case 2: {
			std::ifstream file(filename);
			if (file.is_open() == false) {
				std::cerr << "Failed to open file." << std::endl;
				return 1;
			}
			int vertices, edges;
			file >> vertices >> edges;

			MatrixGraph graph(vertices, true);
			int start;
			int end;
			float weight;
			for (int i = 0; i < edges; i++) {
				file >> start >> end >> weight;
				graph.addEdge(start, end, weight);
			}

			file.close();

			int v1;
			int v2;
			//Read the start and end vertices
			std::cin >> v1;
			std::cin >> v2;


			//Find the path between 2 vertices using BFS
			std::vector<int> path = graph.getBFSPath(v1 - 1, v2 - 1);

			if (path.empty()) {
				std::cout << "No BFS path from " << v1 << " to " << v2 << ".";
			}
			else {//If path is not empty, print it with the vertices and weight
				std::cout << "BFS path from " << v1 << " to " << v2 << " is:\n";
				std::cout << "[" << std::setw(2) << v1 << ":  0.00]";

				float weightt = 0.0;
				for (int i = 1; i < path.size(); i++) {
					weightt += graph.getEdgeWeight(path[i - 1] + 1, path[i] + 1);
					std::cout << "==>[" << std::setw(2) << path[i] + 1 << ":" << std::setw(6) << std::fixed << std::setprecision(2) << weightt << "]";
				}
			}

			std::cout << std::endl;
			break;
		}

		case 3: {
			std::ifstream file(filename);
			if (!file.is_open()) {
				std::cerr << "Failed to open file." << std::endl;
				return 1;
			}

			int vertices, edges;
			file >> vertices >> edges;

			MatrixGraph graph(vertices, true); //Create a graph object with the specified number of vertices and edges, assuming that it is directed

			//Read the edge data from the file and add edges to the graph
			int start, end;
			float weight;
			for (int i = 0; i < edges; i++) {
				file >> start >> end >> weight;
				graph.addEdge(start, end, weight);
			}

			file.close();

			int v1, v2;
			std::cin >> v1 >> v2;

			std::vector<int> path = graph.getDijkstraPath(v1 - 1, v2 - 1); //Get the shortest path from v1 to v2 using Dijkstra's algorithm

			if (path.empty()) {
				std::cout << "No DIJKSTRA path from " << v1 << " to " << v2 << ".\n";
			} else {
			    std::cout << "DIJKSTRA path from " << v1 << " to " << v2 << " is:\n";
				std::cout << "[" << std::setw(2) << v1 << ":  0.00]";

				float weightt = 0.0; //Initialize a variable to store the cumulative weight of the path
				for (int i = 1; i < path.size(); i++) {
					weightt += graph.getEdgeWeight(path[i - 1] + 1, path[i] + 1); //Update the cumulative weight by adding the weight of the edge between the current and previous vertex
					std::cout << "==>[" << std::setw(2) << path[i] + 1 << ":" << std::setw(6) << std::fixed << std::setprecision(2) << weightt << "]"; //Print the currect vertex along with the weight of the edge
				}
				std::cout << std::endl;
			}

			break;
		}
		
		case 4: {
		    std::ifstream file(filename);
		    if(!file.is_open()) {
		        std::cerr << "Failed to open file." << std::endl;
		        return 1;
		    }

		    int vertices;
		    int edges;
		    file >> vertices >> edges;
		    MatrixGraph graph(vertices, !isUndirected); //If isUndirected is false, the graph is directed. Checks for both directed as well as undirected graphs

		    int start, end;
			float weight;
			//Add edges that are read from the file to the graph
			for (int i = 0; i < edges; i++) {
				file >> start >> end >> weight;
				graph.addEdge(start, end, weight);
			}
		    std::cin >> start;

		    //Check if start vertex is a valid input
		    if(start < 1 || start > vertices) {
		        std::cerr << "Invalid vertex" << std::endl;
		        return 1;
		    }

		    file.close();

		    std::vector<std::vector<int>> allPaths = graph.getDijkstraAll(start  -1); //Get all shortest paths from the start vertex to all other vertices using Dijkstra's algorithm

		    //Loop to print the shortest paths to all vertices from the start vertex
		    for(int i = 0; i < allPaths.size(); i++) {
		    	if(i == start - 1) { //If condition to check if the current vertex is the start vertex
		    		std::cout << "DIJKSTRA Paths start at Vertex " << start << std::endl;
		    		continue;
		    	} else {
		    		std::cout << "Path to " << i + 1<< ": ";
		    		if(allPaths[i].empty()) {
		                std::cout << "No DIJKSTRA path from " << start << " to " << i + 1;
		            }
		            else {

		                float weightt = 0.0;
                        std::cout << "[" << std::setw(2) << start << ":  0.00]";
                          for (int j = 1; j < allPaths[i].size(); j++) {

                            weightt += graph.getEdgeWeight(allPaths[i][j - 1] + 1, allPaths[i][j] + 1);
                            std::cout << "==>[" << std::setw(2) << allPaths[i][j] + 1 << ":" << std::setw(6) << std::fixed << std::setprecision(2) << weightt << "]";


                          }
                    }
		    	}
		        std::cout << std::endl;
		    }
		    break;
		}

		case 5: {

			break;
		}

		case 6: {

			break;
		}

		case 7: {

			break;
		}


		case 8: {

			break;
		}


		case 0: {
			if(option == 0) {
				break;
			}
			break;
		}

		case 9999: { //Secret case to print the raw matrix
			std::ifstream file(filename);
			if (file.is_open() == false) {
				std::cerr << "Failed to open file." << std::endl;
				return 1;
			}

			int vertices, edges;
			file >> vertices >> edges;

			MatrixGraph graph(vertices, true);
			int start, end;
			float weight;
			for (int i = 0; i < edges; i++) {
				file >> start >> end;
				if(file.peek() == ' '&& file >> weight) {
					graph.addEdge(start, end, weight);
				}
				else {
					graph.addEdge(start, end);
				}
			}

			file.close();
			std::cout << "Adjacency Matrix:\n" << std::endl;
			graph.printRaw();
			break;
		}

		default: {
			std::cout << "Invalid choice";
		}
		}
	}
	return 0;
}
