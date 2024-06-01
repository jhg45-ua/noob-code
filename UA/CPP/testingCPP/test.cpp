// Error handling
#include <iostream>
#include <stdexcept>

int divide(int a, int b)
{
    if (b == 0)
        throw std::runtime_error("Division by zero!");

    return a / b;
}

int main()
{
    int num1, num2;

    std::cout << "Enter two numbers for division: ";
    std::cin >> num1 >> num2;

    try
    {
        int result = divide(num1, num2);
        std::cout << "The result is: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}