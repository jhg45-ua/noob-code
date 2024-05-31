//
// Created by Julián Hinojosa Gil on 30/5/24.
//

#ifndef EX_JUN23_STUDENT_H
#define EX_JUN23_STUDENT_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

class Student
{
    friend ostream &operator<<(ostream &os, const Student& stu);

  private:
    string name;
    uint group{};
    float mark;

  public:
    Student(string name, uint group);
    string getName() const { return name;}
    uint getGroup() const { return group; }
    float getMark() const { return mark; }

    void setGroup(uint group);
    void setMark(float mark);
};

#endif // EX_JUN23_STUDENT_H
