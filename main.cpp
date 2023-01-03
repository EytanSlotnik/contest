#include <iostream>
#include <fstream>
#include "Compress.hpp"

uint8_t buffer[BUFFER_SIZE];

int main(int argc, char *argv[]) {
    Data_Buffer data = {buffer, 0};
    std::ifstream inputFile;
    FILE *fp;
    fp = fopen(argv[1], "rb");
    data.size = fread(data.data, 1, BUFFER_SIZE, fp);
    fclose(fp);

    METHOD methods[] = {BWT, MTF, HUF};

    if (strcmp(argv[3], "compress") == 0){
        compress(&data, methods, sizeof(methods) / sizeof(methods[1]));
    } else{
        decompress(&data, methods, sizeof(methods) / sizeof(methods[1]));
    }



    printf("%d", data.size);




    std::ofstream out("Samples/out.bin", std::ios::binary);
    out.write(reinterpret_cast<const char *>(data.data), data.size);
    out.close();

    return 0;
}
