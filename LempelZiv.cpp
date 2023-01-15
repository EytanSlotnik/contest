//
// Created by reuto on 15/01/2023.
//

#include "LempelZiv.h"
#include <stdio.h>
#include <conio.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <bitset>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdint>

using namespace std;

map<string, int> ASCII_TO_INT;
map<int, string> INT_TO_ASCII;

void init() {
    for (int i = 0; i < 256; i++) {
        string s = "";
        s += (char)i;
        ASCII_TO_INT[s] = i;
        INT_TO_ASCII[i] = s;
    }
}



string decompress(string encoded_data) {
    map<int, string> keys = INT_TO_ASCII;
    //convert to bits - i think it is already in bits
    string bits= encoded_data;
    int n_extended_bytes=floor(bits.length() / 9);
    bits = bits.substr(bits.size() - n_extended_bytes * 9);
    vector<int> data_list;
    for (int i = 0; i < n_extended_bytes; i++) {
        data_list.push_back(std::stoi(bits.substr(i * 9, 9), nullptr, 2));
    }
    string previous = keys[data_list[0]];
    string uncompressed;
    uncompressed.append(previous);
    int n_keys = 256;
    for (int i = 1; i < data_list.size(); i++) {
        if (n_keys >= 512) {
            keys = INT_TO_ASCII;
            n_keys = 256;
        }
        string current="";
        try {
            current = keys.at(data_list[i]);
        } catch (const std::out_of_range& oor) {
            current = previous + previous[0];
        }
        uncompressed.append(current);
        keys[n_keys] = previous + current[0];
        previous = current;
        n_keys += 1;
    }
    return uncompressed;}

string compress(string data) {
    map<string, int> keys = ASCII_TO_INT;
    int n_keys = 256;
    vector<int> compressed;
    int start = 0;
    int n_data = data.length() + 1;
    while (true) {
        if (n_keys >= 512) {
            keys = ASCII_TO_INT;
            n_keys = 256;
        }
        string w = "";
        bool finished = true;
        for (int i = 1; i < n_data - start; i++) {
            w = data.substr(start, i);
            if (keys.find(w) == keys.end()) {
                compressed.push_back(keys[w.substr(0, w.length() - 1)]);
                keys[w] = n_keys;
                start += i - 1;
                n_keys += 1;
                finished = false;
                break;
            }
        }
        if (finished) {
            compressed.push_back(keys[w]);
            break;
        }
    }
    string bits = "";
    for (int i = 0; i < compressed.size(); i++) {
        bits += bitset<9>(compressed[i]).to_string();
    }
    return bits;
}


//int main() {
//    init();
//    string data = " LaaReutreitreut LaaReutreitreut LaaReutreitreut LaaReutreitreut LaaReutreitreut LaaReutreitreut LaaReutreitreut eutreitreut LaaReutreitreut LaaReutreitreut LaaReutreitreut LaaReutreitreut LaaReutre";
//
//
//    string compressed = compress(data);
//    cout << compressed << endl;
//    cout << compressed.length() << endl;
//    cout << data.length() * 8 << endl;
//    cout << (float)compressed.length() / (data.length() * 8) << endl;
//    cout<< compressed<<endl;
//    string decompress_string = decompress(compressed);
//    cout << decompress_string << endl;
//    cout << decompress_string.length() << endl;
//    cout << data.length() * 8 << endl;
//    cout << (float)compressed.length() / (data.length() * 8) << endl;
//    if(data==decompress_string){
//        cout << "Well Done" << endl;
//    }
