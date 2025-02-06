#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define N 1

// PROTOTIPOS DE FUNCIONES
void generar_cuadros_aleatorios(int (*)[3]);
void swap(int *, int*);
int partition(int (*)[3], int, int);
void quicksort(int (*)[3], int, int);
int maximo(int , int );
void combinar_contornos(int (*)[2], int, int (*)[2], int, int (*)[2], int *);
void dividir_y_conquistar_contorno(int (*)[3], int, int, int (*)[2], int *,unsigned long long *);
void tabla_dv(unsigned long long, int);
void grafica_dv();

int main() {
    // Variables de registro de datos
    int medicion_datos_tabla =1;
  
    // Variables de divide y venceras
    int rectangulos[N][3];
    unsigned long long tiempo_dv;
    /*
    for(int i=0;i<3;i++){
	    // Imprimir coordenadas generadas
	    printf("\nCOORDENADAS DE LOS RECTANGULOS\n");
	    generar_cuadros_aleatorios(rectangulos);
	
	    // Arreglo para almacenar el contorno
	    int contorno[2 * (N - 1)][2]; // El contorno tendrá a lo sumo 2 * (n - 1) puntos
	    int tam_contorno = 0;
	
	    // Ordenar los rectángulos por su coordenada izquierda
	    quicksort(rectangulos, 0, N - 1);
	
	    // Calcular el contorno usando el algoritmo de divide y vencerás
	    dividir_y_conquistar_contorno(rectangulos, 0, N - 1, contorno, &tam_contorno,&tiempo_dv);
	    // Imprimir el contorno
	    printf("\n\nCOORDENADAS DE LA FRANJA\n");
	    for (int i = 0; i < tam_contorno; i++) {
	        printf("(%d, %d) ", contorno[i][0], contorno[i][1]);
	    }
	    
	    // Imprimir el tiempo de ejecución
	    printf("\nEn un tiempo de %llu nanosegundos para DV\n\n", tiempo_dv);
		
		//Obtencion de datos en fichero
		tabla_dv(tiempo_dv,medicion_datos_tabla);
	}*/
	
	//Impresion de DV
	grafica_dv();
    return 0;
}

// GENERAR RECTANGULOS ALEATORIOS
void generar_cuadros_aleatorios(int (*rectangulos)[3]) {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        rectangulos[i][0] = rand() % 115; 
        rectangulos[i][1] = rand() % 115;
        rectangulos[i][2] = rand() % 115;
        while (rectangulos[i][2] <= rectangulos[i][0]) {
            rectangulos[i][2] = rand() % 115;
        }
    }

    // Imprimir coordenadas generadas
    for (int i = 0; i < N; i++) {
        printf("(%d,%d,%d)\n", rectangulos[i][0], rectangulos[i][1], rectangulos[i][2]);
    }
}

//PROCESO DE ORDENAMIENTO CON QUICK SORT DE LAS X DE LA IZQUIERDA
void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int (*rectangulos)[3], int low, int high) {
    int pivot = rectangulos[high][0];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (rectangulos[j][0] <= pivot) {
            i++;
            swap(&rectangulos[i][0], &rectangulos[j][0]);
            swap(&rectangulos[i][1], &rectangulos[j][1]);
            swap(&rectangulos[i][2], &rectangulos[j][2]);
        }
    }

    swap(&rectangulos[i + 1][0], &rectangulos[high][0]);
    swap(&rectangulos[i + 1][1], &rectangulos[high][1]);
    swap(&rectangulos[i + 1][2], &rectangulos[high][2]);

    return i + 1;
}

void quicksort(int (*rectangulos)[3], int low, int high) {
    if (low <= high) {
        int pivotindex = partition(rectangulos, low, high);

        quicksort(rectangulos, low, pivotindex - 1);
        quicksort(rectangulos, pivotindex + 1, high);
    }
}


//ALGORITMO DE DIVIDE Y VENCERAS
// Encontrar el máximo entre dos enteros
int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// Combinar contornos izquierdo y derecho
void combinar_contornos(int (*contorno_izquierdo)[2], int tam_izquierdo, int (*contorno_derecho)[2], int tam_derecho, int (*resultado)[2], int *tam_resultado) {
    int altura_izquierda = 0, altura_derecha = 0;
    int i = 0, j = 0;
    int x = 0, altura = 0;

    while (i < tam_izquierdo && j < tam_derecho) {
        if (contorno_izquierdo[i][0] < contorno_derecho[j][0]) {
            x = contorno_izquierdo[i][0];
            altura_izquierda = contorno_izquierdo[i][1];
            altura = maximo(altura_izquierda, altura_derecha);
            i++;
        } else {
            x = contorno_derecho[j][0];
            altura_derecha = contorno_derecho[j][1];
            altura = maximo(altura_izquierda, altura_derecha);
            j++;
        }

        if (*tam_resultado == 0 || altura != resultado[*tam_resultado - 1][1]) {
            resultado[*tam_resultado][0] = x;
            resultado[*tam_resultado][1] = altura;
            (*tam_resultado)++;
        }
    }

    while (i < tam_izquierdo) {
        resultado[*tam_resultado][0] = contorno_izquierdo[i][0];
        resultado[*tam_resultado][1] = contorno_izquierdo[i][1];
        (*tam_resultado)++;
        i++;
    }
    while (j < tam_derecho) {
        resultado[*tam_resultado][0] = contorno_derecho[j][0];
        resultado[*tam_resultado][1] = contorno_derecho[j][1];
        (*tam_resultado)++;
        j++;
    }
}

void dividir_y_conquistar_contorno(int (*rectangulos)[3], int inicio, int fin, int (*resultado)[2], int *tam_resultado, unsigned long long *tiempo_dv) {
    // Variables para tomar el tiempo
    static unsigned long pre_time0;
    static unsigned long pre_secs0;
    struct timespec ts0;

    // Inicio de la toma de tiempo
    clock_gettime(CLOCK_MONOTONIC, &ts0);
    pre_time0=ts0.tv_nsec;
    pre_secs0=ts0.tv_sec;

    if (inicio == fin) {
        resultado[*tam_resultado][0] = rectangulos[inicio][0];
        resultado[*tam_resultado][1] = rectangulos[inicio][1];
        (*tam_resultado)++;
        resultado[*tam_resultado][0] = rectangulos[inicio][2];
        resultado[*tam_resultado][1] = 0;
        (*tam_resultado)++;
    } else if (inicio < fin) {
        int medio = (inicio + fin) / 2;

        int contorno_izquierdo[2 * (fin - inicio + 1)][2];
        int tam_izquierdo = 0;
        int contorno_derecho[2 * (fin - inicio + 1)][2];
        int tam_derecho = 0;

        dividir_y_conquistar_contorno(rectangulos, inicio, medio, contorno_izquierdo, &tam_izquierdo, tiempo_dv);
        dividir_y_conquistar_contorno(rectangulos, medio + 1, fin, contorno_derecho, &tam_derecho, tiempo_dv);

        combinar_contornos(contorno_izquierdo, tam_izquierdo, contorno_derecho, tam_derecho, resultado, tam_resultado);
    }

    // Fin de la toma de tiempo
    clock_gettime(CLOCK_MONOTONIC, &ts0);
    *tiempo_dv = (ts0.tv_sec - pre_secs0) * 1000000000 + (ts0.tv_nsec - pre_time0);
}

//GENERAR FICHERO CON DATOS DE DV
void tabla_dv(unsigned long long tiempo_dv,int medicion_datos_tabla){
	FILE *f;
	f=fopen("tabla_dv.txt","a");
	if(f==NULL){
		printf("ERROR AL ABRIR EL ARCHIVO\n");
	}
	else{
		fprintf(f,"%d %llu\n",medicion_datos_tabla,tiempo_dv);
		fclose(f);
		printf("\n;) VALORES DE FB ASIGNADOS CORRECTAMENTE\n\n");
	}
}

//IMPRESION GRAFICA DV
void grafica_dv() {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "set title 'Gráfica de datos DV'\n");
        fprintf(gnuplotPipe, "set xlabel 'Número de puntos'\n");
        fprintf(gnuplotPipe, "set ylabel 'Tiempo'\n");

        fprintf(gnuplotPipe, "plot 'tabla_dv.txt' using 1:2 title 'Datos' with linespoints linestyle 5\n");

        fclose(gnuplotPipe);
    } else {
        printf("Error opening Gnuplot pipe!\n");
    }
}





