#include <iostream>

using namespace std;

//类型别名（type alias）是一个名字，它是某种类型的同义词。
//使用关键字typedef
typedef int myint;
typedef double mydouble;
typedef mydouble *pmydouble;

//使用别名声明（alias declaration）来定义类型的别名
using myint2 = int;
using mylong = long;

typedef char *pstr;
const pstr str = "hello,world";

//C++11新标准引入了auto类型说明符，用它就能让编译器替我们去分析表达式所属的类型。
//auto让编译器通过初始值来推算变量的类型。显然，auto定义的变量必须有初始值：
auto a = 123;
auto b = 3.14;

//使用auto也能在一条语句中声明多个变量。因为一条声明语句只能有一个基本数据类型，所以该语句中所有变量的初始基本数据类型都必须一样：
auto i = 10, *p = &i; // auto推导出int

int j = 20, &r = j;
auto k = r; //k的类型是int,是r所引用的类型

int f() {
    return 1;
}

int main() {
    //auto一般会忽略掉顶层const，同时底层const则会保留下来
    {
        int i = 0, &r = i;
        // a是一个整数，类型是r所引用的类型
        auto a = r;
        // cr是一个常量引用，ci是int类型的常量
        const int ci = i, &cr = ci;
        // b是一个整数，ci顶层const被忽略了
        auto b = ci;
        // c是一个整数，cr是ci的别名，ci本身是一个顶层const
        auto c = cr;
        // d 是一个整型指针，i是整型
        auto d = &i;
        // e是一个指向整数常量的指针，对常量对象取地址是一种底层const
        auto e = &ci;

        //如果希望推断出的auto类型是一个顶层const，需要明确指出：
        //顶层const可显示指定,f是一个const int类型
        const auto f = ci;
    }

    //decltype类型指示符
    //C++11新标准引入了第二种类型说明符decltype，它的作用是选择并返回操作数的数据类型。
    int xx = 33;
    decltype(f()) sum = xx; //sum的类型就是函数f的返回值的类型

    const int ci = 0, &cj = ci;
    //x是const int类型
    decltype(ci) x = 0;
    //y是一个const int&类型，y绑定到x
    decltype(cj) y = x;
    //错误，z是一个引用,引用必须初始化
    //decltype(cj) z;

    //decltype（*p）的结果类型就是int&，而非int。decltype和auto的另一处重要区别是，decltype的结果类型与表达式形式密切相关。
    {
        //decltype的结果可以是引用各类型
        int i = 42, *p = &i, &r = i;
        //正确，假发的结果是int，因此b是一个未初始化的int
        decltype(r + 0) b;
        //错误，c是int&，必须初始化
        //decltype(*p) c;
    }

    //decltype的表达式如果加上了括号的变量，结果就是引用
    //错误，d是int&，必须初始化
    //decltype((i)) d;
    //正确,e是一个未被初始化的int类型值
    decltype(r) e = i;

    //切记：decltype（（variable））（注意是双层括号）的结果永远是引用，而decltype（variable）结果只有当variable本身就是一个引用时才是引用。

    return 0;
}
