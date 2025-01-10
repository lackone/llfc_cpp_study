#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

//C++ 提供了多种方式来表示和操作可调用对象，包括传统的函数指针、仿函数（Functors）、Lambda表达式、function 和 bind 等。
//这些工具极大地增强了C++的灵活性和表达能力，尤其在处理回调、事件驱动编程和函数式编程时表现尤为出色。

//函数指针
//函数指针是C++中最基本的可调用对象之一，用于指向普通函数和静态成员函数。
typedef int (*fnPtr)(int a, int b);

int add(int a, int b) {
    return a + b;
}

//仿函数（Functors）
//仿函数（Functors），又称函数对象（Function Objects），是在C++中重载了 operator() 的类或结构体实例。
//仿函数不仅可以像普通函数一样被调用，还能携带状态，提供更大的灵活性和功能性。
struct Add {
    int v;

    Add(int v) : v(v) {
    }

    int operator()(int b) {
        return v + b;
    }
};

struct Cnt {
    int c;

    Cnt() : c(0) {
    }

    void operator()(int b) {
        c += b;
    }
};

struct Than {
    int v;

    Than(int v) : v(v) {
    }

    bool operator()(int b) {
        return v < b;
    }
};

//仿函数与模板相结合，可以实现高度通用和可复用的代码。例如，编写一个通用的比较仿函数。
template<typename T>
struct Compare {
    bool operator()(const T &a, const T &b) {
        return a < b;
    }
};

//Lambda表达式
//Lambda表达式是C++11引入的一种轻量级函数对象，允许在代码中定义匿名函数。 它们可以捕获周围的变量，具有更强的表达能力。
//值捕获 ([=]): 捕获所有外部变量的副本。
//引用捕获 ([&]): 捕获所有外部变量的引用。
//混合捕获: 指定部分变量按值捕获，部分按引用捕获，如 [=, &var] 或 [&, var]。
//无捕获 ([]): 不捕获任何外部变量。

class Processor {
public:
    Processor(int threshold) : threshold(threshold) {
    }

    void process(vector<int> &data) {
        cout << "处理前数据: ";
        for (auto num: data) cout << num << " ";
        cout << endl;

        //Lambda表达式可以捕获类的成员变量和成员函数，使其在类的上下文中更加灵活。
        // 使用Lambda表达式进行过滤
        data.erase(remove_if(data.begin(), data.end(), [this](int n) -> bool {
            return n < threshold;
        }), data.end());

        cout << "处理后数据: ";
        for (auto num: data) cout << num << " ";
        cout << endl;
    }

private:
    int threshold;
};

//std::function 对象
//std::function 是C++11提供的一个通用的可调用包装器，能够封装任何可调用对象，包括普通函数、Lambda表达式、函数对象以及绑定表达式。
//它实现了类型擦除，使得不同类型的可调用对象可以通过统一的接口进行操作。
int mydiv(int a, int b) {
    return a / b;
}

struct MyDiv {
    int operator()(int a, int b) {
        return a / b;
    }
};

//回调机制
using Callback = function<void(int)>;

void triggerEvent(Callback cb, int value) {
    cb(value);
}

//std::bind 操作
//std::bind 是C++11中提供的一个函数适配器，用于绑定函数或可调用对象的部分参数，生成一个新的可调用对象。
//它允许提前固定某些参数，简化函数调用或适应接口需求。
void displayStr(const string &str, int cnt) {
    for (int i = 0; i < cnt; i++) {
        cout << str << endl;
    }
}

//绑定类的成员函数
//在C++中，成员函数与普通函数不同，因为它们需要一个对象实例来调用。使用 std::bind 或Lambda表达式，可以方便地绑定类的成员函数，生成可调用对象。
class Calculator {
public:
    int multiply(int a, int b) const {
        return a * b;
    }
};

//静态成员函数不依赖于类的实例，可以像普通函数一样使用 std::bind 和 std::function。
class Logger {
public:
    static void log(const std::string &message) {
        std::cout << "Log: " << message << std::endl;
    }
};

//绑定带有返回值的成员函数
class Math {
public:
    double power(double base, double exponent) const {
        double result = 1.0;
        for (int i = 0; i < static_cast<int>(exponent); ++i) {
            result *= base;
        }
        return result;
    }
};

int main() {
    //函数指针
    fnPtr fn = add;
    cout << fn(5, 6) << endl;

    //仿函数（Functors）
    Add add(10);
    cout << add(5) << endl;

    Cnt cnt;
    cnt(10);
    cnt(20);
    cnt(30);
    cout << cnt.c << endl;

    vector<int> vec = {1, 4, 5, 17, 18, 20};
    Than than(5);
    auto it = find_if(vec.begin(), vec.end(), than);
    if (it != vec.end()) {
        cout << *it << endl;
    } else {
        cout << "没有" << endl;
    }

    // 使用仿函数进行排序
    vector<int> vec2 = {19, 4, 1, 17, 3, 20};
    sort(vec2.begin(), vec2.end(), Compare<int>());
    for (auto num: vec2) {
        cout << num << endl;
    }

    int threshold = 5;
    vector<int> vec3 = {5, 1, 55, 12, 23, 4};

    // 使用lambda表达式进行过滤
    vec3.erase(remove_if(vec3.begin(), vec3.end(), [threshold](int n) -> bool {
        return n < threshold;
    }), vec3.end());

    for (auto num: vec3) {
        cout << num << endl;
    }

    //可变Lambda
    //默认情况下，Lambda表达式是不可变的（const）。通过mutable关键字，可以允许修改捕获的变量副本。
    int cnt2 = 0;

    auto inc = [&cnt2]() {
        cnt2++;
        cout << cnt2 << endl;
    };

    inc();
    inc();
    cout << cnt2 << endl;

    auto inc2 = [cnt2]() mutable {
        //通过mutable关键字，可以允许修改捕获的变量副本。
        //这里修改的是副本
        cnt2++;
        cout << cnt2 << endl;
    };

    inc2();
    inc2();
    cout << cnt2 << endl;

    vector<int> vec4 = {1, 6, 3, 8, 2, 7};
    Processor proc(5);
    proc.process(vec4);

    //Lambda表达式与标准库算法紧密结合，提供了更简洁和直观的代码书写方式。
    vector<int> vec5 = {4, 2, 5, 1, 3};
    // 使用Lambda表达式进行排序
    sort(vec5.begin(), vec5.end(), [](int a, int b) -> bool {
        return a < b;
    });
    for (auto num: vec5) {
        cout << num << " "; // 输出: 1 2 3 4 5
    }
    cout << endl;

    // 封装普通函数
    function<int(int, int)> func1 = mydiv;
    cout << func1(100, 6) << endl;
    // 封装Lambda表达式
    function<int(int, int)> func2 = [](int a, int b) -> int {
        return a / b;
    };
    cout << func2(100, 6) << endl;
    // 封装函数对象
    MyDiv mydiv2;
    function<int(int, int)> func3 = mydiv2;
    cout << func3(100, 6) << endl;

    // 使用Lambda作为回调
    triggerEvent([](int a) {
        cout << a << endl;
    }, 66);
    // 使用仿函数作为回调
    struct Prt {
        void operator()(int a) {
            cout << a << endl;
        }
    } prt;
    triggerEvent(prt, 88);

    //std::function 可以在容器中存储各种不同类型的可调用对象，只要它们符合指定的签名。
    vector<function<int(int, int)> > vf;
    vf.push_back(mydiv);
    vf.push_back([](int a, int b) -> int { return a / b; });
    vf.push_back(MyDiv());
    for (auto &v: vf) {
        cout << v(88, 4) << endl;
    }

    // 绑定第一个参数为10，生成新的函数对象
    //std::bind 使用占位符来表示未绑定的参数，这些占位符决定了在生成的新函数对象中如何传递参数。
    auto mdiv = bind(mydiv, 100, placeholders::_1);
    cout << mdiv(3) << endl;

    // 绑定消息为"Hello"，生成新的函数对象，只需要传递次数
    auto ds = bind(displayStr, "hello,world", placeholders::_1);
    ds(3);

    //std::bind 曾在C++11中广泛使用，但随着Lambda表达式的普及，很多情况下Lambda更为直观和高效。
    //不过，在某些复杂的参数绑定场景下，std::bind 依然有其独特优势。
    auto mdiv2 = bind(mydiv, 100, placeholders::_1);
    cout << mdiv2(5) << endl;
    auto mdiv3 = [](int b) -> int { return 100 / b; };
    cout << mdiv3(5) << endl;

    // 绑定成员函数multiply，固定第一个参数为5
    Calculator calc;
    auto multiplyBy5 = std::bind(&Calculator::multiply, &calc, 5, std::placeholders::_1);
    cout << multiplyBy5(3) << endl;
    // 使用Lambda表达式绑定成员函数
    auto multiplyBy6 = [&calc](int b) -> int { return calc.multiply(5, b); };
    cout << multiplyBy6(3) << endl;

    // 使用std::bind绑定静态成员函数
    //静态成员函数不需要this，但要占位
    auto logfn = bind(&Logger::log, placeholders::_1);
    logfn("this is a test");

    Math mathObj;
    auto powerOf2 = std::bind(&Math::power, &mathObj, 2.0, std::placeholders::_1);
    cout << powerOf2(5) << endl;

    return 0;
}
