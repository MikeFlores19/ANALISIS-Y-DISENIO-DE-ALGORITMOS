#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#define N 52
#define GRADO_POLINOMIO 2

void generar_aleatorios_fb_dv(float **);
void ordenamiento(float **,int, int);
float par_cercano(float **,int, unsigned long long *,unsigned long long *);
void tabla_fb(unsigned long long,int);
void tabla_dv(unsigned long long,int);
void tabla_umbral(unsigned long long, unsigned long long, int);
void ajuste_fb(double *, double *, double *);
void ajuste_dv(double *, double *);
void grafica_fb();
void grafica_dv();
void grafica_umbral();
void grafica_fb_dv_umbral(); 

int main(){
	//VARIABLE COMPARTIDA PARA EL REGISTRO DE N DATOS EN LOS FICHEROS
	 int medicion_datos_tabla=52;
	 
	//VARIABLES FUERZA BRUTA
    unsigned long long tiempo_fb;
    double a_fb,b_fb,c_fb;
   
    
    //VARIABLES DIVIDE Y VENCERAS
    float **coordenadas_dv;// divide y venceras
    float distance;
    unsigned long long tiempo_dv;
    struct timespec ts;
	double m_dv,b_dv;
	
	
	//ITERACION PARA OBTENER DIVERSOS DATOS A LA VEZ
   
	for(int i=0;i<3;i++){
		//EJECUCION DE DIVIDE Y VENCERAS Y FUERZA BRUTA
		coordenadas_dv=(float **) malloc (sizeof (float*)*N); //memoria dinamica para divide y venceras
    	for (int i = 0; i < N; i++) {
        coordenadas_dv[i] = (float *)malloc(2 * sizeof(float*));// incializar todo a 0
    	}
		generar_aleatorios_fb_dv(coordenadas_dv);
		printf("\nCOORDENADAS PARA DIVIDE Y VENCERAS Y FUERZA BRUTA\n");
		for(int i=0;i<N;i++){
			printf("%.2f,%.2f\n",coordenadas_dv[i][0],coordenadas_dv[i][1]);
		}
		//printf("\nCoordenadas ordenadas en x\n");
		ordenamiento(coordenadas_dv,N,0);//Se ordena el arreglo en base a las coordenadas x, de menor a mayor
	    /*for (int i = 0; i < N; i++) {
	        printf("[%.2f, %.2f]\n ", coordenadas_dv[i][0], coordenadas_dv[i][1]);
	    }*/
	    distance = par_cercano(coordenadas_dv, N,&tiempo_dv,&tiempo_fb);
	    //Liberación de memoria
	    for (int i = 0; i < N; i++) {
	        free(coordenadas_dv[i]);
	    }
	    free(coordenadas_dv);
	    
	    
	    //RESULTADOS FUERZA BRUTA, DIVIDE Y VENCERAS
	    //printf("Distancia mas corta de %.2f y en un tiempo de %llu nanosegundos para FB\n",distance,tiempo_fb);
	    printf("\nDistancia mas corta de %.2f en un tiempo de %llu nanosegundos para DV", distance,tiempo_dv);
		
		
		//OBTENCION DE DATOS EN FICHEROS FB, DV
		//tabla_fb(tiempo_fb,medicion_datos_tabla);
		//tabla_dv(tiempo_dv,medicion_datos_tabla);
		tabla_umbral(tiempo_fb,tiempo_dv,medicion_datos_tabla);
	}
	
	
	//ajuste_fb(&a_fb, &b_fb, &c_fb);
	//ajuste_dv(&m_dv, &b_dv);
	

    grafica_fb();
    grafica_dv();
    grafica_umbral();
    grafica_fb_dv_umbral();

    return 0;
}

//GENERAR NUMEROS ALEATORIOS PARA FUERZA BRUTA Y  DIVIDE Y VENCERAS
void generar_aleatorios_fb_dv(float **coordenadas_dv){
    srand(time(NULL));
    for(int i=0;i<N;i++){
        coordenadas_dv[i][0] = ((float)rand() / RAND_MAX)*100;
        coordenadas_dv[i][1] = ((float)rand() / RAND_MAX)*100;
    }
}


//ALGORITMO DIVIDE Y VENCERAS
void ordenamiento(float **arreglo, int tamanio, int coord){
    if(tamanio<2)
        return;
    //Contadores para los ciclos posteriores
    int j=0,k=0,l=0;
    //Tamaños para el arreglo de izquierda y el de derecha
    int mitad=tamanio/2;
    int mitad2=tamanio-mitad;
    //Genera los arreglos
    float **izquierda, **derecha;
    izquierda= (float **)malloc(sizeof(float*)*mitad);
    derecha= (float **)malloc(sizeof(float*)*mitad2);
    for (int i=0;i<mitad;i++) {
        izquierda[i]=(float *)malloc(2*sizeof(float));
    }
    for (int i=0;i<mitad2;i++) {
        derecha[i]=(float *)malloc(2*sizeof(float));
    }
    // Divide el arreglo en 2 mitades
    for(int i=0; i<mitad; i++) {
        izquierda[i][0] = arreglo[i][0];
        izquierda[i][1] = arreglo[i][1];
    }
    for(int i=mitad;i<tamanio;i++) {
        derecha[i-mitad][0] = arreglo[i][0];
        derecha[i-mitad][1] = arreglo[i][1];
    }
    //Ordena recursivamente
    ordenamiento(izquierda, mitad,coord);
    ordenamiento(derecha,tamanio - mitad,coord);

    // Une las dos mitades mientras se ordenan ascendentemente
    while (l < mitad && j < mitad2) {
        if (izquierda[l][coord] <= derecha[j][coord]) {
            arreglo[k][0] = izquierda[l][0];
            arreglo[k][1] = izquierda[l][1];
            k++;
            l++;
        } else {
            arreglo[k][0] = derecha[j][0];
            arreglo[k][1] = derecha[j][1];
            k++;
            j++;
        }
    }

    // Pone los elementos restantes de la primera mitad
    while (l < mitad) {
        arreglo[k][0] = izquierda[l][0];
        arreglo[k][1] = izquierda[l][1];
        k++;
        l++;
    }

    // Pone los elementos restantes de la segunda mitad
    while (j < mitad2) {
        arreglo[k][0] = derecha[j][0];
        arreglo[k][1] = derecha[j][1];
        k++;
        j++;
    }
    //Liberación de memoria
    for (int i=0;i<mitad;i++){
        free(izquierda[i]);
    }
    for (int i=0;i<mitad2;i++){
        free(derecha[i]);
    }
    free(izquierda);
    free(derecha);
}

float par_cercano(float **coord,int num,unsigned long long *tiempo_dv,unsigned long long *tiempo_fb){
    float **arreglo_y;
    int j=0;
    float x_medio;
    float distancia,distancia1=0,distancia2=0;
    static unsigned long pre_time0;//VARIABLES PARA LA TOMA DE TIEMPO DE FB
    static unsigned long pre_secs0;
    struct timespec ts0;
    static unsigned long pre_time1;// VARIABLES PARA LA TOMA DE TIEMPO DE DV (1)
    static unsigned long pre_secs1;
    struct timespec ts1;
    
    //Caso base, cuando n<=umbral y utiliza el algoritmo de FUERZA BRUTA
    //2 puede cambiarse por el umbral necesario en la primera condición
    if (num<=38){// PARA EL UMBRAL
    	//Inicio de medición 
        if(num>=2){//SI ES MAYOR O IGUAL A DOS SI TIENE CASO HACER LA MEDICION SINO ENTONCES RETORNA -1
        	clock_gettime(CLOCK_MONOTONIC,&ts0);
        	pre_time0=ts0.tv_nsec;
        	pre_secs0=ts0.tv_sec;
			float distancia_temp,x1,x2,y1,y2;
			float distancia_minima=999999;
			for(int i=0;i<num;i++){
		        for(int k=i+1;k<num;k++){
		            distancia_temp=sqrt(pow(coord[k][0]-coord[i][0],2) + pow(coord[k][1]- coord[i][1],2));
		            if(distancia_temp<distancia_minima){
		                distancia_minima=distancia_temp;
		            	x1=coord[i][0];
		                x2=coord[k][0];
		                y1=coord[i][1];
		                y2= coord[k][1];
		            }
		        }
		    }
		    clock_gettime(CLOCK_MONOTONIC,&ts0);
		    *tiempo_fb=(ts0.tv_sec-pre_secs0)*1000000000+ts0.tv_nsec-pre_time0;
			return distancia_minima;
            free(tiempo_fb);
        }
		else{
            return -1;
        }
    }
    
    //Línea L
    clock_gettime(CLOCK_MONOTONIC,&ts1); //Inicio del tiempo para el algoritmo DV1
	pre_time1=ts1.tv_nsec;
	pre_secs1=ts1.tv_sec;
    int mitad=num/2;
    x_medio=coord[mitad][0];
    
	//Divide y vencerás
    distancia1=par_cercano(coord,mitad,tiempo_dv,tiempo_fb);
    distancia2=par_cercano(coord+mitad,num-mitad,tiempo_dv,tiempo_fb);
    
    //Mínimo(d1,d2)
    if(distancia1==-1){
        distancia=distancia2;
    }else if(distancia2==-1){
        distancia=distancia1;
    }else if(distancia1<distancia2){
        distancia=distancia1;
    }else{
        distancia=distancia2;
    }
    //Eliminación de puntos lejos de L a una distancia delta
    arreglo_y= (float **)malloc(sizeof(float *)*num);
    for (int i=0;i<num;i++) {	
        arreglo_y[i]=(float *)malloc(2*sizeof(float*));
    }
    for(int i=0; i<num; i++){
        if((abs(coord[i][0]-x_medio))<distancia){
            arreglo_y[j][0]=coord[i][0];
            arreglo_y[j][1]=coord[i][1];
            j++;
        }
    }
    arreglo_y=(float **)realloc(arreglo_y,sizeof(float *)*j);
    for (int i=0;i<j;i++) {
        arreglo_y[i]=(float *)realloc(arreglo_y[i],2*sizeof(float));
    }
    //Ordenamiento y
    ordenamiento(arreglo_y,j,1);
    /*printf("\nCoordenadas y\n ");
    for (int i=0;i<j;i++){
        printf("[%d,%d]\n ", arreglo_y[i][0],arreglo_y[i][1]);
    }*/

    //Encuentra la distancia entre los dos puntos cercanos de en medio si es mas pequeño lo remplaza por la distancia minima izquierda o derecha
    for(int i=0;i<j;i++){
        for(int k=i+1;k<j;k++){
            float dist=sqrt(pow(arreglo_y[i][0]-arreglo_y[k][0],2)+pow(arreglo_y[i][1]-arreglo_y[k][1],2));
            if (dist<distancia){
                distancia=dist;
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC,&ts1);
    *tiempo_dv=(ts1.tv_sec-pre_secs1)*1000000000+ts1.tv_nsec-pre_time1;//Termino de tiempo para algoritmo DV
    
    for (int i=0;i<j;i++) {
        free(arreglo_y[i]);
    }
    free(arreglo_y);
    return distancia;
    free(tiempo_dv);
}

//GENERAR FICHERO CON DATOS DE FUERZA BRUTA
void tabla_fb(unsigned long long tiempo_fb,int medicion_datos_tabla){
	FILE *f;
	f=fopen("tabla_fb_nuevo.txt","a");
	if(f==NULL){
		printf("ERROR AL ABRIR EL ARCHIVO\n");
	}
	else{
		fprintf(f,"%d %llu\n",medicion_datos_tabla,tiempo_fb);
		fclose(f);
		printf("\n\n:) VALORES DE FB ASIGNADOS CORRECTAMENTE\n");
	}
}

//GENERAR FIHCERO CON DATOS DIVIDE Y VENCERAS
void tabla_dv(unsigned long long tiempo_dv,int medicion_datos_tabla){
	FILE *f;
	f=fopen("tabla_dv_nuevo.txt","a");
	if(f==NULL){
		printf("ERROR AL ABRIR EL ARCHIVO\n");
	}
	else{
		fprintf(f,"%d %llu\n",medicion_datos_tabla,tiempo_dv);
		fclose(f);
		printf("\n:) VALORES DE DV ASIGNADOS CORRECTAMENTE\n\n");
	}
}

void tabla_umbral(unsigned long long tiempo_fb,unsigned long long tiempo_dv,int medicion_datos_tabla){
	FILE *f;
	f=fopen("tabla_umbral_nuevo.txt","a");
	if(f==NULL){
		printf("ERROR AL ARBIR EL ARCHIVO\n");
	}
	else{
		fprintf(f,"%d %llu\n",medicion_datos_tabla,tiempo_dv);//el tiempo_fb o tiempo_dv debe ir cambiando con respecto a se cruce el umbral
		fclose(f);
		printf("\n:) VALORES DEL UMBRAL ASIGNADOS CORRECTAMENTE\n\n");
	}
}

//AJUSTE DE LA FUNCION CUADRATICA FB
void ajuste_fb(double *a_fb, double *b_fb, double *c_fb){
	//AJUSTE CUADRATICO
    FILE *archivo;
    float *x, *y;
    int num_muestras = 0;
    int max_muestras = 100; // Tamaño inicial de las matrices

    // Asignar memoria para las matrices
    x = (float *)malloc(max_muestras * sizeof(float));
    y = (float *)malloc(max_muestras * sizeof(float));

    // Verificar si la asignación de memoria fue exitosa
    if (x == NULL || y == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }
    
    // Abrir archivo
    archivo = fopen("tabla_fb_nuevo.txt", "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Leer muestras del archivo
    while (fscanf(archivo, "%f %f", &x[num_muestras], &y[num_muestras]) == 2) {
        num_muestras++;
        // Verificar si se alcanzó el tamaño máximo de las matrices
        if (num_muestras >= max_muestras) {
            max_muestras *= 2; // Duplicar el tamaño de las matrices
            x = (float *)realloc(x, max_muestras * sizeof(float));
            y = (float *)realloc(y, max_muestras * sizeof(float));
            if (x == NULL || y == NULL) {
                printf("Error al asignar memoria.\n");
                return;
            }
        }
    }

    // Cerrar archivo
    fclose(archivo);

    // Calcular coeficientes del polinomio de grado 2
    float matriz_coeficientes[GRADO_POLINOMIO + 1][GRADO_POLINOMIO + 2] = {0};
    for (int i = 0; i < num_muestras; i++) {
        for (int j = 0; j <= GRADO_POLINOMIO; j++) {
            for (int k = 0; k <= GRADO_POLINOMIO; k++) {
                matriz_coeficientes[j][k] += pow(x[i], j + k);
            }
            matriz_coeficientes[j][GRADO_POLINOMIO + 1] += pow(x[i], j) * y[i];
        }
    }

    // Resolver el sistema de ecuaciones
    float coeficientes[GRADO_POLINOMIO + 1] = {0};
    for (int i = 0; i < GRADO_POLINOMIO + 1; i++) {
        for (int j = i + 1; j < GRADO_POLINOMIO + 1; j++) {
            float factor = matriz_coeficientes[j][i] / matriz_coeficientes[i][i];
            for (int k = 0; k <= GRADO_POLINOMIO + 1; k++) {
                matriz_coeficientes[j][k] -= factor * matriz_coeficientes[i][k];
            }
        }
    }
    for (int i = GRADO_POLINOMIO; i >= 0; i--) {
        coeficientes[i] = matriz_coeficientes[i][GRADO_POLINOMIO + 1];
        for (int j = i + 1; j < GRADO_POLINOMIO + 1; j++) {
            coeficientes[i] -= matriz_coeficientes[i][j] * coeficientes[j];
        }
        coeficientes[i] /= matriz_coeficientes[i][i];
    }

    // Imprimir coeficientes
    printf("Ecuacion del ajuste polinomial: h(n) = %.4f + %.4fx + %.4fx^2\n", coeficientes[0], coeficientes[1], coeficientes[2]);

	//Asignar las coeficientes a las variables
	*c_fb=coeficientes[0];
	*b_fb=coeficientes[1];
	*a_fb=coeficientes[2];
	
    // Liberar memoria
    free(x);
    free(y); 
}

//AJUSTE DE LA FUNCION LINEAL DV
void ajuste_dv(double *m_dv, double *b_dv) { 
    int i;
    float sumax = 0, sumay = 0, sumaxy = 0, sumax2 = 0;
    float *x, *y;
    int max_muestras = 100;
    int num_muestras =291; //PUNTOS A EVALUAR
    FILE *archivo;

    x = (float *)malloc(num_muestras * sizeof(float));
	y = (float *)malloc(num_muestras * sizeof(float));

    

    // Verificar si la asignación de memoria fue exitosa
    if (x == NULL || y == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }
    
    // Abrir archivo
    archivo = fopen("tabla_dv_nuevo.txt", "r");
  	
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    
    // Leemos los puntos del archivo
    for (i = 0; i < num_muestras; i++) {
        if (fscanf(archivo, "%f %f", &x[i], &y[i]) != 2) {
            printf("Error al leer los datos del archivo.\n");
            return;
        }
    }

    // Hacemos las sumatorias 
    for (i = 0; i < num_muestras; i++) {
        sumaxy += x[i] * y[i];
        sumax2 += x[i] * x[i];
        sumax += x[i];
        sumay += y[i];
    }

    // Calculamos la pendiente (m) y la interseccion (b)
    *m_dv= (num_muestras * sumaxy - sumax * sumay) / (num_muestras * sumax2 - sumax * sumax);
	*b_dv = (sumay - (*m_dv) * sumax) / num_muestras;


    // Mostramos los valores de la pendiente y de la interseccion
    printf("\n\nPendiente (m) = %f \nIntersección (b) = %f\n\n", *m_dv, *b_dv);
  
    // La fórmula para calcular la variable dependiente (Y) es:
    printf("\n\nValor de la variable dependiente es g(n) = %f*X + %f\n\n", *m_dv, *b_dv);
  
    // Liberamos la memoria asignada para los arreglos
    free(x);
    free(y);
    
    // Cerramos el archivo
    fclose(archivo);
}

//IMPRESION DE GRAFICA FB
void grafica_fb() {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w"); // Abre Gnuplot

    fprintf(gnuplotPipe, "set title 'Gráfica de datos y ajuste cuadrático FB'\n");
    fprintf(gnuplotPipe, "set xlabel 'Número de puntos'\n");
    fprintf(gnuplotPipe, "set ylabel 'Tiempo'\n");
    
    // Ajuste cuadratico
    fprintf(gnuplotPipe, "fit a*x**2 + b*x + c 'tabla_fb_nuevo.txt' via a, b, c\n");
    // Graficar datos y ajuste cuadrático
    fprintf(gnuplotPipe, "plot 'tabla_fb_nuevo.txt' using 1:2 title 'Datos' with linespoints linestyle 15, "
                         "a*x**2 + b*x + c title 'Ajuste cuadrático' with lines linestyle 9\n");

    fclose(gnuplotPipe); // Cierrar Gnuplot
}

//IMPRESION DE GRAFICA DV
void grafica_dv(){
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");//Abrir Gnuplot
    
    fprintf(gnuplotPipe, "set title 'Gráfica de datos y ajuste lineal DV'\n");
    fprintf(gnuplotPipe, "set xlabel 'Número de puntos'\n");
    fprintf(gnuplotPipe, "set ylabel 'Tiempo'\n");
    // Ajuste lineal
    fprintf(gnuplotPipe, "fit m*x+b 'tabla_dv_nuevo.txt' via m, b\n"); 
     // Graficar datos y ajuste lineal
    fprintf(gnuplotPipe, "plot 'tabla_dv_nuevo.txt' using 1:2 title 'Datos' with linespoints linestyle 10, "
                         "m*x + b title 'Ajuste lineal' with lines linestyle 11\n"); 

    fclose(gnuplotPipe);//Cierra Gnuplot
}

//IMPRESION DE GRAFICA CON UMBRAL
void grafica_umbral() {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    
	fprintf(gnuplotPipe, "set title 'Gráfica de datos con umbral'\n");
    fprintf(gnuplotPipe, "set xlabel 'Número de puntos'\n");
    fprintf(gnuplotPipe, "set ylabel 'Tiempo'\n");
    
	fprintf(gnuplotPipe, "plot 'tabla_umbral_nuevo.txt' using 1:2 title 'Datos' with linespoints linestyle 12\n"); // Plot de datos y ajuste

	fclose(gnuplotPipe);

}

//IMPRESION DE LA GRAFICA FB & DV
void grafica_fb_dv_umbral() {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    fprintf(gnuplotPipe, "set title 'Gráfica de datos FB y DV y UMBRAL'\n");
    fprintf(gnuplotPipe, "set xlabel 'Número de puntos'\n");
    fprintf(gnuplotPipe, "set ylabel 'Tiempo'\n");

    // Ajuste cuadrático para los datos de FB
    fprintf(gnuplotPipe, "fit a*x**2+b*x+c 'tabla_fb_nuevo.txt' via a, b, c\n");
    // Ajuste lineal para los datos de DV
    fprintf(gnuplotPipe, "fit m*x+b 'tabla_dv_nuevo.txt' via m, d\n");
    // Graficar datos de FB, ajuste cuadrático, datos de DV y ajuste lineal y cuadrático
    fprintf(gnuplotPipe,"plot \
        'tabla_fb_nuevo.txt' using 1:2 title 'Datos en FB' with linespoints linestyle 1,\
        a*x**2+b*x+c title 'Ajuste cuadrático FB' with lines linestyle 2,\
        'tabla_dv_nuevo.txt' using 1:2 title 'Datos en DV' with linespoints linestyle 3,\
        m*x+b title 'Ajuste lineal DV' with lines linestyle 4,\
		'tabla_umbral_nuevo.txt' using 1:2 title 'Datos con UMBRAL' with linespoints linestyle 5\n");
    fclose(gnuplotPipe);
}





