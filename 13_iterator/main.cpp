#include <iostream>
#include <vector>
using namespace std;

//迭代器（Iterator）是C++标准模板库（STL）中的一个重要概念，它提供了一种方法，按顺序访问容器（如vector, list, map等）中的元素，而无需暴露容器的内部表示。
//迭代器就像是一个指针，但它比指针更加安全，因为它只能访问容器内的元素，并且它的类型与容器紧密相关。

//和指针不一样的是，获取迭代器不是使用取地址符，有迭代器的类型同时拥有返回迭代器的成员。
//auto b = v.begin(), e = v.end();
//end成员则负责返回指向容器（或string对象）“尾元素的下一位置（one past the end）”的迭代器，也就是说，该迭代器指示的是容器的一个本不存在的“尾后（off the end）”元素。

//特殊情况下如果容器为空，则begin和end返回的是同一个迭代器。

int main() {
    //比较运算
    std::string s("some string");
    //确保s非空
    if (s.begin() != s.end()) {
        //第一个字母改为大写
        auto it = s.begin();
        *it = toupper(*it);
    }
    cout << s << endl;

    //把字符串中的第一个单词改为大写
    std::string s2 = "another string";
    //自增运算
    for (auto it = s2.begin(); it != s2.end() && !isspace(*it); ++it) {
        *it = toupper(*it);
    }
    std::cout << s2 << std::endl;

    //迭代器类型
    // 迭代器it, it能读写vector<int>的元素
    std::vector<int>::iterator it;
    // it2能读写string对象的字符
    std::string::iterator it2;
    // it3只能读元素，不能写元素
    std::vector<int>::const_iterator it3;
    // it4只能读字符,不能写字符
    std::string::const_iterator it4;

    vector<int> num = {1, 2, 3, 4, 5};
    // 使用 const_iterator 遍历
    vector<int>::const_iterator iit;
    for (iit = num.cbegin(); iit != num.cend(); ++iit) {
        cout << *iit << endl;
    }

    //begin和end运算符
    //begin和end返回的具体类型由对象是否是常量决定，如果对象是常量，begin和end返回const_iterator；如果对象不是常量，返回iterator：
    std::vector<int> v;
    const std::vector<int> cv;
    //it1是 vector<int>的迭代器，
    auto it11 = v.begin();
    //it2是const vector<int>的迭代器
    auto it12 = cv.begin();

    //迭代器失效
    //曾经介绍过，虽然vector对象可以动态地增长，但是也会有一些副作用。已知的一个限制是不能在范围for循环中向vector对象添加元素。
    //另外一个限制是任何一种可能改变vector对象容量的操作，比如push_back，都会使该vector对象的迭代器失效。

    //注意下面逻辑错误，在for循环中push元素导致死循环
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    for (auto i = 0; i < numbers.size(); ++i) {
        //numbers.push_back(i);
    }

    //注意下面逻辑错误，在for循环中push元素导致迭代器失效,也会导致死循环
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        //numbers.push_back(1);
    }

    std::vector<int> numbers2 = {1, 2, 3, 4, 5};
    //循环遍历,并删除其中奇数
    for (auto it = numbers2.begin(); it != numbers2.end();) {
        // 删除奇数
        if (*it % 2 != 0) {
            it = numbers2.erase(it); //返回删除元素后面一个元素
            continue;
        }
        ++it;
    }
    for (auto num: numbers2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    //迭代器的算术运算
    //可以令迭代器和一个整数值相加（或相减），其返回值是向前（或向后）移动了若干个位置的迭代器。
    vector<int> numbers3 = {1, 2, 3, 4, 5};
    auto mid = numbers3.begin() + numbers3.size() / 2;
    if (mid != numbers3.end()) {
        cout << *mid << endl;
    }

    //相邻元素的和
    vector<int> input;
    int number;
    cout << "请输入一组整数：" << endl;
    while (cin >> number && number != -1) {
        input.push_back(number);
    }
    for (auto it = input.begin(); it + 1 != input.end(); it++) {
        cout << (*it + *(it + 1)) << endl;
    }

    //反向打印
    input.clear();
    cout << "请输入一组整数：" << endl;
    while (cin >> number && number != -1) {
        input.push_back(number);
    }
    for (auto it = input.rbegin(); it != input.rend(); it++) {
        cout << *it << endl;
    }

    //合并两个 vector
    vector<int> vint1;
    vector<int> vint2;
    vector<int> mint;
    cout << "请输入一组整数：" << endl;
    while (cin >> number && number != -1) {
        vint1.push_back(number);
    }

    cout << "请输入一组整数：" << endl;
    while (cin >> number && number != -1) {
        vint2.push_back(number);
    }

    mint.insert(mint.end(), vint1.begin(), vint1.end());
    mint.insert(mint.end(), vint2.begin(), vint2.end());

    for (auto num: mint) {
        cout << num << " ";
    }

    return 0;
}
