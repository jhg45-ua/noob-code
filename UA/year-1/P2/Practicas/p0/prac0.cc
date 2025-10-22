
// Práctica 0
// DNI 48795869N Hinojosa Gil, Julián
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

bool multiple(int a, int b);
bool mult(int a, int b);
int printN(int n);
int firstPrimes(int n);
bool isPrime(int p);
void Goldbach(int n,int &p1,int &p2);
bool search(int v[], const int TAMVECTOR, int n);
int position(int v[], const int TAMVECTOR, int n);
int count(int v[], const int TAMVECTOR, int n);
int minOdds(int v[], const int TAMVECTOR);
void deleteChar(char str[],char c);



/*                      Ejercicio 1
 * Función: recibe dos números y comprueba si son múltiplos entre ellos
 * a: primer número
 * b: segundo número
 * return: devuelve el resultado de la función mult que devuelve TRUE
 *         en caso de que se cumpla la condición
 */
bool multiple(int a, int b)
{
    return mult(a, b) || mult(b, a);
}

/*
 * Función: método auxiliar para multiple que devuelve TRUE si
 * el resto de a y b es 0
 */
bool mult(int a, int b)
{
    return a%b == 0;
}

/*                      Ejercicio 2
 * Función: dibuja con * la letra N en forma cuadrada según un entero positivo n
 * n: determina el tamaño de la N
 * return: devuelve la variable local asteriscos que sirve como contador para saber
 *         el total de asteriscos usados
 */
int printN(int n)
{
    if(n < 4)
    {
        cout << "ERROR" << endl;
        return 0;
    }

    int asteriscos = 0; // contador interno
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == 0 || j == n - 1 || i == j)
            {
                cout << "*";
                asteriscos++;
            }
            else
                cout << " ";
        }
        cout << endl;
    }
    return asteriscos;
}

/*                      Ejercicio 3
 * Función: recibe un numero n entero positivo y devuelve los n números primos más su suma total
 * n: números primos a imprimir
 * total: la suma de todos los n números primos
 * contador: contador interno que controla que el bucle itere hasta n
 * numero: variable para empezar a buscar números primos, empieza en 2 pues es el primer número primo
 * return: devuelve la suma total de los números primos obtenidos según n
 */
int firstPrimes(int n)
{
    int total = 0;
    int contador = 0;
    int numero = 2;

    while (contador < n)
    {
        if (isPrime(numero))
        {
            total += numero;
            contador++;
            cout << numero << " ";
        }
        numero++;
    }
    return total;
}

/*
 * Función: método auxiliar para firstPrimes que comprueba que si un número es primo
 * p: número proporcionado a comprobar si es primo
 * return 1: en caso de p sea menor de 2 devuelve FALSE, pues 2 es el primer número primo
 * return 2: devuelve FALSE cuando y exactamente divide a p hasta recorrer los divisores de p
 * hasta su raíz cuadrada
 * return 3: devuelve TRUE cuando se cumpla la condición contraria del caso anterior
 */
bool isPrime(int p)
{
    if (p < 2) return false;

    for (int i = 2; i * i <= p; i++)
    {
        if (p % i == 0) return false;
    }
    return true;
}

/*                      Ejercicio 4
 * Función: cumple la conjetura de goldbach donde cualquier número par mayor que dos
 *          puede ser obtenido como suma de dos números primos
 * n: número base para sacar los números primos
 * p1: primer número primo (el menor)
 * p2: segundo número primo (el mayor)
 * En este caso la función no devuelve nada sino que modifica por referencia
 * los valores de p1 y p2
 */
void Goldbach(int n,int &p1,int &p2)
{
    for (int i = 2; i <= n; i++)
    {
        if (isPrime(n - i) && isPrime(i))
        {
            p1 = n - i;
            p2 = i;
        }
    }
}

/*                      Ejercicio 5
 * Función: busca el número n en el array v de tamaño TAMVECTOR
 * v[]: array
 * TAMVECTOR: tamaño del array v
 * n: número a buscar
 * return: true (1) si encuentra el número deseado y false (0) si no
 * NOTA: a la hora de recorrer un vector se hará desde la posición n hasta la n-1,
 * por tanto, solo usamos < o > no ≤ o ≥, no se coge el valor entero
 */
bool search(int v[], const int TAMVECTOR, int n)
{
    for (int i = 0; i < TAMVECTOR; i++)
        if (v[i] == n)
            return true;
    return false;
}

/*
 * Función: indica la posición del número n en el array v de tamaño TAMVECTOR
 * v[]: array
 * TAMVECTOR: tamaño del array v
 * n: número a buscar posición
 * return: devuelve la posición del número n y si no lo encuentra devuelve -1
 */
int position(int v[], const int TAMVECTOR, int n)
{
    for (int i = 0; i < TAMVECTOR; i++)
        if (v[i] == n)
            return i;
    return -1;
}

/*
 * Función: cuenta todas las veces que n se encuentra en v
 * v[]: array de números
 * TAMVECTOR: tamaño de v
 * n: número a comprobar
 * count: contador de n
 * return: devuelve count
 */
int count(int v[], const int TAMVECTOR, int n)
{
    int count = 0;
    for (int i = 0; i < TAMVECTOR; i++)
        if(v[i] == n)
            count++;
    return count;
}

/*                      Ejercicio 6
 * Función: busca los números impares en el vector y devuelve el mínimo
 * v[]: array de números
 * TAMVECTOR: tamaño de v
 * return: en el caso que se encuentre el número lo devuelve, pero
 *         en caso contrario devuelve -1
 */
int minOdds(int v[], const int TAMVECTOR)
{
    int min;
    bool found = false;

    for (int i = 0; i < TAMVECTOR; i++)
    {
        if (v[i] %2 != 0)
        {
            if (!found)
            {
                min = v[i];
                found = true;
            }
            else if (v[i] < min)
            {
                min = v[i];
            }
        }
    }

    if (found)
        return min;
    else
        return -1;
}

/*
 * Función: devuelve la posición del primer número múltiplo de 5
 * v[]: array de números
 * TAMVECTOR: tamaño de v
 * return: devuelve la posición que del número que cumple las condiciones
 */
int posMaxMultFive(int v[],const int TAMVECTOR)
{
    int maxNum = -1;
    int pos = -1;

    for (int i = 0; i < TAMVECTOR; i++)
    {
        if (mult(v[i], 5) && (pos == -1 || v[i] > maxNum))
        {
            maxNum = v[i];
            pos = i;
        }
    }
    return pos;
}

/*                      Ejercicio 7
 * Función: con un string dado busca la letra solicitada y la elimina sin dejar espacios
 * str[]: string/frase de base
 * c: letra a eliminar
 * En este caso no devuelve nada solo, pues se trata de un procedimiento
 */
void deleteChar(char str[],char c)
{
    size_t len = strlen(str); // Tamaño de la cadena

    int delChar = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == c)
            delChar++;
        else
            str[i - delChar] = str[i];
    }
    str[len - delChar] = '\0';
}
