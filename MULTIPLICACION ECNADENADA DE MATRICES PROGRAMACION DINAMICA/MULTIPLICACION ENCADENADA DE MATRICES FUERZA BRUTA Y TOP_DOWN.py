import random
import time
import matplotlib.pyplot as plt

def printMCP(s, i, j):
    if i == j:
        print(f"A{i+1}", end="")
    else:
        print("(", end="")
        printMCP(s, i, s[i][j])
        printMCP(s, s[i][j] + 1, j)
        print(")",end="")

def generarDimensionesAleatorias(n):
    dimensiones = [random.randint(1, 100) for _ in range(n + 1)]
    return dimensiones

#FUERZA BRUTA
def fuerza_bruta(p, n):
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
    return min_cost, s  # Devolver los valores calculados

#TOP_DOWN
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


#GRAFICA DE FUERZA BRUTA
def grafica_fuerza_bruta(numMatriz_tiempFB):
    for numMatrices, tiempos in enumerate(numMatriz_tiempFB, start=0):
        for tiempo in tiempos:
            plt.plot(numMatrices, tiempo, 'o', color='red')
    plt.xlabel('Número de matrices')
    plt.ylabel('Tiempo (ns)')
    plt.title('Tiempo de ejecución de FUERZA BRUTA')
    plt.show()

#GRAFICA DE TOP-DOWN
def grafica_top_down(numMatriz_tiempoTD):
    for numMatrices, tiempos in enumerate(numMatriz_tiempoTD, start=0):
        for tiempo in tiempos:
            plt.plot(numMatrices, tiempo, 'o', color='blue')
    plt.xlabel('Número de matrices')
    plt.ylabel('Tiempo (ns)')
    plt.title('Tiempo de ejecución de TOP-DOWN')
    plt.show()


#GRAFICA FUERZA BRUTA VS TOPD-DOWN
def grafica_fuerza_bruta_vs_top_down(numMatriz_tiempFB, numMatriz_tiempoTD):
    for numMatrices, tiempos in enumerate(numMatriz_tiempFB, start=0):
        for tiempo in tiempos:
            plt.plot(numMatrices, tiempo, 'o', color='red')
    
    for numMatrices, tiempos in enumerate(numMatriz_tiempoTD, start=0):
        for tiempo in tiempos:
            plt.plot(numMatrices, tiempo, 'o', color='blue')

    # Agregar etiquetas
    plt.text(0.5, 0.9, 'Fuerza Bruta', color='red', transform=plt.gca().transAxes)
    plt.text(0.5, 0.85, 'Top-Down', color='blue', transform=plt.gca().transAxes)

    plt.xlabel('Número de matrices')
    plt.ylabel('Tiempo (ns)')
    plt.title('Comparación de Tiempo de Ejecución entre Fuerza Bruta y Top-Down')
    plt.show()


def main():
    numMatriz_tiempFB = [[] for i in range(2, 251)]
    numMatriz_tiempTD = [[] for i in range(2, 251)]

    for numMatrices in range(2,251):
        random.seed(time.time())
        for i in range(3):
            p = generarDimensionesAleatorias(numMatrices)
            print("Dimensiones generadas aleatoriamente de las matrices: ")
            for i in range(1, numMatrices + 1):
                print(f"A{i}: {p[i - 1]} x {p[i]}")
                
            # Fuerza bruta
            inicio_fb = time.perf_counter_ns()
            minOperaciones, solucion = fuerza_bruta(p, numMatrices + 1)
            fin_fb = time.perf_counter_ns()
            tiempo_fuerza_bruta_actual = fin_fb - inicio_fb

            numMatriz_tiempFB[numMatrices - 2].append(tiempo_fuerza_bruta_actual)
            print(f"\nNumero total de operaciones optimo fuerza bruta: {minOperaciones}")
            print("Multiplicacion optima de matrices fuerza bruta: ", end="")
            printMCP(solucion, 0, numMatrices-1)
            print("\nEl tiempo de fuerza bruta para", numMatrices, "matrices es:", tiempo_fuerza_bruta_actual)
            
            #top-down
            tabla = [[None for i in range(numMatrices)] for i in range(numMatrices)]
            s= [[0 for i in range(numMatrices)] for i in range(numMatrices)]

            inicio_td=time.perf_counter_ns()
            top_down(p, tabla, s, 0,numMatrices-1)
            fin_td=time.perf_counter_ns()
            tiempo_top_down_actual=fin_td-inicio_td
            
            numMatriz_tiempTD[numMatrices - 2].append(tiempo_top_down_actual)
            print(f"\n\nNumero total de operaciones optimo top-down: {tabla[0][numMatrices-1]}")
            print("Multiplicacion optima de matrices top-down: ", end="")
            printMCP(s, 0, numMatrices-1)
            print("\nEl tiempo top-down para", numMatrices, " matrices es:", tiempo_top_down_actual)
            print("\n\n")   
            #print("El tiempo de de top-down para", numMatrices, "es:", tiempo_top_down)

    grafica_fuerza_bruta(numMatriz_tiempFB)
    grafica_top_down(numMatriz_tiempTD)
    grafica_fuerza_bruta_vs_top_down(numMatriz_tiempFB,numMatriz_tiempTD)

if __name__== "__main__":
    main()
