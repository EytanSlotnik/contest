project(contest C CXX)
set(CMAKE_CXX_STANDARD 20)
add_executable(contest main.cpp Compress.hpp Huffman.cpp Compress.cpp BWT.cpp MTF.cpp)

add_executable(autogen_freqs Trees.cpp Compress.hpp Huffman.cpp Compress.cpp BWT.cpp MTF.cpp)
