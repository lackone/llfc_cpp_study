#include <iostream>

using namespace std;

//当一个数组的元素仍然是数组时，通常使用两个维度来定义它：一个维度表示数组本身大小，另外一个维度表示其元素（也是数组）大小：

void array_sum() {
    int arr1[2][3] = {0};
    int arr2[2][3] = {0};

    cout << "请输入第一个2x3矩阵的元素（共6个整数）:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> arr1[i][j];
        }
    }
    cout << "请输入第二个2x3矩阵的元素（共6个整数）:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> arr2[i][j];
        }
    }
    cout << "两个矩阵的和为:" << endl;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr1[i][j] + arr2[i][j] << " ";
        }
        cout << endl;
    }
}

void array_tran() {
    cout << "请输入一个3x3矩阵的元素（共9个整数）:" << endl;

    int arr[3][3] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> arr[i][j];
        }
    }

    int tran[3][3] = {0};
    cout << "矩阵的转置为:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tran[j][i] = arr[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << tran[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // 大小为3的数组，每个元素是大小为4的数组
    int ia[3][4];

    //三个元素，每个元素是大小为4的数组
    int ia2[3][4] = {
        //第一行的初始值
        {0, 1, 2, 3},
        //第二行初始值
        {4, 5, 6, 7},
        //第三行初始值
        {8, 9, 10, 11}
    };

    //其中内层嵌套着的花括号并非必需的
    int ia3[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    //类似于一维数组，在初始化多维数组时也并非所有元素的值都必须包含在初始化列表之内。
    //初始化每一行的首元素
    int ia4[3][4] = {{0}, {4}, {8}};

    int ia5[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int arr[1][1][1] = {{{1}}};
    // 用arr的首元素为ia的最后一个元素赋值
    ia5[2][3] = arr[0][0][0];
    //row是一个4维数组的引用,将row绑定到ia的第二个元素(4维数组)上
    int (&row)[4] = ia5[1];

    //我们可以使用for循环构建数组
    constexpr int rowNum = 3, colNum = 4;
    int ia6[rowNum][colNum];

    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < colNum; j++) {
            ia6[i][j] = i * rowNum + j;
        }
    }

    for (auto &row: ia6) {
        for (auto &col: row) {
            cout << col << " ";
        }
        cout << endl;
    }

    //指针和多维数组
    //大小为3的数组，每个元素是含有4个整数的数组
    int ia7[3][4];
    //p指向含有4个整数的数组
    int (*p)[4] = ia7;
    //将p修改为指向ia数组的尾部
    p = &ia7[2];

    int ia8[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    //随着C++11新标准的提出，通过使用auto或者decltype就能尽可能地避免在数组前面加上一个指针类型了：
    //输出ia中每个元素的值,每个内存数组各占一行
    //p指向含有4个整数的数组
    for (auto p = ia8; p != ia8 + 3; ++p) {
        //q指向4个整数的数组的首元素
        for (auto q = *p; q != *p + 4; ++q) {
            std::cout << *q << ' ';
        }
        std::cout << std::endl;
    }

    //使用C++11提供的std::begin也能实现类似的功能
    // p指向ia的第一个数组
    for (auto p = std::begin(ia8); p != std::end(ia8); ++p) {
        // q指向内存数组的首元素
        for (auto q = std::begin(*p); q != std::end(*p); ++q) {
            // 输出q所指的整数值
            std::cout << *q << ' ';
        }
        std::cout << std::endl;
    }

    //可以使用using 进行类型别名的声明，或者使用typedef声明类型的别名
    // 新标准下类型别名的声明
    using int_array = int[4];
    // 使用typedef 声明类型的别名
    typedef int int_array_t[4];

    for (int_array *p = ia8; p != ia8 + 3; ++p) {
        for (int *q = *p; q != *p + 4; ++q) {
            std::cout << *q << " ";
        }
        std::cout << std::endl;
    }

    array_sum();

    array_tran();

    return 0;
}
