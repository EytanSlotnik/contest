//
// Created by eythe on 25/12/2022.
//
#include "Huffman.hpp"
#include <bitset>
#include <queue>
#include <iostream>
#include <functional>
#include <cmath>
#include <numeric>

double calculateDivergence(const uint32_t *array1, const uint32_t *array2) {
    double divergence = 0;
    uint32_t array1_len = 0;
    uint32_t array2_len = 0;
    for (uint32_t i = 0; i < 256; i++) {
        array1_len += array1[i];
        array2_len += array2[1];
    }

    for (size_t i = 0; i < 256; ++i) {
        double p = static_cast<double>(array1[i]) / array1_len;
        double q = static_cast<double>(array2[i]) / array2_len;

        if (p != 0 && q != 0) {
            divergence += p * std::log2(p / q);
        }
        if ((array1[i] == 0 && array2[i] != 0) || (array1[i] != 0 && array2[i] == 0)){
            return std::numeric_limits<double>::max();
        }
    }

    return divergence;
}


#define SET_BIT(arr, index) (arr[index >> 3] |= (1 << (index & 7)))
#define UNSET_BIT(arr, index) (arr[index >> 3] &= ~(1 << (index & 7)))
#define GET_BIT(arr, index) (((arr[index >> 3] & (1 << (index & 7)))) >> (index & 7))


uint32_t freqs[NUM_OF_TREES][256] = {
        {41379, 5248, 2816, 2137, 1603, 1314, 1130, 958, 839, 708, 639, 561, 550, 456, 398, 388, 348, 292, 259, 235, 228, 206, 193, 189, 156, 153, 126, 98, 94, 93, 117, 106, 88, 89, 78, 69, 63, 63, 62, 60, 54, 39, 54, 50, 43, 41, 37, 37, 23, 33, 28, 30, 24, 29, 23, 20, 35, 32, 25, 27, 14, 14, 21, 11, 16, 21, 13, 12, 9, 9, 8, 12, 6, 8, 12, 12, 9, 6, 12, 8, 7, 3, 7, 7, 4, 4, 9, 5, 7, 4, 3, 3, 2, 7, 6, 0, 3, 3, 2, 3, 1, 3, 2, 3, 0, 3, 0, 2, 3, 2, 0, 1, 3, 4, 1, 3, 3, 3, 5, 2, 4, 3, 1, 3, 0, 4, 2, 3, 1, 1, 1, 2, 4, 2, 3, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 2, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 2, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 2, 2, 0, 1, 0, 0, 1, 3, 2, 0, 1, 1, 0, 0, 1, 1, 2, 1, 0, 2, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        {33426, 3545, 1856, 1740, 1584, 1369, 1355, 1186, 1169, 988, 928, 883, 821, 738, 762, 684, 620, 588, 566, 510, 532, 473, 410, 404, 414, 355, 357, 320, 340, 289, 287, 259, 257, 239, 236, 224, 207, 230, 201, 160, 171, 189, 183, 178, 153, 143, 149, 131, 126, 130, 103, 105, 128, 84, 97, 99, 89, 95, 98, 76, 69, 66, 64, 66, 64, 57, 49, 50, 52, 46, 42, 47, 34, 29, 38, 39, 43, 30, 31, 31, 25, 29, 25, 23, 24, 26, 14, 20, 22, 13, 15, 15, 15, 13, 10, 13, 12, 8, 8, 5, 6, 14, 15, 4, 8, 10, 9, 4, 8, 6, 3, 1, 4, 6, 1, 2, 1, 5, 3, 4, 1, 4, 1, 2, 3, 1, 7, 3, 1, 1, 8, 1, 1, 2, 3, 1, 2, 0, 3, 4, 1, 4, 2, 2, 2, 3, 0, 3, 2, 1, 3, 3, 3, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 0, 2, 2, 2, 2, 1, 2, 0, 0, 3, 1, 2, 0, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 3, 1, 2, 1, 2, 7, 5, 2, 2, 2, 4, 0, 4, 0, 3, 3, 0, 4, 0, 8, 4, 6, 0, 4, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 0, 4, 2, 2, 1, 3, 3, 4, 0, 4, 9, 1, 1, 2, 3, 3, 3, 3, 1, 2, 3, 6, 5, 1, 3, 4, 3, 2, 3, 2, 3, },
        {4391, 745, 521, 455, 477, 407, 405, 400, 405, 438, 381, 381, 351, 371, 360, 307, 372, 314, 340, 320, 326, 305, 307, 300, 296, 304, 269, 290, 269, 277, 290, 278, 299, 279, 317, 265, 284, 269, 257, 296, 276, 284, 254, 256, 297, 278, 287, 266, 256, 277, 275, 251, 256, 263, 256, 281, 282, 257, 259, 255, 249, 254, 277, 252, 276, 234, 249, 246, 265, 241, 267, 269, 259, 270, 243, 251, 261, 230, 239, 281, 242, 245, 247, 264, 270, 259, 241, 281, 228, 239, 234, 251, 253, 245, 228, 219, 214, 228, 219, 265, 239, 224, 241, 245, 248, 250, 227, 243, 259, 227, 239, 209, 232, 253, 242, 216, 238, 256, 225, 239, 227, 225, 211, 242, 238, 232, 219, 237, 242, 227, 218, 243, 230, 228, 221, 241, 230, 215, 207, 227, 224, 209, 212, 245, 211, 223, 208, 227, 223, 216, 196, 244, 214, 232, 244, 183, 213, 228, 247, 221, 229, 186, 206, 239, 227, 235, 198, 205, 211, 214, 201, 223, 199, 202, 234, 207, 206, 224, 200, 212, 177, 211, 221, 226, 175, 242, 231, 216, 205, 205, 193, 193, 209, 215, 203, 178, 206, 223, 214, 218, 213, 213, 224, 205, 196, 200, 202, 186, 166, 217, 211, 196, 172, 224, 188, 191, 192, 190, 184, 199, 197, 185, 172, 206, 158, 196, 219, 154, 188, 204, 206, 194, 170, 209, 189, 197, 183, 190, 174, 179, 184, 177, 171, 149, 158, 170, 167, 162, 171, 179, 145, 187, 167, 163, 160, 63, },
        {7625, 5626, 4654, 3921, 3386, 3146, 2932, 2853, 2691, 2620, 2487, 2288, 2273, 2066, 2085, 1967, 1757, 1530, 1338, 1173, 1041, 921, 769, 606, 528, 464, 408, 349, 315, 251, 236, 210, 175, 143, 146, 122, 85, 60, 59, 43, 40, 32, 37, 27, 23, 11, 13, 14, 7, 7, 3, 1, 2, 5, 2, 1, 3, 0, 1, 2, 2, 1, 2, 0, 0, 3, 3, 3, 0, 2, 1, 2, 2, 0, 2, 2, 0, 1, 0, 0, 4, 1, 3, 0, 1, 3, 1, 1, 3, 0, 2, 2, 3, 0, 0, 1, 1, 1, 2, 1, 3, 3, 1, 1, 1, 2, 1, 0, 3, 1, 2, 1, 2, 0, 1, 2, 2, 0, 0, 0, 1, 2, 1, 0, 0, 1, 2, 0, 1, 1, 0, 2, 1, 3, 0, 0, 0, 4, 2, 4, 1, 2, 0, 1, 1, 2, 1, 0, 5, 3, 2, 1, 5, 5, 2, 1, 2, 3, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, },
        {223673, 58653, 30121, 19855, 14588, 11050, 8835, 7441, 6330, 5352, 4725, 4113, 3552, 3038, 2525, 2043, 1673, 1445, 1139, 823, 670, 534, 441, 314, 275, 222, 194, 171, 153, 163, 121, 113, 102, 97, 74, 70, 77, 55, 60, 41, 52, 41, 40, 41, 37, 17, 25, 26, 25, 32, 15, 16, 14, 19, 19, 12, 22, 19, 8, 12, 10, 6, 6, 4, 4, 6, 3, 6, 6, 6, 5, 5, 0, 4, 1, 2, 2, 2, 4, 2, 4, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 3, 1, 1, 1, 0, 2, 0, 0, 4, 1, 2, 0, 1, 0, 3, 4, 5, 1, 1, 6, 0, 3, 5, 2, 5, 2, 3, 2, 4, 1, 2, 2, 1, 1, 2, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        {212915, 56637, 29123, 19144, 14319, 11029, 9007, 7525, 6232, 5351, 4659, 4060, 3256, 2911, 2304, 2037, 1618, 1227, 1077, 760, 597, 536, 412, 325, 278, 198, 205, 166, 138, 135, 115, 93, 81, 81, 57, 63, 68, 55, 59, 39, 40, 39, 40, 22, 26, 24, 30, 33, 18, 18, 21, 14, 21, 23, 14, 17, 12, 11, 13, 6, 14, 16, 11, 7, 7, 10, 7, 7, 2, 5, 5, 5, 4, 2, 2, 3, 1, 4, 2, 2, 0, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 3, 2, 3, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 2, 1, 1, 2, 2, 6, 1, 0, 3, 5, 1, 2, 3, 1, 2, 6, 3, 2, 2, 0, 0, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, },
};

uint8_t find_best_freq(uint32_t target[256]) {
    uint8_t min_idx;
    double min_div = std::numeric_limits<double>::max();
    for (uint32_t i = 0; i < NUM_OF_TREES; i++) {
        double cur_div = calculateDivergence(reinterpret_cast<const uint32_t *>(target),
                                             reinterpret_cast<const uint32_t *>(freqs[i]));
        if (cur_div < min_div){
            min_div = cur_div;
            min_idx = i;
        }
    }
    return min_idx;

}


void print_huff_tree_initializer(huff_tree *tree) {
    printf("{ .root = &trees[SAMP3].nodes[%u],\n", tree->root - tree->nodes);

    printf("  .nodes = {\n");
    for (int i = 0; i < 512; i++) {
        node *n = &tree->nodes[i];
        if (n->left) {
            printf("    { .symbol = %u, .freq = %u, .left = &trees[SAMP3].nodes[%u], .right = &trees[SAMP3].nodes[%u] }",
                   n->symbol, n->freq, n->left - tree->nodes, n->right - tree->nodes);
        } else {
            printf("    { .symbol = %u, .freq = %u, .left = nullptr, .right = nullptr }",
                   n->symbol, n->freq);
        }


        if (i < 511) printf(",");
        printf("\n");
    }
    printf("  },\n");

    printf("  .codes = {\n");
    for (int i = 0; i < 256; i++) {
        printf("    { ");
        for (int j = 0; j < 256 / 8; j++) {
            printf("0x%02x", tree->codes[i][j]);
            if (j < 256 / 8 - 1) printf(", ");
        }
        printf(" }");
        if (i < 255) printf(",");
        printf("\n");
    }
    printf("  },\n");

    printf("  .code_lengths = { ");
    for (int i = 0; i < 256; i++) {
        printf("%u", tree->code_lengths[i]);
        if (i < 255) printf(", ");
    }
    printf(" }\n");

    printf("}");
}


std::ostream &operator<<(std::ostream &os, node &n) {
    const char *node_type = (n.left == nullptr) ? "symbol - " : "empty - ";
    os << node_type << (uint32_t) n.symbol << " - freq " << n.freq;
    if (n.left) {
        os << " - right " << (uint32_t) n.right->symbol << " - left " << (uint32_t) n.left->symbol;
    }
    os << std::endl;
    return os;
}

bool operator<(const node &lhs, const node &rhs) {
    return lhs.freq > rhs.freq;
}

void code_map_gen(node *node, uint8_t *code, uint32_t depth, huff_tree *tree) {
    if (node == nullptr) {
        return;
    }
    if (node->left == nullptr) {
        for (int i = 0; i < (depth >> 3) + 1; ++i) {
            tree->codes[node->symbol][i] = code[i];
        }
        tree->code_lengths[node->symbol] = depth;
    } else {
        SET_BIT(code, depth);
        code_map_gen(node->left, code, depth + 1, tree);
        UNSET_BIT(code, depth);
        code_map_gen(node->right, code, depth + 1, tree);
    }
}

void create_tree(const uint32_t freq[256], huff_tree &tree) {
    node *nodes = tree.nodes;
    for (int i = 0; i < 512; i++) {
        nodes[i].symbol = i;
        nodes[i].freq = freq[i];
        nodes[i].left = nullptr;
        nodes[i].right = nullptr;
    }
    for (int i = 256; i < 511; i++) {
        nodes[i].symbol = 0;
        nodes[i].freq = 0;
        nodes[i].left = nullptr;
        nodes[i].right = nullptr;
    }
    // Create priority queue of reference of nodes with lowest freq at top
    std::priority_queue<std::reference_wrapper<node>> pq;
    for (int i = 0; i < 256; i++) {

            pq.push(nodes[i]);

    }

    uint32_t non_leaf_idx = 256;

    while (pq.size() > 1) {
        node &left = pq.top();
        pq.pop();
        node &right = pq.top();
        pq.pop();
        nodes[non_leaf_idx].freq = left.freq + right.freq;
        nodes[non_leaf_idx].left = &left;
        nodes[non_leaf_idx].right = &right;
        pq.push(nodes[non_leaf_idx]);
        non_leaf_idx++;
    }
    tree.root = &nodes[--non_leaf_idx];


    uint8_t code[256 / 8 + 1] = {0};
    code_map_gen(tree.root, code, 0, &tree);

    // print tree in breadth first order
//    std::queue<node *> q;
//    q.push(tree.root);
//    while (!q.empty()) {
//        node *cur = q.front();
//        q.pop();
//
//        std::cout << *cur << std::endl;
//        if (cur->left != nullptr) {
//            q.push(cur->left);
//        }
//
//        if (cur->right != nullptr) {
//            q.push(cur->right);
//        }
//    }

}

void encode_with_tree(Data_Buffer *data, huff_tree &tree) {
//    for (uint32_t i = 0; i < data->size; i++){
//        std::cout << data->data[i] << " - " ;
//        for (uint32_t j = 0; j < tree.code_lengths[data->data[i]]; j++){
//            std::cout << GET_BIT(tree.codes[data->data[i]], j);
//        }
//        std::cout << std::endl;
//    }
    uint32_t new_size = 0;
    uint8_t *old = new uint8_t[data->size];
    memcpy(old, data->data, data->size);
    for (uint32_t i = 0; i < data->size; i++) {
        if (tree.code_lengths[old[i]] == 0) {
            data->size = -1;
            return;
        }
        for (uint32_t j = 0; j < tree.code_lengths[old[i]]; j++) {
            if (GET_BIT(tree.codes[old[i]], j)) {
                SET_BIT(data->data, new_size);
            } else {
                UNSET_BIT(data->data, new_size);
            }
            new_size++;
        }
    }

//    for (uint32_t i = 0; i < new_size; ++i) {
//        std::cout << GET_BIT(data->data, i);
//    }
//    std::cout << std::endl;
    data->size = new_size;
}


void HUF_transform(Data_Buffer *data) {


    huff_tree tree = {0};
    // freqs array for each symbol in data with a[i] = i
    uint32_t freq[256] = {0};
    for (uint32_t i = 0; i < data->size; i++) {
        freq[data->data[i]]++;
    }
//    std::cout << "{";
//    for (uint32_t f: freq) {
//        std::cout << f << ", ";
//    }
//    std::cout << "}";
    uint8_t freq_idx = find_best_freq(freq);
    create_tree(freqs[freq_idx], tree);
    encode_with_tree(data, tree);

    uint32_t j = data->size;
    while ((j & 7) != 0) {
        UNSET_BIT(data->data, j);
        j++;
    }
    uint32_t *int_end = (uint32_t *) (data->data + (j / 8));
    *(int_end) = data->size;
    data->size = (j / 8) + sizeof(uint32_t);
    data->data[data->size++] = freq_idx;

}

void decode_with_tree(Data_Buffer *data, huff_tree &tree) {
    uint8_t *old = new uint8_t[(data->size >> 3) + 1];
    memcpy(old, data->data, (data->size >> 3) + 1);
    uint32_t new_size = 0;
    node *cur = tree.root;
    for (uint32_t i = 0; i < data->size; i++) {
        uint8_t bit = GET_BIT(old, i);
        if (bit) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }

        if (cur->left == nullptr) {
            data->data[new_size++] = cur->symbol;
            cur = tree.root;
        }
    }
    data->size = new_size;
}


void HUF_inverse(Data_Buffer *data) {
    huff_tree tree = {0};

    uint8_t freq_idx = data->data[--data->size];
    data->size = *((uint32_t *) (data->data + data->size - 4));
    create_tree(freqs[freq_idx], tree);

    decode_with_tree(data, tree);
}