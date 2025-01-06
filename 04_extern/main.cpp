#include <iostream>
#include "global.h"

//只要是包含global.h的文件都会展开global.h，main.cpp展开了一次，global.cpp展开了一次

using namespace std;

int main() {

    cout << g_int_var << endl;
    cout << g_string_var << endl;

    return 0;
}
