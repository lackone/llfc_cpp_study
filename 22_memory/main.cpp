#include <iostream>
#include <stack>
using namespace std;

//C++ 提供了多种内存管理方式，包括传统的 C 风格的 malloc 和 free，以及 C++ 专用的 new 和 delete。
//栈（Stack）：自动管理内存，存储局部变量和函数调用信息。内存分配和释放速度快，但空间有限。
//堆（Heap）：手动管理内存，用于动态分配内存。内存分配和释放由程序员控制，灵活但易出错（如内存泄漏、 悬挂指针）。
//全局/静态区（Data/BSS Segment）：存储全局变量和静态变量。

//malloc（memory allocation）用于在堆上分配指定字节数的内存。
//free 用于释放之前由 malloc、calloc 或 realloc 分配的内存。

//C++ 提供了更高层次的内存管理操作符：new 和 delete，它们不仅分配和释放内存，还调用构造函数和析构函数，提供类型安全。
class MyClass {
public:
    MyClass(int v) : _value(v) {
        cout << "MyClass" << endl;
    }

    ~MyClass() {
        cout << "~MyClass" << endl;
    }

private:
    int _value;
};

//new delete 区别于 malloc 和 free
//类型安全：new 返回正确类型的指针，免去了强制类型转换。
//构造/析构：new 和 delete 自动调用构造函数和析构函数。
//异常处理：在分配失败时，new 默认抛出 std::bad_alloc 异常，而 malloc 返回 nullptr。

class MyClass2 {
public:
    MyClass2(int v) : _value(v) {
        cout << "MyClass2" << endl;
    }

    ~MyClass2() {
        cout << "~MyClass2" << endl;
    }

    int _value;
};

//使用 malloc 和 realloc 来手动管理动态数组可以实现可变大小的数组，但需要处理内存分配、释放和数据复制。
class DynamicArray {
public:
    DynamicArray(size_t size) : _size(size), _data((int *) malloc(size * sizeof(int))) {
        if (_data == nullptr) {
            throw std::bad_alloc();
        }
    }

    ~DynamicArray() {
        if (_data) {
            free(_data);
        }
    }

    void resize(size_t size) {
        int *tmp = (int *) realloc(_data, size * sizeof(int));
        if (tmp == nullptr) {
            throw std::bad_alloc();
        }
        _data = tmp;
        _size = size;
    }

    int &operator[](size_t index) {
        return _data[index];
    }

    size_t getSize() const {
        return _size;
    }

private:
    size_t _size;
    int *_data;
};

class DynamicArray2 {
public:
    DynamicArray2() : _cap(2), _size(0), _data((int *) malloc(_cap * sizeof(int))) {
        if (_data == nullptr) {
            throw std::bad_alloc();
        }
    }

    ~DynamicArray2() {
        if (_data) {
            free(_data);
        }
    }

    void add(int value) {
        if (_size == _cap) {
            resize(_cap * 2);
        }
        _data[_size++] = value;
    }

    int get(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("out of range");
        }
        return _data[index];
    }

    void resize(size_t cap) {
        int *tmp = (int *) realloc(_data, cap * sizeof(int));
        if (tmp == nullptr) {
            throw std::bad_alloc();
        }
        _data = tmp;
        _cap = cap;
    }

    size_t getSize() const {
        return _size;
    }

private:
    size_t _cap;
    size_t _size;
    int *_data;
};

//自定义内存管理器
//实现一个简单的内存池，用于高效分配和释放固定大小的对象。
class MemoryPool {
public:
    MemoryPool(size_t obj_size, size_t pool_size) : _obj_size(obj_size), _pool_size(pool_size),
                                                    _pool((char *) malloc(obj_size * pool_size)) {
        if (_pool == nullptr) {
            throw std::bad_alloc();
        }
        // 初始化 _pool_list
        for (size_t i = 0; i < _pool_size; i++) {
            _pool_list.push(_pool + i * _obj_size);
        }
    }

    ~MemoryPool() {
        if (_pool) {
            free(_pool);
        }
    }

    void *allocate() {
        if (_pool_list.empty()) {
            throw std::bad_alloc();
        }
        void *p = _pool_list.top(); //获取栈顶元素但不移除它。
        _pool_list.pop(); //移除栈顶元素。
        return p;
    }

    void deallocate(void *p) {
        _pool_list.push(p);
    }

private:
    size_t _obj_size; //对象大小
    size_t _pool_size; //池大小
    char *_pool;
    stack<void *> _pool_list; //池列表
};

//避免内存泄漏
//内存泄漏是指程序分配的内存未被释放，导致内存被浪费，甚至耗尽。避免内存泄漏的策略包括：
//  确保每个 new 有对应的 delete。
//  使用 RAII 和智能指针：自动管理资源，避免手动管理内存。
//  工具辅助：使用工具如 Valgrind 检测内存泄漏。

//RAII（资源获取即初始化）
//  RAII 是 C++中的一种编程惯用法，通过对象的生命周期管理资源，确保资源在对象构造时获取，析构时释放，避免泄漏。
//示例：RAII 实现类似于shared_ptr智能指针
//  std::shared_ptr 是 C++ 标准库中功能强大的智能指针之一，提供了共享所有权的能力，使得多个指针可以共同管理同一个动态分配的对象。
//  通过引用计数机制，shared_ptr 确保了对象在最后一个指针被销毁时自动释放，极大地简化了内存管理，防止了内存泄漏和悬挂指针问题。

//SimpleSharedPtr 的基本概念
//SimpleSharedPtr 是一个简化版的 shared_ptr 实现，旨在帮助理解其核心机制。
//其基本功能包括：
//  共享所有权：多个 SimpleSharedPtr
//  实例可以指向同一个对象，共享对该对象的所有权。
//  自动管理生命周期：当最后一个 SimpleSharedPtr被销毁或指向其他对象时，管理的对象被自动释放。
//  引用计数：内部维护一个引用计数，记录有多少个 SimpleSharedPtr 实例指向同一个对象。
struct CtlBlock {
    int ref_cnt;

    CtlBlock() : ref_cnt(1) {
    }
};

template<typename T>
class SimpleSharedPtr {
public:
    // 默认构造函数
    SimpleSharedPtr() : _ptr(nullptr), _ctl(nullptr) {
    }

    // 参数化构造函数
    explicit SimpleSharedPtr(T *p) : _ptr(p) {
        if (p) {
            _ctl = new CtlBlock();
        } else {
            _ctl = nullptr;
        }
    }

    // 拷贝构造函数
    SimpleSharedPtr(const SimpleSharedPtr &other) : _ptr(other._ptr), _ctl(other._ctl) {
        if (_ctl) {
            _ctl->ref_cnt++;
        }
    }

    // 拷贝赋值操作符
    SimpleSharedPtr &operator=(const SimpleSharedPtr &other) {
        if (this == &other) {
            return *this;
        }
        release();
        _ptr = other._ptr;
        _ctl = other._ctl;
        if (_ctl) {
            _ctl->ref_cnt++;
        }
        return *this;
    }

    // 移动构造函数
    SimpleSharedPtr(SimpleSharedPtr &&other) noexcept : _ptr(other._ptr), _ctl(other._ctl) {
        other._ptr = nullptr;
        other._ctl = nullptr;
    }

    // 移动赋值操作符
    SimpleSharedPtr &operator=(SimpleSharedPtr &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        release();
        _ptr = other._ptr;
        _ctl = other._ctl;
        other._ptr = nullptr;
        other._ctl = nullptr;
        return *this;
    }

    // 析构函数
    ~SimpleSharedPtr() {
        release();
    }

    // 解引用操作符
    T &operator*() const {
        return *_ptr;
    }

    // 箭头操作符
    T *operator->() const {
        return _ptr;
    }

    // 获取引用计数
    int getRefCount() const {
        return _ctl ? _ctl->ref_cnt : 0;
    }

    // 获取裸指针
    T *get() const {
        return _ptr;
    }

    // 重置指针
    void reset(T *p = nullptr) {
        release();
        _ptr = p;
        if (p) {
            _ctl = new CtlBlock();
        } else {
            _ctl = nullptr;
        }
    }

private:
    //释放资源
    void release() {
        if (_ctl) {
            _ctl->ref_cnt--;
            if (_ctl->ref_cnt == 0) {
                delete _ptr;
                delete _ctl;
            }
        }
        _ptr = nullptr;
        _ctl = nullptr;
    }

    T *_ptr;
    CtlBlock *_ctl;
};

//SimpleUniquePtr 的实现
//std::unique_ptr 是一种独占所有权的智能指针，确保在任意时刻，只有一个 unique_ptr 实例指向特定资源。 它不支持拷贝操作，只支持移动操作。
template<typename T>
class SimpleUniquePtr {
public:
    SimpleUniquePtr() : _ptr(nullptr) {
    }

    explicit SimpleUniquePtr(T *p) : _ptr(p) {
    }

    ~SimpleUniquePtr() {
        delete _ptr;
    }

    // 删除拷贝构造和拷贝赋值
    SimpleUniquePtr(const SimpleUniquePtr &other) = delete;

    SimpleUniquePtr &operator=(const SimpleUniquePtr &other) = delete;

    // 移动构造
    SimpleUniquePtr(SimpleUniquePtr &&other) : _ptr(other._ptr) {
        other._ptr = nullptr;
    }

    // 移动赋值
    SimpleUniquePtr &operator=(SimpleUniquePtr &&other) {
        if (this == &other) {
            return *this;
        }
        delete _ptr;
        _ptr = other._ptr;
        other._ptr = nullptr;
        return *this;
    }

    // 解引用操作符
    T &operator*() const {
        return *_ptr;
    }

    // 箭头操作符
    T *operator->() const {
        return _ptr;
    }

    // 获取裸指针
    T *get() const {
        return _ptr;
    }

    // 释放所有权
    T *release() {
        T *tmp = _ptr;
        _ptr = nullptr;
        return tmp;
    }

    // 重新设定指针
    void reset(T *ptr = nullptr) {
        delete _ptr;
        _ptr = ptr;
    }

private:
    T *_ptr;
};

int main() {
    //类型转换：malloc 返回 void*，需要显式转换为所需类型的指针。
    int *p = (int *) malloc(10 * sizeof(int));
    if (p == nullptr) {
        cout << "内存分配失败" << endl;
        return -1;
    }
    //初始化：malloc 分配的内存未初始化，内容不确定。
    for (int i = 0; i < 10; i++) {
        p[i] = i;
    }
    for (int *q = p; q != p + 10; q++) {
        cout << *q << endl;
    }
    //释放对应性：由 malloc 分配的内存必须使用 free 释放，避免使用 delete。
    free(p);

    MyClass *mc = new MyClass(10);
    delete mc; // 调用析构函数并释放内存

    //数组
    int *arr = new int[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << endl;
    }
    delete []arr; // 释放数组内存

    //释放单个对象  delete ptr;
    //释放数组  delete[] ptr;

    //可以通过 nothrow 参数防止 new 抛出异常，改为返回 nullptr。
    int *p2 = new(nothrow) int;
    if (p2 == nullptr) {
        cout << "内存分配失败" << endl;
        return -1;
    }
    delete p2;

    MyClass2 *mc2 = new MyClass2(10);
    if (mc2 == nullptr) {
        cout << "内存分配失败" << endl;
        return -1;
    }
    cout << mc2->_value << endl;

    //注意这里并没有重新生成新内存
    new(mc2) MyClass2(20); // 通过“定位 new”调用构造函数
    cout << mc2->_value << endl;
    mc2->~MyClass2(); // 手动调用析构函数
    free(mc2);

    MyClass2 *mc3 = new MyClass2(30);
    cout << mc3->_value << endl;
    delete mc3;

    //realloc 用于调整之前分配的内存块大小。这在动态数组等数据结构中非常有用。
    int *arr2 = (int *) malloc(3 * sizeof(int));
    if (arr2 == nullptr) {
        return -1;
    }
    // 初始化数组
    for (int i = 0; i < 3; i++) {
        arr2[i] = i;
    }
    for (int i = 0; i < 3; i++) {
        cout << arr2[i] << endl;
    }
    // 重新分配为 5 个整数
    int *arr2_tmp = (int *) realloc(arr2, 5 * sizeof(int));
    if (arr2_tmp == nullptr) {
        return -1;
    }
    for (int i = 3; i < 5; i++) {
        arr2_tmp[i] = i;
    }
    for (int i = 0; i < 5; i++) {
        cout << arr2_tmp[i] << endl;
    }
    free(arr2_tmp);

    //动态数组
    try {
        DynamicArray darr(3);
        for (int i = 0; i < darr.getSize(); i++) {
            darr[i] = i;
        }
        for (int i = 0; i < darr.getSize(); i++) {
            cout << darr[i] << endl;
        }
        darr.resize(5);
        darr[3] = 33;
        darr[4] = 44;
        for (int i = 0; i < darr.getSize(); i++) {
            cout << darr[i] << endl;
        }
    } catch (std::bad_alloc &e) {
        cout << e.what() << endl;
    }

    try {
        DynamicArray2 darr2;
        darr2.add(10);
        darr2.add(20);
        darr2.add(30);
        for (int i = 0; i < darr2.getSize(); i++) {
            cout << darr2.get(i) << endl;
        }
    } catch (std::bad_alloc &e) {
        cout << e.what() << endl;
    }

    //MemoryPool 管理固定大小的内存块，避免频繁调用 malloc 和 free。
    //使用“ 定位 new” 在预分配的内存上构造对象。
    //需要手动调用析构函数和将内存返回给内存池。
    //创建一个能容纳 3 个 MyClass2 对象的内存池
    MemoryPool mp(sizeof(MyClass2), 3);
    void *mm1 = mp.allocate();
    void *mm2 = mp.allocate();
    //使用“定位 new”构造对象
    MyClass2 *obj1 = new(mm1) MyClass2(11);
    MyClass2 *obj2 = new(mm2) MyClass2(22);
    cout << obj1->_value << endl;
    cout << obj2->_value << endl;
    // 显式调用析构函数
    obj1->~MyClass2();
    obj2->~MyClass2();
    // 释放内存
    mp.deallocate(mm1);
    mp.deallocate(mm2);

    return 0;
}
