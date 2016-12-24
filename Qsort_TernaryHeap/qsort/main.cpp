#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sys/time.h>


using namespace std;

long getMilliseconds() {
    timeval tv;
    gettimeofday( &tv, NULL );
    long int ms = tv.tv_sec;
    ms = ms * 1000 + tv.tv_usec / 1000;
    return ms;
}

/**********************************************
Function:
Description:
Parameters:
Returns:
***********************************************/
void insertionSort(vector<int> &a, int p, int q){

    for(int i= p+1; i <= q; ++i){
        if(a[i] < a[i-1]){
            int j = i;
            int key = a[i];
            while(j > p && (a[j-1] > key)){
                a[j] = a[j-1];
                j--;
            }
            a[j] = key;
        }
    }
}

/******************************************
Function: partition
Description: partition
Parameters : vector<int> : array to be partitioned,
            int : start index, int end index
Returns : index at which partition happens
******************************************/
int partition(vector<int> &a, int p, int q){

    int i = p-1;
    int j = p;
    int key = q;
    while(j < q){
        if(a[j] < a[key]){
            i += 1;
            swap(a[j], a[i]);
        }
        j++;
    }

    swap(a[key],a[i+1]);
    return i+1;
}
/*******************************************
Function:
Description:
Parameters:
Returns:
*********************************************/
void quickSort(vector<int> &a, int p, int r, int limit){
    if(p + limit > r){
        insertionSort(a,p,r);
        return;
    }
    int q = partition(a, p, r);
    /*
    for(unsigned int i=0; i < a.size(); ++i){
        cout << a[i] << " ";
    }
    */
    quickSort(a,p,q-1,limit);
    quickSort(a,q+1,r,limit);
}
int main(int argc, char* argv[])
{
    vector<int> A;
    string inputFile = "";
    ifstream iFile;
    ofstream oFile;
    int limit = 0;
    int x = 0;
    if(argc >= 3){
        limit = atoi(argv[1]);
        iFile.open(argv[2], ios::in);
        oFile.open(argv[3], ios::out | ios::trunc);
    }
    while(true){
        string x = "";
        int val = 0;
        iFile >> x;
        val = atoi(x.c_str());
        A.push_back(val);
        if(iFile.eof())break;
    }
    long t0 = getMilliseconds();
    quickSort(A,0,A.size()-1,limit);
    for(unsigned int i=0; i < A.size(); ++i){
        oFile << A[i] << endl;
    }
    long t1 = getMilliseconds();
    fprintf( stderr, "%ld\n", t1 - t0 );
    iFile.close();
    oFile.close();
    return 0;
}
