//
// Created by eythe on 11/01/2023.
//
#include "RLE.hpp"
void RLE_transform(Data_Buffer* data)
{
	uint32_t size = data->size;
	uint8_t* old_data = (uint8_t*)malloc(size);
	memcpy(old_data, data->data, size);
	uint32_t new_size = 0;
	for (uint32_t i = 0; i < size; ++i)
	{
		uint16_t count = 1;
		while (i < size - 1 && old_data[i] == old_data[i + 1] && count < 255)
		{
			++count;
			++i;
		}
		if (count > 1)
		{
			data->data[new_size++] = old_data[i];
			data->data[new_size++] = old_data[i];
			data->data[new_size++] = count;
		}
		else
		{
			data->data[new_size++] = old_data[i];
		}
	}
	data->size = new_size;
	free(old_data);
}

void RLE_inverse(Data_Buffer* data)
{
	uint32_t size = data->size;
	uint8_t* old_data = (uint8_t*)malloc(size);
	memcpy(old_data, data->data, size);
	uint32_t new_size = 0;
	for (uint32_t i = 0; i < size; ++i)
	{
		if (i < size - 1 && old_data[i] == old_data[i + 1])
		{
			uint16_t count = old_data[i + 2];
			for (uint16_t j = 0; j < count; ++j)
			{
				data->data[new_size++] = old_data[i];
			}
			i += 2;
		}
		else
		{
			data->data[new_size++] = old_data[i];
		}
	}
	data->size = new_size;
	free(old_data);
}