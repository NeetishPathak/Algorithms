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

//#define DEBUG
#ifdef DEBUG
#include <fstream>
ifstream ipFile;
ofstream opFile;
#define cin ipFile
#define cout opFile
#endif

/*This function helps get the key for a value in a hash-map*/
int getKey(map<int, string> cmap, string str){
    for(map<int,string>::const_iterator itr =  cmap.begin(); itr != cmap.end(); ++itr){
        if(itr->second == str){
            return itr->first;
        }
    }
    return -1;
}


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

Graph::Graph(int v){
    this->verticesNum = v;
    adjacencyList = new list<int>[v];
}

Graph::Graph(int v, map<int,string> cmap){
    this->verticesNum = v;
    this->courseMap = cmap;
    adjacencyList = new list<int>[v];
}

Graph::~Graph(){

}

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

void Graph::addEdge(int v, int w){
    adjacencyList[v].push_back(w);
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack){
    visited[v] = true;

    for(list<int>::iterator itr = adjacencyList[v].begin(); itr != adjacencyList[v].end(); ++itr){
        if(visited[*itr] != true){
            fillOrder(*itr,visited,Stack);
        }
    }
    Stack.push(v);
}

void Graph::printSCC(){
    bool *visited = new bool[verticesNum];
    stack<int> testStack;

    for(int i = 0; i< verticesNum; ++i){
        visited[i]  = false;
    }

    for(int i=0; i < verticesNum; ++i){
        if(visited[i] == false){
            fillOrder(i, visited, testStack);
        }
    }

    Graph revGr = revGraph();

    for(int i = 0; i< verticesNum; ++i){
        visited[i]  = false;
    }

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



int main()
{
    #ifdef DEBUG
        ipFile.open("t3.txt");
        opFile.open("o3.txt");

    #endif

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

    #ifdef DEBUG
        ipFile.close();
        opFile.close();
    #endif // DEBUG
    return 0;
}
