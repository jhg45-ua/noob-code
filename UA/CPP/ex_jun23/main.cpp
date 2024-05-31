#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Task
{
    unsigned int id;
    string hour, min, desc;
};

struct Database
{
    unsigned int nextId = 0;
    vector<Task> tasks;
};

void showMenu()
{
    cout << "-----------" << endl
         << "  Options" << endl
         << "-----------" << endl
         << "1. Add task" << endl
         << "2. Delete task" << endl
         << "q. Quit" << endl
         << "Option: ";
}

void addTask(Database &data)
{
    string strInput, time, desc;
    cout << "Insert task: ";
    getline(cin, strInput);

    // Separar la hora de la descripción
    size_t pos = strInput.find(',');
    time = strInput.substr(0, pos);
    desc = strInput.substr(pos + 1);

    // Separar la hora y los minutos
    size_t colonPos = time.find(':');
    string hour = time.substr(0, colonPos);
    string min = time.substr(colonPos + 1);

    // Crear la nueva tarea
    Task newTask = {data.nextId, hour, min, desc};
    data.nextId++;
    data.tasks.push_back(newTask);



    cout << "Tarea añadida: " << hour << ":" << min << "," << desc << endl;
}

void deleteTasks(Database &data)
{
    string strTaskId;
    uint taskId, pos = 0;

    for (int i = 0; i < data.tasks.size(); i++)
    {
        cout << data.tasks[i].id << ". "
             << data.tasks[i].hour << ":" << data.tasks[i].min
             << " " << data.tasks[i].desc << endl;
    }

    cout << "Insert number: ";
    getline(cin , strTaskId);
    taskId = stoi(strTaskId);

    for (int i = 0; i < data.tasks.size(); i++)
        if (data.tasks[i].id == taskId)
            pos = i;


    data.tasks.erase(data.tasks.begin() + pos);
}

int main(int argc, char *argv[])
{

    Database data;
    data.nextId = 1;
    char option;

    do
    {
        showMenu();
        cin >> option;
        cin.get();

        switch (option)
        {
        case '1':
            addTask(data);
            break;
        case '2':
            deleteTasks(data);
            break;
        case 'q':
            break;

        default:
            cout << "Error: wrong option" << endl;
        }
    } while (option != 'q');
    return 0;
}

