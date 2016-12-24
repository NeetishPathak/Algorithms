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


void quickSort(vector<int> &a, int p, int r, int limit){

    if(p + limit > r){
        insertionSort(a,p,r);
        return;
    }
    int q = partition(a, p, r);

    quickSort(a,p,q-1,limit);

    quickSort(a,q+1,r,limit);

}

int main(int argc, char* argv[])

{

    vector<int> A;

    int limit = 0;

    int x = 0;

    if(argc >= 1){

        limit = atoi(argv[1]);

	while(cin >> x){
		A.push_back(x);		
	}

	long t0 = getMilliseconds();
	quickSort(A,0,A.size()-1,limit);
	long t1 = getMilliseconds();
	fprintf( stderr, "%ld\n", t1 - t0 );

	for(int i=0; i < A.size(); ++i){
		cout << A[i] << endl;
	}
    }else{
	cerr << "Please enter the quickSort break point" << endl; 
	
    }

    
    return 0;

}
