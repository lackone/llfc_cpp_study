#include <iostream>
#include <vector>
using namespace std;

//运算符（Operator） 是用来对变量进行操作的符号或函数。C++中的运算符可分为多种类型，每种运算符具有特定的功能和使用规则。
//运算符可以单目（仅操作一个操作数）、双目（操作两个操作数）、甚至三目（操作三个操作数）等。

struct Point {
    int x;
    int y;
};

//成员函数重载示例：
class complex {
public:
    double real, imag;

    complex operator+(const complex &c) {
        complex result;
        result.real = real + c.real;
        result.imag = imag + c.imag;
        return result;
    }
};

//友元函数重载示例：
class complex2 {
public:
    double real, imag;

    friend complex operator+(const complex &c1, const complex &c2);
};

complex operator+(const complex &c1, const complex &c2) {
    complex result;
    result.real = c1.real + c2.real;
    result.imag = c1.imag + c2.imag;
    return result;
}

class complex3 {
public:
    double real, imag;

    complex3(double r, double i) : real(r), imag(i) {
    }

    complex3 operator+(const complex3 &c) {
        return complex3(real + c.real, imag + c.imag);
    }

    friend ostream &operator<<(ostream &os, const complex3 &c);
};

ostream &operator<<(ostream &os, const complex3 &c) {
    os << "(" << c.real << ", " << c.imag << ")";
    return os;
}

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void square(int *a) {
    *a = (*a) * (*a);
}

int sumRange(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    int ret = 0;
    while (start != end) {
        ret += *start;
        start++;
    }
    return ret;
}

int main() {
    //1. 算术运算符
    //用于执行基本的数学计算。
    cout << 1 + 2 << endl;
    cout << 1 - 2 << endl;
    cout << 1 * 2 << endl;
    cout << 1 / 2 << endl;
    cout << 1 % 2 << endl;

    //2. 关系运算符
    //用于比较两个值之间的关系，返回布尔值（true 或 false）。
    cout << (1 == 1) << endl;
    cout << (1 != 2) << endl;
    cout << (3 > 1) << endl;
    cout << (1 < 5) << endl;
    cout << (3 >= 1) << endl;
    cout << (1 <= 4) << endl;

    //3. 逻辑运算符
    //用于组合或反转布尔表达式，返回布尔值。
    cout << (1 && 0) << endl;
    cout << (1 || 1) << endl;
    cout << (!1) << endl;

    //4. 位运算符
    //用于按位操作整数类型的二进制位。
    cout << (0x001 & 0x010) << endl;
    cout << (0x001 | 0x010) << endl;
    cout << (0x001 ^ 0x010) << endl;
    cout << (~0x001) << endl;
    cout << (0x001 << 1) << endl;
    cout << (0x001 >> 1) << endl;

    //5. 赋值运算符
    //用于向变量赋值。
    int a = 5;
    int b = 3;
    a += b; // a = 8
    a *= 2; // a = 16
    a &= b; // a = 16 & 3 = 0

    //6. 复合赋值运算符
    //结合赋值与其他运算的运算符（如上表中所示的 +=,  -=, 等）。
    int a2 = 10;
    a2 += 5; // 等同于 a2 = a2 + 5; 结果 a2 = 15

    //7. 条件运算符
    //用于基于条件选择值。
    int a3 = 10, b3 = 20, c3;
    c3 = (a3 > b3) ? a3 : b3; // c3 = 20

    //8. 递增和递减运算符
    //用于增加或减少变量的值，前缀和后缀形式。
    int a4 = 5;
    int b4 = ++a4; // a = 6, b = 6
    int c4 = a4--; // a = 5, c = 6

    //9. 指针运算符
    //用于操作指针。
    int a5 = 10;
    int *ptr = &a5;
    int value = *ptr; // value = 10

    //10. 成员访问运算符
    //用于访问类或结构体的成员。
    Point p2 = {10, 20};
    Point *ptr2 = &p2;
    int aa = p2.x; // 使用 . 运算符
    int bb = ptr2->y; // 使用 -> 运算符

    //11. 其他运算符
    //sizeof  	返回变量或类型所占字节数
    //?:  条件（三目）运算符
    //,  	逗号运算符
    //typeid  运行时类型信息运算符
    //new  动态内存分配
    //delete  动态内存释放

    //运算符重载
    //运算符重载（Operator Overloading） 允许开发者为自定义类型（如类和结构体）定义或改变运算符的行为，使其表现得像内置类型一样。 这提高了代码的可读性和可维护性。

    //运算符重载的规则
    //可重载运算符：几乎所有的运算符都可以被重载，但如::,  ? :, sizeof 等运算符不能被重载。
    //至少一个操作数必须是用户定义类型：即至少有一个操作数是类、 结构体或联合体类型。
    //运算符重载不改变运算符的优先级、 结合性和操作数数量。

    complex3 cc1(1, 2);
    complex3 cc2(3, 4);
    complex3 cc3 = cc1 + cc2;
    cout << cc3 << endl;

    int ia = 3, ib = 4;
    swap(&ia, &ib);
    cout << ia << " " << ib << endl;

    int ic = 5;
    square(&ic);
    cout << ic << endl;

    int iarr[] = {1, 2, 3, 4, 5};
    vector<int> ivec(begin(iarr), end(iarr));
    cout << *begin(iarr) << endl;
    cout << *(end(iarr) - 1) << endl; //end()会返回数组最后一个元素的下一个
    cout << sumRange(ivec.begin(), ivec.end());

    return 0;
}
