#include <iostream>
#include <vector>
#include <memory>
using namespace std;

//类继承 是面向对象编程（OOP）中的一个核心概念，允许一个类（派生类）从另一个类（基类）继承属性和行为。通过继承，派生类可以重用基类的代码，并根据需要添加新的成员或重写现有成员。
class Base {
public:
    int public_member;

protected:
    int protected_member;

private:
    int private_member;
};

class Derived : public Base {
    // 公有继承
};

class Animal {
public:
    void eat() {
        cout << "animal eat" << endl;
    }

protected:
    int age;
};

class Dog : public Animal {
public:
    void setAge(int age) {
        this->age = age;
    }

    int getAge() {
        return this->age;
    }
};

//虚函数 允许派生类重新定义基类中的函数，以实现多态性。在运行时，根据对象的实际类型调用相应的函数版本。
class Shape {
public:
    virtual void draw() {
        cout << "shape draw" << endl;
    }
};

class Circle : public Shape {
public:
    void draw() {
        cout << "circle draw" << endl;
    }
};

class Square : public Shape {
public:
    void draw() {
        cout << "square draw" << endl;
    }
};

// 动态绑定，根据实际对象类型调用对应的draw()
void showDraw(Shape *shape) {
    shape->draw();
}

//纯虚类与抽象基类（Pure Virtual Classes and Abstract Base Classes）
//纯虚函数 是在基类中声明但不提供实现的虚函数。
//包含至少一个纯虚函数的类称为 抽象基类（Abstract Base Class，ABC）。抽象基类不能被实例化，要求派生类必须实现所有纯虚函数才能被实例化。
class Vehicle {
public:
    virtual void startEngine() = 0;
};

class Car : public Vehicle {
public:
    void startEngine() {
        cout << "car start" << endl;
    }
};

class Motorcycle : public Vehicle {
public:
    void startEngine() {
        cout << "motorcycle start" << endl;
    }
};

//继承后的访问控制（Access Control in Inheritance）
//继承时的 访问控制 决定了基类成员在派生类中的可访问性。继承方式主要有三种：public、protected 和 private。它们影响继承成员的访问级别。
//公有继承（public inheritance）：
//  基类的 public 成员在派生类中保持 public。
//  基类的 protected 成员在派生类中保持 protected。
//  基类的 private 成员在派生类中不可访问。
//保护继承（protected inheritance）：
//  基类的 public 和 protected 成员在派生类中都变为 protected。
//私有继承（private inheritance）：
//  基类的 public 和 protected 成员在派生类中都变为 private。
class BaseExample {
public:
    int public_m;

protected:
    int protected_m;

private:
    int private_m;
};

class PublicExample : public BaseExample {
public:
    void access() {
        public_m = 1;
        protected_m = 2;
        //private_m = 3; //不可访问
    }
};

class ProtectedExample : protected BaseExample {
public:
    void access() {
        public_m = 1; //转为 protected
        protected_m = 2; //转为 protected
        //private_m = 3; //不可访问
    }
};

class PrivateExample : private BaseExample {
public:
    void access() {
        public_m = 1; //转为 private
        protected_m = 2; //转为 private
        //private_m = 3; //不可访问
    }
};

//继承中类的作用域（Scope of Classes in Inheritance）
//在继承关系中，类的作用域决定了成员名称的可见性和访问方式。派生类可以访问基类的成员，根据访问控制的不同，还可能需要使用 作用域解析符 来访问隐藏的成员。
class Base2 {
public:
    void display() {
        cout << "Base2 display" << endl;
    }

    virtual void show() {
        cout << "Base2 show" << endl;
    }
};

class Derived2 : public Base2 {
public:
    void display() {
        cout << "Derived2 display" << endl;
    }

    void callBaseDisplay() {
        Base2::display();
    }

    void show() {
        cout << "Derived2 show" << endl;
    }
};

//构造函数与拷贝控制（Constructors and Copy Control in Inheritance）
//在继承体系中，类的构造函数和拷贝控制函数（拷贝构造函数、拷贝赋值运算符、析构函数）的调用顺序和行为需要注意。基类的构造函数在派生类之前调用，析构函数则在派生类之后调用。
//基类的 默认构造函数 首先被调用，除非派生类在初始化列表中显式调用其他基类构造函数。
//派生类的成员按照声明顺序被构造。
//派生类的构造函数体被执行。
class Base3 {
public:
    Base3() {
        cout << "Base3默认构造" << endl;
    }

    Base3(const string &name) : _name(name) {
        cout << "Base3参数构造 " << _name << endl;
    }

    Base3(const Base3 &other) : _name(other._name) {
        cout << "Base3拷贝构造" << endl;
    }

    Base3 &operator=(const Base3 &other) {
        cout << "Base3赋值" << endl;
        if (this != &other) {
            _name = other._name;
        }
        return *this;
    }

    virtual ~Base3() {
        cout << "Base3析构" << endl;
    }

protected:
    string _name;
};

class Derived3 : public Base3 {
public:
    Derived3() : Base3("Default Derived") {
        cout << "Derived3默认构造" << endl;
    }

    Derived3(const string &name, int value) : Base3(name), _value(value) {
        cout << "Derived3参数构造 " << _value << endl;
    }

    Derived3(const Derived3 &other) : Base3(other), _value(other._value) {
        cout << "Derived3拷贝构造" << endl;
    }

    Derived3 &operator=(const Derived3 &other) {
        cout << "Derived3赋值" << endl;
        if (this != &other) {
            Base3::operator=(other);
            _value = other._value;
        }
        return *this;
    }

    ~Derived3() override {
        cout << "Derived3析构" << endl;
    }

private:
    int _value;
};

//容器与继承（Containers and Inheritance）
//C++ 容器（如 vector、list 等） 通常存储对象的副本，而非指向对象的指针。
//因此，当与继承结合使用时，可能导致 切片（Object Slicing） 问题，即仅存储基类部分，丢失派生类特有的信息。为了实现多态性，推荐使用指针或智能指针存储对象。
class Base4 {
public:
    virtual void show() const { cout << "Base4 show" << endl; }

    virtual ~Base4() {
    }
};

class Derived4 : public Base4 {
public:
    void show() const override { cout << "Derived4 show" << endl; }
};

//使用指针避免切片
class Base5 {
public:
    virtual void show() const { std::cout << "Base5 show" << std::endl; }

    virtual ~Base5() {
    }
};

class Derived5 : public Base5 {
public:
    void show() const override { std::cout << "Derived5 show" << std::endl; }
};

//智能指针选择
//std::unique_ptr：
//  独占所有权，不可复制，只能移动。
//  适用于明确的单一所有权场景。
//std::shared_ptr：
//  共享所有权，可以被多个指针共享和引用计数。
//  适用于需要多个所有者的场景。

int main() {
    Dog dog;
    dog.eat();
    dog.setAge(10);
    cout << dog.getAge() << endl;

    Circle circle;
    Square square;
    showDraw(&circle);
    showDraw(&square);

    Car car;
    Motorcycle motorcycle;
    car.startEngine();
    motorcycle.startEngine();

    Vehicle *v1 = &car;
    Vehicle *v2 = &motorcycle;
    v1->startEngine(); //动态绑定
    v2->startEngine(); //动态绑定

    Derived2 d2;
    d2.display();
    d2.callBaseDisplay();
    d2.show();

    Base2 *base2 = &d2;
    base2->show();
    base2->display(); //不是虚函数，调用Base2::display

    Derived3 dd1;
    Derived3 dd2("Custom Derived", 42);
    Derived3 dd3 = dd2;
    dd1 = dd2;

    vector<Base4> vec;
    Derived4 d;
    vec.push_back(d); // 切片发生，派生类特有部分被丢弃
    vec[0].show(); // 输出: Base show

    std::vector<unique_ptr<Base5> > vec2;
    vec2.emplace_back(make_unique<Derived5>());
    vec2[0]->show(); // 输出: Derived show

    return 0;
}
