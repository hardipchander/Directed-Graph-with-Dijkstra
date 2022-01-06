// Hardip Chander 
// Date of Creation : December 1 2021
// Title of File : (graph.h)
// This file contains the Graph class that stores an adjacency list which is a 2D vector 
// This file also has the Dijkstra Algorithm implemented in a function 
// I will use this file for both parts of the project 

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <vector>
#include <limits>
using namespace std;

class Graph {
public :
	// Constructor 
	Graph() : number_of_vertices_(0) {
	}

	// Resize data member elements which is a 2d vector and this fucntion is used in part 1
	void Resize(size_t number_of_vertices) {
		number_of_vertices_ = number_of_vertices;
		elements_.resize(number_of_vertices);
	}

	// Simple getter fucntion that returns the number of vertices 
	size_t GetNumberOfVertices() const {
		return number_of_vertices_;
	}

	// Adds element at the specified vertex into the adjacency list which is the 2d vector elements 
	void InsertElement(int & vertex, double & element) {
		elements_[vertex].push_back(element);
	}

	// This function returns the weight between two vertexes and this function is used in part 1
	// It returns 0 if first vertex is not connected to the second vertex else it returns the weight that connects them 
	double TwoVertexConnected(double& vertex_first, double& vertex_second) {
		if (elements_[vertex_first - 1].size() == 0) {
			return 0;
		}
		else {
			for (int i = 0; i < (elements_[vertex_first - 1].size() - 1); i = i + 2) {
				if (elements_[vertex_first - 1][i] == vertex_second) {
					return elements_[vertex_first - 1][i + 1];
				}
			}
		}

		return 0;
	}

	// This function is used in part 2 inside the Dijkstra algorithm and it returns the weight that connects the two specified vertexes 
	// I call this function when I know that both of the vertexes are adjacent to each other 
	double TwoVertexConnect(size_t vertex_first, size_t vertex_second) {
		for (int i = 0; i < (elements_[vertex_first - 1].size() - 1); i = i + 2) {
			if (elements_[vertex_first - 1][i] == vertex_second) {
					return elements_[vertex_first - 1][i + 1];
			}
		}
		
		return 0;
	}

	// The Dijkstra Algorithm 
	void Dijkstra(int vertex_number) {
		// The two function set all vertex values like for known to false, for distance to infinity and sets up the adjacency vertices for each vertex 
		BuildUpVertices();
		BuildUpAdjacnecyList();

		Vertex &s = vertices_[vertex_number - 1];
		s.distance_ = 0;

		BinaryHeap<Vertex> priority_queue;
		priority_queue.insert(s);

		while (true) {

			bool sucessful = false;
			size_t num;

			while (priority_queue.isEmpty()==false  && sucessful==false) {
				const Vertex& v_copy = priority_queue.findMin();
				num = v_copy.number_;
				priority_queue.deleteMin();
				if (v_copy.known_or_not_ == false) {
					sucessful = true;
				}

			}

			if (sucessful==false) {
				break;
			}

			// Set v to vertex in vector data member and say that v is known 
			Vertex& v = vertices_[num-1];
			v.known_or_not_ = true;

			// w is all the vertices adjacent to vertex v
			for (int i = 0; i < v.adjacent_elements_.size(); i++) {

				Vertex &w = vertices_[(v.adjacent_elements_[i]-1)];
				// We only care if w is not known and if it is then ignore it
				if (w.known_or_not_ == false) {
					if (v.distance_ + TwoVertexConnect(v.number_, w.number_) < w.distance_) {

						w.distance_ = v.distance_ + TwoVertexConnect(v.number_, w.number_);
						priority_queue.insert(w);
						w.previous_vertex_ = &v;
					}

				}
			}

		}
	}

	// This function will print the path from the start vertex to the target vertex and it is called after Dijkstra has finished 
	// When I call this function I know there is a path from start vertex to target vertex and start vertex does not equal target vertex 
	void PrintPath(int start_vertex, int target_vertex) const {
		vector<int> path_values;
		path_values.push_back(target_vertex);
		int transverse_vertex = target_vertex;

		bool reach_end = false;
		while (reach_end == false) {
			if (transverse_vertex == start_vertex) {
				path_values.push_back(start_vertex);
				reach_end = true;
			}
			else {
				transverse_vertex = vertices_[transverse_vertex - 1].previous_vertex_->number_;
				path_values.push_back(transverse_vertex);
			}

		}

		// print out the path by printing the numbers of the vertices in the vector path_values 
		for (int s = path_values.size() - 2; s >= 0; s--) {
			cout << path_values[s] << " ";
		}
	}

	// Simple function that returns whether the vertex is known or not after the Dijkstra Algorithm has been completed 
	// It is used for displaying the output at the end
	bool KnownVertexOrNot(int vertex_number) const {
		return vertices_[vertex_number - 1].known_or_not_;
	}

	// Returns the cost of the vertex after the Dijkstra Algorithm has been completed 
	// This function is used to display the output 
	double CostOfVertex(int vertex_number) const {
		return vertices_[vertex_number - 1].distance_;
	}

private :
	// I will use this struct in part 2 of the project 
	struct Vertex {

		// number of the vertex (1,2....)
		size_t number_;

		// a vector that stores the numbers of the adjacent vertices 
		vector<double> adjacent_elements_;

		// whether the vertex is known or not 
		bool known_or_not_;

		// distance of vertex from source 
		double distance_;

		// pointer to previous vertex in the path 
		Vertex* previous_vertex_;

		// Default Constructor and I need it because if I do not write it my compiler gives me errors for some reason
		Vertex() {

		}

		// Copy Constructor 
		Vertex(const Vertex& rhs) {
			number_ = rhs.number_;
			adjacent_elements_ = rhs.adjacent_elements_;
			known_or_not_ = rhs.known_or_not_;
			distance_ = rhs.distance_;
			previous_vertex_ = rhs.previous_vertex_;
		}

		// Move Constructor 
		Vertex(Vertex&& rhs) : previous_vertex_(rhs.previous_vertex_) {
			number_ = rhs.number_;
			adjacent_elements_ = rhs.adjacent_elements_;
			known_or_not_ = rhs.known_or_not_;
			distance_ = rhs.distance_;
		}

		// Copy Assigment 
		Vertex& operator=(const Vertex& rhs) {
			Vertex copy = rhs;
			std::swap(*this, copy);
			return *this;
		}

		// Move Assignment  
		Vertex& operator=(Vertex&& rhs) {
			std::swap(number_, rhs.number_);
			std::swap(adjacent_elements_, rhs.adjacent_elements_);
			std::swap(known_or_not_, rhs.known_or_not_);
			std::swap(distance_, rhs.distance_);
			std::swap(previous_vertex_, rhs.previous_vertex_);
			return *this;
		}

		// Overload the < operator because I will need the operator in the Binary Heap Priority Queue
		bool operator<(const Vertex& other) const {
			if (this->distance_ < other.distance_) {
				return true;
			}
			else {
				return false;
			}
		}

	};

	// I will call this function at the begining of the Dijkstra Algorithm and this function intializes the values for all the vertices like known, distance, previous  
	void BuildUpVertices() {
		vertices_.resize(number_of_vertices_);
		for (int i = 0; i < number_of_vertices_; i++) {
			vertices_[i].number_ = i + 1;
			vertices_[i].known_or_not_ = false;
			vertices_[i].distance_ = numeric_limits<double>::infinity();
			vertices_[i].previous_vertex_ = nullptr;
		}

	}

	// I will call this function at the begining of the Dijkstra Algorithm to bulit up the adjacnecy vectors for each of the vertices 
	void BuildUpAdjacnecyList() {
		for (int i = 0; i < number_of_vertices_; i++) {

			if (elements_[i].size() == 2) {
				vertices_[i].adjacent_elements_.push_back(elements_[i][0]);
			}
			else if (elements_[i].size() > 2) {

				for (int z = 0; z < (elements_[i].size() - 1); z = z + 2) {
					double num_adjacent_vertex = elements_[i][z];
					vertices_[i].adjacent_elements_.push_back(num_adjacent_vertex);
				}
			}
			else {
				// Do nothing if vertex has no adjacent elements 
			}
		}

	}

    // A list of vectors that constructs an adjacency list 
	vector<vector<double>> elements_;
	
	// stores all the vertices of the graph in a vector and it is used only in part 2 
	vector<Vertex> vertices_;

	// number of vertices in adjacency list
	size_t number_of_vertices_;
};


#endif
