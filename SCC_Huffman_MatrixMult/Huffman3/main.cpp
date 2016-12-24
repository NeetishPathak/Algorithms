#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>
#define HEAPTYPE 2
#define MAXVAL 2147483647
#define MINVAL -2147483648
#define DEBUG
#define null 0x00
using namespace std;

#ifdef DEBUG
#include <fstream>
ifstream iFile;
ofstream oFile;

#define cin iFile
#define cout oFile
#endif // DEBUG

#define CHAR_MIN 0
#define CHAR_MAX 256 //Assuming an Imaginary character EOF also exists
#define INIT_FREQ 1
class Node{
int c;
int freq;
bool isleaf;
Node *leftChild;
Node *rightChild;
public:
    /*Constructor*/
    Node(int c, int f, bool b, Node* lc, Node* rc);
    /*Destructor*/
    ~Node();
    /*byte getter*/
    int getChar();
    /*Frequency getter*/
    int getFreq();
    /*Check if the node is a leaf*/
    bool isLeaf();
    /*Overloading operator >*/
    bool operator>(const Node& node){
        if(freq > node.freq){
            return true;
        }
        return false;
    }
    /*Overloading operator < */
    bool operator<(const Node& node){
        if(freq <= node.freq){
            return true;
        }
        return false;
    }

    /*overloading Node comparison with an integer*/
    bool operator>(int val){
        if(freq > val){
            return true;
        }
        return false;
    }

    bool operator<(int val){
        if(freq <= val){
            return true;
        }
        return false;
    }
    /*Retrieve children of this node
    For a leaf in the final Huffman tree, there will no child nodes*/
    Node* getLeftChild();
    Node* getRightChild();

};

Node::Node(int c, int f, bool b, Node* lc, Node* rc){
    this->c = c;
    this->freq = f;
    this->isleaf = b;
    this->leftChild = lc;
    this->rightChild = rc;
}

Node::~Node(){
    //Do nothing
}

int Node::getChar(){
    return c;
}

int Node::getFreq(){
    return freq;
}

bool Node::isLeaf(){
    return isleaf;
}

Node* Node::getLeftChild(){
    return leftChild;
}

Node* Node::getRightChild(){
    return rightChild;
}

int toInt(char c){
    stringstream ss;
    ss << c;
    int i;
    ss >> i;
    return i;
}

char toChar(int i){
//    stringstream ss;
//    char c;
//    ss << i;
//    ss >> c;
//    ss >> c;
    char c = i;
    return c;
}

void printChar(char c){
    if(c < 33 || c > 126){
        cout << ' ';
        cout << internal // fill between the prefix and the number
             << setfill('0'); // fill with 0s
        cout << hex << std::setw(2) << std::uppercase << (unsigned int )(unsigned char)c << " ";
    }else{
        cout << setfill(' ');
        cout << std::setw(3) << (unsigned char)c << " ";
    }
}

void printNode(Node a){
        Node x = a;
        printChar(toChar(x.getChar()));
        cout << x.getFreq() << " ";
        cout << x.isLeaf() << " ";

        if(x.getLeftChild() != null){
            cout << "\nLeft Child's attribute" << endl;
            Node *x1 = x.getLeftChild();
            printChar(toChar(x1->getChar()));
            cout << x1->getFreq() << " ";
            cout << x1->isLeaf();
        }

        if(x.getRightChild() != null){
            cout << "\nRight Child's attribute" << endl;
            Node *x1 = x.getRightChild();
            printChar(toChar(x1->getChar()));
            cout << x1->getFreq() << " ";
            cout << x1->isLeaf();
        }

    cout << endl;
}

void printVec(vector<Node> a){
    for(int i=0; i<a.size(); ++i){
        Node x = a[i];
        printChar(toChar(x.getChar()));
        cout << x.getFreq() << " ";
        cout << x.isLeaf() << " ";

        if(x.getLeftChild() != null){

            cout << "\nLeft Child's attribute " << x.getLeftChild() << endl;
            Node *x1 = x.getLeftChild();
            printChar(toChar(x1->getChar()));
            cout << x1->getFreq() << " ";
            cout << x1->isLeaf();
        }

        if(x.getRightChild() != null){
            cout << "\nRight Child's attribute " << x.getRightChild() << endl;
            Node *x1 = x.getRightChild();
            printChar(toChar(x1->getChar()));
            cout << x1->getFreq() << " ";
            cout << x1->isLeaf();
        }
        cout << endl;
    }

}

void copyNode(Node*n,Node m){
    *n = m;
}
/**************************************
Function name: getMinChild
Description : function to return the minimum child node index
Arguments: vector - consisting of heap elements
            int   - parent node ID
Returns: minimum Child node index
***************************************/
int getMinChild(vector<Node> &a, int x){
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
                    Node temp = a[child];
                    minChildVal = temp.getFreq();
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
Parameters: vector<Node> vector containing heap values
            int index of node to be min-heapified
Returns: void
***************************************/
void min_heapify(vector<Node> &a, int x){

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
void percolate_up(vector<Node> &a, int x){

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
Description : Function to insert Nodes in the heap
Parameters : vector<Node> Representative vector of the heap
             Node that is to be inserted in the heap
Returns : void
****************************************/
void insertNode(vector<Node> &a, Node n){

    a.push_back(n);
    //printVec(a);
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
Node removeMin(vector<Node> &a){
//    int retVal = 0;
    Node n(-1,0,false,null,null);
    if(a.size() > 0){
        //retVal = a[0].getFreq();
        Node retNode = a[0];
        a[0] = a[a.size()-1];
        a.pop_back();
        min_heapify(a,0);
        return retNode;
    }
    return (n);
}


/***************************************
Function: createHuffmanTree(vector<Node>)
Description: Function to create a Huffman tree using a priority queue
Parameters : vector<Node> Representative vector of the heap
returns : void
****************************************/
void createHuffmanTree(vector<Node> &priorityQueue){
    while(priorityQueue.size() > 1){
        Node min1 = removeMin(priorityQueue);
//        cout << "Printing minNode1" << endl;
//        printNode(min1);
        Node min2 = removeMin(priorityQueue);
//        cout << "Prinitng minNode2" << endl;
//        printNode(min2);
        int newChar = -1;
        Node *leftChild = (Node*)malloc(sizeof(Node));//()&min1;
        Node *rightChild = (Node*)malloc(sizeof(Node));//&min2;
        copyNode(leftChild,min1);
        copyNode(rightChild,min2);
        Node newNode(newChar, min1.getFreq() + min2.getFreq(), false, leftChild, rightChild);
//        printNode(newNode);
        insertNode(priorityQueue, newNode);
    }

//    cout << "**************** Printing PQ ***************" << endl;
//    printVec(priorityQueue);
}

void printCode(vector<int> huffmanCode){
    for(unsigned int i=0;  i< huffmanCode.size(); ++i){
        cout << huffmanCode[i];
    }
}

/***************************************
Function: getCodeString
Description: Function to get the string from a value in vector
Parameters : vector<int>
returns : void
****************************************/
string getCodeString(vector<int> codeArr){
    string retString = "";
    stringstream ss;
    for(int i=0; i<codeArr.size(); ++i){
        ss << codeArr[i];
        string str = ss.str();
        retString = str;
    }
    return retString;
}


/***************************************
Function: printHuffmanCodes
Description: Function to traverseHuffmanTree and print corresponding codes
Parameters : vector<Node> Representative vector of the heap
returns : void
****************************************/
void printHuffmanCodes(vector<Node> &priorityQueue, vector<int> &codeArr, Node root, map<int,string> &charMap){

    if(root.getLeftChild() != null){
//        cout << "left child found" << endl;
//        cout << "Freq of root" << endl;
//        cout << root.getChar() << " " << root.getFreq() << " " << root.isLeaf() << endl;
        Node *x = root.getLeftChild();
//        cout << "LeftChild Props" << endl;
//        cout << x->getChar() << " " << x->getFreq() << " " << x->isLeaf() << endl;
        codeArr.push_back(0);
        printHuffmanCodes(priorityQueue, codeArr, *x, charMap);
    }

    if(root.getRightChild() != null){
//        cout << "Right child found" << endl;
        codeArr.push_back(1);
        printHuffmanCodes(priorityQueue, codeArr, *root.getRightChild(), charMap);
    }

    if(root.isLeaf()){
//        printChar(toChar(root.getChar()));
//        printCode(codeArr);
//        cout << endl;
        string codeString = getCodeString(codeArr);
        charMap[root.getChar()] = codeString;
    }
    codeArr.pop_back();
}

/******************************
Function: main
Arguments: Expects stdin
*******************************/
int main(){

    #ifdef DEBUG
    iFile.open("t1.bin", fstream::in|std::fstream::out|fstream::binary);
    oFile.open("o1.txt", fstream::in|fstream::out|fstream::binary);
    #endif // DEBUG
    map<int,int> charMap;
    map<int, string> cMap;
    vector<Node> priorityQueue;
    vector<int> insertOrder;
    char c;
    for(int i= CHAR_MIN; i <= CHAR_MAX ; ++i){
            charMap[i] = INIT_FREQ;
    }

    while(cin >> c){
        //cout << c << endl;
        charMap[toChar(c)] += 1;
    }

    for(int i= CHAR_MIN; i <= CHAR_MAX; ++i){
        Node node = Node(i,charMap[i],true,null,null);
//        printChar(c);
//        cout << charMap[c] << endl;
        insertNode(priorityQueue, node);
    }

//    for(map<char, int>::const_iterator it = charMap.begin(); it != charMap.end(); ++it){
////        cout << it->first << " : " << it->second << endl;
//        Node node = Node(it->first, it->second, true, null, null);
//        insertNode(priorityQueue, node);
//    }
//    cout << "Printing priority Queue Before" << endl;
//    printVec(priorityQueue);

//    for(unsigned int i=0; i< priorityQueue.size(); ++i){
//
//        cout << priorityQueue[i].getChar() << " ";
//    }
//    cout << endl;
    createHuffmanTree(priorityQueue);
//    for(unsigned int i=0; i< priorityQueue.size(); ++i){
//
//        cout << "I am printing" << endl;
//        //cout << priorityQueue[i].getChar() << " ";
//    }
//   cout << endl;
//   cout << "Printing priority Queue" << endl;
//   printVec(priorityQueue);
//    for(unsigned int i=0; i<priorityQueue.size(); ++i){
//        cout << priorityQueue[i].getFreq() << endl;
//        cout << priorityQueue.size();
//    }
    vector<int> codeVector;
    printHuffmanCodes(priorityQueue, codeVector, priorityQueue[0], cMap);
//    for(int i=0;  i<=255; ++i){
//        cout  << internal // fill between the prefix and the number
//         << setfill('0'); // fill with 0s
//        char x = i;
//        cout << hex << std::setw(2) << std::uppercase << (unsigned int )(unsigned char)x << endl;
//    }

for(int i= CHAR_MIN; i <= CHAR_MAX; ++i){
    if(i != CHAR_MAX){
        printChar(toChar(i));
    }else{
        cout << "EOF ";
    }
    cout << cMap[i] << endl;
}
//cout << "EOF ";
//cout << cMap[CHAR_MAX];
//
//
//    vector<int> A;
//	string x,y;
//	while(cin >> x){
//		int val;
//		if(x  == "add"){
//            cin >> y;
//            val = atoi(y.c_str());
//            insert(A,val);
//        }
//        else if(x == "remove"){
//            cout << removeMin(A) << endl;;
//        }
//	}

	#ifdef DEBUG
	iFile.close();
	oFile.close();
	#endif // DEBUG
	return 0;
}
