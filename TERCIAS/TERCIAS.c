//MIGUEL ALEJANDRO FLORES SOTELO, JUAN CARLOS FLORES MORA, SERGIO DE JESUS CASTILLO MOLANO
//09/04/24
//TERCIAS
//ESTE PROGRAMA SE ENCARGA DE CONTAR LAS TERCIAS CON SECUENCIA NUMERICA

#include <stdio.h>
#include <stdlib.h>
#define MAX_LINEA 7000
int busqBin(int A[],int inicio,int fin,int vB){
    while(inicio<=fin){
        int mid=inicio+(fin-inicio)/2;
        if(A[mid]==vB){ //si el valor es mid
            return mid;
        }
        else if(vB>A[mid]) //buscar del lado derecho
            inicio=mid+1;
        else
            fin=mid-1; //buscar lado izquierdo
    }
    return -1;
}



int main() {
    char linea[11];
    int index=0, limit,tercias=0;
    int *n;
    FILE *f;

    f = fopen("tercias10.in", "r");
    if (f == NULL) {
        printf("\nERROR AL ABRIR EL ARCHIVO\n");
        return 1;
    }


    fgets(linea, MAX_LINEA, f);  // Leer el límite de números
    limit = atoi(linea);


    n = (int*)malloc(limit * sizeof(int));


    while (fgets(linea, MAX_LINEA, f) && index < limit) { // leer los nUmeros del archivo y almacenarlos en el arreglo
        n[index] = atoi(linea);
        index++;
    }
    fclose(f);
    for(int i=0;i<limit-1;i++){
        for(int j=i+1;j<limit;j++){
            int aux=n[j]+(n[j]-n[i]);
            if (aux>n[limit-1]){
                break;
            }
            else{
                if(busqBin(n,j+1,limit-1,aux)>=0){
                tercias++;
                }
            }
        }
    }
        printf("\nExisten %d tercias",tercias);



    free(n);//liberar memoria asignada

    return 0;
}

