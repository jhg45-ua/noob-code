//
// Created by Julián Hinojosa Gil on 30/5/24.
//

#ifndef EX_JUN23_SUBJECT_H
#define EX_JUN23_SUBJECT_H

#include "student.h"

class Subject
{
    friend ostream &operator<<(ostream &os, const Subject &subj);


  private:
    static const char SEPARATOR = ';';
    uint nextGroup;
    string name;
    vector<Student> students;


    void addStudent(string name, uint group);
    vector<Student*>filterByGroup(uint group);
  public:
    Subject(string name = "Programing 2");
    void addGroup(string group);
    void setGroupMark(uint group, float mark);

    uint getGroup() const { return nextGroup; }
};

#endif // EX_JUN23_SUBJECT_H