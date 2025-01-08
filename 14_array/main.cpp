#include <iostream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

//数组概念
//数组是一种类似于标准库类型vector的数据结构，但是在性能和灵活性的权衡上又与vector有所不同。
//数组是一种复合类型。数组的声明形如
//类型 a[d];
//维度必须是一个常量表达式

// 自定义的字符串复制函数
char *my_strcpy(char *dest, const char *src) {
    char *p = dest;
    while (*src != '\0') {
        *p++ = *src++;
    }
    *p = '\0';
    return dest;
}

// 自定义的字符串连接函数
char *my_strcat(char *dest, const char *src) {
    char *p = dest;
    while (*p++ != '\0');
    p--;
    while (*src != '\0') {
        *p++ = *src++;
    }
    *p = '\0';
    return dest;
}

int main() {
    constexpr int size = 10;

    int arr[size];

    //显式初始化数组元素
    int ival[size] = {0, 1, 2};

    int ival2[] = {0, 1, 2};

    string sval[] = {"aaa", "bbb"};

    //不能将数组的内容拷贝给其他数组作为其初始值，也不能用数组为其他数组赋值：
    //int ival3[] = ival2;

    //理解复杂的数组声明
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *parr[10]; //数组元素都是指针

    int (*parr2)[10]; //指针，指向 int[10]

    int (&parr3)[10] = arr2; //引用，

    //访问数组元素
    //数组的大小可以用sizeof(arr)获取，要进一步计算获取其中的元素个数，我们可以使用sizeof(arr)/sizeof(int)
    for (int i = 0; i < (sizeof(arr2) / sizeof(int)); i++) {
        cout << arr2[i] << endl;
    }

    //指针和数组
    //数组的元素也是对象，对数组使用下标运算符得到该数组指定位置的元素。因此像其他对象一样，对数组的元素使用取地址符就能得到指向该元素的指针：
    int arr3[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // 第一个元素地址
    cout << "first element: address is " << &arr3[0] << endl;
    // 数组首地址
    cout << "arr address is " << arr3 << endl;
    // 数组首地址
    cout << "arr address is " << &arr3 << endl;
    //数组还有一个特性：在很多用到数组名字的地方，编译器都会自动地将其替换为一个指向数组首元素的指针：
    //等价于 int * first_elem_addr = &arr[0];
    int *first_elem_addr = arr;
    cout << "first element address is " << first_elem_addr << endl;

    //ia2是一个int类型的指针,指向ia的第一个元素
    auto ia2(arr);
    //当使用decltype关键字时上述转换不会发生，decltype（ia）返回的类型是由10个整数构成的数组：
    decltype(arr) ia3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    //指针也是迭代器
    int arr4[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *e = arr4 + 10;
    for (int *b = arr4; b != e; b++) {
        cout << *b << endl;
    }

    //C++11提供了获取最后元素的下一个位置的指针，以及指向首元素的指针
    for (auto it = begin(arr4); it != end(arr4); it++) {
        cout << *it << endl;
    }

    //指针运算
    //指向数组元素的指针可以执行的运算，包括解引用、递增、比较、与整数相加、两个指针相减等，用在指针和用在迭代器上意义完全一致。

    //两个指针相减的结果是它们之间的距离。
    cout << end(arr4) - begin(arr4) << endl;

    //解引用和指针运算的交互
    //指针加上一个整数所得的结果还是一个指针。
    int ia[] = {0, 2, 4, 6, 8};
    int last = *(ia + 4);
    cout << "last is " << last << endl;

    //下标和指针的关系
    //对数组执行下标运算其实是对指向数组元素的指针解引用
    int ia4[] = {0, 2, 4, 6, 8};
    //等价于ia4[1]
    int value = *(ia4 + 1);

    //C风格字符串
    //字符串字面值是一种通用结构的实例，这种结构即是C++由C继承而来的C风格字符串（C-style character string）。
    //C风格字符串不是一种类型，而是为了表达和使用字符串而形成的一种约定俗成的写法。按此习惯书写的字符串存放在字符数组中并以空字符结束（null terminated）。
    //以空字符结束的意思是在字符串最后一个字符后面跟着一个空字符（'\0'）。一般利用指针来操作这些字符串。
    char *msg = "hello,world";
    cout << strlen(msg) << endl;

    char *s1 = "a string";
    char *s2 = "b string";
    if (strcmp(s1, s2) == 0) {
        cout << "相等" << endl;
    }

    //字符串拼接
    char dest[20] = "hello";

    strcpy(dest + strlen(dest), "world");
    cout << dest << endl;
    strcat(dest, "!!!");
    cout << dest << endl;

    //混用string对象和C风格字符串
    string s("Hello World");
    //注意返回const char *
    const char *str = s.c_str();

    //使用数组初始化vector对象
    int int_arr[] = {0, 1, 2, 3, 4, 5};
    vector<int> ivec(begin(int_arr), end(int_arr));
    for (auto e: ivec) {
        cout << e << " ";
    }
    cout << endl;

    char msg1[20] = "";
    char msg2[] = "aaaa";
    cout << my_strcpy(msg1, msg2) << endl;

    char msg3[] = "bbbb";
    cout << my_strcat(msg2, msg3) << endl;

    return 0;
}
