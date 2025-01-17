#include <iostream>
#include <string>
using namespace std;

//1. 内置类型（基本类型）
/**
整型（Integer Types）
    int：标准整型，通常为4字节。
    short：短整型，通常为2字节。
    long：长整型，通常为4或8字节（取决于平台）。
    long long：更长的整型，通常为8字节。
    unsigned：无符号整型，不支持负数。
    unsigned short、unsigned long、unsigned long long：对应的无符号版本。
字符型（Character Types）
    char：字符型，通常为1字节。
    wchar_t：宽字符型，通常为2或4字节（用于表示Unicode字符）。
    char16_t、char32_t：用于表示UTF-16和UTF-32编码的字符。
浮点型（Floating Point Types）
    float：单精度浮点型，通常为4字节。
    double：双精度浮点型，通常为8字节。
    long double：扩展精度浮点型，通常为8字节或16字节（取决于平台）。
布尔型（Boolean Type）
    bool：布尔型，表示真（true）或假（false）。
*/

//复合类型
/**
数组（Array）
    一组相同类型的数据元素，可以通过索引访问。
结构体（Struct）
    一种用户定义的数据类型，可以包含不同类型的数据成员。
联合体（Union）
    与结构体类似，但所有成员共享同一内存位置，只有一个成员可以在任何给定时间存储值。
枚举（Enum）
    一种用户定义的类型，用于定义一组命名的整型常量。
类（Class）
    C++的面向对象编程特性，允许定义包含数据和成员函数的复杂数据类型。
指针（Pointer）
    指向其他类型的内存地址，可以用来动态分配内存和实现复杂的数据结构。
引用（Reference）
    对现有变量的别名，提供了对变量的另一种访问方式。
*/

//引用类型
//C++ 中的引用类型是一种复合类型，它是对另一个变量的别名。

std::string foo() {
    return std::string("hello world");
}

int main() {
    int a = 100;
    int &b = a; //b相当于a的别名

    cout << a << endl;
    cout << b << endl;

    cout << &a << endl; //两个变量的地址完全一样
    cout << &b << endl;

    a = 111; //修改a的值影响b
    cout << a << endl;
    cout << b << endl;

    b = 222; //修改b的值影响a
    cout << a << endl;
    cout << b << endl;

    //必须初始化：引用在创建时必须被初始化，它必须指向某个已存在的对象。
    //一旦绑定，不可改变：引用一旦被初始化后，它将一直保持与其初始对象的绑定，不能改变为另一个对象的引用。
    //没有空引用：引用必须指向某个对象，不能存在空引用。

    //引用主要用于函数参数和返回值，以及类的成员变量等场景，以提供对原始数据的直接访问，从而提高程序的效率和可读性。
    //引用可以是const的，这表示你不能通过引用来修改它所指向的对象的值。
    //引用在内部实现上通常是通过指针来实现的，但它们在语法和用途上与指针有显著的不同。引用提供了更直观、 更安全的访问方式。

    //左值（lvalue）和右值（rvalue）
    //左值通常指的是具有持久状态的对象，它们有明确的内存地址，可以被多次赋值
    //右值通常是临时的、没有持久状态的值，它们通常没有内存地址，或者其内存地址在表达式结束后就变得无效。

    //C++11引入了右值引用（rvalue reference），用T&&表示，作为对左值引用（lvalue reference，用T&表示）的补充。

    //左值引用
    int aa = 101;
    int &bb = aa;

    //右值引用是C++11新增的特性，它允许我们为右值（即临时对象或即将被销毁的对象）创建一个引用。
    int &&cc = 123;

    std::string &&dd = foo(); //dd是foo()返回临时字符串的右值引用

    //右值引用的主要用途是作为函数参数（实现移动语义）和返回值（允许链式调用等）。

    return 0;
}
