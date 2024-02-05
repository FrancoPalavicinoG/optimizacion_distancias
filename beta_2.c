#include <stdio.h>
#include <string.h>
#include <math.h>


int main(void) {
    FILE* equipos;
    FILE* salida;
    char linea[999];
    char equipo[999][999];
    double x[999], y[999];
    equipos = fopen("equipos.txt", "r");
    salida = fopen("salida.txt", "w");
    
    int ctr = 0;
    while (fgets(linea, sizeof(linea), equipos)) {
        //"%[^,] lee todos los caracteres hasta que llegue a una coma: https://stackoverflow.com/questions/39431924/what-does-n-mean-in-c 
        sscanf(linea,"%[^,],%lf,%lf", equipo[ctr], &x[ctr], &y[ctr]);
        ctr++;
    }
    fclose(equipos);

    int matriz_equipos[999][999] = {0};
    int distancias[ctr][2];
    int d;
    int index = 0;
    int ctr_fila[999] = {0};
    for (int i = 0; i < ctr; i++) {
        for (int j = 0; j < ctr; j++) {
            if (i != j) {
                d = sqrt(pow(x[j]-x[i], 2) + pow(y[j]-y[i], 2));
                distancias[index][0] = d; //distancia [0]
                distancias[index][1] = j; //indice de la distancia [1]
                index++;
            }
        }
        //Algoritmo bubble sort, para ordenar de menor a mayor: https://stackoverflow.com/questions/17655748/bubble-sort-algorithm-in-c
        int index2 = index -1;
        for (int k = 0; k < index2; k++) {
            for (int l = 0; l < index2-k; l++) {
                if (distancias[l][0] > distancias[l+1][0]) {
                    int tmp_dist = distancias[l][0];
                    int tmp_index = distancias[l][1];
                    distancias[l][0] = distancias[l+1][0];
                    distancias[l][1] = distancias[l+1][1];
                    distancias[l+1][0] = tmp_dist;
                    distancias[l+1][1] = tmp_index;
                }
            }
        }
        for (int m = 0; m < 4; m++) {
            int rival_dist = distancias[m][0];
            int rival_index = distancias[m][1];
            if(ctr_fila[rival_index] < 4){
                if (matriz_equipos[i][rival_index] == 0){
                    if (matriz_equipos[rival_index][i] == 0){
                        matriz_equipos[i][rival_index] = 1; 
                        matriz_equipos[rival_index][i] = 1; 
                        ctr_fila[rival_index]++;
                        ctr_fila[i]++;
                    }
                }
            }
        }
        for (int i = 0; i < ctr; i++) {
            for (int j = 0; j < ctr; j++) {
                if (i != j ){
                    if (ctr_fila[i] < 4){
                        if (ctr_fila[j] < 4){ 
                            if (matriz_equipos[i][j] == 0){
                                if (matriz_equipos[j][i] == 0){
                                    matriz_equipos[i][j] = 1;
                                    matriz_equipos[j][i] = 1;
                                    ctr_fila[i]++;
                                    ctr_fila[j]++;
                                }
                            }
                        }
                    }
                }
            }
        }
        index = 0;
    }

    printf("\n");
    for (int i = 0; i < ctr; i++){
        char unir[9999] = "";
        for (int j = 0; j < ctr; j++){
            if (i != j){
                if (matriz_equipos[i][j] == 1){
                    if (matriz_equipos[j][i] == 1){
                        strcat(unir, equipo[j]);
                        strcat(unir, ", ");
                    }
                }
            }
        }
        fprintf(salida, "%s, %s\n", equipo[i], unir);
    }
    fclose(salida); 
    return 0;
}
