// Programación 2 - Práctica 1
// DNI: 48795869N
// Nombre: Julián Hinojosa Gil

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAXSUBJECT = 50;

/* #region Estructuras {{{ */

// Registro para las fechas
struct Date
{
    int day;
    int month;
    int year;
};

// Registro para las frases
struct Phrase
{
    string text;
    Date date;
    int rating;
};

// Registro para los profesores
struct Teacher
{
    string name;
    string nickname;
    char subject[MAXSUBJECT];
    int rating;
    vector<Phrase> listPhrases;
};

// Registros para los años escolares
struct AcademicYear
{
    int id;
    vector<Teacher> listTeachers;
};

// Tipos de errores
enum Error
{
    ERR_OPTION,
    ERR_EMPTY,
    ERR_DUPLICATED,
    ERR_NOT_EXIST,
    ERR_RATING
};

/* #endregion }}} */

/* #region Funciones {{{*/

/*
    Funcion: muestra el menu del programa
    return: nada
*/
void showMenu()
{
    cout << "1- Add academic year" << endl    // DONE
         << "2- Delete academic year" << endl // DONE
         << "3- Add teacher" << endl          // DONE
         << "4- Delete teacher" << endl       // DONE
         << "5- Show teacher" << endl         // DONE
         << "6- Add phrase" << endl           // DONE
         << "7- Summary" << endl              // DONE
         << "q- Quit" << endl
         << "Option: ";
}

/*
    Funcion: imprime un mensaje de error segun el enum e
    e: tipos de errores definidos
    return: nada
*/
void error(Error e)
{
    switch (e)
    {
    case ERR_OPTION:
        cout << "\nERROR: wrong option\n"
             << endl;
        break;
    case ERR_EMPTY:
        cout << "\nERROR: empty string\n"
             << endl;
        break;
    case ERR_DUPLICATED:
        cout << "\nERROR: duplicated value\n"
             << endl;
        break;
    case ERR_NOT_EXIST:
        cout << "\nERROR: value does not exist\n"
             << endl;
        break;
    case ERR_RATING:
        cout << "\nERROR: number out of range\n"
             << endl;
    }
}

/*
    FUNCIÓN: manageInput
    PROPÓSITO: Solicitar una cadena al usuario y almacenarla en strReq.
             Si converToInt es verdadero, entonces intentar convertir strReq
             a un entero utilizando strtol y almacenarlo en numReq. Si la
             conversión no es válida, imprimir un mensaje de error y retornar sin
             realizar nada. Si converToInt es falso, entonces simplemente
             retornar strReq sin realizar ninguna conversión.
    ARGUMENTOS:
        reqTmp: Una cadena que se imprimirá al usuario como una solicitud de
                entrada.
        strReq: Una referencia a una cadena que la entrada solicitada se
                almacenará en.
        numReq: Una referencia a un entero que, si converToInt es verdadero, se
                utilizará para almacenar el número convertido de strReq.
        converToInt: Un booleano que determina si se debe intentar convertir
                     la entrada a un entero.
        checkSize: Un booleano que determina si se debe verificar si la cadena de
                   entrada está vacía. Si es verdadero, entonces la función
                   verificará si strReq es vacía y, si lo es, imprimirá un
                   mensaje de error y retornará sin hacer nada.
    RETORNO: Si converToInt es verdadero, entonces la función retornará un
             número entero. Si converToInt es falso, la función retornará la
             cadena original que se solicitó al usuario.
*/
void manageInput(const string &reqTmp, string &strReq, int &numReq, bool converToInt, bool checkSize)
{
    // Imprimir la solicitud de entrada y obtener la entrada del usuario
    cout << reqTmp;
    getline(cin, strReq);

    // Si checkSize es verdadero, entonces verificar si strReq está vacía y,
    // si lo está, imprimir un mensaje de error y retornar sin hacer nada
    if (checkSize && strReq.empty())
    {
        error(ERR_EMPTY);
        return;
    }

    // Si converToInt es verdadero, entonces intentar convertir strReq a un
    // número entero utilizando strtol y almacenar el resultado en numReq. Si
    // la conversión no es válida, imprimir un mensaje de error y retornar sin
    // hacer nada
    if (converToInt)
    {
        char *ptr;
        numReq = strtol(strReq.c_str(), &ptr, 10); // Convertir strReq a entero
        if (*ptr != '\0')                         // Verificar si la conversión fue válida
        {
            cerr << "Error -> " << strReq << " no es un número entero" << endl;
            return;
        }
    }
}


/*
    Funcion: busca un año en el vector proporcionado
    year: listado de años del vector
    encontrado: booleano en caso de que encuentre el número
    pos: posición en el vector
    numYear: número introducido
    flag: 1-> imprime error duplicado
    return: TRUE si lo encuentra y su posición en el vector
*/
void searchYear(vector<AcademicYear> &year, bool &encontrado, int &pos, int numYear, int flag)
{
    for (int i = 0; i < (int)year.size(); i++)
    {
        if (year[i].id == numYear)
        {
            encontrado = true;
            pos = i; // posición del año
            if (flag == 1)
                error(ERR_DUPLICATED);
            break;
        }
    }
}

/*
    Funcion: busca un profesor en el vector de profesores de un año académico
    year: vector de años académicos
    strName: nombre del profesor a buscar
    flag: indicador de si mostrar mensaje de error en caso de duplicado (1) o no (0)
    return: true si se encuentra el profesor, false en caso contrario
*/
void searchName(vector<AcademicYear> &year, bool &encontrado, int &pos, int &namePos, string &strName, int flag)
{
    for (int i = 0; i < (int)year.size(); i++) // recorremos todos los años academicos
    {
        for (int j = 0; j < (int)year[i].listTeachers.size(); j++) // recorremos todos los profesores del año
        {
            if (year[i].listTeachers[j].name == strName)
            {
                encontrado = true;
                pos = i;
                namePos = j;
                if (flag == 1)
                    error(ERR_DUPLICATED);
                break;
            }
        }
        if (encontrado) // si ya hemos encontramos el profesor, saltamos del bucle externo
            break;
    }
}

/*
    Funcion: añade un año academico
    year: listado de años del vector
    return: nada
*/
void addAcademicYear(vector<AcademicYear> &year)
{
    AcademicYear academic_year;
    string strYear;
    int numYear = 0, pos; // Inicializamos numYear para asegurarnos
    bool encontrado;

    do
    {
        // Funcion encargada de manejar el input
        manageInput("Enter academic year: ", strYear, numYear, true, true);

        // Buscamos el numero introducido y nos quedamos con si posicion
        encontrado = false; // duplicado
        pos = -1;
        searchYear(year, encontrado, pos, numYear, 1);
    } while (encontrado);

    // Comprobación para guardar el año
    if (!(strYear.empty()))
    {
        academic_year.id = numYear;
        year.push_back(academic_year);
    }
}

/*
    Funcion: elimina un año academico
    year: listado de años del vector
    return: nada
*/
void deleteAcademicYear(vector<AcademicYear> &year)
{
    AcademicYear academic_year;
    string strYear;
    int numYear, pos;
    bool encontrado;

    do
    {
        manageInput("Enter academic year: ", strYear, numYear, true, true);
        if (strYear.empty())
            return;

        // Buscamos el año y nos quedamos con su posición
        encontrado = false;
        pos = -1;
        searchYear(year, encontrado, pos, numYear, 0);
        if (!encontrado)
            error(ERR_NOT_EXIST);

    } while (!encontrado);

    year.erase(year.begin() + pos);
}

/*
    Funcion: agrega un nuevo profesor a la lista de profesores de un año académico
    year: vector de años académicos
    return: nada
*/
void addTeacher(vector<AcademicYear> &year)
{
    Teacher new_teacher;
    string strYear, strName,
        strNick, strSub, strRtg;
    bool encontrado;
    int numYear, numRtg, pos, namePos;

    // Pedimos el año hasta encontralo
    do
    {
        manageInput("Enter academic year: ", strYear, numYear, true, true);

        if (strYear.empty())
            return;

        // Buscamos el año y nos quedamos con su posición
        encontrado = false;
        pos = -1;
        searchYear(year, encontrado, pos, numYear, 0);
        if (!encontrado)
            error(ERR_NOT_EXIST);

    } while (!encontrado);

    // Pedimos los datos del nuevo profesor y los guardamos en el struct new_teacher
    do
    {
        manageInput("Enter teacher name: ", strName, numYear = 0, false, true);
        encontrado = false;
        int yearPos = 0;
        searchName(year, encontrado, yearPos, namePos, strName, 1);
    } while (encontrado);

    if (strName.size() != 0)
    {
        new_teacher.name = strName;
    }
    else
        return;

    manageInput("Enter nickname: ", strNick, numYear = 0, false, false);
    new_teacher.nickname = strNick;

    // Asignatura
    manageInput("Enter subject: ", strSub, numYear = 0, false, true);
    if (strSub.empty())
        return;
    // Recortamos la asignatura a 49 caracteres
    strSub = strSub.substr(0, MAXSUBJECT - 1);
    strcpy(new_teacher.subject, strSub.c_str());

    // Valoración
    do
    {
        manageInput("Enter rating: ", strRtg, numRtg, true, false);        

        if (strRtg.size() == 0)
        {
            numRtg = 0;
            new_teacher.rating = numRtg;
            break;
        }
        if (numRtg < 1 || numRtg > 5)
            error(ERR_RATING);
    } while (numRtg < 1 || numRtg > 5);
    new_teacher.rating = numRtg;

    // Guardamos los datos en el vector
    year[pos].listTeachers.push_back(new_teacher);
}

/*
    Funcion: elimina un profesor del vector de profesores de un año académico
    year: vector de años académicos
    return: nada
*/
void deleteTeacher(vector<AcademicYear> &year)
{
    string strName;
    int numYear = 0, pos, namePos;
    bool encontrado;

    do
    {
        manageInput("Enter teacher name: ", strName, numYear, false, true);
        if (strName.empty())
            return;

        encontrado = false;
        pos = 0;
        searchName(year, encontrado, pos, namePos, strName, 0);
        if (!encontrado)
            error(ERR_NOT_EXIST);
    } while (!encontrado);

    // Eliminamos los datos
    year[pos].listTeachers.erase(year[pos].listTeachers.begin() + pos);
}

/*
    Funcion: resumen del profesor
    year: vector de años académicos
    return: nada
*/
void showTeacher(vector<AcademicYear> &year)
{
    string strName;
    bool encontrado = true;
    int numYear = 0, pos, namePos;

    do
    {
        manageInput("Enter teacher name: ", strName, numYear, false, true);
        if (strName.empty())
            return;

        encontrado = false;
        pos = 0;
        searchName(year, encontrado, pos, namePos, strName, 0);
        if (!encontrado)
            error(ERR_NOT_EXIST);
    } while (!encontrado);

    // Mostramos año
    cout << "Academic year: " << year[pos].id << endl;

    // Mostramos el nombre
    cout << "Name: " << year[pos].listTeachers[namePos].name << endl;

    // Mostramos el apado si lo hay
    if (!(year[pos].listTeachers[namePos].nickname.empty()))
        cout << "Nickname: " << year[pos].listTeachers[namePos].nickname << endl;

    // Mostramos la asignatura
    cout << "Subject: " << year[pos].listTeachers[namePos].subject << endl;

    // Mostramos el rating
    if (year[pos].listTeachers[namePos].rating != 0)
    {
        cout << "Rating: ";
        for (int i = 0; i < year[pos].listTeachers[namePos].rating; i++)
            cout << "*";
        cout << endl;
    }

    for (int i = 0; i < (int)year[pos].listTeachers[pos].listPhrases.size(); i++)
    {
        cout << "Phrase " << i + 1;
        if (year[pos].listTeachers[namePos].listPhrases[i].date.year != 0)
        {
            cout << " ";
            cout << "(" << year[pos].listTeachers[namePos].listPhrases[i].date.year;
            cout << "-";
            cout << year[pos].listTeachers[namePos].listPhrases[i].date.month;
            cout << "-";
            cout << year[pos].listTeachers[namePos].listPhrases[i].date.day << ")";
        }
        if (year[pos].listTeachers[namePos].listPhrases[i].rating != 0)
        {
            cout << " ";
            cout << "[" << year[pos].listTeachers[namePos].listPhrases[i].rating << "]";
        }
        cout << ": ";

        cout << year[pos].listTeachers[namePos].listPhrases[i].text << endl;
    }
}

/*
    Funcion: agrega una frase al vector
    year: vector de años académicos
    return: nada
*/
void addPhrase(vector<AcademicYear> &year)
{
    Phrase new_phrase;
    string strName, strPhr, strRtg, strDate;
    int numYear = 0, pos, namePos, numRtg;
    int dateYear, dateMonth, dateDay;
    bool encontrado;

    do
    {
        manageInput("Enter teacher name: ", strName, numYear, false, true);
        if (strName.empty())
            return;

        encontrado = false;
        pos = 0;
        searchName(year, encontrado, pos, namePos, strName, 0);
        if (!encontrado)
            error(ERR_NOT_EXIST);
    } while (!encontrado);

    manageInput("Enter phrase: ", strPhr, numYear, false, true);
    if (strPhr.empty())
        return;
    new_phrase.text = strPhr;

    cout << "Enter date (year-month-day): ";
    getline(cin, strDate);

    if (strDate.empty())
    {
        new_phrase.date.year = 0;
        new_phrase.date.day = 0;
        new_phrase.date.month = 0;
    }
    else
    {
        size_t separador = strDate.find('-');
        dateYear = stoi(strDate.substr(0, separador));
        strDate = strDate.substr(separador + 1);

        separador = strDate.find('-');
        dateMonth = stoi(strDate.substr(0, separador));
        strDate = strDate.substr(separador + 1);

        dateDay = stoi(strDate);

        new_phrase.date.year = dateYear;
        new_phrase.date.month = dateMonth;
        new_phrase.date.day = dateDay;
    }

    do
    {
        manageInput("Enter rating: ", strRtg, numRtg, true, false);

        if (strRtg.empty())
        {
            numRtg = 0;
            new_phrase.rating = numRtg;
            break;
        }

        new_phrase.rating = numRtg;

        if (numRtg < 1 || numRtg > 10)
            error(ERR_RATING);
    } while (numRtg < 1 || numRtg > 10);

    year[pos].listTeachers[namePos].listPhrases.push_back(new_phrase);
}

/*
    Funcion: resumen anual de todos los años con sus frases, rating y quien las dijo
    year: vector de años académicos
    return: nada
*/
void summary(vector<AcademicYear> &year)
{
    sort(year.begin(), year.end(), [](AcademicYear &a, AcademicYear &b)
         { return a.id > b.id; });

    for (int i = 0; i < (int)year.size(); ++i)
    {
        if (!year[i].listTeachers.empty())
        {
            cout << "Academic year: " << year[i].id << endl;

            for (int j = 0; j < (int)year[i].listTeachers.size(); ++j)
            {
                for (int k = 0; k < (int)year[i].listTeachers[j].listPhrases.size(); ++k)
                {
                    int rating = year[i].listTeachers[j].listPhrases[k].rating;
                    string teacherName = year[i].listTeachers[j].name;
                    string phrase = year[i].listTeachers[j].listPhrases[k].text;
                    string ratingInfo = (rating > 0) ? (" - " + to_string(rating)) : "";
                    cout << teacherName << ratingInfo << " - " << phrase << endl;
                }
            }
        }
    }
    cout << endl;
}

/* #endregion }}}*/

/* #region Funcion principal {{{ */

int main()
{
    char op;
    vector<AcademicYear> listYears;

    do
    {
        showMenu();
        cin >> op;
        cin.get();

        switch (op)
        {
        case '1': // Llamar a la función "addAcademicYear" para crear un nuevo
                  // curso
            addAcademicYear(listYears);
            break;
        case '2': // Llamar a la función "deleteAcademicYear" para eliminar un
                  // curso
            deleteAcademicYear(listYears);
            break;
        case '3': // Llamar a la función "addTeacher" para crear un nuevo
                  // profesor
            addTeacher(listYears);
            break;
        case '4': // Llamar a la función "deleteTeacher" parar eliminar un
                  // profesor
            deleteTeacher(listYears);
            break;
        case '5': // Llamar a la función "showTeacher" para mostrar la
                  // información del profesor
            showTeacher(listYears);
            break;
        case '6': // Llamar a la función "addPhrase" para añadir una nueva frase
            addPhrase(listYears);
            break;
        case '7': // Llamar a la función "summary" para mostrar un resumen de
                  // las frases por curso
            summary(listYears);
            break;
        case 'q':
            break;
        default:
            error(ERR_OPTION);
        }
    } while (op != 'q');
}

/* #endregion }}} */