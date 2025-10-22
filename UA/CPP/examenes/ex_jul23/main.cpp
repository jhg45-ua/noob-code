//
// Created by Julián Hinojosa Gil on 2/6/24.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

// Representación de un trabajador
struct Employee
{
    char dni[10];
    char name[100];
    unsigned int bruteSalary;
    unsigned int startedYear;
};
/* Función: carga los empleados encontrados en un archivo binario
 * filename: nombre del archivo
 * vector<Employee> &employees: paso por referencia de un conjunto de empleados
 * */
bool loadEmployee(const char *filename, vector<Employee> &employees)
{
    // Abrimos archivo binario
    ifstream inputFile(filename, ios::binary);
    if(!inputFile.is_open())
    {
        cerr << "Error: Cannot open file!" << endl;
        return false;
    }

    // Creamos un empleado hasta que no queda nada en el archivo y lo metemos al conjunto
    Employee emp;
    while (inputFile.read(reinterpret_cast<char *>(&emp), sizeof(Employee)))
    {
        employees.push_back(emp);
    }

    inputFile.close();
    return true;
}
/* Función: calcula el salario medio dado un conjunto de empleados
 * */
double calculateAverageSalary(vector<Employee> &employees)
{
    // Recorremos el vector donde en cada iteración vamos sumando el total de salarios
    double totalSalary = 0;
    for (int i = 0; i < employees.size(); i++)
    {
        totalSalary += employees[i].bruteSalary;
    }

    return totalSalary / employees.size();
}

/* Función: creamos un archivo donde vamos metiendo a los empleados que cumplen
 * las condiciones para teletrabajar
 *
 * */
void writeAptEmployee(const char *filename, const vector<Employee> &employees, double averageSalary)
{
    // Creamos el archivo con el nombre filename de forma normal (no binaria)
    ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        cerr << "Error: Cannot open file!" << endl;
    }

    // Inicializamos un ID para ordenar a los empleados
    int id = 1;
    for (int i = 0; i < employees.size(); i++)
    {
        // Tiene que cumplir estar más de 3 años desde 2023 y tener un salario bruto mayor al medio
        if (2023 - employees[i].startedYear > 3 && employees[i].bruteSalary >= averageSalary)
        {
            outputFile << id << "-" << employees[i].dni << endl;
            id++;
        }
    }
    outputFile.close();
}

int main(int argc, char *argv[])
{
    const char *inputFilename = nullptr;
    double averageSalary = -1;

    // Recorremos argumentos
    for (int i = 1; i < argc; i++)
    {
        // Vemos si coincide
        if (strcmp(argv[i], "-b") == 0)
        {
            // Vemos si tiene algo después
            if (i + 1 < argc)
            {
                inputFilename = argv[i + 1];
                i++;
            }
            else
            {
                cerr << "Error: wrong arguments!" << endl;
                return 1;
            }
        }

        // Lo mismo con el siguiente
        else if (strcmp(argv[i], "-s") == 0)
        {
            if (i + 1 < argc)
            {
                averageSalary = atof(argv[i + 1]);
                if (averageSalary < 10000 || averageSalary > 100000)
                {
                    cerr << "Error: wrong arguments" << endl;
                    return 1;
                }
                i++;
            }
            else
            {
                cerr << "Error: wrong arguments" << endl;
                return 1;
            }
        }

        else
        {
            cerr << "Error: wrong arguments" << endl;
            return 1;
        }
    }

    if (inputFilename == nullptr)
    {
        cerr << "Error: wrong arguments" << endl;
        return 1;
    }

    const char *outputFilename = "aptos.txt";

    vector<Employee> employees;
    if (!loadEmployee(inputFilename, employees))
        return 1;

    if (employees.empty())
    {
        ofstream outfile(outputFilename);
        if(!outfile.is_open())
        {
            cerr << "Error: cannot open file!" << endl;
            return 1;
        }
        outfile.close();
        return 0;
    }

    if (averageSalary == -1)
        averageSalary = calculateAverageSalary(employees);

    writeAptEmployee(outputFilename, employees, averageSalary);

    return 0;
}