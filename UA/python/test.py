from sympy.abc import x
import numpy as np
from sympy import expand

x_puntos = [1, 0.5, 3]
y_puntos = [3, -10, 2]

def diff_div(x_data, y_data):
    '''
    funccion para calcular la tabla de diferencias divididas
    '''

    n = len(y_data)         # tamaño de y
    coef = np.zeros([n, n]) # crea una matriz de n*n llena de 0
    coef[:,0] = y_data      # la primera columna es y
    
    print("Calculo de los coeficientes")
    for j in range(1,n):     # itera cada columna de la tabla, empezando en 1 (la columna 0 ya está rellenada)
        for i in range(n-j): # itera cada línea de la tabla, de 0 hasta (máximo - posición de columna). Esto hace que se recorra de forma triangular
            # El numerador avanza en las líneas y mantiene las columnas fija
            # El denominador mantiene la posición de la línea fija y "salta" (de forma proporcional) con posición de línea + posición de columna
            coef[i][j] = (coef[i+1][j-1] - coef[i][j-1]) / (x_data[i+j]-x_data[i])
        print("f[",","*j,"]", sep="")
        print(coef)
        print()
    

    n -=1
    coef = coef[0, :]
    p = coef[n]
    for k in range(1,n+1):
        # Se construye el polinomio con el "multiplicador común" 
        # y se hace desde la potencia más alta hasta x^0
        # Lo más natural sería tener dos bucles para controlar los "x" para cada
        # grado, pero como cada grado contiene los grados anteriores, la expresión puede ser
        # escrita en relación al (x-x1) [y consecuentes]
        # ejemplo:
        # p1 = y0 + a1(x-x0)
        # p2 = y0 + (a1 + a2(x-x1))(x-x0)
        # p3 = y0 + (a1 + ((a2 + a3(x-x2))(x-x1)))(x-x0)
        p = coef[n-k] + (x-x_data[n-k])*p

    print("Polinomio")
    return expand(p)

diff_div(x_puntos,y_puntos)