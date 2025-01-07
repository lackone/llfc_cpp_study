#include <iostream>
#include <string.h>

using namespace std;

//结构体（structure，简称 struct）是一种用户自定义的数据类型，用于将多个不同类型的数据组合在一起。

struct student {
    int id;
    char name[20];

    student(int i = 0, const char *n = "") {
        id = i;
        strcpy(name, n);
    }
};

//类与结构体的相似之处
//都可以包含成员变量和成员函数。
//都支持访问控制（public、 protected、 private）。
//都可以使用继承和多态。

//结构体（struct）：默认成员访问权限为 public。
//类（class）：默认成员访问权限为 private。
class myclass1 {
    int x; //private
};

struct myclass2 {
    int x; //public
};

//结构体（struct）：通常用于纯数据结构，主要存储数据，成员通常是公开的。
//类（class）：用于包含数据和操作数据的函数，支持更加复杂的封装。
struct point {
    int x;
    int y;
};

class rect {
public:
    rect(int w, int h) {
        width = w;
        height = h;
    }

    int area() {
        return width * height;
    }

private:
    int width;
    int height;
};

//嵌套结构体
//结构体可以包含其他结构体作为成员。
struct concat {
    std::string city;
    std::string addr;
    int house_num;
};

struct person {
    std::string name;
    int age;
    concat cat; //嵌套
};

//结构体数组
//可以创建包含多个结构体的数组，用于存储多个相同类型的数据项。
struct stu {
    int id;
    std::string name;
    float score;
};

//结构体指针
//可以创建指向结构体的指针，并通过指针访问结构体成员。
struct car {
    std::string brand;
    std::string model;
    int year;
};

//使用 typedef 简化结构体定义
//使用 typedef（或 using 关键字）可以为结构体类型创建别名，使代码更简洁。
typedef struct {
    int id;
    std::string name;
    float score;
} Stu1, *PStu1;

using Stu2 = struct {
    int id;
    std::string name;
    float score;
};

//结构体中的函数
//虽然结构体主要用于存储数据，但在 C++中，结构体也可以包含成员函数。 这使得结构体更具面向对象的特性。
struct book {
    std::string title;
    std::string author;
    int pages;

    void printInfo() {
        cout << "title: " << title << "author: " << author << "pages: " << pages << endl;
    }
};

//使用结构体作为函数参数和返回值
//传递结构体给函数

//通过值传递
void printPoint(point p) {
    cout << p.x << " " << p.y << endl;
}

//通过引用传递
void movePoint(point &p, int dx, int dy) {
    p.x += dx;
    p.y += dy;
}

//函数返回结构体
point getPoint(int x, int y) {
    return point(x, y);
}

int main() {
    //定义结构体后，可以创建结构体类型的变量。
    struct student s;

    //使用点运算符（.）访问结构体成员。
    s.id = 1;
    strcpy(s.name, "John");
    cout << s.id << endl;
    cout << s.name << endl;

    //方法一：直观初始化
    student s2 = {2, "aaa"};
    //方法二：逐个赋值
    student s3;
    s3.id = 3;
    strcpy(s3.name, "bbb");
    //方法三：使用自定义构造函数
    student s4(4, "ccc");

    //嵌套结构体
    person p;
    p.name = "John";
    p.age = 5;
    p.cat.addr = "中国";
    p.cat.city = "重庆";
    p.cat.house_num = 666;

    //结构体数组
    stu stus[3] = {
        {1, "aaa", 66},
        {2, "bbb", 87},
        {3, "ccc", 92},
    };

    //结构体指针
    car cc = {"toy", "camry", 2024};
    car *pcc = &cc;
    cout << pcc->brand << endl;
    cout << pcc->model << endl;
    cout << pcc->year << endl;

    return 0;
}
