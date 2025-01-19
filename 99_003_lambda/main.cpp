#include <functional>
#include <iostream>

using namespace std;

//lambda表达式又称为匿名表达式，是C11提出的新语法。[]存储lambda表达式要捕获的值，()内的参数为形参，可供外部调用传值。lambda表达式可以直接调用

typedef void (*FuncPtr)(string str);

using FuncPtr2 = function<void(string)>;

void func_test(string str) {
    cout << "func_test" << str << endl;
}

class FuncObj {
public:
    void operator()(string str) {
        cout << "FuncObj" << str << endl;
    }
};

int myadd(int a, int b) {
    cout << a << " " << b << endl;
    return a + b;
}

class BindClass {
public:
    BindClass(int num, string name) : num(num), name(name) {
    }

    static void staticFunc(int age, const string &name) {
        cout << "staticFunc" << endl;
        cout << name << endl;
        cout << age << endl;
    }

    void memberFunc(int score, const string &job) {
        cout << "memberFunc" << endl;
        cout << job << endl;
        cout << score << endl;
        cout << num << endl;
        cout << name << endl;
    }

public:
    int num;
    string name;
};

int main() {
    [](string str) {
        cout << "hello " << str << endl;
    }("lack");

    //通过auto初始化一个变量存储lambda表达式
    auto fn = [](string str) {
        cout << "hello " << str << endl;
    };
    fn("jack");

    // 函数指针
    FuncPtr fn2 = [](string str) {
        cout << "hello " << str << endl;
    };
    fn2("alice");

    // function
    FuncPtr2 fn3 = [](string str) {
        cout << "hello " << str << endl;
    };
    fn3("lili");

    //lambda的捕获
    int age = 33;
    string name = "john";
    double score = 99.8;

    //值捕获
    [age, name](string str) {
        cout << "age:" << age << "name:" << name << str << endl;
    }("test");

    //引用
    //C++的lambda表达式虽然可以捕获局部变量的引用，达到类似闭包的效果，但不是真的闭包
    [&age, &name](string str) {
        age = 44;
        name = "test";
    }("");
    cout << "age:" << age << "name:" << name << endl;

    //全部用值捕获，name用引用捕获
    [=, &name](string str) {
        //通过=表示所有变量都以值的方式捕获
        cout << age << name << score << endl;
        name = "hello";
    }("");

    //全部用引用捕获，只有name用值捕获
    [&, name](string str) {
        age = 55;
        score = 11.1;
    }("");

    //万能的function
    //我们可以用function存储形参和返回值相同的一类函数指针，可调用对象，lambda表达式等。
    vector<function<void(string)> > fnvec;

    fnvec.push_back(func_test); //函数
    fnvec.push_back(FuncObj()); //函数对象
    fnvec.push_back([](string str) {
        //lambda
        cout << "lambde" << str << endl;
    });

    for (auto fn: fnvec) {
        fn("test");
    }

    //bind操作
    //C11同样提供了bind操作，将原函数的几个参数通过bind绑定传值，返回一个新的可调用对象。
    auto new_add = bind(myadd, 100, placeholders::_1);
    cout << new_add(222) << endl;
    auto new_add2 = bind(myadd, 200, 300);
    cout << new_add2() << endl;

    //通过bind绑定静态成员函数
    auto static_bind = bind(BindClass::staticFunc, 66, placeholders::_1);
    static_bind("test");

    //bind绑定成员函数
    BindClass bc(100, "jack");
    // 绑定类的成员函数,一定要传递对象给bind的第二个参数，可以是类对象，也可以是类对象的指针
    // 如果要修改类成员，必须传递类对象的指针
    auto member_bind = bind(BindClass::memberFunc, &bc, 99, placeholders::_1);
    member_bind("司机");

    auto member_bind2 = bind(BindClass::memberFunc, placeholders::_1, placeholders::_2, placeholders::_3);
    //绑定类成员时，对象必须取地址
    member_bind2(&bc, 999, "开车");

    //当然也可以直接用function对象接受bind返回的结果
    function<void(int, string)> fnbind = bind(BindClass::memberFunc, &bc, placeholders::_1, placeholders::_2);
    fnbind(99999, "打人");

    function<void(BindClass *, int, const string &)> fnbind2 = bind(BindClass::memberFunc,
                                                                    placeholders::_1,
                                                                    placeholders::_2,
                                                                    placeholders::_3);
    fnbind2(&bc, 999, "飞天");

    return 0;
}
