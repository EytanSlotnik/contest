//
// Created by reuto on 15/01/2023.
//

#ifndef DUMMY_H_
#define DUMMY_H_

#include "Compress.hpp"


//
// Created by reuto on 15/01/2023.
//
// C++ program to print all
// possible strings of length k
#include <bits/stdc++.h>
using namespace std;





// The main recursive method
// to print all possible
// strings of length k

std::vector<vector<METHOD>> global_result;




void print_vector(vector<METHOD> str);


void print_global_result();

void printAllKLengthRec(vector<METHOD> set, vector<METHOD> prefix, int len, int num_of_methods);
vector<vector<METHOD>>  printAllKLength(vector<METHOD> set, int len, int num_of_methods) ;





#endif //DUMMY_H_
