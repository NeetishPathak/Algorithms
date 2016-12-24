#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#define HEAPTYPE 3
#define MAXVAL 2147483647
#define MINVAL -2147483648
using namespace std;

/**************************************
Function name: getMinChild
Description : function to return the minimum child node index
Arguments: vector - consisting of heap elements
            int   - parent node ID
Returns: minimum Child node index
***************************************/
int getMinChild(vector<int> &a, int x){
    unsigned int childCount = 1;
    int minValIndex = x;
    int minChildVal = MAXVAL;

    if(a.size() > 0){
        while(childCount <= HEAPTYPE){
            unsigned int child = (HEAPTYPE * x) + childCount;
            if(child > a.size() - 1){
                break;
            }else{
                if(a[child] < minChildVal && a[child] < a[x]){
                    minValIndex = child;
                    minChildVal = a[child];
                }
                childCount++;
            }
        }
    }
    return minValIndex;
}

/**************************************
Function: min_heapify
Description: places the value at its correct position in the heap
            by comparing child values
Parameters: vector<int> vector containing heap values
            int index of node to be min-heapified
Returns: void
***************************************/
void min_heapify(vector<int> &a, int x){

        int minChild = getMinChild(a, x);

        if(minChild != x){
            swap(a[minChild],a[x]);
        }else{
            return;
        }
        min_heapify(a,minChild);
}

/*****************************************
Function: getParent
Description: Function to retrieve the index of parent node
Parameters: int x : Node index whose parent node index is needed
Return value: parent index node
******************************************/
int getParent(int x){
    return (x-1)/HEAPTYPE;
}

/****************************************
Function: percolate_up
Description : Function to place a value in heap at its right
             position by comparing with the greater  valued
             parent nodes if any
Parameters : vector<int> representative vector of the heap
Returns : void
*****************************************/
void percolate_up(vector<int> &a, int x){

    int parent = getParent(x);

    if(a[parent] > a[x]){
        swap(a[x], a[parent]);
    }
    if(parent > 0)
    {
        percolate_up(a, parent);
    }
}

/***************************************
Function: insert
Description : Function to insert values in the heap
Parameters : vector<int> Representative vector of the heap
             int value that is to be inserted in the heap
Returns : void
****************************************/
void insert(vector<int> &a, int x){

    a.push_back(x);

    if(a.size() == 1){
        return;
    }

    percolate_up(a,a.size()-1);
}

/***************************************
Function: removeMin
Description: Function to remove Minimum value from the heap
Parameters : vector<int> Representative vector of the heap
returns : The minimum value in the heap
****************************************/
int removeMin(vector<int> &a){
    int retVal = 0;
    if(a.size() > 0){
        retVal = a[0];
        a[0] = a[a.size()-1];
        a.pop_back();
        min_heapify(a,0);
    }
    return retVal;
}

/******************************
Function: main
Arguments: Expects stdin
*******************************/
int main(int argc, char* args[])
{
    vector<int> A;
	string x,y;
	while(cin >> x){
		int val;
		if(x  == "add"){
            cin >> y;
            val = atoi(y.c_str());
            insert(A,val);
        }
        else if(x == "remove"){
            cout << removeMin(A) << endl;;
        }
	}
	return 0;
}
