#include "myclass.h"

#include <iostream>

//源文件（.cpp）

MyClass::MyClass() {
    std::cout << "MyClass::MyClass()" << std::endl;
}

void MyClass::myfunc() {
    std::cout << "MyClass::myfunc()" << std::endl;
}
