#include <stdio.h>
#include <string.h>

int convertirAEntero(char texto[]) {
    int resultado = 0;
    int i = 0;
    while (texto[i] >= '0' && texto[i] <= '9') {
        resultado = resultado * 10 + (texto[i] - '0');
        i++;
    }
    return resultado;
}

int main() {
    char nombres[4][30];
    int goles[4][4] = {0};
    int puntos[4] = {0};
    int favor[4] = {0};
    int contra[4] = {0};
    int diferencia[4] = {0};

    int i, j;
    for (i = 0; i < 4; i++) {
        do {
            printf("Ingrese el nombre del equipo %d (max 29 caracteres): ", i + 1);
            fgets(nombres[i], 30, stdin);
            nombres[i][strcspn(nombres[i], "\n")] = '\0';
        } while (strlen(nombres[i]) == 0);
    }

    int partidos[6][2] = {
        {0, 1}, {0, 2}, {0, 3},
        {1, 2}, {1, 3},
        {2, 3}
    };

    char resultado[10], parte1[5], parte2[5];
    int local, visita, golLocal, golVisita;

    printf("\nIngrese los resultados de los 6 partidos en formato GOL1-GOL2:\n");

    for (i = 0; i < 6; i++) {
        local = partidos[i][0];
        visita = partidos[i][1];
        do {
            printf("Resultado del partido entre equipo %d vs equipo %d (ej. 2-1): ", local + 1, visita + 1);
            scanf("%s", resultado);

     
            int posicion = -1;
            for (j = 0; resultado[j] != '\0'; j++) {
                if (resultado[j] == '-') {
                    posicion = j;
                    break;
                }
            }

            if (posicion != -1) {
                
                for (j = 0; j < posicion; j++) {
                    parte1[j] = resultado[j];
                }
                parte1[posicion] = '\0';

                
                int k = 0;
                j = posicion + 1;
                while (resultado[j] != '\0') {
                    parte2[k] = resultado[j];
                    j++;
                    k++;
                }
                parte2[k] = '\0';

                golLocal = convertirAEntero(parte1);
                golVisita = convertirAEntero(parte2);

                if (golLocal >= 0 && golVisita >= 0) {
                    goles[local][visita] = golLocal;
                    goles[visita][local] = golVisita;
                    break;
                } else {
                    printf("Los goles deben ser números no negativos.\n");
                }
            } else {
                printf("Formato incorrecto. Use el formato GOL1-GOL2 (ej: 2-1).\n");
            }
        } while (1);
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i != j) {
                favor[i] += goles[i][j];
                contra[i] += goles[j][i];
                if (goles[i][j] > goles[j][i]) {
                    puntos[i] += 3;
                } else if (goles[i][j] == goles[j][i]) {
                    puntos[i] += 1;
                }
            }
        }
        diferencia[i] = favor[i] - contra[i];
    }

    printf("\n%-20s %-7s %-7s %-7s %-10s\n", "Equipo", "Puntos", "Favor", "Contra", "Diferencia");
    printf("-------------------------------------------------------------\n");
    for (i = 0; i < 4; i++) {
        printf("%-20s %-7d %-7d %-7d %-10d\n", nombres[i], puntos[i], favor[i], contra[i], diferencia[i]);
    }


    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            if (puntos[j] > puntos[i] || (puntos[j] == puntos[i] && diferencia[j] > diferencia[i])) {
                int temp;
                char tempNombre[30];

                temp = puntos[i]; puntos[i] = puntos[j]; puntos[j] = temp;
                temp = diferencia[i]; diferencia[i] = diferencia[j]; diferencia[j] = temp;

                strcpy(tempNombre, nombres[i]);
                strcpy(nombres[i], nombres[j]);
                strcpy(nombres[j], tempNombre);
            }
        }
    }

    printf("\nEquipos finalistas:\n");
    printf("1. %s\n", nombres[0]);
    printf("2. %s\n", nombres[1]);

    return 0;
}
