#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>

typedef struct _Student {
    int id;
    std::string name;
    float score;

    void printInfo() {
        std::cout << "id: " << id << " name: " << name << " score: " << score << std::endl;
    }
} Student, *PStudent;

//添加学生
bool add_student(std::vector<Student> *stus, int id, std::string name, float score);

//显示所有学生
void print_student(std::vector<Student> *stus);

//查找所有学生
Student find_student(std::vector<Student> *stus, int id);

//删除学生
bool delete_student(std::vector<Student> *stus, int id);

#endif //STUDENT_H
