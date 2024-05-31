//
// Created by Julián Hinojosa Gil on 30/5/24.
//

#include "../include/student.h"

Student::Student(string name, uint group)
{
    if (name.empty())
        throw invalid_argument(name);

    this->name = name;
    this->mark = 0;
    setGroup(group);
}


void Student::setGroup(uint group)
{
    this->group = group;
}

void Student::setMark(float mark)
{
    this->mark = mark;
}

ostream &operator<<(ostream &os, const Student& stu)
{
    os << stu.getName() << " (" << stu.getGroup() << "): " << stu.getMark();
    return os;
}