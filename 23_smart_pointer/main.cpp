#include <iostream>
#include <memory>
using namespace std;

//C++ 引入智能指针的主要目的是为了自动化内存管理，减少手动 new 和 delete 带来的复杂性和错误。
//智能指针通过 RAII（资源获取即初始化）机制，在对象生命周期结束时自动释放资源，从而有效防止内存泄漏和资源管理错误。

//原生指针
//原生指针是 C++ 最基本的指针类型，允许程序员直接管理内存。然而，原生指针存在以下问题：
//  内存泄漏：未释放动态分配的内存。
//  悬挂指针：指针指向已释放或未初始化的内存。
//  双重释放：多次释放同一内存区域。

//智能指针的优势
//智能指针通过封装原生指针，自动管理内存，解决上述问题。主要优势包括：
//  自动销毁：在智能指针生命周期结束时自动释放资源。
//  引用计数：共享智能指针能够跟踪引用数量，确保资源在最后一个引用结束时释放。
//  避免内存泄漏：通过 RAII 机制自动管理资源生命周期。
//  类型安全：提供更严格的类型检查，减少错误。

//unique_ptr
//unique_ptr 是一种独占所有权的智能指针，任何时刻只能有一个 unique_ptr 实例拥有对某个对象的所有权。不能被拷贝，只能被移动。

//shared_ptr
//shared_ptr 是一种共享所有权的智能指针，允许多个 shared_ptr 实例共享对同一个对象的所有权。通过引用计数机制，管理资源的生命周期。

//weak_ptr
//weak_ptr 是一种不拥有对象所有权的智能指针，用于观察但不影响对象的生命周期。主要用于解决 shared_ptr 之间的循环引用问题。
class B; // 前向声明

class A {
public:
    shared_ptr<B> ptrB;

    A() { cout << "A Constructor" << endl; }
    ~A() { cout << "A Destructor" << endl; }
};

class B {
public:
    shared_ptr<A> ptrA;

    B() { cout << "B Constructor" << endl; }
    ~B() { cout << "B Destructor" << endl; }
};

//使用 weak_ptr
//改用 weak_ptr 其中一方（如 B 的 ptrA），打破循环引用。
class D;

class C {
public:
    shared_ptr<D> ptrD;

    C() { cout << "C Constructor" << endl; }
    ~C() { cout << "C Destructor" << endl; }
};

class D {
public:
    weak_ptr<C> ptrC; // 使用 weak_ptr

    D() { cout << "D Constructor" << endl; }
    ~D() { cout << "D Destructor" << endl; }
};

class Test {
public:
    Test(int val) : value(val) {
        cout << "Test constructor" << endl;
    }

    ~Test() {
        cout << "Test destructor" << endl;
    }

    void show() const {
        cout << value << endl;
    }

private:
    int value;
};

//有时，默认的 delete 操作不适用于所有资源管理场景。此时，可以使用自定义删除器来指定资源释放的方式。例如，管理文件句柄、网络资源或自定义清理逻辑。
struct FileDeleter {
    void operator()(FILE *fp) const {
        if (fp) {
            cout << "Closing file." << endl;
            fclose(fp);
        }
    }
};

//选择合适的智能指针
//std::unique_ptr：
//  用于明确的独占所有权场景。
//  适用于资源的单一管理者或需要所有权转移的情况。
//  更轻量，性能更优。
//std::shared_ptr：
//  用于共享所有权的场景。
//  需要多个指针共同管理同一资源时使用。
//  引用计数带来一定的性能开销。
//std::weak_ptr：
//  用于观察不拥有资源的场景。
//  适用于需要避免循环引用或只需临时访问资源的情况。

int main() {
    //由于 unique_ptr 不能被拷贝，必须通过移动语义转移所有权。这保证了资源的独占性。

    unique_ptr<Test> ptr(new Test(111));
    ptr->show();

    // 使用 make_unique（C++14 引入）
    auto ptr2 = make_unique<Test>(222);
    ptr2->show();

    unique_ptr<Test> ptr3 = move(ptr); //移动语义
    ptr3->show();
    if (!ptr) {
        cout << "ptr已为nullptr" << endl;
    }

    ptr2.reset(new Test(33));
    ptr2->show();

    shared_ptr<Test> sp(new Test(44));
    cout << sp.use_count() << endl;
    sp->show();

    shared_ptr<Test> sp2 = sp;
    cout << sp.use_count() << endl;
    cout << sp2.use_count() << endl;

    shared_ptr<Test> sp3;
    sp3 = sp2;
    cout << sp.use_count() << endl;
    cout << sp2.use_count() << endl;
    cout << sp3.use_count() << endl;

    sp2.reset(new Test(55)); //原资源释放，新资源为1
    cout << sp.use_count() << endl; //2
    cout << sp2.use_count() << endl; //1
    cout << sp3.use_count() << endl; //2


    shared_ptr<A> a = make_shared<A>();
    shared_ptr<B> b = make_shared<B>();
    a->ptrB = b;
    b->ptrA = a;

    //改用 weak_ptr 其中一方（如 B 的 ptrA），打破循环引用。
    shared_ptr<C> c = make_shared<C>();
    shared_ptr<D> d = make_shared<D>();
    c->ptrD = d;
    d->ptrC = c;

    //weak_ptr 不能直接访问对象，需要通过 lock() 方法转换为 shared_ptr，并检查对象是否仍然存在。
    shared_ptr<int> spp = make_shared<int>(66);
    weak_ptr<int> wp = spp;
    if (auto lock = wp.lock()) {
        cout << *lock << endl;
    } else {
        cout << "spp release" << endl;
    }
    spp.reset();
    if (auto lock = wp.lock()) {
        cout << *lock << endl;
    } else {
        cout << "spp release" << endl;
    }

    //自定义删除器 FileDeleter 用于在 shared_ptr 被销毁时关闭文件。
    shared_ptr<FILE> filePtr(fopen("test.txt", "w"), FileDeleter());
    if (filePtr) {
        cout << "File opened successfully." << endl;
        //使用 filePtr.get() 获取原生 FILE* 指针进行文件操作。
        // 使用 filePtr 进行文件操作
        fprintf(filePtr.get(), "Hello, World!\n");
    }

    //C++11 允许使用 lambda 表达式作为删除器，简化代码。
    auto fileDeleter = [](FILE *fp) {
        if (fp) {
            cout << "Closing file via lambda." << endl;
            fclose(fp);
        }
    };

    unique_ptr<FILE, decltype(fileDeleter)> filePtr2(fopen("test2.txt", "w"), fileDeleter);
    if (filePtr2) {
        cout << "File opened successfully." << endl;
        fprintf(filePtr2.get(), "Hello, Lambda!\n");
    }

    return 0;
}
