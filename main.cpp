#include <iostream>
#include <fstream>
#include "Compress.hpp"

uint8_t buffer[BUFFER_SIZE];
uint8_t temp_buffer[BUFFER_SIZE];
#define LEN 256
struct methods_list
{
	uint8_t length;
	METHOD methods[283];
};

#define MAKE_METHODS_LIST(l, ...) (methods_list){.length = l, \
.methods \
= {__VA_ARGS__, HUF}}


// initialize list of methods_list
methods_list list[] = {
	{0, {}},
	MAKE_METHODS_LIST(2, BWT, RLE),
	MAKE_METHODS_LIST(3, BWT, MTF),
	MAKE_METHODS_LIST(3, BWT, MTF, RLE),
//	[3] = {3, {BWT, MTF, RLE}},
//	[4] = {4, {BWT, MTF, HUF, RLE}},
//	[5] = {5, {BWT, RLE, MTF, HUF, RLE}},
//	[6] = {5, {BWT, MTF, RLE, HUF, RLE}},
//	[7] = {3, {BWT, MTF, HUF}}
};
int main(int argc, char* argv[])
{
	Data_Buffer data = {buffer, 0};
	std::ifstream inputFile;
	FILE* fp;
	fp = fopen(argv[1], "rb");
	data.size = fread(data.data, 1, BUFFER_SIZE, fp);
	fclose(fp);

	METHOD methods[] = {BWT, MTF, HUF, RLE};




	if (strcmp(argv[3], "compress") == 0)
	{
//		compress(&data, methods, 4);
//	}
//	{
//		compress(&data, methods, sizeof(methods) / sizeof(methods[1]));
//		std::cout << "size: " << data.size << std::endl;
		// choose the best method list
		uint32_t best_size = 0;
		uint8_t best_list = 0;
		for (uint32_t i = 1; i < sizeof(list) / sizeof(list[0]); ++i)
		{
			Data_Buffer temp = {temp_buffer, 0};
			memcpy(temp.data, data.data, data.size);
			temp.size = data.size;
			compress(&temp, list[i].methods, list[i].length);
			if (temp.size < best_size || best_size == 0)
			{
				best_size = temp.size;
				best_list = i;
			}
		}
		std::cout << "best list: " << (int)best_list << std::endl;
		std::cout << "best size: " << best_size << std::endl;
		compress(&data, list[best_list].methods, list[best_list].length);
		// add the best list to the end
		data.data[data.size] = best_list;
		data.size++;

	}
	else
	{
		// get the best list
		uint8_t best_list = data.data[data.size - 1];
		data.size--;
		decompress(&data, list[best_list].methods, list[best_list].length);
//		decompress(&data, methods, sizeof(methods) / sizeof(methods[1]));
	}

//	compress(&data, methods, sizeof(methods) / sizeof(methods[1]));
//	printf("%d\n", data.size);
//	decompress(&data, methods, sizeof(methods) / sizeof(methods[1]));
//	printf("%d", data.size);



	std::ofstream out("Samples/out.bin", std::ios::binary);
	out.write(reinterpret_cast<const char*>(data.data), data.size);
	out.close();

	return 0;
}
