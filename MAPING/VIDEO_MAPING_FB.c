#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define N 1

//PROTOTIPOS DE FUNCIONES
void generar_cuadros_aleatorios(int **);
void swap(int *, int *);
int partition(int **,int,int);
void quicksort(int **, int, int);
void fb(int **,unsigned long long *);
void tabla_fb(unsigned long long,int);
void grafica_fb();

int main() {
	//VARIABLES REGISTRO DE DATOS
	int medicion_datos_tabla=1;
	
    // VARIABLES PARA FUERZA BRUTA
    int **coordenadas_cuadros;
    unsigned long long tiempo_fb;
 
    
    //for(int i=0;i<3;i++){//Ciclo que itera para repetir y guardar en el fichero
	
	    // Reservar memoria para coordenadas_cuadros
	    coordenadas_cuadros = (int **)malloc(N * sizeof(int *));
	    for (int i = 0; i < N; i++) {
	        coordenadas_cuadros[i] = (int *)malloc(3 * sizeof(int));
	    }
	    
	    //Funcion de generar aletorios
	    printf("COORDENADAS DE LOS RECTANGULOS\n");
	    generar_cuadros_aleatorios(coordenadas_cuadros);
	    
	    //Funcion de ordenamiento para las x de la izquierda
	    quicksort(coordenadas_cuadros,0,N-1);
	    
	    //Comprobacion del ordenamiento
	    printf("\nCOORDENADAS ORDENADAS POR SU X DE LA IZQUIERDA\n");
	    for(int i=0;i<N;i++){
	    	printf("(%d,%d,%d) ",coordenadas_cuadros[i][0],coordenadas_cuadros[i][1],coordenadas_cuadros[i][2]);
		}
		
		//Coordenadas resultantes
		printf("\n\nCOORDENADAS DE LA FRANJA\n");
		fb(coordenadas_cuadros,&tiempo_fb);

	    // Liberar memoria asignada
	    for (int i = 0; i < N; i++) {
	        free(coordenadas_cuadros[i]);
	    }
	    free(coordenadas_cuadros);
	    
	    // Resultados de tiempo 
	    printf("En un tiempo de %llu nanosegundos para FB\n\n",tiempo_fb);
	    
	    //Obtencion de datos en ficheros
	    //tabla_fb(tiempo_fb,medicion_datos_tabla);
	//}
	
	//Gráfica de fb
	//grafica_fb();
    return 0;
}


// GENERA RECTANGULOS ALETORIOS
void generar_cuadros_aleatorios(int **coordenadas_cuadros) {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
    	/*printf("\ningresa la coordenada x izq:\n ");
    	scanf("%d",&coordenadas_cuadros[i][0]);
    	printf("\ningresa la altura:\n ");
    	scanf("%d",&coordenadas_cuadros[i][1]);
    	printf("\ningresa la coordenada x der:\n ");
    	scanf("%d",&coordenadas_cuadros[i][2]);*/
        coordenadas_cuadros[i][0] = rand() % 100; 
        coordenadas_cuadros[i][1] = rand() % 100;
        coordenadas_cuadros[i][2] = rand() % 100;
        while(coordenadas_cuadros[i][2]<=coordenadas_cuadros[i][0]){
        	coordenadas_cuadros[i][2] = rand() % 100;
			/*printf("\ningresa la coordenada x der:\n ");
    		scanf("%d",&coordenadas_cuadros[i][2]); */
		}
    }

    // Imprimir coordenadas generadas
    for(int i = 0; i < N; i++) {
        printf("(%d,%d,%d)\n", coordenadas_cuadros[i][0], coordenadas_cuadros[i][1], coordenadas_cuadros[i][2]);
    }
}


//PROCESO DE ORDENAMIENTO CON QUICK SORT DE LAS X DE LA IZQUIERDA
void swap (int *a, int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

int partition(int **coordenadas_cuadros,int low, int high){
	//Indicamos que el pivote es el ultimo elemento
	int pivot=coordenadas_cuadros[high][0];
	//Indica el elmento mas pequeño (que aun no se ha encontrado)
	int i=low-1;
	//Ciclo que recorre uno antes del pivote
	for(int j=low;j<high;j++){
		if (coordenadas_cuadros[j][0]<=pivot){
			//incrementa el indice del elemento mas pequeño
			i++;
			//hace el intercambio para pasar todos los menores del pivote al lado izquierdo
			swap(&coordenadas_cuadros[i][0],&coordenadas_cuadros[j][0]);
			swap(&coordenadas_cuadros[i][1],&coordenadas_cuadros[j][1]);
			swap(&coordenadas_cuadros[i][2],&coordenadas_cuadros[j][2]);
		}
	}
	
	//Colocamos el pivote en la posicion correcta
	swap(&coordenadas_cuadros[i+1][0],&coordenadas_cuadros[high][0]);
	swap(&coordenadas_cuadros[i+1][1],&coordenadas_cuadros[high][1]);
	swap(&coordenadas_cuadros[i+1][2],&coordenadas_cuadros[high][2]);
	
	//retorna la posicion del pivote
	return i+1;
}

void quicksort(int **coordenadas_cuadros, int low, int high){
	if(low<=high){
		
		//encontrar el indice dle pivote
		int pivotindex=partition(coordenadas_cuadros,low,high);
		
		quicksort(coordenadas_cuadros,low,pivotindex-1);//ordena subarreglo derecha
		quicksort(coordenadas_cuadros,pivotindex+1,high);//ordena sub arreglo izquierda
	}
	
}

//ALGORITMO DE FUERZA BRUTA
void fb(int **coordenadas_cuadros, unsigned long long *tiempo_fb) {
    //Variables para tomar el tiempo
    static unsigned long pre_time0;
	static unsigned long pre_secs0;
	struct timespec ts0; 
	
	// Encontrar el punto más a la derecha en todas las coordenadas
    int maxX = 0; // Inicializa la variable que almacenará el valor máximo de la coordenada X derecha
    clock_gettime(CLOCK_MONOTONIC,&ts0);//Inicio d ela toma de tiempo
	pre_time0=ts0.tv_nsec;
    pre_secs0=ts0.tv_sec;
	for (int i = 0; i < N; i++) { // Itera sobre todas las coordenadas
        if (coordenadas_cuadros[i][2] > maxX) { // Comprueba si la coordenada X derecha actual es mayor que maxX
            maxX = coordenadas_cuadros[i][2]; // Actualiza maxX si la coordenada X derecha actual es mayor
        }
    }

    // Definir un arreglo para almacenar las alturas para cada punto en el eje X
    int alturas[maxX + 1]; // Declara un arreglo para almacenar las alturas de cada punto en el eje X, el tamaño se ajusta al valor máximo de la coordenada X derecha
    for (int i = 0; i <= maxX; i++) { // Itera sobre todos los puntos en el eje X
        alturas[i] = 0; // Inicializa todas las alturas en cero
    }

    // Rellenar el arreglo de alturas con las alturas de las coordenadas
    for (int i = 0; i < N; i++) { // Itera sobre todas las coordenadas
        for (int j = coordenadas_cuadros[i][0]; j < coordenadas_cuadros[i][2]; j++) { // Itera sobre todos los puntos en el rango de la coordenada X izquierda a la coordenada X derecha de la coordenada actual
            if (coordenadas_cuadros[i][1] > alturas[j]) { // Comprueba si la altura de la coordenada actual es mayor que la altura almacenada en el punto j en el arreglo alturas
                alturas[j] = coordenadas_cuadros[i][1]; // Actualiza la altura almacenada en el punto j si la altura de la coordenada actual es mayor
            }
        }
    }

    // Imprimir el contorno de la franja
    int prev_altura = 0; // Inicializa una variable para almacenar la altura previa
    for (int i = 0; i <= maxX; i++) { // Itera sobre todos los puntos en el eje X
        if (alturas[i] != prev_altura) { // Comprueba si la altura en el punto actual es diferente a la altura previa
            printf("(%d, %d) ", i, alturas[i]); // Imprime el punto del contorno si la altura es diferente a la anterior
            prev_altura = alturas[i]; // Actualiza la altura previa
        }
    }
   	clock_gettime(CLOCK_MONOTONIC,&ts0);
   	*tiempo_fb=(ts0.tv_sec-pre_secs0)*1000000000+ts0.tv_nsec-pre_time0;//Fin de la toma de tiempo
    printf("\n"); // Imprime una nueva línea al final del contorno
}


//GENERAR FICHERO CON DATOS DE TIEMPO DE FUERZA BRUTA
void tabla_fb(unsigned long long tiempo_fb,int medicion_datos_tabla){
	FILE *f;
	f=fopen("tabla_fb.txt","a");
	if (f==NULL){
		printf("ERROR AL ABRIR EL ARCHIVO\n");
	}
	else{
		fprintf(f,"%d %llu\n",medicion_datos_tabla,tiempo_fb);
		fclose(f);
		printf("\n\n;) VALORES DE FB ASIGNADOS CORRECTAMENTE\n\n");
	}
}

//IMPRESION GRAFICA FB
void grafica_fb() {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "set title 'Gráfica de datos FB'\n");
        fprintf(gnuplotPipe, "set xlabel 'Número de puntos'\n");
        fprintf(gnuplotPipe, "set ylabel 'Tiempo'\n");

        fprintf(gnuplotPipe, "plot 'tabla_fb.txt' using 1:2 title 'Datos' with linespoints linestyle 3\n");

        fclose(gnuplotPipe);
    } else {
        printf("Error opening Gnuplot pipe!\n");
    }
}


