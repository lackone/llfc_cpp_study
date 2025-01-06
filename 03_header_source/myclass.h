#ifndef MYCLASS_H
#define MYCLASS_H //防止头文件被重复

//头文件（.h 或 .hpp）

//#pragma once 和 宏定义（如 #ifndef, #define, #endif）都是用来防止头文件被重复包含的机制，但它们在工作方式和使用场景上存在一些区别。

//#pragma once 是一个非标准的但广泛支持的预处理指令，它告诉编译器该头文件在单个编译过程中只应被包含一次。

//#ifndef, #define, #endif 通过宏定义来防止头文件被重复包含。

class MyClass {
public:
    MyClass(); //构造函数
    void myfunc(); //成员函数
};

#endif //MYCLASS_H
