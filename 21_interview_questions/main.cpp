#include <iostream>
#include <vector>
using namespace std;

//什么是默认构造
//默认构造就是不带参数的构造函数，如果我们不实现任何构造函数，系统会为我们生成一个默认的构造函数
class A {
public:
    int getI() {
        return _i;
    }

private:
    int _i;
};

//什么是有参构造
//有参构造就是传递参数的构造函数，可以根据参数构造对象
class B {
public:
    B(int i): _i(i) {
    }

    int getI() {
        return _i;
    }

private:
    int _i;
};

//拷贝构造函数是什么
//拷贝构造函数用于创建一个对象，该对象是通过复制另一个同类型对象来初始化的。
//使用现有对象初始化新对象。
//按值传递对象作为函数参数。
//按值返回对象。
class C {
public:
    C(const C &c) {
        // 拷贝构造函数
    }
};

//是否会默认生成拷贝构造
//在 C++中，如果你没有为一个类显式定义拷贝构造函数，编译器会自动生成一个默认的拷贝构造函数。
//这个默认拷贝构造函数会按成员的逐个拷贝（member-wise copy）方式来复制对象的每个成员变量。

//默认拷贝构造函数的行为
//逐个拷贝：默认拷贝构造函数会逐个拷贝所有的非静态成员变量。
//指针成员：如果类中有指针成员，默认拷贝构造函数只会拷贝指针的值（地址），而不会拷贝指针所指向的对象。 这可能会导致多个对象指向同一块内存，进而引发问题（如双重释放、 内存泄漏等）。
//const 和引用成员：如果类中有 const 成员或引用成员，编译器不会生成默认的拷贝构造函数，因为这些成员不能被复制。
//类中包含不可拷贝对象时，无法合成默认拷贝构造函数

//拷贝构造是否必须实现
//当一个类A中有成员变量是另一个类类型B的时候，有时候拷贝构造会失效。

//什么是浅拷贝和深拷贝
//类在拷贝构造或者拷贝赋值的时候，将被拷贝的类中的成员值拷贝到目的类，如果被拷贝的类中包含指针成员，只是简单的拷贝指针的值。

//构造顺序和析构顺序
//类A中包含成员变量是类B的类型，如果是先调用A的构造还是B的构造呢？
//如果析构的时候是A先析构还是B先析构呢？
class InnerB {
public:
    InnerB() {
        cout << "InnerB()" << endl;
    }

    ~InnerB() {
        cout << "~InnerB()" << endl;
    }
};

class WrapperC {
public:
    WrapperC() {
        cout << "WrapperC()" << endl;
    }

    ~WrapperC() {
        cout << "~WrapperC()" << endl;
    }

    InnerB _inner;
};

//类默认构造是否必须实现
//如果类中有继承关系或者其他类型的成员，默认构造函数是很有必要实现的。
//系统提供的合成的默认构造函数不会对成员做初始化操作。
class BaseA {
public:
    BaseA(const string &name) : _name(name) {
    }

private:
    string _name;
};

class DerivedA : public BaseA {
public:
    DerivedA(string name, string num) : BaseA(name), _num(num) {
        cout << "DerivedA()" << endl;
    }

private:
    string _num;
};

//this 指针的特性和用途
//指向当前对象
//this 指针是一个隐式参数，指向调用成员函数的对象。通过 this，你可以访问当前对象的属性和方法。
//区分成员变量和参数：
//在构造函数或成员函数中，参数名和成员变量可能同名。使用
class MyClass {
public:
    MyClass(int value) {
        this->value = value; // 使用 this 指针区分成员变量和参数
    }

private:
    int value;
};

//可以用于返回当前对象的引用，以支持链式调用。例如：
class MyClass2 {
public:
    MyClass2 &setValue(int value) {
        this->value = value;
        return *this; // 返回当前对象的引用
    }

private:
    int value;
};

//在 const 成员函数中的使用：
//  在 const 成员函数中，this 的类型为 const MyClass *，这意味着你不能通过 this 修改成员变量。 这有助于确保对象的状态不被改变。
//在静态成员函数中的不可用性：
//  静态成员函数没有 this 指针，因为它们不属于任何特定对象，而是属于类本身。 因此，静态成员函数不能访问非静态成员变量和成员函数。
class MyClass3 {
public:
    // 构造函数
    MyClass3(int value) {
        this->value = value; // 使用 this 指针区分成员变量和参数
    }

    // 成员函数
    MyClass3 &setValue(int value) {
        this->value = value; // 使用 this 指针
        return *this; // 返回当前对象的引用
    }

    // 输出值
    void printValue() const {
        cout << "Value: " << this->value << endl; // 使用 this 指针
    }

private:
    int value;
};

//delete和default
//delete可以删除指定的构造函数。
//default可以指定某个构造函数为系统默认合成。
class DefaultClass {
public:
    DefaultClass() = default;

    ~DefaultClass() = default;

    DefaultClass(const DefaultClass &) = delete;

    DefaultClass &operator=(const DefaultClass &) = delete;

    friend ostream &operator <<(ostream &out, const DefaultClass &defaultClass);

private:
    int _num;
};

//什么是移动构造函数？与拷贝构造函数有何不同？
//移动构造函数用于通过“移动”资源来初始化对象，而不是复制资源。
//使用右值引用作为参数 (MyClass(MyClass&& other)).
//优势
//  性能更高，避免不必要的深拷贝。
//  适用于临时对象。
//拷贝构造函数复制资源，移动构造函数转移资源所有权。
class MyClass4 {
public:
    MyClass4(MyClass4 &&other) noexcept {
        // 移动构造函数
        // 移动资源
    }
};

//默认构造函数和用户定义的构造函数有什么区别？
//默认构造函数
//  无参数的构造函数。
//  如果没有用户定义的构造函数，编译器会自动生成一个默认构造函数。
//用户定义的构造函数
//  开发者自定义的构造函数，可以有参数。
//  一旦定义了任何构造函数，编译器不会再生成默认构造函数
class MyClass5 {
public:
    MyClass5() {
        // 默认构造函数
        // 初始化代码
    }

    MyClass5(int x) {
        // 有参数的构造函数
        // 初始化代码
    }
};

//什么是初始化列表？为什么在构造函数中使用它？
//初始化列表是在构造函数的参数列表之后，函数体之前，用于初始化成员变量的语法。
//提高性能，特别是对于常量成员或引用成员。
//必须用于初始化常量成员、 引用成员以及基类。
//避免对象先默认构造再赋值，减少不必要的操作。
class MyClass6 {
    string x;
    string y;

public:
    MyClass6(string a, string b): x(a), y(b) {
        // 初始化列表
        // 其他初始化代码
    }
};

//什么是虚析构函数？为什么需要它？
//在基类中将析构函数声明为virtual，以确保通过基类指针删除派生类对象时，能正确调用派生类的析构函数。
//防止内存泄漏。
//确保派生类的资源被正确释放。
//不使用虚析构函数的风险
//  仅调用基类析构函数，导致派生类资源未释放。
class AA {
public:
    AA(string name) : _name(name) {
        cout << "AA" << endl;
    }

    virtual ~AA() {
        cout << "~AA" << endl;
    }

private:
    string _name;
};

class BB : public AA {
public:
    BB(string name, string num) : AA(name), _num(num) {
        cout << "BB" << endl;
    }

    ~BB() {
        cout << "~BB" << endl;
    }

private:
    string _num;
};

//什么是委托构造函数？它是如何工作的？（C++11引入的特性）
//一个构造函数可以调用同一类中的另一个构造函数，从而委托初始化任务。
class MyClass7 {
    int x;
    int y;

public:
    MyClass7() : MyClass7(0, 0) {
    } // 委托构造函数

    MyClass7(int a, int b) : x(a), y(b) {
    }
};

//什么是析构函数的顺序？
//成员变量的析构顺序：按照声明的逆序析构。
//继承关系的析构顺序：先析构派生类的成员和资源，再析构基类。
//全局/静态对象：按照创建的逆序析构。
class Base2 {
public:
    ~Base2() { cout << "Base2析构\n"; }
};

class Derived2 : public Base2 {
public:
    ~Derived2() { cout << "Derived2析构\n"; }
};

//如何防止对象被复制？
//C++11及以上：使用delete关键字显式删除拷贝构造函数和拷贝赋值运算符。
//C++11之前：将拷贝构造函数和拷贝赋值运算符声明为私有且不实现。
class NonCopyable {
public:
    NonCopyable() = default;

    NonCopyable(const NonCopyable &) = delete; // 禁止拷贝构造
    NonCopyable &operator=(const NonCopyable &) = delete; // 禁止拷贝赋值
};

//构造函数中抛出异常会发生什么？
//对象未完全构造：如果构造函数中抛出异常，析构函数不会被调用，因为对象尚未完全构造。
//资源泄漏风险：如果在构造函数中分配了资源，需使用RAII（资源获取即初始化）类或智能指针来确保资源被正确释放。
//异常安全：确保在构造函数抛出异常时，任何已经初始化的成员都会被正确析构。
class MyClass8 {
    vector<int> data;

public:
    MyClass8() {
        data.reserve(100);
        /* some condition */
        if (1) {
            throw runtime_error("构造函数异常");
        }
    }
};

//解释RAII及其与构造函数、析构函数的关系
//RAII（资源获取即初始化）
//  编程范式，通过对象的生命周期管理资源。
//  资源在对象构造时获取，在对象析构时释放。
//关系
//  构造函数负责获取资源。
//  析构函数负责释放资源。
//优点
//  自动管理资源，防止内存泄漏。
//  异常安全，确保资源在异常发生时被释放。
class FileHandler {
    FILE *file;

public:
    FileHandler(const char *filename) {
        file = fopen(filename, "r");
        if (!file) throw runtime_error("打开文件失败");
    }

    ~FileHandler() {
        if (file) fclose(file);
    }

    // 禁止拷贝和移动
    FileHandler(const FileHandler &) = delete;

    FileHandler &operator=(const FileHandler &) = delete;
};

//解释什么是赋值运算符重载？与拷贝构造函数有何不同？
//赋值运算符重载：通过重载operator=，定义对象之间的赋值行为。
//区别与拷贝构造函数
//  拷贝构造函数用于初始化新对象。
//  赋值运算符用于将一个已存在的对象赋值给另一个已存在的对象。
//常规实现
//  检查自赋值。
//  释放已有资源。
//  复制资源。
//  返回 *this。
class MyClass9 {
    int *data;

public:
    MyClass9 &operator=(const MyClass9 &other) {
        // 赋值运算符重载
        if (this == &other) return *this; // 自赋值检查
        delete data; // 释放已有资源
        data = new int(*other.data); // 复制资源
        return *this;
    }
};

//解释静态成员变量在构造和析构中的处理
//静态成员变量
//  属于类本身，而非任何对象实例。
//  在程序开始时初始化，在程序结束时析构。
//构造顺序
//  单例模式中，静态成员在第一次使用时构造。
//析构顺序
//  按逆序构造顺序析构，确保依赖关系被正确处理。
class MyClass10 {
public:
    static MyClass10 instance;
    MyClass10() { cout << "MyClass10构造\n"; }
    ~MyClass10() { cout << "MyClass10析构\n"; }
};

MyClass10 MyClass10::instance; // 静态成员变量定义

//虚继承与菱形继承问题

// 基类 Device
class Device {
public:
    string brand;

    Device(const string &brand_) : brand(brand_) {
    }

    void showBrand() const {
        cout << "Brand: " << brand << endl;
    }
};

// 派生类 Laptop，虚继承 Device
class Laptop : virtual public Device {
public:
    Laptop(const string &brand_) : Device(brand_) {
    }
};

// 派生类 Tablet，虚继承 Device
class Tablet : virtual public Device {
public:
    Tablet(const string &brand_) : Device(brand_) {
    }
};

//在无虚继承的情况下，Convertible 类将拥有两份 Device 的成员变量，这会导致二义性问题。
//通过使用虚继承（virtual public），确保 Convertible 类只有一份 Device 的成员。
//在 Convertible 的构造函数中，需要明确调用基类 Device 的构造函数，避免二义性。

//菱形继承（多重继承导致的重复基类）可以通过虚继承来解决，确保共享同一份基类成员。
//虚继承会增加一定的开销，需根据具体需求权衡使用。

// 派生类 Convertible
class Convertible : public Laptop, public Tablet {
public:
    Convertible(const string &brand_) : Device(brand_), Laptop(brand_), Tablet(brand_) {
    }
};

//协变返回类型
//在 C++ 中，协变返回类型（Covariant Return Types）是一个与函数重写（Override）相关的概念。
//当一个派生类重写基类的虚函数时，协变返回类型允许派生类的函数返回一个从基类函数返回类型派生而来的类型。
// 基类
class Base {
public:
    virtual Base *clone() const {
        //基类 Base 定义了一个虚函数 clone()，返回 Base* 类型的指针。
        std::cout << "Base cloned." << std::endl;
        return new Base(*this);
    }

    virtual ~Base() {
    }
};

// 派生类
class Derived : public Base {
public:
    //协变返回类型允许派生类的重写函数返回更具体的类型，增强类型安全性和代码可读性。
    Derived *clone() const override {
        //派生类 Derived 重写了 clone() 函数，返回类型为 Derived*，这是一种协变返回类型。
        // 协变返回类型
        std::cout << "Derived cloned." << std::endl;
        return new Derived(*this);
    }
};

int main() {
    A a; //默认构造函数
    cout << a.getI() << endl; //默认构造函数并不会帮我们初始化类成员变量。

    B b(1);
    cout << b.getI() << endl;

    //如果我们实现了参数构造而不实现无参构造，系统将不会为我们实现默认构造，导致无法使用默认构造生成对象。
    //B b(); //报错

    //执行结果，先调用B的构造，在调用C的构造。
    //析构时，先析构C再析构B
    WrapperC wc;

    MyClass3 mc3(10);
    mc3.printValue();
    // 链式调用
    mc3.setValue(11).printValue();

    DefaultClass bb;
    //cout << bb << endl;

    AA *base = new BB("test", "1001");
    delete base; //只调用了基类AA的析构函数。

    Derived2 d2; //首先调用Derived2的析构函数，然后调用Base2的析构函数。

    Convertible c("TechBrand");
    c.showBrand();

    Base *ba = new Base();
    Base *da = new Derived();

    Base *bClone = ba->clone(); // 输出: Base cloned.
    Base *dClone = da->clone(); // 输出: Derived cloned.

    delete ba;
    delete da;
    delete bClone;
    delete dClone;

    return 0;
}
