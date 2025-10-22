import numpy as np
from sympy import * # Librería de Calculo
from sympy.plotting import plot as symplot # Librería para las gráficas
from sympy.abc import x, y, z, h # Carga de un simbolico "x"
from sympy.plotting.pygletplot import PygletPlot as Plot # Librería para las gráficas

def newton_raphson(func: any, x0: float, error: int, max_iter: int, decimals=20):
    print("f(x)=", func)
    func_diff = diff(func, x)
    print("f'(x)=", func_diff)
    h = x0
    i = 0

    while i < max_iter and abs(h) > error:
        a = func.subs(x, x0)
        b = func_diff.subs(x, x0)
        h = a/b
        x0 = x0 - h
        i += 1
        print(f'Iteración {i}: f(x) = {a}, f_deriv(x) = {b}, valor = {x0}, error = {abs(h).evalf(4)}')
    return round(x0, decimals)

f = x * ln(x) - sin(x)
f
result = newton_raphson(f, 1, 0.0005, 10, 4)
print(result)