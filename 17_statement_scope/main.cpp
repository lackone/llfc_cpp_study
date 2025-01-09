#include <iostream>
#include <exception>
using namespace std;

//声明语句
//声明语句用于声明变量、函数、类等标识符。
// 函数声明
int add(int x, int y);

//作用域的基本概念
//作用域定义了变量或其他标识符在程序中的可见范围。C++ 中主要有以下几种作用域：
//局部作用域(Local Scope)：在函数或代码块内部定义的变量，仅在其所在的块内可见。
//全局作用域(Global Scope)：在所有函数外部定义的变量，在整个文件中可见。
//命名空间作用域(Namespace Scope)：在命名空间内部定义的标识符。

//全局变量
int g_var = 10;

void display() {
    int local_var = 10; //局部变量
    cout << g_var << " " << local_var << endl;
}

// 函数，返回两个数中的较大者
int max(int a, int b) {
    if (a > b) {
        return a; // 返回 a，退出函数
    }
    return b; // 返回 b，退出函数
}

double mydiv(double a, double b) {
    if (b == 0) {
        throw invalid_argument("不能为0");
    }
    return a / b;
}

// 函数，检查数组索引
int getElement(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index is out of range."); // 抛出异常
    }
    return arr[index];
}

// 函数，抛出异常
void func1() {
    throw runtime_error("Error in func1.");
}

// 函数，调用 func1 并重新抛出异常
void func2() {
    try {
        func1();
    } catch (...) {
        // 捕获所有异常
        cout << "func2() caught an exception and is rethrowing it." << endl;
        throw; // 重新抛出当前异常
    }
}

void print99() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            cout << i << "x" << j << "=" << i * j << "\t";
        }
        cout << endl;
    }
}

int main() {
    //表达式语句
    //在 C++ 中，最常见的简单语句是表达式语句。它由一个表达式组成，并以分号结束。表达式语句可以包括函数调用、赋值操作、增减操作等。

    int a = 5; // 赋值表达式语句
    a = a + 10; // 赋值表达式语句
    cout << a; // 函数调用表达式语句

    //代码块作用域
    //通过使用花括号 {}，可以创建新的代码块，从而定义局部作用域。
    int x = 10; {
        int x = 20; //块作用域
        cout << x << endl;
    }

    //条件语句
    int num = 10;
    //if 语句用于在条件为真时执行特定的代码块。
    if (num > 0) {
        cout << "num > 0" << endl;
    }

    //if-else 语句
    //if-else 语句在条件为假时执行另一个代码块。
    if (num % 2 == 0) {
        cout << "num is even" << endl;
    } else {
        cout << "num is odd" << endl;
    }

    //else if 语句
    //else if 允许在多重条件下执行不同的代码块。
    int score;
    cout << "输入分数:" << endl;
    cin >> score;
    if (score >= 90) {
        cout << "A" << endl;
    } else if (score >= 80) {
        cout << "B" << endl;
    } else if (score >= 70) {
        cout << "C" << endl;
    } else if (score >= 60) {
        cout << "D" << endl;
    } else {
        cout << "F" << endl;
    }

    //switch 语句
    //switch 语句根据变量的值选择执行的代码块，适用于离散的值。
    char grade;
    cout << "Enter your grade (A, B, C, D, F): " << endl;
    cin >> grade;
    switch (grade) {
        case 'A':
            cout << "Excellent!" << endl;
            break;
        case 'B':
            cout << "Good!" << endl;
            break;
        case 'C':
            cout << "Fair!" << endl;
            break;
        case 'D':
            cout << "Poor!" << endl;
            break;
        case 'F':
            cout << "Fail!" << endl;
            break;
        default:
            cout << "Invalid grade." << endl;
            break;
    }

    //for 循环
    //for 循环用于已知循环次数的情况，结构紧凑。
    for (int i = 0; i < 10; i++) {
        cout << i << endl;
    }

    //while 循环
    //while 循环在循环前判断条件，适合未知循环次数的情况。
    int i = 0;
    while (true) {
        if (i == 10) {
            break;
        }
        cout << i << endl;
        i++;
    }

    //do-while 循环
    //do-while 循环在循环后判断条件，保证至少执行一次循环体。
    int j = 0;
    do {
        cout << j++ << endl;
    } while (j < 10);

    //嵌套循环
    //一个循环内部嵌套另一个循环，常用于多维数据结构的遍历。
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << i * j << " ";
        }
        cout << endl;
    }

    //跳转语句
    //C++ 中主要有 break、continue、return 和 goto。
    for (int i = 1; i <= 10; ++i) {
        if (i == 5) {
            break; // 结束循环
        }
        cout << i << " ";
    }

    //continue 用于跳过当前的循环迭代，继续下一次循环。
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 != 0) {
            continue; // 跳过奇数
        }
        cout << i << " ";
    }

    //return 用于从函数中返回一个值或结束函数执行。
    cout << max(11, 22) << endl;

    //goto 允许无条件跳转到程序中指定的标签。虽然 goto 有时能简化代码，但不推荐频繁使用，因为它会使程序流程难以理解和维护。
    int input;
    cout << "请输入:" << endl;
    cin >> input;
    if (input < 0) {
        //goto END;
    }

    //异常处理语句
    //异常处理用于应对程序运行过程中可能出现的错误情况，确保程序的健壮性和可靠性。
    //try, catch, 和 throw 语句
    try {
        mydiv(3, 0);
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    //多重 catch 块
    //可以为 try 块指定多个 catch 块，以处理不同类型的异常。
    try {
        cout << "请输入1到2：" << endl;
        int a;
        cin >> a;

        if (a == 1) {
            throw bad_alloc();
        } else if (a == 2) {
            throw logic_error("逻辑错误");
        } else {
            throw invalid_argument("参数错误");
        }
    } catch (bad_alloc &e) {
        cout << e.what() << endl;
    } catch (logic_error &e) {
        cout << e.what() << endl;
    } catch (invalid_argument &e) {
        cout << e.what() << endl;
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    //throw 通常位置
    //throw 语句可以在任何需要引发异常的位置使用，包括函数内部、嵌套调用中等。
    int myArray[5] = {10, 20, 30, 40, 50};
    int index;
    cout << "请输入(0-4): ";
    cin >> index;
    try {
        int value = getElement(myArray, 5, index);
        cout << "Element at index " << index << " is " << value << "." << endl;
    } catch (out_of_range &e) {
        cerr << "Error: " << e.what() << endl;
    }

    //rethrow 异常
    //可以在 catch 块中使用 throw 语句重新抛出捕获的异常，以便其他部分处理。
    try {
        func2();
    } catch (exception &e) {
        // 在 main 中捕获异常
        cerr << "Main caught: " << e.what() << endl;
    }

    print99();

END:
    cout << "END..." << endl;

    return 0; // return 表达式语句
}

// 函数定义
int add(int x, int y) {
    return x + y;
}
