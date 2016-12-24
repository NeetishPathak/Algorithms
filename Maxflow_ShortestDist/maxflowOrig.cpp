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
class: Node
Description: Required for adjacency List 
	     represenation of the graph
********************************************/
class Node{
public: 
	int nodeId;
	int wt;
	Node* next;
	Node(int n, int wt, Node* next);
	~Node();
};


/**********************************************
Function: Node()
Arguments: int, Node*
Returns: Constuctor (NA)
Description: constructor for Node
**********************************************/
Node::Node(int n, int wt, Node* next){
	this->nodeId = n;
	this->wt = wt;
	this->next = next;
}

/**********************************************
Function: Destrctor for Node class

***********************************************/
Node::~Node(){
	// do nothing
}

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
	vector<Node*> adl;
	list< pair<int,int> > *adjList;
public:
	Graph(int n);
	~Graph();
	void addEdge(int i, int j, int wt);
	void displayGraph();
	void displayAdjList();
	void displayAdjListLib();
	void edmondKarp();
	vector<int> BFS();
	void displayFlowValues(vector< pair<int,int> >);
};

/********************************************
Arguments: int
Function: Constructor
Description: Create an adjacency matrix with 
	     of size n 
*********************************************/
Graph::Graph(int n){
	this->n = n;
	this->maxFlow = 0;
	this->source = 0;
	this->sink = 1;
	adjList = new list< pair<int,int> >[n];
	
	adj = new int*[n];	
	for(int i=0; i < n; ++i){
		adj[i] = new int[n];
		
		Node *head = NULL;
		adl.push_back(head);
						
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
		/*Populate the adjacency list from library functions*/
		pair<int,int> p1 = make_pair(j,wt);
		pair<int,int> p2 = make_pair(i,0);
		adjList[i].push_back(p1);
		adjList[j].push_back(p2);
		
		/*Populate the adjacency List made of Linked List*/		
		Node *n = new Node(j,wt,NULL);
		Node *oth = new Node(i,0,NULL);
		Node* curHead = adl[i];
		Node* otherHead = adl[j];
		n->next = curHead;
		oth->next = otherHead;
		adl[i] = n;
		adl[j] = oth;		
		 
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

/**************************************************
FunctionL displayAdjList
Arguments: none
Returns: void
Description: Displays graph as an adjecancy matrix
**************************************************/
void Graph::displayAdjList(){
	cout << "Displaying graph as an adjacency list" << endl;
	for(int i=0; i< adl.size(); ++i){
		Node* temp = adl[i];
		while(temp != NULL){
			cout << "(" << temp->nodeId << "," << temp->wt << ") ";
			temp = temp->next;
		}
		cout << endl;
	}
}

/**************************************************
FunctionL displayAdjList
Arguments: none
Returns: void
Description: Displays graph as an adjecancy matrix
**************************************************/
void Graph::displayAdjListLib(){
	cout << "Displaying graph as an adjacency list using Library list function" << endl;
	for(int i=0; i< n; ++i){
		list< pair<int,int> > l = adjList[i];  
		for(std::list< pair<int,int> >::const_iterator it = l.begin();\
			 it != l.end(); ++it){
			cout << "(" <<it->first << "," << it->second << ") ";
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
	bool visited[n];
	vector<int> shortestOrder;
	vector<int> criticalVec;
	for(int i=0; i<n; ++i){
		visited[i] = false;
		shortestOrder.push_back(0);
		criticalVec.push_back(INT_MAX);
	}
	shortestOrder.push_back(0);
	
	int criticalEdge = INT_MAX;
	list<int> queue;
	visited[source] = true;
	queue.push_back(source);

	while(!queue.empty()){

		int s = queue.front();
		//cout << s << " ";
		queue.pop_front();
		
		for(int j=0; j < n; ++j){
			if(adj[s][j] == INT_MAX){
				continue;
			}
			//cout << "Node : " << s << " Connected to : " << j << endl;
			if(!visited[j] && adj[s][j] != 0){
				//cout << "Entered Node :" << s << " Connected To : " << j  << endl;
				shortestOrder[j] = s;
				
				//cout << "Critical value for node s" << criticalVec[s] << " ";
				//cout << "Critical value for adj[s][j] - adj[j][s]" << adj[s][j] << endl;
				criticalVec[j] = min(criticalVec[s],adj[s][j]);

				if(j == sink){
					shortestOrder[n] = criticalVec[sink];
					//cout << "Found sink" << endl;
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
	vector<int> shortestOrder = BFS();
	int check = 3;
	while(check){
		for(int i=0; i<shortestOrder.size(); ++i){
			cout << shortestOrder[i] << " ";
		}
		cout << endl;
		int critEdge = shortestOrder[n];
		if(critEdge == 0){
			//cout << "I am breaking" << endl;
				break;
		}
		//cout << "Reached " << endl;
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
	
	for(int j=0; j<n; ++j){
		if(adj[j][source] != INT_MAX){
			maxFlow += adj[j][source];
		}
	}
	cout << maxFlow <<endl ;
	
	return;
}

/***************************************************
 * Function: displayFlowValues
 * Arguments: vector< pair<int,int> >
 * Returns: void
 * Description: to display the values of the flow on
 * 				the entered edges
 * ************************************************/
void Graph::displayFlowValues(vector< pair<int, int> > connectVec){
	
	for(int i=0; i < connectVec.size(); ++i){
		cout << (connectVec[i]).first << " " << (connectVec[i]).second << " " << adj[(connectVec[i]).second][(connectVec[i]).first] << endl;
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
	/*The graph was implemented and tested with three methods and */
//	g.displayGraph();
//	g.displayAdjList();
//	g.displayAdjListLib();
	/**/
	g.edmondKarp();
	g.displayFlowValues(edgeFillOrder);
//	g.displayGraph();
	return 0;
}
