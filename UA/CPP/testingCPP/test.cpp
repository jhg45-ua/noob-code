#include <iostream>
#include <unistd.h>  // Para getopt

int main(int argc, char* argv[])
{
    int opt;
    std::string valorB, valorC;
    bool opcionA = false;

    // Procesar las opciones
    while ((opt = getopt(argc, argv, "ab:c:")) != -1) {
        switch (opt)
        {
            case 'a':
                opcionA = true;
                break;
            case 'b':
                valorB = optarg;
                break;
            case 'c':
                valorC = optarg;
                break;
            default:
                std::cerr << "Uso: " << argv[0] << " [-a] [-b valor] [-c valor]" << std::endl;
                return 1;
        }
    }

    // Mostrar los resultados
    if (opcionA)
    {
        std::cout << "Opción a activada" << std::endl;
    }
    if (!valorB.empty())
    {
        std::cout << "Opción b con valor: " << valorB << std::endl;
    }
    if (!valorC.empty())
    {
        std::cout << "Opción c con valor: " << valorC << std::endl;
    }

    return 0;
}
