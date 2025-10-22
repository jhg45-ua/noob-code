//test correccion ficheros ejercicio examen
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Product
{
    char name[51];
    unsigned int num;
    std::string unit;
};

void fileHandle(const char *filename, std::vector<Product> &listProd, const char *mode)
{
    if (strcmp(mode, "save") == 0)
    {
        std::ofstream outFile("salida.bin", std::ios::binary);
        if (!outFile.is_open())
        {
            std::cerr << "No se pudo abrir el archivo binario para escritura." << std::endl;
            return;
        }

        for (int i = 0; i < listProd.size(); i++)
        {
            outFile.write((const char*)(&listProd), sizeof(Product));
            size_t unitSize = listProd[i].unit.size();
            outFile.write((const char*)(&unitSize), sizeof(unitSize));
        }

        outFile.close();
    } else if(strcmp(mode, "load") == 0)
    {
        std::ifstream inputFile(filename);

        if (!inputFile.is_open())
        {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inputFile, line))
        {
            size_t sep1 = line.find('|');
            size_t sep2 = line.find('|', sep1 + 1);

            std::string strProdName = line.substr(0, sep1);
            std::string strNum = line.substr(sep1 + 1, sep2 - sep1 - 1);
            std::string strUnit = line.substr(sep2 + 1);

            unsigned int num = static_cast<unsigned int>(std::stoi(strNum));

            Product newProduct;
            strcpy(newProduct.name, strProdName.c_str());
            newProduct.num = num;
            newProduct.unit = strUnit;

            listProd.push_back(newProduct);
        }

        inputFile.close(); // Cerrar el archivo
    }
}


int main()
{

    std::vector<Product> productList;


    fileHandle("datos.txt", productList, "load");
    fileHandle("", productList, "save");

    // Imprimir los productos del vector
    for (const auto& producto : productList)
    {
        std::cout << "Nombre del producto: " << producto.name << std::endl;
        std::cout << "Cantidad: " << producto.num << std::endl;
        std::cout << "Unidad de medida: " << producto.unit << std::endl;
        std::cout << "--------------------------" << std::endl;
    }
}