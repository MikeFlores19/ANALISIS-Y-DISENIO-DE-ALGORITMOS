import time
import matplotlib as plt

# FUNCION DE LECTURA 
def lectura( array, l_r):
    lineas=[]
    with open('datos.txt', 'r') as archivo:
        contenido = archivo.readlines()

    for linea in contenido:
        elementos = linea.strip().split()
        lineas.append(elementos)

    n = int(lineas[0][0])
    consultas = int(lineas[0][1])

    array.extend([int(num) for num in lineas[1]])

    for i in range(consultas):
        aux = [int(num) for num in lineas[2 + i]]
        l_r.append(aux)

    return consultas

def fuerza_bruta(array, l_r):
    resultados = []
    for idx, i in enumerate(l_r):
        l = i[0] -1
        r = i[1] -1
        suma = 0
        
        
        if l == r:
            suma = array[l]
        elif abs(l - r) == 1:
            suma = array[l] + abs(array[l] - array[r])
        elif (l % 2 != 0) and (r % 2 != 0):
            for j in range(l, r+1):
                xor = array[j]
                for k in range(j+1, r):
                    xor = abs(xor - array[k])
                suma += xor
        else:
            for j in range(l, r + 1):
                xor = array[j]
                for k in range(j + 1, r + 1):
                    xor = abs(xor - array[k])
                suma += xor
        resultados.append(suma)
    return resultados

def resultados_archivo(resultados,nombre_archivo,l_r):
    with open(nombre_archivo, 'w') as archivo:
        archivo.write("Resultados de FUERZA BRUTA:\n")
        for idx,cada_resultado in enumerate(resultados):
            archivo.write(f"Consulta {idx + 1}: Suma XOR de array[{l_r[idx][0]}] a array[{l_r[idx][1]}] = {cada_resultado}\n")
    print ("\nARCHIVO DE RESULTADOS CREADO CORRECTAMENTE :)\n")

def registro_tiempo(nombre_archivo, consultas, tiempos):
    with open(nombre_archivo, 'a') as archivo:
            archivo.write(f"{consultas} {tiempos}\n")
    print("\nARCHIVO DE TIEMPOS CREADO CORRECTAMENTE ;)\n")

def main():
    # Variables de lectura
    array = []  
    l_r = []

    #Proceso de FUERZA BRUTA
    consultas=lectura(array, l_r)

    inicio_fb= time.perf_counter_ns()
    resultados = fuerza_bruta(array, l_r)
    fin_fb = time.perf_counter_ns()
    tiempo_fb = fin_fb - inicio_fb

    # Imprimir resultados
    print("Resultados FB:")
    for idx, cada_resultado in enumerate(resultados):
        print(f"Consulta {idx + 1}: Suma XOR de array[{l_r[idx][0]}] a array[{l_r[idx][1]}] = {cada_resultado}")

    #Impresion del tiempo en terminal por n consultas
    print(f"\nPara {consultas} consultas  se tardo {tiempo_fb} nanosegundos\n")

    #Guardar resultados en un archivo
    resultados_archivo(resultados,'resultados_fuerza_bruta.txt',l_r)

    #Guardar tiempos en un archivo
    #registro_tiempo('tiempos_fuerza_bruta.txt',consultas,tiempo_fb)

main()
