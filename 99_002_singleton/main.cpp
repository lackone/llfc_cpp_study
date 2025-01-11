#include <iostream>
#include <memory>
#include <thread>
using namespace std;

//1、局部静态变量方式
class Single1 {
private:
    Single1() {
        //把构造函数声明为私有
    }

    Single1(const Single1 &obj) = delete; //拷贝构造删除
    Single1 &operator=(const Single1 &obj) = delete; //赋值删除
public:
    static Single1 &instance() {
        //函数的局部静态变量生命周期随着进程结束而结束
        static Single1 inst;
        return inst;
    }
};

void Single1_test(int i) {
    cout << i << " " << &Single1::instance() << endl;
}

//2、静态成员变量指针方式
class Single2 {
private:
    Single2() {
        //把构造函数声明为私有
    }

    Single2(const Single2 &obj) = delete; //拷贝构造删除
    Single2 &operator=(const Single2 &obj) = delete; //赋值删除
public:
    static Single2 *instance() {
        if (inst == nullptr) {
            inst = new Single2();
        }
        return inst;
    }

private:
    static Single2 *inst;
};

//饿汉式初始化
Single2 *Single2::inst = Single2::instance();

void Single2_test(int i) {
    cout << i << " " << Single2::instance() << endl;
}

class Single3 {
private:
    Single3() {
    }

    Single3(const Single3 &obj) = delete;

    Single3 &operator=(const Single3 &obj) = delete;

public:
    static Single3 *instance() {
        if (inst != nullptr) {
            return inst;
        }

        lock.lock();
        if (inst != nullptr) {
            lock.unlock();
            return inst;
        }
        inst = new Single3();
        lock.unlock();
        return inst;
    }

private:
    static Single3 *inst;
    static mutex lock;
};

//3、智能指针方式
class Single4 {
private:
    Single4() {
    }

    Single4(const Single4 &obj) = delete;

    Single4 &operator=(const Single4 &obj) = delete;

public:
    static shared_ptr<Single4> instance() {
        if (inst != nullptr) {
            return inst;
        }
        lock.lock();
        if (inst != nullptr) {
            lock.unlock();
            return inst;
        }
        inst = shared_ptr<Single4>(new Single4());
        lock.unlock();
        return inst;
    }

private:
    static shared_ptr<Single4> inst;
    static mutex lock;
};


//4、辅助类智能指针单例模式
class Single5;

class Single5Del {
public:
    void operator()(Single5 *obj) {
        delete obj;
    }
};

class Single5 {
private:
    Single5() {
    }

    ~Single5() {
    }

    Single5(const Single5 &obj) = delete;

    Single5 &operator=(const Single5 &obj) = delete;

    friend class Single5Del;

public:
    static shared_ptr<Single5> instance() {
        if (inst != nullptr) {
            return inst;
        }
        lock.lock();
        if (inst != nullptr) {
            return inst;
        }
        inst = shared_ptr<Single5>(new Single5(), Single5Del());
        lock.unlock();
        return inst;
    }

private:
    static shared_ptr<Single5> inst;
    static mutex lock;
};

//5、通用的单例模板类
template<typename T>
class Single_Del_T {
public:
    void operator()(T *obj) {
        delete obj;
    }
};

template<typename T>
class Single_T {
protected:
    Single_T() = default;

    Single_T(const Single_T<T> &obj) = delete;

    Single_T<T> &operator=(const Single_T<T> &obj) = delete;

    ~Single_T() = default;

    friend class Single_Del_T<T>;

public:
    static shared_ptr<T> instance() {
        if (inst != nullptr) {
            return inst;
        }
        lock.lock();
        if (inst != nullptr) {
            lock.unlock();
            return inst;
        }
        inst = shared_ptr<T>(new T, Single_Del_T<T>());
        lock.unlock();
        return inst;
    }

private:
    static shared_ptr<T> inst;
    static mutex lock;
};

int main() {
    //2次打印的地址一样
    cout << &Single1::instance() << endl;
    cout << &Single1::instance() << endl;
    //对于多线程方式生成的实例可能时多个。
    thread tarr[10];
    for (int i = 0; i < 10; i++) {
        tarr[i] = thread(Single1_test, i);
    }
    for (int i = 0; i < 10; i++) {
        tarr[i].join();
    }

    //无论单线程还是多线程模式下，通过静态成员变量的指针实现的单例类都是唯一的
    for (int i = 0; i < 10; i++) {
        tarr[i] = thread(Single2_test, i);
    }
    for (int i = 0; i < 10; i++) {
        tarr[i].join();
    }

    return 0;
}
