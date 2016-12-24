/*
File Name: common.cpp
Created by: Neetish Pathak
Date: Sept, 07, 2016
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*********************************************************
Name: compareInc
Arguments: String vector, String vector
Description: compares two string vectors with sorted unique
             string values and gives the count of common values from them
Return: int
**********************************************************/
int compareInc(vector<string> v1, vector<string> v2){
    int l1 = v1.size();
    int l2 = v2.size();
    int countVal = 0;
    int i = 0,j = 0,k=0;
        while((k < l1 + l2) && (i < l1) && (j < l2)){

            if(v1[i] == v2[j]){
                countVal++;
                k++; i++; j++;
            }else if(v1[i] > v2[j]){
                j++;
                k++;
            }else{
                i++;
                k++;
            }
        }
        return countVal;
}


/*********************************************************
Name: LongestCommPrefix
Arguments: string, string
Description: compares two strings and give the index of last matching character
Return: int
**********************************************************/
int LongestCommPrefix(string s1, string s2){
    unsigned int m = 0;
    while(m <= s1.size() && m <= s2.size() && (s1.substr(m,1) == s2.substr(m,1))){
        m++;
    }
    return m;
}

/*********************************************************
Name: findDistinctSubStrs
Arguments: string
Description: gives a vector containing sorted unique substrings of a string
Return: vector<string>
**********************************************************/
vector<string> findDistinctSubStrs(string str){
    vector<string> suffixes;
    vector<string> distinctVals;
    unsigned int len = str.size();

    /*Extract all the suffixes from the input string*/
    for(int i=len-1; i >= 0; --i){
        string x = str.substr(i,len-i);
        suffixes.push_back(x);
    }
    /*sort the vector containing suffixes from the given string*/
    sort(suffixes.begin(),suffixes.end());

    /*get all substrings possible from the first suffix  */
    int l = suffixes[0].size();
    int r = 0;
    while(r != l){
        distinctVals.push_back(suffixes[0].substr(0,r+1));
        r++;
    }

    /*compare adjacent pair of suffixes and look for longest common prefix*/
    for(unsigned int i=0; i < suffixes.size() - 1; ++i){
        int m = LongestCommPrefix(suffixes[i],suffixes[i+1]);

        int l = suffixes[i+1].size();

        while(m != l){
            distinctVals.push_back(suffixes[i+1].substr(0,m+1));
            m++;
        }
    }
    return distinctVals;
}

/*********************************************************
Name: main
Arguments: int argc,char[][] argv
Description: main function
Return: int
**********************************************************/
int main(int argc, char* argv[])
{
    string word1, word2;

    if(argc < 3){
        cerr << "Enter two strings <string1> <string2>" << endl;
        return 1;
    }
    /*Read the two words from command line arguments and make a unique substring vector from them*/
    vector<string> distinctSubstrWord1 =  findDistinctSubStrs(argv[1]);
    vector<string> distinctSubstrWord2 =  findDistinctSubStrs(argv[2]);

    /*compare the two vectors and find the count of common substrings*/
    int commVal = compareInc(distinctSubstrWord1, distinctSubstrWord2);

    /*print the count of common substrings*/
    cout << commVal << endl;

    return 0;
}
