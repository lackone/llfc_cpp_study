#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

//在C++中，extern 关键字用于声明一个变量或函数是在另一个文件或同一个文件的其他位置定义的。
//这主要用于处理全局变量或函数声明，确保在多个源文件中能够正确地链接到这些全局变量或函数的定义。

//int g_int_var = 123;
//std::string g_string_var = "hello";

//头文件只做变量的声明，不能做变量的定义
//头文件声明变量可以采用extern的方式

extern int g_int_var;
extern std::string g_string_var;

#endif //GLOBAL_H
