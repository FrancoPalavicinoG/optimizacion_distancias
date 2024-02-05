
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    FILE* equipos;
    char linea[999];
    char equipo[999][999];
    double x[20], y[20];
    equipos = fopen("equipos.txt", "r");
    
    int ctr = 0;
    while (fgets(linea, sizeof(linea), equipos)) {
        //"%[^,] lee todos los caracteres hasta que llegue a una coma: https://stackoverflow.com/questions/39431924/what-does-n-mean-in-c 
        sscanf(linea,"%[^,],%lf,%lf",equipo[ctr], &x[ctr], &y[ctr]);
        printf("%s %lf %lf\n",equipo[ctr], x[ctr], y[ctr]);
        ctr++;
    }
    printf("\n");
    fclose(equipos);

    int distancias[999];
    int distancia;
    int index = 0;
    for (int i = 0; i < ctr; i++) {
        printf("\nEquipo: %s\n", equipo[i]);
        for (int j = 0; j < ctr; j++) {
            if (i != j) {
                distancia = sqrt(pow(x[j]-x[i], 2) + pow(y[j]-y[i], 2));
                distancias[index] = distancia;
                printf("distancia con %s: %d\n",equipo[j], distancias[index]);
                index++;
            }
        }
    }
    printf("\n");
    // genera que el random sea aleatorio: https://stackoverflow.com/questions/52801380/srandtimenull-function
    srand(time(NULL));
    //combinacion sin repet. del largo de (ctr) sobre 4: https://www.scaler.com/topics/factorial-of-a-number-in-c/
    int comb = tgamma(ctr+1)/(tgamma(5)*tgamma(ctr-3));
    int index2 = 0;
    double distancia_total[comb];
    while (index2 < comb){
        //indice de la cant. de equipos
        int num_equipo[ctr];
        for(int i=0; i<ctr; i++){
            num_equipo[i]=i;
        }
        int len_rival = ctr-1;
        int rivales[len_rival][4];
        for (int i = 0; i < ctr ; i++) {
            //crear el array de rivales, sin el equipo actual
            int comb_equipos[len_rival];
            int n = 0;
            for (int j = 0; j < ctr; j++) {
                if (i != j) {
                    comb_equipos[n] = num_equipo[j];
                    n++;
                }
            }
            //Algoritmo de Fisher-Yates para permutar aleatoriamente: https://www.sanfoundry.com/c-program-implement-fisher-yates-algorithm-array-shuffling/
            for (int k = len_rival-1; k > 0; k--) {
                int l = rand() % (k+1);
                int tmp = comb_equipos[l];
                comb_equipos[l] = comb_equipos[k];
                comb_equipos[k] = tmp;
            }
            //solo hacer append un rival que no se encuentre en la matriz, si se encuentra saltarmelo
            for (int m = 0; m < 4; m++) {
                int rival = comb_equipos[m];
                for(int p=0; p<m; p++){
                    if (rival == rivales[i][p]) {
                        rival = comb_equipos[++m];
                        p = 0;
                    } else {
                        p++;
                    }
                }
                rivales[i][m] = rival;
            }
        }
        double suma = 0.0;
        for (int i = 0; i < ctr; i++) {
            //printf("Equipo %s:\n", equipo[i]);
            for (int j = 0; j < 4; j++) {
                //indice cuando i<j
                if (i<rivales[i][j]){
                    int index3 = rivales[i][j]*(len_rival)+i;
                    printf("Su rival es %s, su distancia: %d\n", equipo[rivales[i][j]], distancias[index3]);
                    suma+=distancias[index3];
                }
                //cuando i>j, invierto indices
                else if (i>rivales[i][j]){
                    int index3 = i*(len_rival) + rivales[i][j];
                    printf("Su rival es %s, su distancia: %d\n", equipo[rivales[i][j]], distancias[index3]);
                    suma+=distancias[index3];
                }
            }
            printf("la suma total es %lf\n",suma);
            printf("\n");
        }
        printf("la distancia total recorrida es %lf\n",suma);
        distancia_total[index2] = suma;
        index2++;

    } 
    int dist_minima = distancia_total[0];
    int i;
    for (i = 0; i < comb; i++) {
        if (distancia_total[i] < dist_minima) {
            dist_minima = distancia_total[i];
        }
    }
    printf("la distancia mas optima es:%d", dist_minima);
    return 0;
}
