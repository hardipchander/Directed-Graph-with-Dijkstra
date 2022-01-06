// Hardip Chander 
// Date of Creation : December 1 2021
// Title of File : (CreateGraphAndTest.cc)
// In this file I will first create the adjacnecy list from the txt files 
// Then from the Adjacency Files QueryFiles I will show if the vertexes are connected by using my helper function 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "graph.h"

using namespace std;

// Used in creating the adjacency list and it is a simple function that counts the number of spaces in a string 
int CountOfSpacesInString(const string & str) {
    int counter = 0;
    for (int i = 0; i < str.length();i++) {
        if (str[i] == ' ') {
            counter++;
        }
    }

    return counter;
}

int graphTestDriver(int argc, char **argv) {
    const string input_graph_file = string(argv[1]);
    const string adjacency_queryfile= string(argv[2]);

    // Input the graph file to make the adjacency list
    Graph graph;
    ifstream graph_file(input_graph_file);
    size_t size_of_graph;

    graph_file >> size_of_graph;
    graph.Resize(size_of_graph);

    string line;
    getline(graph_file, line);
    
    // I am going to fill up the adjacency list with the numbers in the txt file by parsing the txt file 
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
                    line = line.substr(line.find(" ") +1);
                    double numbers = std::stod(number);
                    graph.InsertElement(counter, numbers);
                }
            }
        }

        counter++;
    }
    
    // Now that I have the adjacency list bulit it is time for the adjacency query file 
    ifstream adjacency_query(adjacency_queryfile);
    string line_two;
    while (getline(adjacency_query, line_two)) {
        double vertex_one = std::stod(line_two.substr(0, 1));
        double vertex_two = std::stod(line_two.substr(2));
        
        // I will call my helper function that will tell me whether the two vertexes are connected and returns the weight betweeen them 
        if (graph.TwoVertexConnected(vertex_one, vertex_two) == 0) {
            cout << line_two << ": not_connected" << endl;
        }
        else {
            cout << line_two << ": connected " << graph.TwoVertexConnected(vertex_one, vertex_two) << endl;
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    graphTestDriver(argc, argv);

    return 0;
}
