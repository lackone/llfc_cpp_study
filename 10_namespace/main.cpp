#include <iostream>

//使用using声明（using declaration），有了using声明就无须专门的前缀（形如命名空间::）也能使用所需的名字了。using声明具有如下的形式：
using std::cin;
using std::cout;
using std::endl;

//using namespace std;

//头文件不应包含using声明
//位于头文件的代码一般来说不应该使用using声明。 这是因为头文件的内容会拷贝到所有引用它的文件中去，如果头文件里有某个using声明，那么每个使用了该头文件的文件就都会有这个声明。
//对于某些程序来说，由于不经意间包含了一些名字，反而可能产生始料未及的名字冲突。

int main() {
    int i;
    cin >> i;

    cout << i << endl;

    return 0;
}
