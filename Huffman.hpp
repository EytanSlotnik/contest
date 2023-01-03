//
// Created by eythe on 25/12/2022.
//

#ifndef PROJECT_HUFFMAN_HPP
#define PROJECT_HUFFMAN_HPP

#include "Compress.hpp"


void HUF_transform(Data_Buffer *data);

void HUF_inverse(Data_Buffer *data);

typedef struct node {
    uint8_t symbol;
    uint32_t freq;
    struct node *left, *right;
} node;


typedef struct huff_tree {
    node *root;
    node nodes[512];
    uint8_t codes[256][256 / 8];
    uint8_t code_lengths[256];
} huff_tree;

typedef enum TREE {
    SAMP1,
    SAMP2,
    SAMP3,
    SAMP4,
    BOOK,
    BOOK2,
    NUM_OF_TREES
} TREE;

#endif //PROJECT__HUFFMAN_HPP
