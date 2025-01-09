#include <algorithm>
#include <iostream>
#include "func.h"
#include <vector>
#include <functional>
using namespace std;

//函数是执行特定任务的代码块，可以被程序中的多个地方调用。使用函数可以增加代码的可重用性、可读性和可维护性。
//封装：将特定功能封装在函数中，便于管理和修改。
//复用：同一段功能代码可以在程序中多次调用，减少代码重复。
//结构化：通过函数组织代码，提高程序的结构清晰度。

//函数声明（Function Declaration）
//告诉编译器函数的名称、 返回类型和参数类型，但不包含函数体。 通常放在头文件中或在使用函数前进行声明。
int multiply(int a, int b); // 函数声明

//函数定义（Function Definition）
//提供函数的具体实现，包括函数体。 函数定义可以在源文件中或与声明一起在头文件中出现（推荐仅声明在头文件中）。
int multiply(int a, int b) {
    // 函数定义
    return a * b;
}

//函数声明
int add(int a, int b);

//C++中函数参数的传递方式主要有以下三种：
//传值调用（Pass by Value）
//传引用调用（Pass by Reference）
//传指针调用（Pass by Pointer）

void func1(int a) {
    a = 10;
}

//传引用调用
//定义：函数接收参数的引用，函数内对参数的修改会影响原始数据。
void func2(int &a) {
    a = 20;
}

//传指针调用
//定义：函数接收指向参数的指针，函数内通过指针可以修改原始数据。
void func3(int *a) {
    *a = 30;
}

//返回值
//函数可以通过return语句将结果返回给调用者。返回值的类型可以是基本数据类型、引用、 指针、 对象等。
int ret1() {
    return 99;
}

int ret2(int &a) {
    a += 10;
    return a;
}

int *ret3(int size) {
    int *a = new int[size];
    for (int i = 0; i < size; i++) {
        a[i] = i;
    }
    return a;
}

class Person {
public:
    string name;
    int age;

    Person(string s, int a) : name(s), age(a) {
    }
};

Person ret4(string s, int a) {
    Person p(s, a);
    return p;
}

//函数重载
//函数重载允许在同一个作用域内定义多个名称相同但参数列表不同的函数。编译器通过参数列表的不同来区分调用哪个函数。
//函数名相同。
//参数列表（类型、 数量或顺序）不同。
//返回类型不参与重载的区分。
int mydiv(int a, int b) {
    return a / b;
}

double mydiv(double a, double b) {
    return a / b;
}

//默认参数
//函数参数可以指定默认值，调用函数时可以省略这些参数，默认值将被使用。
//默认参数从右到左设置，不能部分设置。
//函数声明和定义中默认参数只需在声明中指定。
void displayInfo(string name, int age = 88, string city = "unknown") {
    cout << "name:" << name << "age:" << age << "city:" << city << endl;
}

//内联函数
//内联函数通过在函数前加inline关键字，建议编译器将函数代码嵌入到调用处，减少函数调用的开销。
//适用于函数体积小、调用频繁的函数，如访问器（getter）和修改器（setter）等。
inline int square(int x) {
    return x * x;
}

//递归函数
//递归函数是指在函数体内调用自身的函数。递归通常用于解决可以分解为相似子问题的问题，如阶乘、斐波那契数列、树的遍历等。
//基准情形（Base Case）：直接返回结果，避免无限递归。
//递归情形（Recursive Case）：将问题分解为更小的子问题并调用自身。
long long factorial(int n) {
    if (n < 0) {
        return -1; //错误情况
    }
    if (n == 0 || n == 1) {
        return 1; //基准情形
    }
    return n * factorial(n - 1); //递归情形
}

// 递归函数计算斐波那契数
int fibonacci(int n) {
    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Lambda表达式
//Lambda表达式是C++11引入的匿名函数，便于在需要函数对象的地方快速定义和使用函数。它允许定义内联的、小型的可调用对象，无需单独定义函数。

//捕获列表（Capture List）：指定如何访问外部变量。
//[ ]：不捕获任何外部变量。
//[&]：按引用捕获所有外部变量。
//[=]：按值捕获所有外部变量。
//[x, &y]：按值捕获x，按引用捕获y。
//参数列表（Parameter List）：类似普通函数的参数列表，可以省略类型（C++14及以上支持自动类型推断）。
//返回类型（Return Type）：可指定返回类型，也可省略，编译器自动推断。
//函数体（Function Body）：Lambda的具体实现。

//函数指针
//指向函数的指针变量，保存函数的地址，可以通过指针调用函数。
void greet() {
    cout << "hello, greet" << endl;
}

//函数指针作为参数
void exec(void (*p)()) {
    p();
}

//通过函数指针传递的函数，通常用于在特定事件发生时执行自定义操作。
typedef void (*callback)();

void regCallback(callback cb) {
    cb();
}

void mycallback() {
    cout << "my callback" << endl;
}

void sortstr(vector<string> &v) {
    sort(v.begin(), v.end(), [](string a, string b) -> bool {
        return a.length() > b.length();
    });
}

using Callback = function<void(int)>;

class Event {
public:
    void regCallback(Callback cb) {
        callbacks.push_back(cb);
    }

    void triggerEvent(int data) {
        for (auto cb: callbacks) {
            cb(data);
        }
    }

private:
    vector<Callback> callbacks;
};

void onEvent(int data) {
    cout << "onEvent:" << data << endl;
}

int main() {
    cout << add(10, 20) << endl;

    cout << mul(10, 20) << endl;

    int a = 1;
    func1(a);
    cout << a << endl;
    func2(a);
    cout << a << endl;
    func3(&a);
    cout << a << endl;

    cout << factorial(5) << endl;

    vector<int> vec = {1, 2, 3, 4, 5};

    // 使用Lambda表达式打印每个元素
    for_each(vec.begin(), vec.end(), [](int x) {
        cout << x << endl;
    });

    // 使用Lambda表达式计算总和
    int sum = 0;
    std::for_each(vec.begin(), vec.end(), [&sum](int x) {
        sum += x;
    });
    cout << sum << endl;

    // 按升序排序，使用Lambda表达式
    std::sort(vec.begin(), vec.end(), [](int a, int b) -> bool {
        return a < b;
    });

    for (auto x: vec) {
        cout << x << endl;
    }

    //函数指针
    void (*pfn)() = greet;
    pfn();

    exec(pfn);

    regCallback(mycallback);

    //捕获外部变量的Lambda无法转换为普通函数指针。
    callback cb2 = []() {
        cout << "lambda callback" << endl;
    };
    regCallback(cb2);

    vector<string> sv = {"hello", "test", "a", "city", "bb"};
    sortstr(sv);
    for_each(sv.begin(), sv.end(), [](string x) {
        cout << x << endl;
    });

    Event ev;
    ev.regCallback(onEvent);
    ev.regCallback([](int x) {
        cout << x << endl;
    });
    int num = 10;
    ev.regCallback([num](int x) {
        cout << x * num << endl;
    });
    ev.triggerEvent(99);

    return 0;
}

int add(int a, int b) {
    return a + b;
}
