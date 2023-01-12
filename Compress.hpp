//
// Created by eythe on 22/12/2022.
//
#ifndef COMPRESS_H_
#define COMPRESS_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define BUFFER_SIZE 1048577
typedef struct Data_Buffer
{
	uint8_t* data;
	uint32_t size;
} Data_Buffer;

typedef void (*compression_method)(Data_Buffer*);

typedef enum METHOD
{
	BWT,
	MTF,
	HUF,
	RLE
} METHOD;


void compress(Data_Buffer* data, const METHOD methods[], uint32_t
num_of_methods);
void decompress(Data_Buffer* data, const METHOD methods[], uint32_t
num_of_methods);

#endif //COMPRESS_H_
