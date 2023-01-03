//
// Created by eythe on 22/12/2022.
//

#include <stdbool.h>
#include "BWT.hpp"
typedef struct rotation
{
	uint32_t index;
	uint8_t* data;
	uint8_t prev;
} rotation;
static uint32_t data_size;
uint8_t* data_end;

int compare(const void* a, const void* b)
{
	if (a == b)
		return 0;
	rotation* x = (rotation*)a;
	rotation* y = (rotation*)b;
	uint8_t* x_data = x->data;
	uint8_t* y_data = y->data;
	uint32_t i = data_size + 1;
	while (i--)
	{
		if (*(x_data) < *(y_data))
		{
			return -1;
		}
		if (*(x_data) > *(y_data))
		{
			return 1;
		}
		x_data = x_data < data_end - 1 ? x_data + 1 : data_end - data_size;
		y_data = y_data < data_end - 1 ? y_data + 1 : data_end - data_size;
	}
	return 0;
}
rotation rotations[BUFFER_SIZE];
void BWT_transform(Data_Buffer* data)
{
	data_size = data->size;
	data_end = data->data + data->size;
	// fill rotations
	rotations[0].index = 0;
	rotations[0].data = data->data;
	rotations[0].prev = data->data[data->size - 1];
	for (uint32_t i = 1; i < data->size; i++)
	{
		rotations[i].index = i;
		rotations[i].data = data->data + i;
		rotations[i].prev = data->data[i - 1];
	}
	// sort rotations
	qsort(rotations, data->size, sizeof(rotation), compare);
//	for (uint32_t i = 0; i < data->size; i++)
//	{
//		printf("%s\n", rotations[i].data);
//	}
	uint32_t x;
	for (uint32_t i = 0; i < data->size; i++)
	{
		if (rotations[i].index == 0)
		{
			x = i;
		}
		data->data[i] = rotations[i].prev;
	}
	uint32_t *int_end =(uint32_t*) data_end;
	*(int_end) = x;
	data->size = data->size + sizeof(uint32_t);

}
int compare_uint8_t(const void* a, const void* b)
{
	uint8_t ai = *(uint8_t*)a;
	uint8_t bi = *(uint8_t*)b;
	if (ai < bi)
	{
		return -1;
	}
	if (ai > bi)
	{
		return 1;
	}
	return 0;
}
typedef struct node
{
	uint32_t index;
	struct node* next;
} node;

typedef struct list
{
	node* head;
	node* cur;
	node* tail;
} list;

void fill_next(uint32_t* next, const uint8_t* sorted,
	Data_Buffer* data, uint32_t size)
{
	list lists[256] = {0};
	for (uint32_t i = 0; i < size; i++)
	{
		node* new_node = (node*)malloc(sizeof(node));
		new_node->index = i;
		new_node->next = NULL;
		if (lists[data->data[i]].head == NULL)
		{
			lists[data->data[i]].head = new_node;
			lists[data->data[i]].cur = new_node;
			lists[data->data[i]].tail = new_node;
		}
		else
		{
			lists[data->data[i]].tail->next = new_node;
			lists[data->data[i]].tail = new_node;
		}
	}

	for (int i = 0; i < data->size; ++i)
	{
		next[i] = lists[sorted[i]].cur->index;
		lists[sorted[i]].cur = lists[sorted[i]].cur->next;
	}

	//free lists
	for (uint32_t j = 0; j < 256; j++)
	{

		node* cur = lists[j].head;
		while (cur != NULL)
		{
			node* temp = cur->next;
			free(cur);
			cur = temp;
		}
	}
//	for (uint32_t i = 0; i < size; i++)
//	{
//		printf("%d ", next[i]);
//	}
}
void BWT_inverse(Data_Buffer* data)
{
	uint32_t x = *((uint32_t*)(data->data + data->size - 4));
	data->size -= 4;
//	printf("%d\n", x);
	uint8_t* sorted = (uint8_t*) malloc(data->size);
	memcpy(sorted, data->data, data->size);
	qsort(sorted, data->size, sizeof(char), compare_uint8_t);

	uint32_t* next = (uint32_t*)malloc(data->size * sizeof(uint32_t));

	fill_next(next, sorted, data, data->size);

	memcpy(sorted, data->data, data->size);
	for (uint32_t i = 0; i < data->size; i++)
	{
		x = next[x];
		data->data[i] = sorted[x];
	}
//	printf("%s", data->data);
	return;
}
