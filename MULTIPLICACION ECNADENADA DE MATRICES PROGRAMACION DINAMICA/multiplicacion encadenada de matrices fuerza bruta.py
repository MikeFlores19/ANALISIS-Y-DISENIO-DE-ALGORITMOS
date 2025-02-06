import random
import time


def printMCP(solucion, i, j):
    if i == j:
        print (f"A{i+1}", end="")
    else:
        print("(",end="")
        printMCP(solucion, i, solucion[i][j])
        printMCP(solucion, solucion[i][j]+1, j)
        print(")", end="")

# Fuerza bruta
def multiplicacionMatricesOptima(p, n):
    m = [[0] * n for _ in range(n)]
    s = [[0] * n for _ in range(n)]
    # Calcular los costos óptimos
    for l in range(2, n):  
        for i in range(1, n - l + 1):  # i es el índice de inicio de la cadena
            j = i + l - 1  # j es el índice de fin de la cadena
            m[i][j] = 0  # Inicializado a 0
            min_cost = None  # Inicializar el costo mínimo
            for k in range(i, j):  # k es el índice para dividir la cadena
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]
                if min_cost is None or q < min_cost:  # Si encontramos un costo menor, lo actualizamos
                    min_cost = q
                    s[i][j] = k
            m[i][j] = min_cost
    return min_cost, s

def generarDimensionesAleatorias(n):
    dimensiones = [random.randint(1, 100) for _ in range(n + 1)]
    return dimensiones

def main():
    random.seed(time.time())
    numMatrices = int(input("Ingrese el numero de matrices: "))
    p = generarDimensionesAleatorias(numMatrices)

    print("Dimensiones generadas aleatoriamente de las matrices fuerza bruta:")
    for i in range(1, numMatrices + 1):
        print(f"A{i}: {p[i - 1]} x {p[i]} ")

    minOperaciones, solucion = multiplicacionMatricesOptima(p, numMatrices + 1)
    print(f"Numero total de operaciones optimo: {minOperaciones}")

    print("Multiplicacion optima de matrices: ", end="")
    printMCP(solucion, 0, numMatrices-1)

if __name__ == "__main__":
    main()
