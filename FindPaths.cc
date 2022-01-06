// Hardip Chander 
// Date of Creation : December 1 2021
// Title of File : (FindPaths.cc)
// In this file I will call the Dijkstra Algorithm and display its output for each vertex
// I made several helper functions in the graph.h file and I will use them here 

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "binary_heap.h"
#include "graph.h"

using namespace std;

// Used in creating the adjacency list and it is a simple function that counts the number of spaces in a string 
int CountOfSpacesInString(const string& str) {
    int counter = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            counter++;
        }
    }

    return counter;
}

int pathfindDriver(int argc, char **argv) {
    const string input_graph_file = string(argv[1]);
    int start_vertex = stoi(string(argv[2]));

    // Input the graph file to make the adjacency list like in part 1
    Graph graph;
    ifstream graph_file(input_graph_file);
    size_t size_of_graph;

    graph_file >> size_of_graph;
    graph.Resize(size_of_graph);

    string line;
    getline(graph_file, line);

    // I am going to fill up the adjacency list with the numbers in the txt file just like part 1
    // counter represents each vertex 
    int counter = 0;
    for (int i = 0; i < size_of_graph; i++) {
        getline(graph_file, line);
        int num_spaces = CountOfSpacesInString(line);

        if (num_spaces > 1) {
            line = line.substr(2);
            for (int z = 0; z < num_spaces; z++) {
                if (z == num_spaces - 1) {
                    double numbers = std::stod(line);
                    graph.InsertElement(counter, numbers);
                }
                else {
                    string number = line.substr(0, line.find(" "));
                    line = line.substr(line.find(" ") + 1);
                    double numbers = std::stod(number);
                    graph.InsertElement(counter, numbers);
                }
            }
        }

        counter++;
    }
    
    // Now I will call the Dijkstra Algorithm and display the output for each vertex in the graph by using my helper functions 
    graph.Dijkstra(start_vertex);
    int count = 0;
    while (count < size_of_graph) {
        cout << (count + 1) << ": ";
        // target vertex is the start vertex then it is a special case 
        if ((count+1) == start_vertex) {
            cout << start_vertex << " cost: " << graph.CostOfVertex(start_vertex)<<endl;
        }
        else {
            size_t vertex_num = count + 1;
            // If the target vector can not be reached from the start vertex then it is a special case 
            if (graph.KnownVertexOrNot(vertex_num) == false) {
                cout << " not_possible" << endl;
            }
            else {
                // Call my print path function that will print the path from start vertex to the target vertex 
                graph.PrintPath(start_vertex, vertex_num);
                cout << "cost: " << graph.CostOfVertex(vertex_num) << endl;

            }
        }

        count++;
    }
    
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
