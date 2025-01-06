#include <iostream>
#include "global.h"
using namespace std;

//const 是 C++ 关键字，用于指示变量的值不可修改。通过使用 const，可以提高代码的安全性与可读性，防止无意中修改变量的值。

const double PI = 3.14;
//PI = 3.33; //const 变量无法修改

//const 在变量声明中的位置
//const 关键字通常放在变量类型之前

int GetSize() {
    return 20;
}

inline constexpr int GetSizeConst() {
    return 1;
}

int global_i = 1;

int main() {
    const int i = 11;
    int j = i;

    //const变量必须初始化
    //const int k; //此行报错

    //const 修饰的变量在编译时会被视为只读，尝试修改其值会导致编译错误。此外，编译器可能会对 const 变量进行优化，如将其存储在只读内存区域。
    //默认状态下，const对象仅在文件内有效

    cout << buf_size << endl;

    PrintBufAddress();

    //可以看出global.cpp中的buf_size和main.cpp中的buf_size不是同一个变量
    //如果想在多个文件之间共享const对象，必须在变量的定义之前添加extern关键字。

    std::cout << "main.cpp buf_size =" << &buf_size << std::endl;
    std::cout << "main.cpp buf_size2 =" << &buf_size2 << std::endl;

    //const的引用
    const int a = 11;
    const int &ra = a; //常量引用绑定常量
    //ra = 22; //不能修改

    int b = 22;
    const int &rb = b; //绑定非const变量

    const int &rc = 123; //绑定字面量

    const int &rd = b * 3; //绑定表达式的值

    double dv = 3.14;
    //int &rdv = dv; //类型不批配
    const int &rdv = dv; //可以，这里产生了临时变量

    //指针和const
    //指向常量的指针(pointer to const)
    //可以令指针指向常量或非常量。 类似于常量引用，指向常量的指针（pointer to const）不能用于改变其所指对象的值。
    const double pi = 3.14;
    //double *ppi = &pi; //错误
    const double *ppi = &pi; //指针指向的是一个常量
    //*ppi = 4.14; //错误，无法修改

    //指针的类型必须与其所指对象的类型一致，但是允许令一个指向常量的指针指向一个非常量对象
    int ii = 222;
    const int *pii = &ii; //指向一个非常量

    //const指针
    //指针是对象而引用不是，因此就像其他对象类型一样，允许把指针本身定为常量。
    //常量指针（const pointer）必须初始化，而且一旦初始化完成，则它的值（也就是存放在指针中的那个地址）就不能再改变了。
    //把＊放在const关键字之前用以说明指针是一个常量，这样的书写形式隐含着一层意味，即不变的是指针本身的值而非指向的那个值：
    int jj = 333;
    int kk = 444;
    int *const pjj = &jj;
    //pjj = &kk; //pjj是常量，无法修改，但它指向的可以修改

    //顶层const
    //指针本身是一个对象，它又可以指向另外一个对象。因此，指针本身是不是常量以及指针所指的是不是一个常量就是两个相互独立的问题
    //用名词顶层const（top - level const）表示指针本身是个常量，而用名词底层const（low - level const）表示指针所指的对象是一个常量。
    //顶层const可以表示任意的对象是常量，这一点对任何数据类型都适用，如算术类型、类、 指针等。
    //底层const则与指针和引用等复合类型的基本类型部分有关。 比较特殊的是，指针类型既可以是顶层const也可以是底层const，这一点和其他类型相比区别明显：
    int zz = 44;
    int *const pzz = &zz; //顶层，本身是常量
    const int mm = 55; //顶层，
    const int *pzz2 = &zz; //底层，指向的对象是常量
    const int *const pzz3 = &zz; //靠右边的const是顶层const，靠左边的const是底层const
    const int &rmm = mm; //底层

    //constexpr和常量表达式
    //常量表达式（const expression）是指值不会改变并且在编译过程就能得到计算结果的表达式。
    //一个对象（或表达式）是不是常量表达式由它的数据类型和初始值共同决定
    {
        //max_files是一个常量表达式
        const int max_files = 20;
        //limit是一个常量表达式
        const int limit = max_files + 10;
        //staff_size不是常量表达式,无const声明
        int staff_size = 20;
        //sz不是常量表达式,运行时计算才得知
        const int sz = GetSize();
    }

    //C++11新标准规定，允许将变量声明为constexpr类型以便由编译器来验证变量的值是否是一个常量表达式。
    //20是一个常量表达式
    constexpr int mf = 20;
    //mf+1是一个常量表达式
    constexpr int limit = mf + 10;
    //错误，GetSize()不是一个常量表达式，需要运行才能返回
    //constexpr int sz = GetSize();
    constexpr int sz = GetSizeConst();

    //指针和constexpr
    //必须明确一点，在constexpr声明中如果定义了一个指针，限定符constexpr仅对指针有效，与指针所指的对象无关：
    //p是一个指向整形常量的指针
    const int *p = nullptr;
    //q是一个指向整数的常量指针
    constexpr int *q = nullptr;

    //constexpr指针只能绑定固定地址
    //constexpr int *p = &mvalue;
    constexpr int *p2 = nullptr;
    //可以绑定全局变量，全局变量地址固定
    constexpr int *cp = &global_i;

    //常量指针，地址固定，指向的变量也是常量
    constexpr const int *cp2 = &global_i;
    //*cp2 = 2; //不能修改

    return 0;
}
