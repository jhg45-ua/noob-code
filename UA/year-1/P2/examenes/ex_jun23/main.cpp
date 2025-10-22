#include <cstring>
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
    unsigned int nextId;
    vector<Task> tasks;
};

void showMenu()
{
    cout << "-----------" << endl
         << "  Options" << endl
         << "-----------" << endl
         << "1. Add task" << endl
         << "2. Delete task" << endl
         << "3. Read file (Debug)" << endl
         << "q. Quit" << endl
         << "Option: ";
}

void reorderId(Database &data)
{
    // Reasignar los ID para asegurar que sean secuenciales
    for (int i = 0; i < data.tasks.size(); i++)
    {
        data.tasks[i].id = i + 1;
    }
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
    Task newTask = {data.nextId++, hour, min, desc};
    data.tasks.push_back(newTask);

    reorderId(data);

    //cout << "Tarea añadida: " << hour << ":" << min << "," << desc << endl; // Debug
}

void deleteTasks(Database &data)
{
    string strTaskId;
    uint taskId;

    for (int i = 0; i < data.tasks.size(); i++)
    {
        cout << data.tasks[i].id << ". "
             << data.tasks[i].hour << ":" << data.tasks[i].min
             << " " << data.tasks[i].desc << endl;
    }

    cout << "Insert number: ";
    getline(cin , strTaskId);
    taskId = stoi(strTaskId);

    if (taskId > 0 && taskId <= data.tasks.size())
    {
        data.tasks.erase(data.tasks.begin() + (taskId - 1));

        for (int i = 0; i < data.tasks.size(); i++)
            data.tasks[i].id = i + 1;

        data.nextId = data.tasks.size() + 1; // Ajustar el nextId
    } else
    {
        cout << "Error: wrong number" << endl;
    }
}

void fileHandle(string fileName, Database &data, const char *mode)
{
    fstream fichero;

    if (fileName.empty())
        fileName = "tasks.bin";

    if (strcmp(mode, "save") == 0)
    {
        fichero.open(fileName, ios::out | ios::binary);

        if (!fichero.is_open())
        {
            cout << "Error: cannot write file" << endl;
        }

        for (int i = 0; i < data.tasks.size(); i++)
        {
            // Pasamos las horas y minutos a enteros
            int hour = stoi(data.tasks[i].hour);
            int minutes = stoi(data.tasks[i].min);
            // Los escribimos de la forma común
            fichero.write(reinterpret_cast<const char*>(&hour), sizeof(hour));
            fichero.write(reinterpret_cast<const char*>(&minutes), sizeof(minutes));
            // Desc al ser string simplemente lo pasamos a una string de c, con su tamaño + 1 para el carácter final
            fichero.write(data.tasks[i].desc.c_str(), 101);
        }
    }
    else if (strcmp(mode, "read") == 0)
    {
        fichero.open(fileName, ios::in | ios::binary);

        if (!fichero.is_open())
        {
            cout << "Error: cannot read file" << endl;
            return;
        }

        int hour, min;
        char desc[101];

        // Mientras vaya leyendo la hora
        while (fichero.read(reinterpret_cast<char *>(&hour), sizeof(hour)))
        {
            // Lee los minutos y la descripción
            fichero.read(reinterpret_cast<char *>(&min), sizeof(min));
            fichero.read(desc, 101);
            desc[100] = '\0'; // Asegurarse de que la descripción esté terminada en nulo

            // Lo añade a la estructura en su tipo de dato correcto
            Task task = {data.nextId++, to_string(hour), to_string(min), string(desc)};
            data.tasks.push_back(task);

            cout << hour << ":" << min << " " << desc << endl;
        }
        fichero.close();

        reorderId(data);
    }
}


int main(int argc, char *argv[])
{

    Database data;
    data.nextId = 1;
    string fileName;
    char option;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-f") == 0)
        {
            if (i + 1 < argc)
            {
                string argName = argv[i + 1];
                fileHandle(argName, data, "save");
                i++;
            }
        }
        else if (strcmp(argv[i], "-a") == 0)
        {
            addTask(data);
        }
    }

    // Menu en bucle infinito hasta que se elige opción para salir
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
        case '3': // debug
            fileHandle("", data, "read");
            break;
        case 'q':
            fileHandle("", data, "save");
            break;
        default:
            cout << "Error: wrong option" << endl;
        }
    } while (option != 'q');
    return 0;
}
