//
// Created by eslotnik on 02/01/2023.
//
#include <iostream>
#include <fstream>
#include "Compress.hpp"


int main(){
    uint32_t freqs[256][256] = {0};
    uint8_t data[BUFFER_SIZE] = {0};
    Data_Buffer buffer = {data, 0};
    METHOD methods[] = {BWT, MTF};

    std::ofstream out("out.bin", std::ios::binary);
    out << "#include \"Huffman.hpp\"\n" <<
                                        "uint32_t freqs[NUM_OF_TREES][256] = {\n";


    const char *files[] = {"Samp1.bin", "Samp2.bin", "Samp3.bin", "Samp4.bin", "book.bin", "book2.bin"};

    for (uint32_t i = 0; i < sizeof(files) / sizeof(files[0]); i++){
        out << "{";

        FILE *fp;
        fp = fopen(files[i], "rb");
        buffer.size = fread(buffer.data,1,  BUFFER_SIZE, fp);
        fclose(fp);

        compress(&buffer, methods, 2);

        for (uint32_t j = 0; j < buffer.size; j++) {
            freqs[i][buffer.data[j]]++;
        }

        for (uint32_t j: freqs[i]){
            out << j << ", ";
        }
        out << "},\n";


    }
    out <<"};";
    out.close();
    return 0;
}


