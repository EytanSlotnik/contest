//
// Created by eythe on 23/12/2022.
//
#include "MTF.hpp"
typedef struct node
{
	uint8_t num;
	struct node* next;
} node;

void MTF_transform(Data_Buffer *data)
{

	node nodes[256];
	node* head = nodes;
	for (int i = 0; i < 255; i++)
	{
		nodes[i].num = i;
		nodes[i].next = &nodes[i + 1];
	}
	nodes[255].num = 255;
	nodes[255].next = NULL;


	for (uint32_t i = 0; i < data->size; i++)
	{
		node* cur = head;
		node* prev = NULL;
		uint8_t num = 0;
		while (cur->num != data->data[i])
		{
			prev = cur;
			cur = cur->next;
			num++;
		}
		if (prev != NULL)
		{
			prev->next = cur->next;
			cur->next = head;
			head = cur;
		}
		data->data[i] = num;
	}
//	for (uint32_t i = 0; i < data->size; i++)
//	{
//		printf("%d,", data->data[i]);
//	}
//	printf("\n");
}


void MTF_inverse(Data_Buffer* data)
{
	node nodes[256];
	node* head = nodes;
	for (int i = 0; i < 255; i++)
	{
		nodes[i].num = i;
		nodes[i].next = &nodes[i + 1];
	}
	nodes[255].num = 255;
	nodes[255].next = NULL;

	for (uint32_t i = 0; i < data->size; i++)
	{
		node* cur = head;
		node* prev = NULL;
		uint8_t num = 0;
		while (num != data->data[i])
		{
			prev = cur;
			cur = cur->next;
			num++;
		}
		if (prev != NULL)
		{
			prev->next = cur->next;
			cur->next = head;
			head = cur;
		}
		data->data[i] = cur->num;
	}
//	for (uint32_t i = 0; i < data->size; i++)
//	{
//		printf("%c", data->data[i]);
//	}
}