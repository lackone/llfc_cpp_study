#include <iostream>

using namespace std;

//指针是一种特殊的变量，它存储的是另一个变量的内存地址，而不是数据本身。通过使用指针，我们可以直接访问和操作内存中的数据。指针也叫做地址。

//和引用的区别
//指针（pointer）是“指向（point to）”另外一种类型的复合类型。与引用类似，指针也实现了对其他对象的间接访问。然而指针与引用相比又有很多不同点。
//其一，指针本身就是一个对象，允许对指针赋值和拷贝，而且在指针的生命周期内它可以先后指向几个不同的对象。
//其二，指针无须在定义时赋初值。 和其他内置类型一样，在块作用域内定义的指针如果没有被初始化，也将拥有一个不确定的值。


int main() {
    int *ptr; //指针可以不赋初值

    //直接赋值内存地址：这通常不是常规做法，因为直接操作内存地址可能会导致未定义行为。
    //赋值变量的地址：这是更常见的做法，使用取地址运算符（ &）来获取变量的地址，并将其赋值给指针。
    int *p1 = (int *) 0x12345678; //直接赋内存地址
    int a = 100;
    int *p2 = &a; //赋变量地址

    cout << p1 << endl;
    cout << p2 << endl;

    int **p3 = &p1; //p3存的是p1的地址
    cout << p3 << endl;
    cout << *p3 << endl; //*p3读取p1地址的值

    //指针值
    //指针的值（即地址）应属下列4种状态之一：
    //1.指向一个对象。
    //2.指向紧邻对象所占空间的下一个位置。
    //3.空指针，意味着指针没有指向任何对象。
    //4.无效指针，也就是上述情况之外的其他值。

    //利用*(解引用操作符)获取指针所指向的对象的数据
    int ival = 66;
    int *pp = &ival;
    cout << *pp << endl;

    //利用指针修改对象
    *pp = 100;
    cout << ival << endl;

    //空指针
    int *pp2 = nullptr;
    int *pp3 = 0;
    int *pp4 = NULL;

    cout << pp2 << endl;
    cout << pp3 << endl;
    cout << pp4 << endl;

    //指针和引用都能提供对其他对象的间接访问，然而在具体实现细节上二者有很大不同，其中最重要的一点就是引用本身并非一个对象。
    int ii = 44;
    int *pii = &ii;
    cout << pii << endl;
    cout << &ii << endl;
    *pii = 55;
    cout << ii << endl;
    int jj = 55;
    pii = &jj; //改变指针的指向
    cout << pii << endl;
    cout << &jj << endl;
    *pii = 66;
    cout << jj << endl;

    //指针判空
    int *pii2 = nullptr;
    if (!pii2) {
        cout << "pii2是空指针" << endl;
    }
    //给指针赋值
    int ff = 100;
    pii2 = &ff;
    if (pii2) {
        cout << "pii2不是空指针" << endl;
    }

    //万能指针 void*
    //void＊是一种特殊的指针类型，可用于存放任意对象的地址。一个void＊指针存放着一个地址，这一点和其他指针类似。
    double dd = 3.14;
    void *pdd = &dd;

    //指向指针的指针
    int iii = 111;
    int *piii = &iii; //指针
    int **piii2 = &piii; //指针的指针
    int ***piii3 = &piii2; //指针的指针的指针
    cout << *piii << endl;
    cout << **piii2 << endl;
    cout << ***piii3 << endl;

    //指向指针的引用
    //引用本身不是一个对象，因此不能定义指向引用的指针。但指针是对象，所以存在对指针的引用：
    int jjj = 222;
    int *pjjj;
    int *&rpjjj = pjjj; //rpjjj是一个引用，引用类型是一个指针
    rpjjj = &jjj; //rpjjj是指针pjjj的别名，相当于 pjjj = &jjj;
    *rpjjj = 333; //相当于 *pjjj = 333;
    cout << jjj << endl;

    //指针运算
    //指针可以进行算术运算，如递增（++）和递减（--），这些操作会改变指针所指向的内存地址。 但是，这种操作仅限于指向数组元素的指针。
    int arr[5] = {1, 2, 3, 4, 5};
    int *pa = arr;

    cout << *pa << endl;
    cout << *(++pa) << endl;
    cout << pa[2] << endl;

    //指针必须在使用前被初始化，否则它们可能包含垃圾值，导致未定义行为。
    //指针运算（如递增和递减）仅适用于指向数组元素的指针。
    //指针的解引用操作必须确保指针不是空指针（nullptr），否则会导致运行时错误。

    return 0;
}
