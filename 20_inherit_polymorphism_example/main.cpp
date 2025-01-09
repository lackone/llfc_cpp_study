#include <algorithm>
#include <iostream>

using namespace std;

class Person {
public:
    Person(string name, int age) : _name(name), _age(age) {
    }

    void displayInfo() {
        cout << "Name: " << _name << "Age: " << _age << endl;
    }

protected:
    string _name;
    int _age;
};

class Student : public Person {
public:
    Student(string name, int age, string sid) : Person(name, age), student_id(sid) {
    }

    void displayInfo() {
        cout << "Name: " << _name << " Age: " << _age << " StudentId: " << student_id << endl;
    }

private:
    string student_id;
};

class Shape {
public:
    virtual void draw() {
        cout << "Drawing a generic shape." << endl;
    }
};

class Circle : public Shape {
public:
    void draw() {
        cout << "Drawing a circle." << endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() {
        cout << "Drawing a rectangle." << endl;
    }
};

class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }

    double add(double a, double b) {
        return a + b;
    }
};

class AdvancedCalculator : public Calculator {
public:
    int add(int a, int b, int c) {
        return a + b + c;
    }
};

class Animal {
public:
    virtual void makeSound() const = 0;
};

class Dog : public Animal {
public:
    void makeSound() const override {
        cout << "Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        cout << "Meow!" << endl;
    }
};

class Vehicle {
public:
    Vehicle() {
        cout << "Vehicle constructed." << endl;
    }

    ~Vehicle() {
        cout << "Vehicle destructed." << endl;
    }
};

class Car : public Vehicle {
public:
    Car() {
        cout << "Car constructed." << endl;
    }

    ~Car() {
        cout << "Car destructed." << endl;
    }
};

int main() {
    Student s1("alice", 20, "S12345");
    s1.displayInfo();

    Shape s;
    Circle c;
    Rectangle r;
    Shape *arr[3] = {
        &s,
        &c,
        &r,
    };
    for_each(begin(arr), end(arr), [](Shape *s) {
        s->draw();
    });

    AdvancedCalculator ac;
    //ac.add(2, 3); //隐藏了
    //ac.add(2.5, 3.5); //隐藏了
    cout << ac.Calculator::add(2, 3) << endl;
    cout << ac.Calculator::add(2.5, 3.5) << endl;
    cout << ac.add(1, 2, 3) << endl;

    Animal *dog = new Dog;
    Animal *cat = new Cat;
    dog->makeSound();
    cat->makeSound();
    delete dog;
    delete cat;

    Car car;

    return 0;
}
