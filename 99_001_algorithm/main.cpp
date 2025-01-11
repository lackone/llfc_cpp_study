#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

//accumulate(累加)
//equal 相等
//fill fill_n 填充
//copy 拷贝
//replace replace_copy 替换
//unique和sort

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};

    //accumulate(累加)
    cout << accumulate(vec.begin(), vec.end(), 0) << endl;

    vector<string> svec = {"aa", "bb", "cc", "dd"};
    //由于string定义了+运算符
    cout << accumulate(svec.begin(), svec.end(), string("")) << endl;

    vector<string> ss1 = {"a", "b", "c", "e"};
    vector<string> ss2 = {"a", "b", "c", "d"};
    //第一个序列中每个元素与第二个序列中的元素都相等
    if (equal(ss1.begin(), ss1.end(), ss2.begin())) {
        cout << "相等" << endl;
    } else {
        cout << "不相等" << endl;
    }

    vector<int> vv = {1, 2, 3, 4, 5};
    //全部填充0
    fill(vv.begin(), vv.end(), 0);
    for (auto num: vv) {
        cout << num << endl;
    }
    //前半部填充99
    fill(vv.begin(), vv.begin() + vv.size() / 2, 99);
    for (auto num: vv) {
        cout << num << endl;
    }
    //fill_n函数，接受一个单迭代器，一个计数值和一个值。
    fill_n(vv.begin(), vv.size(), 88);
    for (auto num: vv) {
        cout << num << endl;
    }

    //back_inserter接受一个指向容器的引用，返回一个与该容器绑定的插入迭代器。
    vector<int> vv2;
    auto iter2 = back_inserter(vv2);
    fill_n(iter2, 10, 666);
    for (auto num: vv2) {
        cout << num << endl;
    }

    //copy
    int arr1[] = {1, 2, 3, 4, 5};
    constexpr int len = sizeof(arr1) / sizeof(int);
    int arr2[len];
    copy(begin(arr1), end(arr1), arr2);
    for (auto num: arr2) {
        cout << num << endl;
    }

    //replace
    vector<int> vv3 = {1, 2, 3, 4, 5};
    replace(vv3.begin(), vv3.end(), 3, 99);
    for (auto num: vv3) {
        cout << num << endl;
    }
    vector<int> vv4 = {1, 2, 3, 4, 5};
    vector<int> copy;
    replace_copy(vv4.begin(), vv4.end(), back_inserter(copy), 3, 99);
    for (auto num: copy) {
        cout << num << endl;
    }
    for (auto num: vv4) {
        cout << num << endl;
    }

    //unique和sort
    vector<string> words = {"good", "idea", "test", "good", "hello"};
    //先将words中的词语排序
    sort(words.begin(), words.end());
    // unique会移动元素，将不重复的元素放在前边，重复的放在后边
    // unique返回不重复的最后一个元素的位置
    auto iter = unique(words.begin(), words.end());
    //调用erase将重复的元素删除
    words.erase(iter, words.end());
    for (auto num: words) {
        cout << num << endl;
    }

    return 0;
}
