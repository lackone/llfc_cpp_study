#include <iostream>

using namespace std;

//变量计算 + - * / %
void calc() {
    int a = 10, b = 20;

    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << a / b << endl;
    cout << a % b << endl;

    //ASCII码为128字符（0-127）分配了唯一的数字编码，包括英文字母（大小写）、数字、标点符号和一些控制字符（如换行、回车等）
    //字符也可以计算
    char aa = 'a';
    char bb = 'b';
    cout << (char) (aa + bb) << endl;
    cout << (int) (aa + bb) << endl;
}

//类型划分
//各种数据类型可以支持转换，double, float，int, char 这种C++给我们提供的基本类型也叫做内置类型。
//我们以后学习了结构体struct和class等自定义类型后，这些类型叫做复合类型，引用和指针也属于复合类型。

int g_int_val = 0; //全局作用域

int g_float_val = 3.14; //全局变量区
static int g_cnt = 0; //全局静态区
const int g_const = 11; //常量区

void func() {
    int a = 10; //变量a局部作用域

    int b = 20; //栈区，函数调用完就会释放

    int *c = new int; //堆区
    *c = 30;

    const char *name = "hello"; //字符串常量区

    delete c;
}

namespace mysp {
    int a = 10; //命名空间作用域

    void print() {
        cout << a << endl;
    }
}

namespace mysp2 {
    int a = 20; //命名空间作用域
}

class MyClass {
public:
    int a; //类作用域

    void print() {
        cout << a << endl;
    }
};

int main() {
    calc();

    //变量大小
    //就是占用内存的大小，单位字节
    cout << sizeof(char) << endl;
    cout << sizeof(short) << endl;
    cout << sizeof(int) << endl;
    cout << sizeof(float) << endl;
    cout << sizeof(double) << endl;
    cout << sizeof(long) << endl;
    cout << sizeof(long long) << endl;

    //类型转换
    char aa = 'a';
    int bb = aa; // char => int
    double cc = bb; // int => double

    //变量作用域
    //全局作用域：在函数外部声明的变量具有全局作用域。它们可以在程序的任何地方被访问，但通常建议在需要时才使用全局变量，因为它们可能导致代码难以理解和维护。
    //局部作用域：在函数内部、 代码块（如if语句、for循环等）内部声明的变量具有局部作用域。它们只能在声明它们的代码块内被访问。 一旦离开该代码块，这些变量就不再可见。
    //命名空间作用域：在命名空间中声明的变量（实际上是实体，如变量、 函数等）具有命名空间作用域。 它们只能在相应的命名空间内被直接访问，但可以通过使用命名空间的名称作为前缀来从外部访问。
    //类作用域：在类内部声明的成员变量和成员函数具有类作用域。 成员变量和成员函数可以通过类的对象来访问，或者在某些情况下（如静态成员）可以通过类名直接访问。
    //块作用域：这是局部作用域的一个特例，指的是由大括号{}包围的代码块内部声明的变量。 这些变量只能在该代码块内被访问。

    //全局变量
    cout << g_int_val << endl;

    //局部作用域
    func();

    //命名空间作用域
    mysp::print();
    cout << mysp::a << endl;
    cout << mysp2::a << endl;

    //类作用域
    MyClass mc;
    mc.print();

    int dd = 1; //main函数作用域
    {
        int ee = 2; //块用域
    }
    //cout << ee << endl; //无法访问ee


    /**
    代码区（Code Segment/Text Segment）：
        存储程序执行代码（即机器指令）的内存区域。这部分内存是共享的，只读的，且在程序执行期间不会改变。
        举例说明：当你编译一个C++程序时，所有的函数定义、控制结构等都会被转换成机器指令，并存储在代码区。
    全局/静态存储区（Global/Static Storage Area）：
        存储全局变量和静态变量的内存区域。这些变量在程序的整个运行期间都存在，但它们的可见性和生命周期取决于声明它们的作用域。
        举例说明：全局变量（在函数外部声明的变量）和静态变量（使用static关键字声明的变量，无论是在函数内部还是外部）都会存储在这个区域。
    栈区（Stack Segment）：
        存储局部变量、函数参数、返回地址等的内存区域。栈是一种后进先出（LIFO）的数据结构，用于存储函数调用和自动变量。
        举例说明：在函数内部声明的变量（不包括静态变量）通常存储在栈上。当函数被调用时，其参数和局部变量会被推入栈中；当函数返回时，这些变量会从栈中弹出，其占用的内存也随之释放。
    堆区（Heap Segment）：
        由程序员通过动态内存分配函数（如new和malloc）分配的内存区域。堆区的内存分配和释放是手动的，因此程序员需要负责管理内存，以避免内存泄漏或野指针等问题。
        举例说明：当你使用new操作符在C++中动态分配一个对象或数组时，分配的内存就来自堆区。同样，使用delete操作符可以释放堆区中的内存。
    常量区（Constant Area）：
        存储常量（如字符串常量、const修饰的全局变量等）的内存区域。这部分内存也是只读的，且通常在程序执行期间不会改变。
        举例说明：在C++中，使用双引号括起来的字符串字面量通常存储在常量区。此外，使用const关键字声明的全局变量，如果其值在编译时就已确定，也可能存储在常量区
     */

    //程序编译过程
    // 预处理 =》编译 =》汇编 =》 链接

    return 0;
}
