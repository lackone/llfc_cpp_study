#include "global.h"
#include <iostream>

const int buf_size2 = 512;

void PrintBufAddress() {
    std::cout << "global.cpp buf_size =" << &buf_size << std::endl;
    std::cout << "global.cpp buf_size2 =" << &buf_size2 << std::endl;
}