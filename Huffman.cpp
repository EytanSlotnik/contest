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
#include <unordered_map>;

#define SET_BIT(arr, index) (arr[index >> 3] |= (1 << (index & 7)))
#define UNSET_BIT(arr, index) (arr[index >> 3] &= ~(1 << (index & 7)))
#define GET_BIT(arr, index) (((arr[index >> 3] & (1 << (index & 7)))) >> (index & 7))

// get the i bit in int n
#define GET_INT64(n, i) (((n) >> (i)) & 1)
#define SET_INT64(n, i, val) ((n) |= ((val) << (i)))

typedef struct canonical_code
{
	uint8_t symbol;
	uint64_t code;
	uint8_t length;
} canonical_code;

void canonical_huffman_codes(canonical_code codes[256])
{

	// sort codes by length first, and then symbol
	std::sort(codes, codes + 256, [](canonical_code a, canonical_code b)
	{
	  if (a.length == b.length)
		  return a.symbol < b.symbol;
	  return a.length < b.length;
	});
	// assign codes
	uint64_t code = 0;
	for (uint32_t i = 0; i < 256; i++)
	{
		if (codes[i].length == 0)
		{
			continue;
		}
		for (uint8_t j = codes[i].length - 1; j != 255; j--)
		{
			codes[i].code =
				SET_INT64(codes[i].code,
					codes[i].length - 1 - j,
					GET_INT64(code, (j)));
		}
		for (uint32_t j = 0; j < codes[i].length; j++)
		{
			std::cout << GET_INT64(codes[i].code, j);
		}
		std::cout << std::endl;
		if (i < 255)
		{
			code = (code + 1) << (codes[i + 1].length - codes[i].length);
		}

	}
	std::sort(codes, codes + 256, [](canonical_code a, canonical_code b)
	{
	  return a.symbol < b.symbol;
	});
}

void canonical_encode(Data_Buffer* data, canonical_code codes[256])
{
//	uint8_t
}

std::ostream& operator<<(std::ostream& os, node& n)
{
	const char* node_type = (n.left == nullptr) ? "symbol - " : "empty - ";
	os << node_type << (uint32_t)n.symbol << " - freq " << n.freq;
	if (n.left)
	{
		os << " - right " << (uint32_t)n.right->symbol << " - left "
		   << (uint32_t)n.left->symbol;
	}
	os << std::endl;
	return os;
}

bool operator<(const node& lhs, const node& rhs)
{
	return lhs.freq > rhs.freq;
}

void code_map_gen(node* node, uint8_t* code, uint32_t depth, huff_tree* tree)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->left == nullptr)
	{
		for (int i = 0; i < (depth >> 3) + 1; ++i)
		{
			tree->codes[node->symbol][i] = code[i];
		}
		tree->code_lengths[node->symbol] = depth;
	}
	else
	{
		SET_BIT(code, depth);
		code_map_gen(node->left, code, depth + 1, tree);
		UNSET_BIT(code, depth);
		code_map_gen(node->right, code, depth + 1, tree);
	}
}

void create_tree(const uint32_t freq[256], huff_tree& tree)
{
	node* nodes = tree.nodes;
	for (int i = 0; i < 512; i++)
	{
		nodes[i].symbol = i;
		nodes[i].freq = freq[i];
		nodes[i].left = nullptr;
		nodes[i].right = nullptr;
	}
	for (int i = 256; i < 511; i++)
	{
		nodes[i].symbol = 0;
		nodes[i].freq = 0;
		nodes[i].left = nullptr;
		nodes[i].right = nullptr;
	}

	std::priority_queue<std::reference_wrapper<node>> pq;
	for (int i = 0; i < 256; i++)
	{
		if (freq[i] > 0)
		{
			pq.push(nodes[i]);
		}

	}

	uint32_t non_leaf_idx = 256;

	while (pq.size() > 1)
	{
		node& left = pq.top();
		pq.pop();
		node& right = pq.top();
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

}

void encode_with_tree(Data_Buffer* data, huff_tree& tree)
{
	uint32_t new_size = 0;
	uint8_t* old = new uint8_t[data->size];
	memcpy(old, data->data, data->size);
	for (uint32_t i = 0; i < data->size; i++)
	{
		if (tree.code_lengths[old[i]] == 0)
		{
			data->size = -1;
			return;
		}
		for (uint32_t j = 0; j < tree.code_lengths[old[i]]; j++)
		{
			if (GET_BIT(tree.codes[old[i]], j))
			{
				SET_BIT(data->data, new_size);
			}
			else
			{
				UNSET_BIT(data->data, new_size);
			}
			new_size++;
		}
	}
	data->size = new_size;
}

void HUF_transform(Data_Buffer* data)
{
//	uint32_t a = 1;
//	uint8_t *b = reinterpret_cast<uint8_t*>(&a);
//	for (uint32_t i = 0; i < 32; i++) {
//		printf("%d", GET_BIT(b, i));
//	}
//	printf("\n");

	huff_tree tree = {0};
	uint32_t freq[256] = {0};
	for (uint32_t i = 0; i < data->size; i++)
	{
		freq[data->data[i]]++;
	}

	create_tree(freq, tree);

	canonical_code codes[256];
	for (uint32_t i = 0; i < 256; i++)
	{
		codes[i].symbol = i;
		if (freq[i] > 0)
		{
			codes[i].length = tree.code_lengths[i];
		}
		codes[i].code = 0;
	}
	canonical_huffman_codes(codes);
	encode_with_tree(data, tree);

	uint32_t j = data->size;
	while ((j & 7) != 0)
	{
		UNSET_BIT(data->data, j);
		j++;
	}
	uint32_t* int_end = (uint32_t*)(data->data + (j / 8));
	*(int_end) = data->size;
	data->size = (j / 8) + sizeof(uint32_t);

}

void decode_with_tree(Data_Buffer* data, huff_tree& tree)
{
	uint8_t* old = new uint8_t[(data->size >> 3) + 1];
	memcpy(old, data->data, (data->size >> 3) + 1);
	uint32_t new_size = 0;
	node* cur = tree.root;
	for (uint32_t i = 0; i < data->size; i++)
	{
		uint8_t bit = GET_BIT(old, i);
		if (bit)
		{
			cur = cur->left;
		}
		else
		{
			cur = cur->right;
		}

		if (cur->left == nullptr)
		{
			data->data[new_size++] = cur->symbol;
			cur = tree.root;
		}
	}
	data->size = new_size;
}

void HUF_inverse(Data_Buffer* data)
{
	huff_tree tree = {0};

//    uint8_t freq_idx = data->data[--data->size];
	data->size = *((uint32_t*)(data->data + data->size - 4));
	for (uint32_t i = 0; i < data->size; i++)
	{
		if (GET_BIT(data->data, i) == 1)
		{
			int counter = 0;
			while (GET_BIT(data->data, i) == 1)
			{
				i++;
				counter++;
			}
			if (counter > 8)
				printf("%d ", counter);
		}
	}
//    create_tree(freqs[freq_idx], tree);

//    decode_with_tree(data, tree);
}