//
// Created by Julián Hinojosa Gil on 2/6/24.
// program arguments
// ejemplo básico
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Número de argumentos: " << argc << std::endl;

    for (int i = 0; i < argc; i++)
    {
        std::cout << "Argumento " << i << ": " << argv[i] << std::endl;
    }

    return 0;
}