/************************************************
Course: Design and Analysis of Algorithms
	Homework4, Problem 2. maxflow.cpp
Author: Neetish Pathak (npathak2@ncsu.edu)
*************************************************/

#include <iostream>	//std::cout
#include <vector> 	//std::vector
#include <utility> 	//std::pair
#include <cmath>	//std::abs
#include <limits>	//std::max
#include <map>
#include <list>
#include <stdio.h>

using namespace std;
#define INT_MAX std::numeric_limits<int>::max()

/*******************************************
Class: Graph
Description: Adjcency Matrix representation
******************************************/
class Graph{
private:
	int n;
	int maxFlow;
	int** adj;
	int source;
	int sink;
public:
	Graph(int n);
	~Graph();
	void addEdge(int i, int j, int wt);
	void displayGraph();
	void edmondKarp();
	vector<int> BFS();
	void displayFlowValues(vector< pair<int,int> >);
};

/********************************************
Function: Constructor
Paprameters: int (no. of nodes in the graph)
Description: Create an adjacency matrix with 
	     of size n 
*********************************************/
Graph::Graph(int n){
	this->n = n;
	this->maxFlow = 0;
	this->source = 0;
	this->sink = 1;
	/*Populate the adjacency matrix*/
	adj = new int*[n];	
	for(int i=0; i < n; ++i){
		adj[i] = new int[n];				
		for(int j=0; j<n; ++j){
			if(i==j){
				adj[i][j] = 0;
			}else{
				adj[i][j] = INT_MAX;
			}
		}	
	}
}

/************************************************
Graph destructor
*************************************************/
Graph::~Graph(){
	//do nothing
}


/************************************************
Function: addEdge
Arguments: int,int,int
Returns: void
Description: this function adds an edge from
	     vertex given by first argument
	     to vertex given by second argument
	     of weight given by third argument
************************************************/
void Graph::addEdge(int i, int j, int wt){
	
	if(i < n && j < n){		 
		/*Populate the adjacency Matrix*/
		adj[i][j] = wt;
		adj[j][i] = 0;
	}else{
		cout << "Invalid Edge" << endl;
	}
}


/************************************************
Function: displayGraph
Arguments: none
Returns: void
Description: Utility function to print the graph
	     as adjacenyMatrix
*************************************************/
void Graph::displayGraph(){
	cout << "Displaying graph as an Adjacecny matrix" << endl;
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			if(adj[i][j] == INT_MAX){
				cout << "X" << " ";
			}else{
				cout << adj[i][j] << " ";
			}
		}
		cout << endl;
	}

}

/************************************************
Function:findShortestRoute
Arguments:none
Returns:
Description: This fucntion uses BFS to find the 
	     shortest augmented path from soure 
	     to sink
*************************************************/
vector<int> Graph::BFS(){
	
	bool visited[n]; //Keeps track of visited nodes
	vector<int> shortestOrder; //saves the shortest order from source to sink
	vector<int> criticalVec; //saves the criticalValue of the edges
	/*Initialize the vectors*/
	for(int i=0; i<n; ++i){
		visited[i] = false;
		shortestOrder.push_back(0);
		criticalVec.push_back(INT_MAX);
	}
	/*An extra space in shortestOrder array will be used to save tge critical (bottleneck edge)*/
	shortestOrder.push_back(0);
	/*Initialize critical edge as INT_MAX*/
	int criticalEdge = INT_MAX;
	/*Initialze a queue to perfrom BFS*/
	list<int> queue;
	visited[source] = true;
	queue.push_back(source);
	
	while(!queue.empty()){

		int s = queue.front();
		queue.pop_front();
		
		for(int j=0; j < n; ++j){
			if(adj[s][j] == INT_MAX){
				continue;
			}
			if(!visited[j] && adj[s][j] != 0){
				/*Save the location of parent nodes to trave the path*/
				shortestOrder[j] = s;
				/*set the critical edge value for connection s->j*/
				criticalVec[j] = min(criticalVec[s],adj[s][j]);
				/*If terminal/sink node is reached, return*/
				if(j == sink){
					shortestOrder[n] = criticalVec[sink];
					return shortestOrder;
				}else{
					visited[j] = true;
					queue.push_back(j);
				}				
			}
		}
	}
	return shortestOrder;
}


/*****************************************
 * Function: edmondKarp
 * Arguments: none
 * Returns: void
 * Description: edmondKarp
 * ***************************************/
void Graph::edmondKarp(){
	
	/*Run while loop forever till augmented paths to sink are explored*/
	
	while(true){
		vector<int> shortestOrder = BFS(); //vector to save the shortest path in BFS
		
		/*To check the shortest returned from BFS, this can be used
		for(int i=0; i<shortestOrder.size(); ++i){
			cout << shortestOrder[i] << " ";
		}
		cout << endl;
		*/
		
		/*Critical Edges for one travesral will be stored at the last index of sortedOrder vector*/
		int critEdge = shortestOrder[n];
		if(critEdge == 0){
				break; // No path is left if critical edge is 0
		}
		/*Iterate over shortest path to update the residual matrix*/
		int curNode = sink;
		while(curNode != source){
			int nextNode = shortestOrder[curNode];
			adj[curNode][nextNode] += critEdge;
			adj[nextNode][curNode] -= critEdge;
			curNode = nextNode;
		}
			shortestOrder.clear();
			//displayGraph();
			shortestOrder = BFS();
	}
	return;
}

/***************************************************
 * Function: displayFlowValues
 * Arguments: vector< pair<int,int> >
 * Returns: void
 * Description: to display the value of maxflow and flow on
 * 				the entered edges
 * ************************************************/
void Graph::displayFlowValues(vector< pair<int, int> > connectVec){
	/*print the value of maxflow*/
	for(int j=0; j<n; ++j){
		if(adj[j][source] != INT_MAX){
			maxFlow += adj[j][source];
		}
	}
	cout << maxFlow <<endl ;
	/*print all the flow values on the edges*/
	for(int i=0; i < connectVec.size(); ++i){
		cout << (connectVec[i]).first << " " << (connectVec[i]).second \
		 << " " << adj[(connectVec[i]).second][(connectVec[i]).first] << endl;
	}
	cout << endl;
}

/************************************************
Function: main function
************************************************/
int main(){
	
	int nodeCount = 0, directedEdgesCount = 0;
	int firstNode, secNode, weight;	
	vector< pair<int,int> > edgeFillOrder;
	/*Read the value of nodeCount and directedEdgesCount*/
	cin >> nodeCount >> directedEdgesCount;
	
	/*Initialze a graph*/
	Graph g(nodeCount);
	
	/*Populate the graph edges*/
	while(directedEdgesCount > 0){
		cin >> firstNode >> secNode >> weight;
		pair<int,int> connection = make_pair(firstNode, secNode);
		edgeFillOrder.push_back(connection);
		g.addEdge(firstNode, secNode, weight);
		directedEdgesCount--;
	}
	/*Run the edmond Karp algorithm on the graph*/
	g.edmondKarp();
	g.displayFlowValues(edgeFillOrder);
	return 0;
}
