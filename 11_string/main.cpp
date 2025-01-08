#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>

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

    //字符串流（stringstream）
    //std::stringstream 是 C++ 标准库中第 <sstream> 头文件提供的一个类，用于在内存中进行字符串的读写操作，类似于文件流。
    stringstream ss;
    ss << "aa" << "bb" << "cc";
    cout << ss.str() << endl;

    //从字符串流中读取数据：
    string data = "123 45 678 test";
    stringstream ss4(data);
    int aa, bb, cc;
    string te;
    ss4 >> aa >> bb >> cc >> te;
    cout << aa << bb << cc << te << endl;

    //将其他类型转换为 std::string：
    //使用 std::to_string()：
    cout << to_string(123) << endl;
    cout << to_string(3.1415) << endl;
    //将 std::string 转换为其他类型：
    //使用字符串流：
    string num1 = "123";
    stringstream ss5(num1);
    int num2;
    ss5 >> num2;
    cout << num2 << endl;

    //使用 std::stoi(), std::stod() 等函数（C++11 及以上）：
    cout << stoi("123") << endl;
    cout << stod("3.1415") << endl;

    //正则表达式与字符串匹配
    std::string txt = "The quick brown fox jumps over the lazy dog.";
    //使用原始字符串字面值（R"()"）以简化正则表达式的编写。
    std::regex pattern(R"(\b\w{5}\b)"); // 匹配所有5个字母的单词

    std::sregex_iterator it(txt.begin(), txt.end(), pattern);
    std::sregex_iterator end;

    std::cout << "5个字母的单词有:" << std::endl;
    while (it != end) {
        std::cout << (*it).str() << std::endl;
        ++it;
    }

    //从 C 风格字符串转换为 std::string
    //通过 std::string 的构造函数，可以轻松将 C 风格字符串转换为 std::string。
    const char *cstr = "hello,world";
    string cstr2(cstr);
    cout << cstr2 << endl;

    //从 std::string 转换为 C 风格字符串
    //使用 c_str() 成员函数，可以获取 C 风格字符串指针。
    string str6 = "hello,world";
    const char *cstr6 = str6.c_str();
    cout << cstr6 << endl;

    return 0;
}
