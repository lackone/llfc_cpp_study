#include <iostream>

using namespace std;

int main() {
    //变量的声明和初始化
    int age;
    int height = 175;
    double weight = 65.5;
    char gender = 'm';

    //变量命名规则
    //包含字母、数字和下划线（_），但不能以数字开头。C++是大小写敏感的
    int a = 1;
    int A = 1;
    // a 与 A 是两个变量

    //变量类型
    //byte char bool short int long long long float double long double
    // enum struct union class

    //输出运算符
    //cout 标准输出流
    //endl 是一个操纵符，用于在输出后插入换行符，并刷新输出缓冲区
    std::cout << "hello,world\n" << std::endl;

    //练习
    double pai_val = 3.14;
    int int_val = 5;
    cout << pai_val << endl;
    cout << int_val << endl;

    bool b_val = -100;
    cout << b_val << endl; //非0输出都是1

    b_val = 0;
    cout << b_val << endl; //输出0
}
