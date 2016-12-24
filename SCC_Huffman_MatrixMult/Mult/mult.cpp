/*This solution is developed using the reference from Dynamic Programming chapter from CLRS textbook, lecture slides
and http://www.geeksforgeeks.org/dynamic-programming-set-8-matrix-chain-multiplication*/

#include <climits>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define INFINITY INT_MAX
#define MAX_ARR_SIZE 1000 //Assuming matrices will be checked for not very big array size. It can be increased if larger matrix dimensions are desired
using namespace std;

/*s array will be used to store the locations
where parenthization is to be done*/
int s[MAX_ARR_SIZE][MAX_ARR_SIZE];
/*finalString will store the string to be printed on the output file*/
string finalString = "";

/*************************************
Function: printOptimalParents
Arguments: int i, int j
Returns : void
Description: recursively prints out the optimal multiplication
	     sequence using the index of the
	     first matrix no. and the last matrix no.
***************************************/
void printOptimalParents(int i,int j){

    stringstream ss;
    ss << i;
    string str;
    ss >> str;
    if(i==j){
        finalString += "M" + str + " ";
    }else{
        finalString += "( ";
        printOptimalParents(i,s[i][j]);
        finalString += "* ";
        printOptimalParents(s[i][j]+1,j);
        finalString += ") ";
    }
}

/****************************************************************************
Function Name: MatrixChainMultiplication
Parameters: int matrixArray[], int matrixDimArraySz
Returns: int optimum cost
Description: Returns the optimum or minimum size of multiplying the matrices
****************************************************************************/
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
    return m[1][matrixDimArraySz-1];
}

/*main function*/
int main()
{
    vector<int> vals; //vector to store the entered dimensions of the matrices
    	int size = 0; //To read the count of the matrices
	cin >> size;
	int val;
	while(cin >> val){
		vals.push_back(val);
	}
	int arr[size];
	for(int i =0; i < vals.size(); ++i){
		arr[i] = vals[i];
	}
    MatrixChainMultiplication(arr, size);
    printOptimalParents(1,size);
    cout << finalString.substr(2,finalString.length()-5) << endl;
    return 0;
}

