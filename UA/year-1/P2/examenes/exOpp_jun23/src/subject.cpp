//
// Created by Julián Hinojosa Gil on 30/5/24.
//

#include "../include/subject.h"

Subject::Subject(string subjName)
{
    this->name = subjName;
    this->nextGroup = 1;
}

void Subject::addStudent(string stuName, uint group)
{
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].getName() == stuName)
            students[i].setGroup(group);
    }
    Student newStudent(stuName, group);
    students.push_back(newStudent);
}

void Subject::addGroup(string group)
{
    if (group.empty())
    {
        cout << "Error: empty group" << endl;
        return;
    }

    stringstream ss(group);
    string stuName;
    bool groupCreated = false;

    while (getline(ss, stuName, SEPARATOR))
    {
        try
        {
            if (name.empty()) {
                throw invalid_argument(name);
            }


            bool stuExists = false;
            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].getName() == stuName)
                {
                    students[i].setGroup(nextGroup);
                    stuExists = true;
                    groupCreated = true;
                    break;
                }
            }

            if (!stuExists)
            {
                addStudent(stuName, nextGroup);
                groupCreated = true;
            }
        }
        catch (const invalid_argument &e)
        {
            cout << "Error: wrong student" << endl;
            continue;
        }
    }

    if (groupCreated)
        ++nextGroup;
}

vector<Student*> Subject::filterByGroup(uint group)
{
    vector<Student*> filteredStudents;
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].getGroup() == group)
            filteredStudents.push_back(&students[i]); // Agrega punteros a un vector de PUNTEROS
    }
    return filteredStudents;
}

void Subject::setGroupMark(uint group, float mark)
{
    vector<Student*> filteredStudents = filterByGroup(group);

    if(filteredStudents.empty())
        return;

    for (int i = 0; i < filteredStudents.size(); i++)
        filteredStudents[i]->setMark(mark);
}

ostream &operator<<(ostream &os, const Subject &subj)
{
    // Mostrar la lista de estudiantes
    for (const Student &student : subj.students)
    {
        os << student << endl;
    }

    float totalMark = 0.0;
    for (int i = 0; i < subj.students.size(); i++)
    {
        totalMark += subj.students[i].getMark();
    }
    float avg = totalMark / subj.students.size();
    os << "Average: " << avg << endl;

    return os;
}