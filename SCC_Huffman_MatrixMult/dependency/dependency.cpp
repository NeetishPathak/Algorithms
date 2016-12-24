/*The following solution is developed using references from the following sources:
1. CLRS textbook
2. http://www.geeksforgeeks.org/strongly-connected-components/
3. Wikipedia: https://en.wikipedia.org/wiki/Strongly_connected_component*/

#include <iostream>
#include <list>
#include <stack>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

/******************************************************************
Function: getKey
Arguments: map<int, string>, string
Return Value: int
Description: This function helps get the key for a value from a map
*******************************************************************/
int getKey(map<int, string> cmap, string str){
    for(map<int,string>::const_iterator itr =  cmap.begin(); itr != cmap.end(); ++itr){
        if(itr->second == str){
            return itr->first;
        }
    }
    return -1;
}

/*Graph class*/
class Graph{
    int verticesNum;
    list<int> *adjacencyList;
    map<int,string> courseMap;
    vector<vector <int> > finalList;
    void fillOrder(int v, bool visited[], stack<int> &Stack);
    void dfs(int v, bool visited[], vector<int> &connVec);
public:
    /*Constructor*/
    Graph(int v);
    Graph(int v, map<int, string> cmap);
    /*Destructor*/
    ~Graph();
    /*Function to add an edge to the graph*/
    void addEdge(int v, int w);
    /*Function to print strongly connected components*/
    void printSCC();
    /*Function to get reverse/transpose the graph*/
    Graph revGraph();
};


/***********************************************************
Function: Graph - constructor
Arguments: int
Return Value: no return
Description: constructor for the graph taking no. of vertices
	     as the input argument
************************************************************/
Graph::Graph(int v){
    this->verticesNum = v;
    adjacencyList = new list<int>[v];
}


/***********************************************************
Function: Graph constructor
Arguments: int, map<int, string>
Return Value: no return value
Description: Constructor for the graph taking no. of vertices
	     and a map as input. map stores the course name and
	     an index for the courses which makes sorting the
	     course order easier(as per their entry)
************************************************************/
Graph::Graph(int v, map<int,string> cmap){
    this->verticesNum = v;
    this->courseMap = cmap;
    adjacencyList = new list<int>[v];
}

/***********************************************************
Function: Graph Destructor
Arguments: No arguments
Return Value: No return value
Description: Destructor function for Graph class
************************************************************/
Graph::~Graph(){

}

/***********************************************************
Function: dfs
Arguments: int, bool[], vector<int>
Return Value: void
Description: runs a depth first search on the graph on
	     vertex v and finds the connected
	     vertices in the order they are explored in dfs
************************************************************/
void Graph::dfs(int v, bool visited[], vector<int> &connVec){
    visited[v] = true;
    connVec.push_back(v);
    list<int>::iterator itr;
    for(itr = adjacencyList[v].begin(); itr != adjacencyList[v].end(); ++itr){
        if(visited[*itr] != true){
            dfs(*itr,visited,connVec);
        }
    }
}


/***********************************************************
Function: revGraph
Arguments: no arguments
Return Value: Graph with all edges reversed
Description: reverses the graph
************************************************************/
Graph Graph::revGraph(){
    Graph graph(verticesNum);
    for(int v = 0; v < verticesNum; ++v){
        list<int>::iterator itr;
        for(itr = adjacencyList[v].begin(); itr != adjacencyList[v].end(); ++itr){
            graph.adjacencyList[*itr].push_back(v);
        }
    }
    return graph;
}


/***********************************************************
Function: addEdge
Arguments: int, int
Return Value: void
Description: Adds an edge between vertex v and w in the graph
************************************************************/
void Graph::addEdge(int v, int w){
    adjacencyList[v].push_back(w);
}


/***********************************************************
Function: fillOrder
Arguments: int, bool[], stack<int>
Return Value: void
Description: pushes the vertices on the stack in the order in
	     which they are explored
************************************************************/
void Graph::fillOrder(int v, bool visited[], stack<int> &Stack){
    visited[v] = true;

    for(list<int>::iterator itr = adjacencyList[v].begin(); itr != adjacencyList[v].end(); ++itr){
        if(visited[*itr] != true){
            fillOrder(*itr,visited,Stack);
        }
    }
    Stack.push(v);
}


/***********************************************************
Function: printSCC
Arguments: no Arguments
Return Value: void
Description: This function prints the connected components of
	     the graph
************************************************************/
void Graph::printSCC(){
    bool *visited = new bool[verticesNum];
    stack<int> testStack;
    /*initially set all the vertices as not visited*/
    for(int i = 0; i< verticesNum; ++i){
        visited[i]  = false;
    }
    /*visit all the vertices and fill the stack in order of exploration*/
    for(int i=0; i < verticesNum; ++i){
        if(visited[i] == false){
            fillOrder(i, visited, testStack);
        }
    }
    /*Reverses the graph*/
    Graph revGr = revGraph();

    /*Again set the vertices as not visited*/
    for(int i = 0; i< verticesNum; ++i){
        visited[i]  = false;
    }

    /*From the filled stack run, a dfs to find the connected components*/
    while(testStack.empty() == false){
        int v = testStack.top();
        testStack.pop();

        if(visited[v] == false){
            vector<int> connVec;
            revGr.dfs(v, visited,connVec);
            if(connVec.size() > 1){
                std::sort(connVec.begin(),connVec.end());
                finalList.push_back(connVec);
            }
        }
    }
    /*Print the connected components in the sorted order
	Order is determined by the entry order of the
	vertices in the graph*/
    std::sort(finalList.begin(),finalList.end());
    for(unsigned int f=0; f < finalList.size(); ++f){
        vector<int> temp = finalList[f];
        for(unsigned int k =0; k < temp.size(); ++k){
            cout << courseMap[temp[k]];
                    if(k != temp.size()-1)
                    cout << " ";
        }
        cout << endl;
    }
}


/*main function*/
int main()
{
    int courseCount = 0;
    cin >> courseCount;
    int x = 0;
    string val;
    map<int,string> cmap;

    while(x < courseCount && cin >> val){
        cmap[x] = val;
        x++;
    }

    Graph g(courseCount, cmap);
    int dependencyCount;
    cin >> dependencyCount;
    x = 0;
    string val1;
    string val2;

    while((x < dependencyCount) && cin >> val1 >> val2){
        int a = getKey(cmap,val1);
        int b = getKey(cmap,val2);
        g.addEdge(a,b);
        x++;
    }

    /*Following are strongly connected components in given graph*/
    g.printSCC();
    return 0;
}

