import random
import time

def printMCP(solucion, i, j):
    if i == j:
        print(f"A{i+1} ", end="")
    else:
        print("(", end="")
        printMCP(solucion, i, solucion[i][j])
        printMCP(solucion, solucion[i][j] + 1, j)
        print(")", end="")

def top_down(p, tabla, solucion, i, j):
    if i == j:
        return 0
    if tabla[i][j] is not None:
        return tabla[i][j]
    
    tabla[i][j] = float('inf')
    for k in range(i, j):
        q = top_down(p, tabla, solucion, i, k) + top_down(p, tabla, solucion, k + 1, j) + p[i] * p[k + 1] * p[j + 1]
        if q < tabla[i][j]:
            tabla[i][j] = q
            solucion[i][j] = k
    return tabla[i][j]

def generarDimensionesAleatorias(n):
    return [random.randint(1, 100) for _ in range(n + 1)]

def main():
    random.seed(time.time())
    numMatrices = int(input("Ingrese el número de matrices: "))
    p = generarDimensionesAleatorias(numMatrices)
    
    print("Dimensiones generadas aleatoriamente de las matrices:")
    for i in range(1, numMatrices + 1):
        print(f"A{i}: {p[i - 1]} x {p[i]}")
    
    tabla = [[None for _ in range(numMatrices)] for _ in range(numMatrices)]
    s = [[0 for _ in range(numMatrices)] for _ in range(numMatrices)]
    
    top_down(p, tabla, s, 0, numMatrices - 1)
    
    print(f"Número total de operaciones óptimo: {tabla[0][numMatrices - 1]}")
    print("Paréntesis óptimos:")
    printMCP(s, 0, numMatrices - 1)
if __name__ == "__main__":
    main()