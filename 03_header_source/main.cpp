#include <iostream>
#include "myclass.h"
using namespace std;

int main() {
    //头文件  头文件（.h 或 .hpp）
    //类（class）的声明
    //函数（functions）的原型（prototypes）
    //模板（templates）的声明
    //宏定义（#define）
    //外部变量（extern variables）的声明
    //内联函数（inline functions）

    //源文件（.cpp）
    //源文件包含实际的代码实现，即函数体、 类的成员函数的实现等。源文件通常包括必要的头文件，以便编译器知道它们正在使用的函数、 类等是如何声明的。

    //g++编译
    // -I 指定额外的头文件搜索路径
    // -o 指定了输出文件的名称
    // -L 选项来指定库文件的搜索路径
    // -l 选项来指定要链接的库名
    //g++ -Iinclude main.cpp -o myprogram

    MyClass mc;
    mc.myfunc();

    return 0;
}
