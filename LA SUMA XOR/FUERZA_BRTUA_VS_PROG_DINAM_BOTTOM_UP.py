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




def bottom_up(A, L, R, n):

    #Creación de la tabla - solución
    S = [[0 for _ in range(n)] for _ in range(n)]
    # Caso base
    for i in range(n):
        S[i][i] = A[i]
    # Calculo del resultado final
    resultado = S[L][L]
    for i in range(L + 1, R + 1):
        #Calculo de cada XOR
        S[L][i] = abs(S[L][i - 1] - S[i][i])
        #Suma del resultado de cada XOR
        resultado += S[L][i]
    return resultado



def main():
    # Variables de lectura para FB_BU
    array = []
    l_r = []
    #Variable para BU
    n = 0
    resultados_bu=[]

    # Imprimir resultados FB
    lectura(array, l_r,n)
    resultados_fb = fuerza_bruta(array, l_r)

    print("Resultados de FB:")
    for idx, i in enumerate(resultados_fb):
        print(f"Consulta {idx + 1}: Suma XOR de array[{l_r[idx][0]}] a array[{l_r[idx][1]}]= {i}")

    print('\n')

    #Imprimir resultados BU
    consultas, n = lectura(array, l_r, n)
    for i in range(consultas):
        resultados= bottom_up(array, l_r[i][0] - 1, l_r[i][1] - 1, n)
        resultados_bu.append(resultados)

    print("Resultados de BU:")
    for idx,i in enumerate(resultados_bu):
        print(f"Consulta {idx+1}: Suma XOR de array[{l_r[idx][0]}] a array [{l_r[idx][1]}]= {i}")

main()