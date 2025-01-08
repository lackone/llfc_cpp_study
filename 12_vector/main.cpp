#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <bits/ranges_algo.h>

using namespace std;

//什么是向量（Vector）？
//向量（Vector）是 C++ 标准模板库（STL）中的一种序列容器，能够动态地管理可变大小的数组。与传统的固定大小的数组不同，向量可以根据需要随时调整其大小，提供更高的灵活性和便利性。

struct student {
    int id;
    string name;
    float score;
};

int main() {
    vector<int> vint;
    vector<string> vstring;

    //默认初始化：
    vector<int> vi; //空向量
    //指定大小和默认值：
    vector<int> vi2(5, 10); // 5个元素，值均为10
    //使用初始化列表：
    vector<int> vi3 = {1, 2, 3, 4, 5};
    //拷贝构造：
    vector<int> vi4(vi3); // 复制vi3
    //移动构造：
    vector<int> vi5(std::move(vi4)); // 移动vi4到vi5

    for (auto num: vi2) {
        cout << num << endl;
    }

    for (auto num: vi3) {
        cout << num << endl;
    }

    //向量的大小与容量
    //size()：返回向量中元素的数量。
    //capacity()：返回向量目前为止分配的存储容量。
    //empty()：检查向量是否为空。
    vector<int> vv = {1, 2, 3, 4, 5};
    cout << vv.size() << endl;
    cout << vv.empty() << endl;
    cout << vv.capacity() << endl;

    // capacity() 并不一定精确匹配 size()，它表示在需要重新分配内存之前，向量可以容纳的元素数量。
    vv.reserve(10); // 预留容量
    cout << vv.capacity() << endl;
    vv.shrink_to_fit(); // 收缩到适合大小
    cout << vv.capacity() << endl;

    //添加与删除元素
    //push_back()：在向量末尾添加一个元素。
    //pop_back()：移除向量末尾的元素。
    //insert()：在指定位置插入元素。
    //erase()：移除指定位置的元素或范围内的元素。
    //clear()：移除所有元素。
    vector<int> vv2;

    vv2.push_back(10);
    vv2.push_back(20);
    vv2.push_back(30);

    for (auto num: vv2) {
        cout << num << endl;
    }

    vv2.pop_back();
    for (auto num: vv2) {
        cout << num << endl;
    }

    // 在第一个位置插入25
    vv2.insert(vv2.begin(), 33);
    for (auto num: vv2) {
        cout << num << endl;
    }

    // 删除第二个元素
    vv2.erase(vv2.begin() + 1);
    for (auto num: vv2) {
        cout << num << endl;
    }

    vv2.clear(); //清空
    cout << vv2.size() << endl;

    //访问元素
    //operator[]：通过索引访问元素。
    //at()：通过索引访问元素，带边界检查。
    //front()：访问第一个元素。
    //back()：访问最后一个元素。
    vector<string> vstr = {"aaa", "bbb", "ccc"};
    cout << vstr[2] << endl;
    cout << vstr.at(1) << endl;
    cout << vstr.front() << endl;
    cout << vstr.back() << endl;

    //遍历向量
    //使用范围 for 循环
    //使用传统 for 循环
    //使用迭代器
    vector<int> vint2 = {1, 2, 3, 4, 5};

    //使用范围 for 循环
    for (auto num: vint2) {
        cout << num << endl;
    }
    //使用传统 for 循环
    for (int i = 0; i < vint2.size(); i++) {
        cout << vint2[i] << endl;
    }
    //使用迭代器
    for (auto it = vint2.begin(); it != vint2.end(); it++) {
        cout << *it << endl;
    }

    //修改元素
    //通过索引或迭代器修改
    //使用 assign() 重新赋值
    //替换整个向量内容
    vector<int> vint3 = {1, 2, 3, 4, 5};
    vint3[2] = 5;
    vint3.at(3) = 6;
    for (auto num: vint3) {
        cout << num << endl;
    }

    //嵌套向量（二维向量）
    //向量可以包含其他向量，形成多维数组结构。
    vector<vector<int> > vvv(3, vector<int>(4, 0));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            vvv[i][j] = (i + 1) * (j + 1);
        }
    }
    for (auto row: vvv) {
        for (auto col: row) {
            cout << col << "\t";
        }
        cout << endl;
    }

    //向量与其他数据结构结合
    //向量可以与结构体、类等其他数据结构结合使用，增强数据组织能力。
    vector<student> vstu;
    vstu.push_back(student{1, "aaa", 131});
    vstu.push_back(student{2, "bbb", 345});
    vstu.push_back(student{3, "ccc", 624});
    for (auto stu: vstu) {
        cout << stu.id << stu.name << stu.score << endl;
    }

    //使用迭代器操作向量
    //迭代器是一种指针类型，用于遍历和操作容器中的元素。
    vector<int> vvi = {1, 2, 3, 4, 5};
    for (auto it = vvi.begin(); it != vvi.end(); it++) {
        *it = *it + 1;
    }
    for (auto it = vvi.begin(); it != vvi.end(); it++) {
        cout << *it << endl;
    }

    //常用算法与向量
    //可以使用 <algorithm> 头文件中的 sort() 函数对向量进行排序。
    vector<int> vsort = {5, 12, 56, 1, 3, 4};

    sort(vsort.begin(), vsort.end());

    for (auto num: vsort) {
        cout << num << endl;
    }

    sort(vsort.begin(), vsort.end(), [](int a, int b) {
        return a > b;
    });

    for (auto num: vsort) {
        cout << num << endl;
    }

    //使用 reverse() 函数可以反转向量中的元素顺序。
    vector<char> vchar = {'a', 'b', 'c', 'd'};
    reverse(vchar.begin(), vchar.end());
    for (auto num: vchar) {
        cout << num << endl;
    }

    vector<std::string> fruits = {"Apple", "Banana", "Cherry", "Date"};
    auto it = find(fruits.begin(), fruits.end(), "Date");
    if (it != fruits.end()) {
        cout << distance(fruits.begin(), it) << endl;
    }

    //向量的性能与优化
    //向量会动态地管理内存，自动调整其容量以适应新增或删除的元素。频繁的内存分配可能会影响性能。
    //使用 reserve() 可以提前为向量分配足够的内存，减少内存重新分配的次数，提高性能。
    vector<int> vr;
    vr.reserve(100);
    for (int i = 0; i < 100; i++) {
        vr.push_back(i);
    }
    cout << vr.size() << endl;
    cout << vr.capacity() << endl;

    //使用 shrink_to_fit() 可以请求收缩向量的容量以匹配其大小，释放多余的内存。
    vector<int> vr2;
    vr2.reserve(100);
    vr2.push_back(0);
    vr2.push_back(1);
    vr2.push_back(2);
    cout << vr2.size() << endl;
    cout << vr2.capacity() << endl;
    vr2.shrink_to_fit(); // 收缩容量
    cout << vr2.size() << endl;
    cout << vr2.capacity() << endl;

    return 0;
}
