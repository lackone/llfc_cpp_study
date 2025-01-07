#include <iostream>
#include <vector>
#include "student.h"
using namespace std;

int main() {
    vector<Student> students;
    int input;
    do {
        cout << "学生信息管理" << endl;
        cout << "1:添加学生" << endl;
        cout << "2:显示所有学生" << endl;
        cout << "3:根据ID查找" << endl;
        cout << "4:根据ID删除" << endl;
        cout << "5:退出" << endl;
        cin >> input;

        switch (input) {
            case 1: {
                int id;
                std::string name;
                float score;
                cout << "输入ID:" << endl;
                cin >> id;
                cout << "输入Name:" << endl;
                cin >> name;
                cout << "输入Score:" << endl;
                cin >> score;
                add_student(&students, id, name, score);
            }
            break;
            case 2:
                print_student(&students);
                break;
            case 3: {
                int id;
                cout << "输入要查找ID:" << endl;
                cin >> id;
                auto stu = find_student(&students, id);
                stu.printInfo();
            }
            break;
            case 4: {
                int id;
                cout << "输入要删除ID:" << endl;
                cin >> id;
                delete_student(&students, id);
            }
            break;
            case 5:
                cout << "byte" << endl;
                break;
        }
    } while (input != 5);

    return 0;
}
