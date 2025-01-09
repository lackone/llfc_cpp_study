#include <iostream>
#include <string.h>

using namespace std;

//什么是类和对象
//类（Class）是C++中创建用户自定义类型的一种方式，它将数据（成员变量）和操作数据的函数（成员函数）封装在一起。
//对象（Object）是类的实例化，拥有类定义的所有属性和行为。
//类更像是汽车图纸，对象更像是造出来的汽车。

//类的作用
//封装（Encapsulation）：将数据和操作数据的代码绑定在一起，保护数据不被外界直接访问。
//抽象（Abstraction）：通过类定义抽象出具有共同特性的对象，提高代码的可重用性和可维护性。
//继承（Inheritance）和多态（Polymorphism）：实现代码的复用与动态绑定。

class ClassName {
public:
    //公有
protected:
    //保护
private:
    //私有
};

//访问修饰符
//public：公有成员，可以被所有代码访问。
//private：私有成员，仅能被类的成员函数和友元访问。
//protected：受保护成员，仅能被类的成员函数、 友元和派生类访问。

class Student {
public:
    //成员函数
    //成员函数（Member Functions）：定义对象的行为，可以访问和修改成员变量。
    //常成员函数（Const Member Functions）：保证函数不会修改对象的状态。
    Student(const string &name, int age);

    void setName(const string &name);

    string getName();

    void setAge(int age);

    int getAge();

private:
    //成员变量
    //成员变量（Member Variables）：用于存储对象的状态信息。
    //命名约定：常用下划线结尾（例如 name_）表示成员变量，避免与局部变量混淆。
    string _name;
    int _age;
};

Student::Student(const string &name, int age) : _name(name), _age(age) {
}

void Student::setName(const string &name) {
    _name = name;
}

void Student::setAge(int age) {
    _age = age;
}

int Student::getAge() {
    return _age;
}

string Student::getName() {
    return _name;
}

//构造函数
//默认构造函数：没有参数的构造函数。
//参数化构造函数：接受参数以初始化对象。
//拷贝构造函数：用一个对象初始化另一个对象。
//移动构造函数（C++11）：从临时对象“ 移动” 资源。

//析构函数
//析构函数（Destructor）：在对象生命周期结束时调用，用于释放资源。
class Example {
public:
    //默认构造函数
    Example() : _data(0) {
    }

    //参数化构造函数
    Example(int data) : _data(data) {
    }

    //拷贝构造函数
    Example(const Example &other) : _data(other._data) {
    }

    //移动构造函数
    Example(Example &&other) : _data(other._data) {
        other._data = 0;
    }

    //析构函数
    ~Example() {
    }

private:
    int _data;
};

// 拷贝构造函数
//定义：用于创建一个新对象，并复制现有对象的成员。
//语法：ClassName(const ClassName &other);

//拷贝赋值运算符
//定义：用于将一个已有对象的值赋给另一个已有对象。
//语法：ClassName &operator=(const ClassName &other);
class MyString {
public:
    //有参构造
    MyString(const char *str = nullptr) {
        if (str) {
            _size = strlen(str);
            _data = new char[_size + 1];
            strcpy(_data, str);
        } else {
            _size = 0;
            _data = new char[1];
            _data[0] = '\0';
        }
    }

    //拷贝构造
    MyString(const MyString &str) : _size(str._size) {
        _data = new char[_size + 1];
        strcpy(_data, str._data);
    }

    //拷贝赋值
    MyString &operator=(const MyString &str) {
        if (this == &str) {
            return *this;
        }
        delete [] _data;
        _size = str._size;
        _data = new char[_size + 1];
        strcpy(_data, str._data);
        return *this;
    }

    ~MyString() {
        if (_data) {
            delete [] _data;
        }
    }

    void print() {
        cout << _data << endl;
    }

private:
    char *_data;
    size_t _size;
};

//移动语义
//什么是移动语义
//移动语义（Move Semantics）：允许资源的所有权从一个对象转移到另一个对象，避免不必要的拷贝，提高性能。

//移动构造函数与移动赋值运算符
//移动构造函数：ClassName(ClassName &&other) noexcept;
//移动赋值运算符：ClassName &operator=(ClassName &&other) noexcept;

class MoveExample {
public:
    MoveExample(int size) : _size(size), _data(new int[size]) {
        cout << "构造" << endl;
    }

    // 拷贝构造函数
    MoveExample(const MoveExample &other) : _size(other._size), _data(new int[other._size]) {
        memcpy(_data, other._data, _size);
        cout << "拷贝构造函数" << endl;
    }

    // 移动构造函数
    MoveExample(MoveExample &&other) : _size(other._size), _data(other._data) {
        other._size = 0;
        other._data = nullptr;
        cout << "移动构造函数" << endl;
    }

    // 拷贝赋值运算符
    MoveExample &operator=(const MoveExample &other) {
        cout << "拷贝赋值运算符" << endl;
        if (this == &other) {
            return *this;
        }
        delete [] _data;
        _size = other._size;
        _data = new int[_size];
        memcpy(_data, other._data, _size);
        return *this;
    }

    // 移动赋值运算符
    MoveExample &operator=(MoveExample &&other) {
        cout << "移动赋值运算符" << endl;
        if (this == &other) {
            return *this;
        }
        delete [] _data;
        _size = other._size;
        _data = other._data;

        other._size = 0;
        other._data = nullptr;
        return *this;
    }

    ~MoveExample() {
        if (_data) {
            delete [] _data;
        }
    }

private:
    int _size;
    int *_data;
};

//什么是友元
//友元（Friend）：可以访问类的私有和保护成员的非成员函数或另一个类。
//友元函数：单个函数可以被声明为友元。
//友元类：整个类可以被声明为友元。
class Box {
public:
    Box(double l, double w, double h) : len(l), wid(w), hig(h) {
    }

    // 声明友元函数
    friend double calcBox(const Box &box);

private:
    double len;
    double wid;
    double hig;
};

double calcBox(const Box &box) {
    return box.len + box.wid + box.hig;
}

//友元类
class Rectangle {
public:
    Rectangle(double w, double h) : width(w), height(h) {
    }

    //友元类
    friend class CalcRect;

private:
    double width;
    double height;
};

class CalcRect {
public:
    double calcRect(const Rectangle &rect) {
        return rect.width * rect.height;
    }
};

//运算符重载
//什么是运算符重载
//运算符重载（Operator Overloading）：允许对自定义类型使用C++运算符，如 +, -, << 等。
//重载运算符的规则
//只能对已有运算符进行重载，不能创建新运算符。
//至少有一个操作数必须是用户定义的类型。
//不能改变运算符的优先级或结合性。
class Point {
public:
    Point(int x, int y) : x(x), y(y) {
    }

    // 成员函数重载 +
    Point operator+(const Point &other) {
        return Point(x + other.x, y + other.y);
    }

    void print() {
        cout << x << ", " << y << endl;
    }

    friend Point operator-(const Point &a, const Point &b);

private:
    int x;
    int y;
};

// 也可以使用友元函数重载 -
Point operator-(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

//重载 << 运算符（输出流）
class Emp {
public:
    Emp(string name, double salary) : name(name), salary(salary) {
    }

    // 声明友元函数以重载 <<
    friend ostream &operator<<(ostream &os, const Emp &e);

private:
    string name;
    double salary;
};

ostream &operator<<(ostream &os, const Emp &e) {
    os << e.name << ", " << e.salary;
    return os;
}

class MyStr {
public:
    MyStr() : _data(nullptr) {
    }

    MyStr(const char *s) {
        //有参构造
        if (s) {
            _data = new char[strlen(s) + 1];
            strcpy(_data, s);
        } else {
            _data = nullptr;
        }
    }

    MyStr(const MyStr &s) {
        //拷贝构造
        if (s._data) {
            _data = new char[strlen(s._data) + 1];
            strcpy(_data, s._data);
        } else {
            _data = nullptr;
        }
    }

    MyStr &operator=(const MyStr &s) {
        //赋值运算符重载
        if (this == &s) {
            return *this;
        }
        delete [] _data;
        if (s._data) {
            _data = new char[strlen(s._data) + 1];
            strcpy(_data, s._data);
        } else {
            _data = nullptr;
        }
        return *this;
    }

    bool operator==(const MyStr &s) {
        // 比较运算符重载
        if (_data == nullptr && s._data == nullptr) {
            return true;
        }
        if (_data == nullptr || s._data == nullptr) {
            return false;
        }
        return strcmp(_data, s._data) == 0;
    }

    friend ostream &operator<<(ostream &os, const MyStr &s) {
        if (s._data) {
            os << s._data;
        }
        return os;
    }

    ~MyStr() {
        if (_data) {
            delete [] _data;
        }
    }

private:
    char *_data;
};

int main() {
    Example e1; //默认
    Example e2(100); //有参
    Example e3(e2); //拷贝
    Example e4(move(e3)); //移动

    MyString s1("Hello World");
    MyString s2 = s1; // 调用拷贝构造函数
    MyString s3;
    s3 = s1; // 调用拷贝赋值运算符

    s1.print();
    s2.print();
    s3.print();

    MoveExample me1(10);
    MoveExample me2 = me1; //拷贝
    MoveExample me3 = MoveExample(20); //移动

    MoveExample me4(50);
    me4 = me1; //拷贝
    me4 = MoveExample(100); //移动

    Box box(1, 2, 3);
    cout << calcBox(box) << endl;

    Rectangle rect(10, 20);
    CalcRect cr;
    cout << cr.calcRect(rect) << endl;

    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p1 + p2;
    p3.print();

    Point p4 = p1 - p2;
    p4.print();

    Emp emp("test", 99);
    cout << emp << endl;

    MyStr ms1("Hello World");
    MyStr ms2 = ms1;
    MyStr ms3;
    ms3 = ms1;
    cout << ms1 << endl;
    cout << ms2 << endl;
    cout << ms3 << endl;

    if (ms1 == ms2) {
        cout << "ms1 == ms2" << endl;
    }

    return 0;
}
