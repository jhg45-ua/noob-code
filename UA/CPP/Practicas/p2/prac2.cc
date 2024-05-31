// Programación 2 - Práctica 2
// DNI: 48795869N
// Nombre: Julián Hinojosa Gil

#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int KMAXNAME = 50;
const int KMAXPASSWORD = 5;

/* #region Estructuras {{{ */

// Registro para las preguntas
struct Question
{
    unsigned int id;
    unsigned int unit;
    string question;
    string answer;
};

// Registro para los profesores
struct Teacher
{
    char name[KMAXNAME];
    char password[KMAXPASSWORD];
    unsigned int answered;
};

// Registro para la base de datos
struct Database
{
    unsigned int nextId;
    vector<Question> questions;
    vector<Teacher> teachers;
};

// Tipos de errores posibles
enum Error
{
    ERR_OPTION,
    ERR_EMPTY,
    ERR_UNIT,
    ERR_CHAR,
    ERR_FILE,
    ERR_NAME,
    ERR_DUPLICATED,
    ERR_PASSWORD,
    ERR_NO_QUESTIONS,
    ERR_ID,
    ERR_ARGS
};

/* #endregion }}} */

/* #region Funciones {{{*/

/*
    Función que muestra los mensajes de error
    -e: tipo de error a mostrar
    -return: nada
*/
void error(Error e)
{
    switch (e)
    {
    case ERR_OPTION:
        cout << "ERROR: wrong option" << endl;
        break;
    case ERR_EMPTY:
        cout << "ERROR: empty string" << endl;
        break;
    case ERR_UNIT:
        cout << "ERROR: wrong unit" << endl;
        break;
    case ERR_CHAR:
        cout << "ERROR: wrong char" << endl;
        break;
    case ERR_FILE:
        cout << "ERROR: cannot open file" << endl;
        break;
    case ERR_NAME:
        cout << "ERROR: wrong teacher name" << endl;
        break;
    case ERR_DUPLICATED:
        cout << "ERROR: duplicated name" << endl;
        break;
    case ERR_PASSWORD:
        cout << "ERROR: wrong password" << endl;
        break;
    case ERR_NO_QUESTIONS:
        cout << "ERROR: no pending questions" << endl;
        break;
    case ERR_ID:
        cout << "ERROR: wrong id" << endl;
        break;
    case ERR_ARGS:
        cout << "ERROR: wrong arguments" << endl;
    }
}

/*
    -Función que muestra el menú de opciones
    -return: nada
*/
void showMenu()
{
    cout << "1- Add question" << endl        // DONE
         << "2- Batch add questions" << endl // WIP --> BUG
         << "3- Delete question" << endl     // DONE
         << "4- Add teacher" << endl         // DONE
         << "5- Add answers" << endl         // DONE
         << "6- View answers" << endl        // DONE
         << "7- View statistics" << endl     // DONE
         << "8- Export questions" << endl    // DONE
         << "q- Quit" << endl
         << "Option: ";
}

/*
    Función: gestiona la solicitud del año académico
    -reqTmp: plantilla de solicitud
    -strReq: dato para almacenar
    -convertToInt: si verdadero, convierte a entero (stoi)
    -numReq: dato solicitado en numero entero
    -checkSize: si verdadero, salta error ERR_EMPTY
    -return: devuelve el entero en caso de convertToInt=true si no devuelve strReq
*/
void manageInput(const string &reqTmp, string &strReq, bool convertToInt, int &numReq, bool checkSize)
{
    // Imprimir la solicitud de entrada y obtener la entrada del usuario
    cout << reqTmp;
    getline(cin, strReq);

    if (checkSize && strReq.empty())
    {
        error(ERR_EMPTY);
        return;
    }

    // convertToInt=true
    if (convertToInt)
    {
        try
        {
            numReq = stoi(strReq); // Convertir strReq a entero
        }
        catch (const invalid_argument &)
        {
            return;
        }
    }
}

/*
    Función busca un ID específico en la estructura questions
    -data: Estructura de tipo Database que representa una base de datos
    -encontrado: "flag" para manejar lógica en bucles
    -pos: posición en Database del ID en cuestión
    -return: devuelve por referencia la posición de ese ID
*/
bool searchId(Database &data, int numId, int &pos)
{
    for (size_t i = 0; i < data.questions.size(); i++)
    {
        if (data.questions[i].id == (unsigned)numId)
        {
            pos = (int)i;
            return true;
        }
    }
    error(ERR_ID);
    return false;
}

/*
    Función Busca un nombre en el vector teachers
    -strName: nombre a buscar
    -pos: posición del nombre en el vector
    -encontrado: "flag" para manejar lógica en bucles
    -return: nada
*/
bool searchName(const Database &data, const string &strName, int &pos)
{
    for (size_t i = 0; i < data.teachers.size(); i++)
    {
        if (data.teachers[i].name == strName)
        {
            pos = (int)i;
            return true;
        }
    }
    return false;
}

/*
    Función: encripta la contraseña según las condiciones del enunciado
    -password: contraseña a encriptar
    -encryptedPass: contraseña encriptada
    -return: por referencia la contraseña encriptada
*/
string handlePass(string &password, const char *mode)
{
    const char *codeTable = "TRWAGMYFPD";

    if (password.length() != 4 && strcmp(mode, "save") == 0)
    {
        error(ERR_PASSWORD);
        return "";
    }

    for (size_t i = 0; i < password.length(); i++)
    {
        if (!isdigit(password[i]) && strcmp(mode, "save") == 0)
        {
            error(ERR_PASSWORD);
            return "";
        }
    }

    string encryptedPass;
    for (size_t i = 0; i < password.length(); i++)
    {
        int base = password[i] - '0';
        encryptedPass += codeTable[base];
    }

    return encryptedPass;
}

/*
    Funcion: añade pregunta de x unidad
    -data: Estructura de tipo Database que representa una base de datos
    -return: nada
*/
void addQuestion(Database &data)
{
    string strUnit, strQn;
    int unit;

    do
    {
        manageInput("Enter unit: ", strUnit, true, unit, true);
        if (strUnit.empty())
        {
            unit = 0;
            return;
        }

        if (unit < 1 || unit > 5)
            error(ERR_UNIT);
    } while (unit < 1 || unit > 5);
    // cout << "Unidad " << unit <<" guardada correctamente" << endl; // debug

    size_t found;
    do
    {
        manageInput("Enter question: ", strQn, false, unit = 0, true);
        if (strQn.empty())
            return;

        char bar = '|';
        found = strQn.find(bar);
        if (found != string::npos)
        {
            // cerr << "Error: elemento | encontrado" << endl; // debug
            error(ERR_CHAR);
        }
    } while (found != string::npos);

    Question qn;
    qn.id = data.nextId;
    qn.unit = stoi(strUnit);
    qn.question = strQn;
    qn.answer = "";

    data.nextId++;
    data.questions.push_back(qn);
    //    cout << "Pregunta guardadada correctamente con el ID " << qn.id << endl; // debug
}

/* BUG: reconoce error en linea 5 que no debería
    Funcion: permite cargar preguntas de un fichero de texto
    -data: Estructura de tipo Database que representa una base de datos
    -return: nada
*/
void batchAddQuestions(Database &data, const string &argFile, const char *mode)
{
    ifstream fichero;
    string strFile, line;

    if (strcmp(mode, "menu") == 0)
    {
        do
        {
            int num;
            manageInput("Enter filename: ", strFile, false, num = 0, true);
            if (strFile.empty())
                return;
            fichero.open(strFile);
            if (!fichero.is_open())
                error(ERR_FILE);
        } while (!fichero.is_open());
    }

    if (strcmp(mode, "args") == 0)
    {
        fichero.open(argFile);

        if (!fichero.is_open())
        {
            error(ERR_FILE);
            exit(1);
        }
    }

    unsigned int numLine = 1, numQuestion = 0, numAddedQuestion = 0, unit;
    while (getline(fichero, line))
    {
        string unitStr, question, answer;

        if (line.empty())
        {
            numLine++;
            continue;
        }
        else
        {
            numQuestion++;

            size_t sepPos1 = line.find('|');
            size_t sepPos2 = line.find('|', sepPos1 + 1);

            if ((sepPos1 == string::npos && sepPos2 == string::npos) || sepPos1 == sepPos2)
            {
                cout << "Error line " << numLine << endl;
                numLine++;
                continue;
            }
            else
            {
                unitStr = line.substr(0, sepPos1);
                question = line.substr(sepPos1 + 1, (sepPos2 - sepPos1) - 1);
                if (sepPos2 == string::npos)
                    answer = "";
                else
                    answer = line.substr(sepPos2 + 1);

                // cout << sepPos2 << endl; // debug
                // cout << line.size() - 1 << endl; // debug
                // cout << "Line " << numLine << endl; // debug

                // bool errorCondition = unitStr.empty() || question.empty() || sepPos2 == line.size() - 1; // debug
                if (unitStr.empty() || question.empty() || sepPos2 == line.size() - 1)
                {
                    cout << "Error line " << numLine << endl;
                    numLine++;
                    continue;
                }
                else
                {
                    unit = stoi(unitStr);
                    if (unit < 1 || unit > 5)
                    {
                        cout << "Error line " << numLine << endl;
                        numLine++;
                        continue;
                    }
                    else
                    {
                        Question qn;
                        qn.id = data.nextId;
                        qn.unit = unit;
                        qn.question = question;
                        qn.answer = answer;

                        data.nextId++;
                        data.questions.push_back(qn);
                        numAddedQuestion++;

                        numLine++;
                    }
                }
            }
        }
    }
    fichero.close();
    cout << "Summary: " << numAddedQuestion << "/" << numQuestion << " questions added" << endl;
}

/*
    Funcion: permite borrar una pregunta dado su identificador
    -data: Estructura de tipo Database que representa una base de datos
    -return: nada
*/
void deleteQuestion(Database &data)
{
    string strId;
    int numId, pos;
    bool encontrado = false;

    do
    {
        manageInput("Enter question id: ", strId, true, numId, true);
        if (strId.empty())
            return;

        pos = -1;
        encontrado = searchId(data, numId, pos);
    } while (!encontrado);

    data.questions.erase(data.questions.begin() + pos);
}

/*
    Función: añade un profesor a la base de datos
    -data: Estructura de tipo Database que representa una base de datos
    -return: nada
*/
void addTeacher(Database &data)
{
    string strName;
    int num, pos = 0;
    bool encontrado;
    bool errName;

    do
    {
        manageInput("Enter teacher name: ", strName, false, num = 0, true);
        if (strName.empty())
            return;

        errName = false;

        for (char c : strName)
        {
            if (!isalpha(c) && c != ' ')
            {
                error(ERR_NAME);
                errName = true;
                break;
            }
        }

        if (!errName)
        {
            size_t esp_inicio = strName.find_first_not_of(' ');
            size_t esp_final = strName.find_last_not_of(' ');
            strName = strName.substr(esp_inicio, esp_final - esp_inicio + 1);

            if (strName.length() < 3 || strName.length() > KMAXNAME - 1)
            {
                error(ERR_NAME);
                errName = true;
            }
        }

        if (!errName)
        {
            encontrado = searchName(data, strName, pos);
            if (encontrado)
                error(ERR_DUPLICATED);
        }

    } while (errName || encontrado);

    // cout << "Name->" << strName << endl; // debug

    string strPass, codedPass;
    do
    {
        manageInput("Enter password: ", strPass, false, num = 0, true);
        if (strPass.empty())
            return;

        codedPass = handlePass(strPass, "save");
        // cout << "Password->" << codedPass << endl; // debug
    } while (strPass.length() != 4);

    Teacher tch = {};
    strcpy(tch.name, strName.c_str());
    strcpy(tch.password, codedPass.c_str());
    data.teachers.push_back(tch);

    // cout << "Datos guardados correctamente" << endl; // debug
}

/*
    Función: responde preguntas de la base de datos o bien que se hayan cargado previamente
    -data: Estructura de tipo Database que representa una base de datos
    -return: nada
*/
void addAnswers(Database &data)
{
    string strName;
    int num, pos;
    bool encontrado;
    // handle name petition
    do
    {
        manageInput("Enter teacher name: ", strName, false, num = 0, true);
        if (strName.empty())
            return;

        encontrado = searchName(data, strName, pos);
        if (!encontrado)
            error(ERR_NAME);
    } while (!encontrado);

    string strPass, codedPass;
    // handle password petition
    do
    {
        codedPass.clear();
        manageInput("Enter password: ", strPass, false, num = 0, true);
        if (strPass.empty())
            return;

        codedPass = handlePass(strPass, "search");
        // cout << "Password->" << codedPass << endl; // debug

        encontrado = (data.teachers[pos].password == codedPass);
        if (!encontrado)
            error(ERR_PASSWORD);
    } while (!encontrado);

    bool exit = false;
    do
    {
        bool noQuestions = true;
        for (size_t i = 0; i < data.questions.size(); i++)
        {
            if (data.questions[i].answer.empty())
            {
                noQuestions = false;
                cout << data.questions[i].id << ". ("
                     << data.questions[i].unit << ") "
                     << data.questions[i].question << endl;
            }
        }

        if (noQuestions)
        {
            error(ERR_NO_QUESTIONS);
            return;
        }

        string strId, strAnswer;
        int numId, posId;
        size_t found;
        do
        {
            manageInput("Enter question id: ", strId, true, numId, true);
            if (strId.empty())
                return;

            if (strId == "b")
            {
                exit = true;
                break;
            }

            posId = -1;

            encontrado = searchId(data, numId, posId);
            if (!encontrado)
                error(ERR_ID);
        } while (!encontrado);

        if (exit)
            return;

        do
        {
            manageInput("Enter answer: ", strAnswer, false, num = 0, true);
            if (strAnswer.empty())
                return;

            found = strAnswer.find('|');
            if (found != string::npos)
                error(ERR_CHAR);
        } while (found != string::npos);

        data.questions[posId].answer = strAnswer;
        data.teachers[pos].answered++;
    } while (true);
}

/*
    Función: Enseña todas las preguntas con respuesta
    -data: Estructura de tipo Database que representa una base de datos
    -return: nada
*/
void viewAnswers(const Database &data)
{
    for (size_t i = 0; i < data.questions.size(); i++)
    {
        if (!(data.questions[i].answer.empty()))
        {
            cout << data.questions[i].id << ". ("
                 << data.questions[i].unit << ") "
                 << data.questions[i].question << ": "
                 << data.questions[i].answer << endl;
        }
    }
}

/*
    Función enseña estadísticas globales de preguntas y respuestas y también de cada profesor
    -data: Estructura de tipo Database que representa una base de datos
    -return: nada
*/
void viewStatistics(const Database &data)
{
    int questionCounter = 0;
    int answersCounter = 0;
    for (size_t i = 0; i < data.questions.size(); i++)
    {
        // Contador total de preguntas
        if (!(data.questions.empty()))
            questionCounter++;

        // Contador de preguntas respondidas
        if (!(data.questions[i].answer.empty()))
            answersCounter++;
    }
    cout << "Total number of questions: " << questionCounter << endl;
    cout << "Number of questions answered: " << answersCounter << endl;

    for (size_t j = 0; j < data.teachers.size(); j++)
    {
        cout << data.teachers[j].name << ": "
             << data.teachers[j].answered << endl;
    }
}

/*
    Función: exporta las preguntas, tengan o no respuesta, siguiendo el formato visto en la funcion 2
    -data: Estructura de tipo Database que representa una base de datos
    -return: nada
*/
void exportQuestions(const Database &data)
{
    fstream fichero;
    string strFile;
    int num;

    do
    {
        manageInput("Enter filename: ", strFile, false, num = 0, true);
        if (strFile.empty())
            return;
        fichero.open(strFile, ios::out | ios::app);
        if (!fichero.is_open())
            error(ERR_FILE);
    } while (!fichero.is_open());

    //fichero << endl;

    for (size_t i = 0; i < data.questions.size(); i++)
    {
        fichero << data.questions[i].unit << "|"
                << data.questions[i].question;
        if (!(data.questions[i].answer.empty()))
        {
            fichero << "|" << data.questions[i].answer;
        }
    }

    //fichero << endl;

    fichero.close();
}

/*
    Función: guarda y carga la lista de profesores
    -data: Estructura de tipo Database que representa una base de datos
    -mode: variable para determinar si cargar("load") o guardar("save") la lista de profesores
    -return: nada
*/
void handleTeachers(Database &data, const char *mode)
{
    if (strcmp(mode, "load") == 0)
    {
        ifstream fichero("teachers.bin", ios::binary);
        if (!fichero.is_open())
        {
            data.teachers.clear();
            // cout << "File teachers.bin doesnt exists or cant be open"  << endl; // debug
            return;
        }

        while (!fichero.eof())
        {
            Teacher tch;
            fichero.read((char *)&tch, sizeof(Teacher));

            if (!fichero.eof())
            {
                // Agregar el profesor leído a la lista de profesores
                data.teachers.push_back(tch);
            }
        }

        fichero.close();
    }
    else if (strcmp(mode, "save") == 0)
    {
        ofstream fichero("teachers.bin", ios::binary);
        if (!fichero.is_open())
        {
            error(ERR_FILE);
            return;
        }

        // Escribir cada profesor en el archivo binario
        for (const auto &teacher : data.teachers)
            fichero.write((const char *)&teacher, sizeof(Teacher));
        
        fichero.close();
    }
}


/* #endregion }}} */

/* #region Funcion principal {{{*/

// Función principal. Tendrás que añadir más código tuyo
int main(int argc, char *argv[])
{
    Database data;
    data.nextId = 1;
    char option;

    handleTeachers(data, "load");

    // Procesar argumentos
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-f") == 0)
        {
            if (i + 1 < argc)
            {
                string argFile = argv[i + 1];
                batchAddQuestions(data, argFile, "args");
                i++;
            }
            else
            {
                error(ERR_ARGS);
                return 1;
            }
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            viewStatistics(data);
            return 0;
        }
        else
        {
            error(ERR_ARGS);
            return 1;
        }
    }

    do
    {
        showMenu();
        cin >> option;
        cin.get();

        switch (option)
        {
        case '1': // Llamar a la función "addQuestion" para añadir una nueva pregunta
            addQuestion(data);
            break;
        case '2': // Llamar a la función "batchAddQuestion" para añadir preguntas desde fichero
            batchAddQuestions(data, "", "menu");
            break;
        case '3': // Llamar a la función "deleteQuestion" para eliminar una pregunta
            deleteQuestion(data);
            break;
        case '4': // Llamar a la función "addTeacher" para añadir un nuevo profesor
            addTeacher(data);
            break;
        case '5': // Llamar a la función "addAnswers" para añadir respuestas a las preguntas
            addAnswers(data);
            break;
        case '6': // Llamar a la función "viewAnswers" para mostrar las preguntas con sus respuestas
            viewAnswers(data);
            break;
        case '7': // Llamar a la función "viewStatistics" para ver las estadísticas de las preguntas
            viewStatistics(data);
            break;
        case '8': // Llamar a la función "exportQuestions" para guardar las preguntas en fichero
            exportQuestions(data);
            break;
        case 'q': // Salir del programa guardando los profesores en fichero
            break;
        default:
            error(ERR_OPTION);
        }
    } while (option != 'q');

    // Save teachers.bin
    handleTeachers(data, "save");

    return 0;
}

/* #endregion }}}*/