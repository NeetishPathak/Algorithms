/************************************************
Course: Design and Analysis of Algorithms
	Homework4, Problem 1. allpairs.cpp
Author: Neetish Pathak (npathak2@ncsu.edu)
*************************************************/


#include <iostream>	//std::cout
#include <vector> 	//std::vector
#include <utility> 	//std::pair
#include <cmath>	//std::abs
#include <limits>	//std::max
#include <map>
#include <stdio.h>

using namespace std;
#define INT_MAX numeric_limits<int>::max()
/*****************************************************
Function: matchWords
Arguments: string, string
Returns: int
Description: This fucntion compares two strings and 
	     sends the difference in character value
	     if they differe at only one position else
	     it returns a value of -1 
*****************************************************/
int matchWords(string s1, string s2){
	int diffChars = 0;
	int diffCharDist = 0;
	int l1 = s1.length();
	int l2 = s2.length();
	int curLoc = 0;
	if(l1 != l2){
		diffCharDist = -1;
		return diffCharDist;			
	}

	while(curLoc < l1){
		/*Cmpare the characters*/
		if(s1[curLoc] == s2[curLoc]){
//			cout << "I cont" << endl;
		}else{
			
			diffCharDist = abs(s1[curLoc] - s2[curLoc]);
			diffChars  += 1;
			if(diffChars > 1){
				diffCharDist = INT_MAX;
				return diffCharDist;				
			} 
		}
		curLoc++; 	
	}
	
	return diffCharDist;
}

/**********************************************
Class: Graph
Attributes: int, int**
Methods: Constructor, Destructor, addEdge
Description: Adjecanecy Matrix implementation 
	     of Graph class
**********************************************/
class Graph{
private:
	int n;
	int **adj;
	vector<string> nodeNamesVec;
	map<string, int> nodeNamesMap;
	float avgReachableWords;
	int **nodeReachable;
public:
	Graph(int n, vector<string> nodeNames, map<string, int> nodeNamesMap);
	~Graph();
	int addEdge(int src, int dest);
	void displayGraph();
	void displayReachableNodes();
	void findShortestPaths();
	void printReachableWordsAvg();
	void printPath(string word1, string word2);
};

/******************************************************************************
Function: Graph constructor
Arguments: int, vector, map
Returns: constructor
Description: size of graph is n
	     a vector will be used to constant time access of the node name
	     a map for constant time retrieval of node keys corresponding to a name
********************************************************************************/
Graph::Graph(int n, vector<string> nodeNamesVec, map<string,int> nodeNamesMap){

	this->n = n;
	this->avgReachableWords = 0.0;
	adj = new int*[n];
	nodeReachable = new int*[n];
	for(int i=0; i<n; ++i){
		adj[i] = new int[n];
		nodeReachable[i] = new int[n];
		this->nodeNamesVec = nodeNamesVec;
		this->nodeNamesMap = nodeNamesMap;
		for(int j=0; j < n; ++j){
			if(i==j){
				adj[i][j] = 0;
			}else{
				adj[i][j] = this->addEdge(i,j);				
			}
			if(adj[i][j] == INT_MAX){
				nodeReachable[i][j] = -1;
			}else{
				nodeReachable[i][j] = j;
				avgReachableWords++;
			}		
		}
	}	
}

/*Graph destrcutor*/
Graph::~Graph(){
	//do nothing	

}

/*************************************************
Function: addEdge
Arguments: int, int
Returns: int
Description: returns the weight between two nodes
**************************************************/
int Graph::addEdge(int src, int dest){
	int weight;
	
	if(src < n && dest < n){
		weight = matchWords(nodeNamesVec[src], nodeNamesVec[dest]);
		adj[src][dest] = weight;
	}else{
		cerr << "Invalid Edge" << endl;
	}
	return weight;
}

/**********************************************************
Function: displayGraph
Arguments: None
Returns: void
Description: To display the adjacency matrix implementation
	     of the graph 
************************************************************/
void Graph::displayGraph(){
	cout << "    ";

	for(int i = 0; i < n; ++i){
		cout << i << " ";	
	}
	cout << endl;
	for(int i=0; i< n; ++i){
		cout << i << " " <<nodeNamesVec[i] << " ";
		
		for(int j=0; j<n; ++j){
			if(INT_MAX == adj[i][j] || adj[i][j] < 0){
				cout << "X" << " ";			
			}
			else
			{
				cout << adj[i][j] << " ";
			}
		}
	
		cout << endl;
	}	
}

/******************************************
Function: displayReachableNodes()
Arguments: None
Returns: void
Description: To display the reachability matrix 
*******************************************/
void Graph::displayReachableNodes(){
	cout << "    ";

	for(int i = 0; i < n; ++i){
		cout << i << " ";	
	}
	cout << endl;
	for(int i=0; i< n; ++i){
		cout << i << " " << nodeNamesVec[i] << " ";
		
		for(int j=0; j<n; ++j){

			cout << nodeReachable[i][j] << " ";
		}
	
		cout << endl;
	}	
}

/*---------------------------------------
	FLOYD- WARSHALL ALGORITHM
-----------------------------------------*/
/*******************************************************
Function: findShortesPath
Arguments: No arguments
Returns : void
Description: calculates all pair shortest distance for
	     for all the nodes in the graph
	     Also stores the k value to retrieve the 
	     paths later (To ensure linear time path access)
	     Also keep incrementing a reachable word count
	     if a path is detected between two nodes  	  
*******************************************************/
void Graph::findShortestPaths(){
	
	for(int k=0; k < n; ++k){
		for(int i=0; i<n; ++i){
			for(int j=0; j<n; ++j){
				//printf("Is %d > %d + %d : ",adj[i][j],adj[i][k],adj[k][j]);

				if(adj[i][k] == INT_MAX || adj[k][j] == INT_MAX){
				//	cout << "No" << endl;				
				}else if(adj[i][j] > adj[i][k] + adj[k][j]){
					adj[i][j] = adj[i][k] + adj[k][j];					
					/*Updating avrage reachable words*/					
					if(nodeReachable[i][j] == -1)
						avgReachableWords++;					
					/*Updating the reachability Matrix
					This matrix will be used later to retrieve path*/
					nodeReachable[i][j] = nodeReachable[i][k];
					
				}else{
								
				}	
			}			
		}
	}
	
}

/*************************************************
Function: printPath
Arguments: string, string
Return: void
Description: prints the shortest distance path from
	     node1 (word1) to node2 (word2)	
**************************************************/
void Graph::printPath(string word1, string word2){
		
	int loc1 = nodeNamesMap[word1];
	int loc2 = nodeNamesMap[word2];
	/*If the ndoes are disconnected, print not reachable*/
	if(nodeReachable[loc1][loc2] == -1){
		cout << word1 << " " << word2 << " not reachable" << endl;
		return;		
	}
	
	/*If the nodes are not exstent, display message*/
	if(word1 != word2 && loc1 == loc2){
		cout << "Entered words are : " << word1 << " "<< word2 << endl;
		cout << "Invalid case (One or both the words from the query do not exist in graph)" << endl;
		return;
	}
	
	/*If there exist a path from node1 to node2, print the path and the shortest distance*/
	cout << adj[loc1][loc2] << " ";
	cout << word1 << " ";
	while(loc1 != loc2){
		//cout << "loc1: " << loc1 << " loc2: "<<loc2 << endl;
		cout << nodeNamesVec[nodeReachable[loc1][loc2]] << " ";
		loc1 = 	nodeReachable[loc1][loc2];		
	}
	//cout << word2 << endl;
	cout << endl;
	return;
}

/********************************************
Function: printReachableWordsAvg
Arguments: No arguments
Return: void
Description: Prints the no. of reachable words
	     averaged over all the words
*********************************************/

void Graph::printReachableWordsAvg(){
	printf("%.2f\n",avgReachableWords/n);
	return;
}
/*********************************
Fucntion: main
Arguments: No arguments
Return: int
Description: The main fucntion
**********************************/
int main(){

/**	Testing matching words
	string s1 = "bot";
	string s2 = "bos";
	cout << "Difference is " << matchWords(s1,s2) << endl;
**/
	int nodeCount;
	string nodeName;
	vector<string> nodeNamesVec;
	map<string,int> nodeNamesMap;
	int queriesCount;
	string word1, word2;
	/*Read  the no. of nodes*/
	
	cin >> nodeCount;

	for(int i=0; i<nodeCount; ++i){
		cin >> nodeName;
		nodeNamesVec.push_back(nodeName);
		nodeNamesMap[nodeName] = i;
	}
	/*
	for(int i =0; i<nodeCount; ++i){
		cout << "no. " << i << " : " << nodeNamesMap[i] << " " << nodeNamesVec[i] << endl;
	}*/
	
	/*Create graph*/
	Graph g(nodeCount, nodeNamesVec, nodeNamesMap);
	//g.displayGraph();
	//g.displayReachableNodes();
	g.findShortestPaths();
	//g.displayGraph();
	//g.displayReachableNodes();
	g.printReachableWordsAvg();
	
	/*Read number of qqueries*/
	cin >> queriesCount;
	while(queriesCount > 0){
		cin >> word1 >> word2;
		/*Print the path from word1 to word2*/		
		g.printPath(word1,word2);	
		queriesCount--;
	}		
}
