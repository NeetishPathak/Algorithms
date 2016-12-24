/*This solution is developed using the Dynamic Programming chapters from Cormen
and http://www.geeksforgeeks.org/dynamic-programming-set-8-matrix-chain-multiplication*/
#include <climits>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define INFINITY INT_MAX

using namespace std;
int s[1000][1000];
string finalString = "";
void printOptimalParents(int i,int j){

    stringstream ss;
    ss << i;
    string str;
    ss >> str;
    if(i==j){
  //      cout << "M" + str;
        finalString += "M" + str + " ";
    }else{
    //    cout << "(";
        finalString += "( ";
        printOptimalParents(i,s[i][j]);

      //  cout << " * ";
        finalString += "* ";
        printOptimalParents(s[i][j]+1,j);
        //cout << " ) ";
        finalString += ") ";
    }
}

int MatrixChainMultiplication(int matrixArray[], int matrixDimArraySz)
{
    /*For starting the matrix row and col indices from 1*/
    int m[matrixDimArraySz][matrixDimArraySz];
    int i, j, k, L, q;

    /* m[i,j] represents the minimum no.of multiplications to compute
       the matrix M[i]M[i+1]...M[j] = M[i..j] where
       dimension of M[i] is matrixArray[i-1] x MatrixArray[i] */
    /* Multiplication cost is zero when multiplying the matrix to itself.*/
    for (i=1; i<matrixDimArraySz; i++)
        m[i][i] = 0;

    /* L is chain length*/
    for (L=2; L<=matrixDimArraySz; L++)
    {
        for (i=1; i<=matrixDimArraySz-L+1; i++)
        {
            j = i+L-1;
            m[i][j] = INFINITY;
            for (k=i; k<=j-1; k++)
            {
                /*q = cost of scalar multiplication*/
                q = m[i][k] + m[k+1][j] + matrixArray[i-1]*matrixArray[k]*matrixArray[j];
                if (q < m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }

            }
        }
    }
    /*cout << "\n";
    for(int p =1; p<matrixDimArraySz; ++p){
            for(int w = 1; w < matrixDimArraySz; ++w )
            {
                cout << m[p][w];
                cout << " ";
            }
            cout << "\n";
    }
cout << "\n" ;
    for(int p =1; p<matrixDimArraySz; ++p){
            for(int w = 1; w < matrixDimArraySz; ++w )
            {
                cout << s[p][w];
                cout << " ";
            }
            cout << "\n";
    }
*/
    return m[1][matrixDimArraySz-1];
}

int main()
{
    //int arr[] = {1, 2, 3, 4};
    //int arr[] = {30,35,15,5,10,20,25};
    //int size = sizeof(arr)/sizeof(arr[0]);
    vector<int> vals;
    /*printf("Minimum number of multiplications is %d ",
                       MatrixChainMultiplication(arr, size));*/
	int size = 0;
	cin >> size;
	int val;
	while(cin >> val){
		vals.push_back(val);
	}
	int arr[size];

	for(int i =0; i < vals.size(); ++i){
		arr[i] = vals[i];
	}
    //cout << "Minimum number of multiplications is " ;
    //cout << MatrixChainMultiplication(arr, size);
    MatrixChainMultiplication(arr, size);
    //cout << endl;
    printOptimalParents(1,size);
    //cout << "\n";
    cout << finalString.substr(2,finalString.length()-5) << endl;
    //getchar();
    return 0;
}
