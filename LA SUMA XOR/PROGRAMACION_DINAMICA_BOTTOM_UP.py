import time
import matplotlib as plt


def lectura(array, l_r, n):
    with open('datos.txt', 'r') as archivo:
        contenido = archivo.readlines()

    lineas = []
    for cada_linea in contenido:
        elementos = cada_linea.strip().split()
        lineas.append(elementos)

    n = int(lineas[0][0])
    consultas = int(lineas[0][1])

    for cada_numero in lineas[1]:
        array.append(int(cada_numero))

    for i in range(consultas):
        aux = [int(i) for i in lineas[2 + i]]
        l_r.append(aux)

    return consultas, n


def bottom_up(A, L, R, n):
    S = [[0 for _ in range(n)] for _ in range(n)]

    for i in range(n):
        S[i][i] = A[i]

    resultado = S[L][L]
    for i in range(L + 1, R + 1):
        S[L][i] = abs(S[L][i - 1] - S[i][i])
        resultado += S[L][i]
    return resultado

def resultados_archivo(resultados_bu,nombre_archivo,l_r):
    with open(nombre_archivo,'w') as archivo:
        archivo.write("Resultados de BOTTOM-UP\n")
        for idx,cada_resultado in enumerate(resultados_bu):
            archivo.write(f"Consulta {idx + 1}: Suma XOR de array[{l_r[idx][0]}] a array[{l_r[idx][1]}] = {cada_resultado}\n")
    print ("\nARCHIVO CREADO CORRECTAMENTE :)\n")

def registro_tiempo(nombre_archivo, consultas, tiempos):
    with open(nombre_archivo, 'a') as archivo:
            archivo.write(f"{consultas} {tiempos}\n")
    print("\nARCHIVO DE TIEMPOS CREADO CORRECTAMENTE ;)\n")

def main():
    #Variables de lectura
    array = []
    l_r = []
    n = 0
    resultados_bu=[]

    #Proceso de BOTTOM-UP
    consultas, n = lectura(array, l_r, n)

    inicio_bu= time.perf_counter_ns()
    for i in range(consultas):
        resultados= bottom_up(array, l_r[i][0] - 1, l_r[i][1] - 1, n)
        resultados_bu.append(resultados)
    fin_bu = time.perf_counter_ns()
    tiempo_bu = fin_bu - inicio_bu

    #Resultados correspondientes a cada consulta
    print("Resultados de BU:")
    for idx,i in enumerate(resultados_bu):
        print(f"Consulta {idx+1}: Suma XOR de array[{l_r[idx][0]}] a array [{l_r[idx][1]}]= {i}")

    #Impresion del tiempo en terminal por n consultas
    print(f"\nPara {consultas} consultas  se tardo {tiempo_bu} nanosegundos\n")
    
    #Guardar resultados en un archivo
    resultados_archivo(resultados_bu,'resultados_bottom_up.txt',l_r)

    #Guardar tiempos en un archivo
    #registro_tiempo('tiempos_bottom_up.txt',consultas,tiempo_bu)
    
main()

