//
// Created by eythe on 24/12/2022.
//
#include "Compress.hpp"
typedef struct func_and_inv
{
	compression_method func;
	compression_method inv;
} func_and_inv;
#include "BWT.hpp"
#include "MTF.hpp"
#include "Huffman.hpp"
#include "RLE.hpp"

const func_and_inv method_map[] = {
	[BWT] = {BWT_transform, BWT_inverse},
	[MTF] = {MTF_transform, MTF_inverse},
	[HUF] = {HUF_transform, HUF_inverse},
	[RLE] = {RLE_transform, RLE_inverse},
};

void compress(Data_Buffer* data, const METHOD methods[], uint32_t
num_of_methods)
{
	for (uint32_t i = 0; i < num_of_methods; ++i)
	{
		method_map[methods[i]].func(data);
	}
}

void decompress(Data_Buffer* data, const METHOD methods[], uint32_t
num_of_methods)
{
	for (uint32_t i = 0; i < num_of_methods; ++i)
	{
		method_map[methods[num_of_methods - 1 - i]].inv(data);
	}
}