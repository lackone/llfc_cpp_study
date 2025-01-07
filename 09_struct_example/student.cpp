#include "student.h"

//添加学生
bool add_student(std::vector<Student> *stus, int id, std::string name, float score) {
  Student s;
  s.id = id;
  s.name = name;
  s.score = score;
  stus->push_back(s);
  return true;
}

//显示所有学生
void print_student(std::vector<Student> *stus) {
  for (auto iter = stus->begin(); iter != stus->end(); iter++) {
    std::cout << "id: " << iter->id << " name: " << iter->name << " score: " << iter->score << std::endl;
  }
}

//查找所有学生
Student find_student(std::vector<Student> *stus, int id) {
  for (auto iter = stus->begin(); iter != stus->end(); iter++) {
    if (iter->id == id) {
      return *iter;
    }
  }
  return Student();
}

//删除学生
bool delete_student(std::vector<Student> *stus, int id) {
  for (auto iter = stus->begin(); iter != stus->end(); iter++) {
    if (iter->id == id) {
      stus->erase(iter);
      break;
    }
  }
  return true;
}