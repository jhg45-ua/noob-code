//test stringstream
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
    std::vector<std::string> palabras;

    std::string lista_de_palabras;

    std::cout << "Dime una lista de palabras (separadas por espacios): ";
    getline(std::cin, lista_de_palabras);

    std::stringstream ss(lista_de_palabras);
    std::string palabra;
    while (ss >> palabra)
    {
        palabras.push_back(palabra);
    }

    std::cout << "Hemos leído " << palabras.size() << " palabras" << std::endl;
    std::cout << "La segunda palabra es: " << palabras[1] << std::endl;
}