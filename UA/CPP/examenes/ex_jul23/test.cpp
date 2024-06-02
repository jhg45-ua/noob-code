#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Employee
{
    char dni[10];
    char name[100];
    unsigned int bruteSalary;
    int startedYear;
};

bool loadEmployees(const char *filename, vector<Employee> &employees)
{
    ifstream infile(filename, ios::binary);
    if (!infile)
    {
        cout << "ERROR: cannot open file" << endl;
        return false;
    }

    Employee emp;
    while (infile.read(reinterpret_cast<char *>(&emp), sizeof(Employee)))
    {
        employees.push_back(emp);
    }

    infile.close();
    return true;
}

double calculateAverageSalary(const vector<Employee> &employees)
{
    double totalSalary = 0;
    for (const auto &emp : employees)
    {
        totalSalary += emp.bruteSalary;
    }
    return totalSalary / employees.size();
}

void writeAptEmployees(const char *filename, const vector<Employee> &employees, double averageSalary)
{
    ofstream outfile(filename);
    if (!outfile)
    {
        cout << "ERROR: cannot open file" << endl;
        return;
    }

    int id = 1;
    for (const auto &emp : employees)
    {
        if (2023 - emp.startedYear > 3 && emp.bruteSalary >= averageSalary)
        {
            outfile << id << "-" << emp.dni << endl;
            ++id;
        }
    }

    outfile.close();
}

int main(int argc, char *argv[])
{
    const char *inputFilename = nullptr;
    double averageSalary = -1;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-b") == 0)
        {
            if (i + 1 < argc)
            {
                inputFilename = argv[i + 1];
                i++;
            }
            else
            {
                cout << "ERROR: wrong arguments" << endl;
                return 1;
            }
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            if (i + 1 < argc)
            {
                averageSalary = atof(argv[i + 1]);
                if (averageSalary < 10000 || averageSalary > 100000)
                {
                    cout << "ERROR: wrong arguments" << endl;
                    return 1;
                }
                i++;
            }
            else
            {
                cout << "ERROR: wrong arguments" << endl;
                return 1;
            }
        }
        else
        {
            cout << "ERROR: wrong arguments" << endl;
            return 1;
        }
    }

    if (inputFilename == nullptr)
    {
        cout << "ERROR: wrong arguments" << endl;
        return 1;
    }

    const char *outputFilename = "aptos.txt";

    vector<Employee> employees;
    if (!loadEmployees(inputFilename, employees))
    {
        return 1;
    }

    if (employees.empty())
    {
        ofstream outfile(outputFilename);
        if (!outfile)
        {
            cout << "ERROR: cannot open file" << endl;
            return 1;
        }
        outfile.close();
        return 0;
    }

    if (averageSalary == -1)
    {
        averageSalary = calculateAverageSalary(employees);
    }

    writeAptEmployees(outputFilename, employees, averageSalary);

    return 0;
}