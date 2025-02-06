#include <stdio.h>


void grafica_fb_dv();

int main(){
	grafica_fb_dv();
	
}

void grafica_fb_dv() {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    fprintf(gnuplotPipe, "set title 'Gr�fica de datos FB y DV'\n");
    fprintf(gnuplotPipe, "set xlabel 'N�mero de puntos'\n");
    fprintf(gnuplotPipe, "set ylabel 'Tiempo'\n");
    
    // Graficar datos de FB, ajuste cuadr�tico, datos de DV y ajuste lineal y cuadr�tico
    fprintf(gnuplotPipe,"plot \
        'tabla_fb.txt' using 1:2 title 'Datos en FB' with linespoints linestyle 3,\
        'tabla_dv.txt' using 1:2 title 'Datos en DV' with linespoints linestyle 5,\n");
    fclose(gnuplotPipe);
}
