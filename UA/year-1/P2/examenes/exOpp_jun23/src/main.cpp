#include "../include/student.h"
#include "../include/subject.h"

int main()
{
    //cout << "Hello, World!" << endl; // Debug

    Subject subject("Literature");

    // Debe crear el grupo 1
    subject.addGroup("Annie Ernaux;Abdulrazak Gurnah;Louise Gluck;Peter Handke");
    //cout << "Debug group number: " << subject.getGroup() << endl; // Debug

    // No debe crear el grupo
    subject.addGroup("");
    //cout << "Debug group number: " << subject.getGroup() << endl; // Debug

    // Debe mostrar un error porque hay un nombre vac´ıo y crear el grupo 2 con dos estudiantes
    subject.addGroup("Kazuo Ishiguro;;Bob Dylan");
    //cout << "Debug group number: " << subject.getGroup() << endl; // Debug

    // Debe crear el grupo 3, actualizando el grupo del primer estudiante (ya estaba en el grupo 1)
    subject.addGroup("Peter Handke;Olga Tokarczuk");
    //cout << "Debug group number: " << subject.getGroup() << endl; // Debug

    subject.setGroupMark(1, 8.7);
    subject.setGroupMark(2, 9.3);
    subject.setGroupMark(3, 7.2);
    cout << subject;

    return 0;
}