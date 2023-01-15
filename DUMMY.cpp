//
// Created by reuto on 15/01/2023.
//
// C++ program to print all
// possible strings of length k
#include <bits/stdc++.h>
#include "DUMMY.h"

using namespace std;

// The main recursive method
// to print all possible
// strings of length k





void print_vector(vector<METHOD> str){
    for (int i=0; i<str.size(); ++i) {
        if (str[i]==HUF){
            std::cout << "HUF" << ' ';
        }
        else{
            std::cout << str[i]<< ' ';
        }
    }
}

void print_global_result(){
    for (int i=0; i<global_result.size(); ++i) {
        print_vector(global_result[i]);
        std::cout<<endl;
    }


}
void printAllKLengthRec(vector<METHOD> set, vector<METHOD> prefix, int len, int num_of_methods) {



    // Base case: k is 0,
    // print prefix
    if (len == 0) {
        //add_vector(prefix, global_result
        global_result.push_back(prefix);
        return;
    }

    // One by one add all characters
    // from set and recursively
    // call for k equals to k-1
    for (int i = 0; i < num_of_methods; i++) {
        vector<METHOD> newPrefix;
        newPrefix = prefix;
        // Next character of input added
        newPrefix.push_back(set[i]);

        // k is decreased, because
        // we have added a new character

        printAllKLengthRec(set, newPrefix, len-1, num_of_methods);


    }
}

vector<vector<METHOD>>  printAllKLength(vector<METHOD> set, int len, int num_of_methods) {
    vector<METHOD> prefix;
    for (int l = 0; l<= len; l++) {
        printAllKLengthRec(set, prefix, l, num_of_methods);
    }
    return global_result;
}

// Driver Code
//int main() {
//
//    cout << "First Test" << endl;
//    vector<METHOD> set1    {BWT,MTF,HUF,RLE};
//    int k = 3;
//    printAllKLength(set1, k, set1.size());
//    std::cout << global_result.size()<<endl;
//    print_global_result();
//}



//    cout << "Second Test\n";
//    vector<METHOD> set2 {"a", "b", "c", "d"};
//    k = 1;
//    printAllKLength(set2, k, set2.size());


// This code is contributed
// by Mohit kumar
