import matplotlib.pyplot as plt

def graficar_datos_fb():
    x = []
    y = []
    

    with open('tiempos_fuerza_bruta.txt', 'r') as archivo:
        # Leer cada línea del archivo
        for linea in archivo:
            # Dividir la línea en dos partes (x, y)
            partes = linea.split()
            x.append(int(partes[0]))  
            y.append(int(partes[1]))  
    
    # Crear el grafico
    plt.plot(x, y, marker='o', linestyle='-', color='r', label='TIEMPO VS CONSULTAS DE FB')
    
    plt.title('CONSULTAS VS TIEMPO DE FUERZA BRUTA')
    plt.xlabel('N CONSULTAS')
    plt.ylabel('TIEMPO')
    plt.grid(True)

    plt.show()


def graficar_datos_bu():
    x = []
    y = []
    
    with open('tiempos_bottom_up.txt', 'r') as archivo:
        # Leer cada línea del archivo
        for linea in archivo:
            # Dividir la línea en dos partes (x, y)
            partes = linea.split()
            if len(partes) == 2: # Verificar que la línea tenga dos partes
                x.append(int(partes[0]))  
                y.append(int(partes[1]))  
    
    # Crear el gráfico
    plt.plot(x, y, marker='o', linestyle='-', color='b', label='TIEMPO VS CONSULTAS DE BU')
    
    plt.title('CONSULTAS VS TIEMPO DE BOTTOM UP')
    plt.xlabel('N CONSULTAS')
    plt.ylabel('TIEMPO')
    plt.grid(True)

    plt.show()


def graficar_datos_fb_vs_bu():
    x_fb = []
    y_fb = []
    x_bu = []
    y_bu = []
    
    with open('tiempos_fuerza_bruta.txt', 'r') as archivo:
        for linea in archivo:
            partes = linea.split()
            if len(partes) == 2:  
                x_fb.append(int(partes[0]))
                y_fb.append(int(partes[1]))
    
    with open('tiempos_bottom_up.txt', 'r') as archivo:
        for linea in archivo:
            partes = linea.split()
            if len(partes) == 2:  
                x_bu.append(int(partes[0]))
                y_bu.append(int(partes[1]))
    
    # Graficar datos de fuerza bruta
    plt.plot(x_fb, y_fb, marker='o', linestyle='-', color='r', label='Fuerza Bruta')
    
    # Graficar datos de bottom-up
    plt.plot(x_bu, y_bu, marker='o', linestyle='-', color='b', label='Bottom-Up')
    
    plt.title('Comparación de Tiempos: Fuerza Bruta vs Bottom-Up')
    plt.xlabel('N Consultas')
    plt.ylabel('Tiempo')
    plt.grid(True)
    
    plt.show()


def main():
    graficar_datos_fb()
    graficar_datos_bu()
    graficar_datos_fb_vs_bu()

main()
