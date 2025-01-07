#include <algorithm>
#include <iostream>
#include <string>
#include <bits/ranges_algo.h>
using namespace std;

//在 C++ 中，有两种主要的字符串类型：
//C 风格字符串（C-strings）：基于字符数组，以空字符 ('\0')结尾。
//C++ std::string 类：更高级、 功能更丰富的字符串类，封装了字符串操作的复杂性。

int main() {
    char str[] = "hello,world";
    string s = "hello,world";

    //定义与初始化
    string str1; //默认构造
    string str2 = "test"; //字面值
    string str3(str2); //拷贝构造
    string str4(str2, 0, 2); //部分初始化
    string str5(6, 'A'); //重复字符初始化

    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;
    cout << str4 << endl;
    cout << str5 << endl;

    //字符串输入与输出
    cout << "hello" << endl;
    string istr;
    cin >> istr;
    cout << istr << endl;

    //读取整行
    string line;
    getline(cin, line);
    cout << line << endl;

    //拼接与连接
    string ss1 = "aa";
    string ss2 = "bb";
    //使用 + 运算符：
    string ss3 = ss1 + ss2;
    //使用 append() 函数：
    ss3.append("cc");
    //使用 += 运算符：
    ss3 += "dd";
    cout << ss3 << endl;

    //比较字符串
    //关于字符串的比较，其实是逐个位置按照字符比较，计算机中字符存储的方式是ASCII码表，每个字符对应一个ASCII码值，比较字符就是比较ASCII码值的大小
    string a = "apple";
    string b = "banana";

    if (a < b) {
        std::cout << "a 在字典序中小于 b" << std::endl;
    } else {
        std::cout << "a 在字典序中不小于 b" << std::endl;
    }

    //使用 find() 查找子字符串：
    string text = "i am china";
    size_t pos = text.find("am");
    if (pos != string::npos) {
        cout << "找到：" << pos << endl;
        string tmp = "have";
        //替换子字符串：
        text.replace(pos, 2, tmp);
        cout << text << endl;
    }

    //子字符串与切片
    cout << text.substr(0, 4) << endl;

    //长度与容量
    string tt = "i am 中国";
    cout << tt.length() << endl;
    cout << tt.size() << endl;

    //获取字符串容量：
    //每个 std::string 对象都有一个容量（capacity），表示它当前能够持有的最大字符数，而不需要重新分配内存。
    string tt2 = "hello";
    cout << tt2.capacity() << endl;
    tt2 += ",world";
    cout << tt2.capacity() << endl;

    //使用索引访问单个字符：
    for (size_t i = 0; i < tt.length(); i++) {
        cout << tt[i] << endl;
    }

    //使用 at() 函数（包含边界检查）：
    cout << tt.at(3) << endl;

    //C++ 标准库中的 std::toupper 和 std::tolower 可以用于转换字符的大小写。结合 std::transform，可以实现整个字符串的大小写转换。
    string tt3 = "abcd";
    transform(tt3.begin(), tt3.end(), tt3.begin(), [](unsigned char c) {
        return toupper(c);
    });
    cout << tt3 << endl;

    string tt4 = "ABCD";
    transform(tt4.begin(), tt4.end(), tt4.begin(), [](unsigned char c) {
        return tolower(c);
    });
    cout << tt4 << endl;

    //empty()：检查字符串是否为空。
    if (string("").empty()) {
        cout << "empty" << endl;
    }

    //clear()：清空字符串内容。
    string tt5 = "test";
    tt5.clear();
    cout << tt5 << endl;

    //erase()：删除字符串的部分内容。
    string tt6 = "hello";
    tt6.erase(2, 2);
    cout << tt6 << endl;

    //insert()：在指定位置插入字符串或字符。
    string tt7 = "hello";
    tt7.insert(3, "aa");
    cout << tt7 << endl;

    //replace()：替换字符串的部分内容（前面已示例）。

    //find_first_of(), find_last_of()：查找字符集合中的任何一个字符。
    cout << tt7.find_first_of("e") << endl;
    cout << tt7.find_last_of("l") << endl;

    return 0;
}
