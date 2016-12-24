#include <iostream>
#include <string>
#include <fstream>
#include <sys/time.h>
#include <vector>
#include <stdlib.h>
using namespace std;

const string selfMainString = "adbabdbcefhrdtcvdbcef";
const string selfNeedle = "cvdb";

/*Function: getMilliseconds (Borrowed from assignment 2)
 * Arguments : NA
 * Returns: long
 * Description: time elapsed in milliseconds at any stage of the program
 * */
long getMilliseconds() {
	timeval tv;
	gettimeofday( &tv, NULL );
	long int ms = tv.tv_sec;
	ms = ms * 1000 + tv.tv_usec / 1000;
	return ms;
}

/*Function: computePrefixFunc
 * Arguments: string
 * Returns: prefix vector
 * Description: finds the prefix from the needle
 * */
vector<int> computePrefixFunc(string needle){

	vector<int> prefixVector(needle.length()); //prefix vector will have same size as needle
	int i = 0, j = 0;
	prefixVector[i] = 0;
	if(needle.length() > 1){
		i = 1;
	}
	while( i < needle.length() ){

		if(needle[i] == needle[j]){				//if a match is found, increment j
			j++;
			prefixVector[i] = j;				//store the value of matching substring index
			i++;
		}else{
			if(j != 0){
				j = prefixVector[j-1];
			}else{
				prefixVector[i] = 0;
				i++;
			}
		}
	}

	return prefixVector;
}

/*FunctionL kmp
 * Arguments: string, string
 * Return: int
 * DEscription: returns the index at the first occurrence of
 * 				needle string n  in the main string m using kmp approach
 * */
int kmp(string m, string n){
	int i=0, j=0;

	vector<int> pfVec = computePrefixFunc(n);

	while(i < m.length()){

		if(m[i] == n[j]){		//If a match is found, keep incrementing the indices
			i++;
			j++;
		}

		if(j == n.length()){	//completely matched, return the index
			return i-j;

		}else if(i < m.length() && m[i] != n[j]){

			if(j != 0){
				j = pfVec[j-1];	 //spot the location from where we can start matching again
			}else{
				i++;
			}
		}

	}

	return -1;
}

/*Function: naive
 * Arguments: string, string
 * Return: int
 * Description: returns the index at the first occurrence of
 * 				needle string n  in the main string m
 * */
int naive(string m, string n){
	unsigned int i=0;
	unsigned int j=0;

	while(i < m.length()){

		while(n[j] == m[i]){		//Matching the characters
			if(j == n.length()-1){
				return (i - n.length() + 1);
			}
			i++;j++;
		}
		j=0;				//Start the comparison of strings once again

		if(n[j] != m[i]){
			i++; 			//since the current character in the main string is not matching the							//start of the needle, we can increment the index
		}
	}
	return -1;
}

//Another implementation of naive algorithm
int naive2(string m, string n){
	unsigned int i =0, j=0, k=0;

	for(i=0; i < m.length(); ++i){
		k = i;
		for(j = 0; j < n.length(); ++j){
			if(n[j] == m[k]){
				if(j == n.length()-1){
					return k-j;
				}
				k++;
			}else{
				break;
			}
		}
	}

	return -1;
}

/*Random string for testing*/

string generateRandomLongString(){
	string longString = "";

	for(int i=0; i<99999; ++i){
			char randChar = 65;
			longString += randChar;


	}
	longString += 66;
	return longString;
}

string generateShortString(){
	string shortString = "";

	for(int i=0; i< 999; ++i){
		char randChar = 65;
		shortString += randChar;
	}
	shortString += 66;
	return shortString;

}

/*Random string for testing*/

string generateRandomLongString2(){
	string longString = "";

	for(int i=0; i<99998; ++i){
			char randChar = 65;
			longString += randChar;


	}
	longString += 66;
	longString += 65;
	return longString;
}

string generateShortString2(){
	string shortString = "";

	for(int i=0; i< 1; ++i){
		char randChar = 66;
		shortString += randChar;
	}
	shortString += 65;
	return shortString;

}



/*Function: main
 *Parameters: command Line argument for name of the input file
 *Returns : int
 *Description: main function reads the word and the needle from
 *			   the command line argument
 * */
int main(int argc, char* argv[]){

	string mainString = "";
	string needle = "";

	if (argc < 2){				//file name is not entered, so red your own string
		mainString = selfMainString;
		needle = selfNeedle;
		string longString = generateRandomLongString();
		string shortString = generateShortString();//longString.substr(rand()%(1000), rand()%100000);
		mainString = longString;
		needle = shortString;


	}else{						//read the strings from the input file

		ifstream inputFile(argv[1]);

		if(!inputFile.is_open()){	//input file in not opening
			cout << "Could not open the input file";
		}else{
			getline(inputFile, mainString);
			getline(inputFile, needle);
		}
	}


	/*naive approach*/
	long t0 = getMilliseconds();
	int naiveOp = naive2(mainString, needle);		//using the naive O(mn) method
	long t1 = getMilliseconds();

	cout << "found at: " << naiveOp << endl;
	cout << "naive search time: " << t1-t0 << endl;

	/*standard c++ function approach*/
	t0 = getMilliseconds();
	int stdOp = mainString.find(needle);			//using standard c++ stl::string find
	t1 = getMilliseconds();

	cout << "found at: " << stdOp << endl;
	cout << "standard search time: " << t1-t0 << endl;

	/*KMP approach*/
	t0 = getMilliseconds();
	int kmpOp = kmp(mainString, needle);			//using kmp
	t1 = getMilliseconds();

	cout << "found at: " << kmpOp << endl;
	cout << "kmp search time: " << t1-t0 << endl;
	return 0;
}
