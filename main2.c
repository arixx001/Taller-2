#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"

int main() {
    
    printf("=========================================\n");
    printf("      MATEMATICAS DISCRETAS 1\n");
    printf("      NOMBRES DE LOS INTEGRANTES: \n");
    printf("      DESCRIPCION DEL PROGRAMA: Desarrollar un programa que implemente una expresion SOP a partir de una tabla de verdad ingresada por el usuario. \n");
    printf("      2026:\n");
    printf("=========================================\n\n");

    
    int numVariables;
    printf("Digite el numero de variables (solo 2 o 3): ");
    scanf("%d", &numVariables);

    
    if (numVariables != 2 && numVariables != 3) {
        printf("Error: ¡Solo se permiten 2 o 3 variables!\n");
        return 1;
    }
    
    int numFilas = (1 << numVariables); 


    int *salidas = (int *)malloc(numFilas * sizeof(int));
    if (salidas == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    printf("\nIngrese los valores de salida (0 o 1) para cada fila:\n");
    
    if (numVariables == 2) {
        printf(" A | B || S\n");
        printf("-----------\n");
    } else {
    
        printf(" A | B | C || S\n");
        printf("----------------\n");
    }
    

    for (int i = 0; i < numFilas; i++) {

        for (int bit = numVariables - 1; bit >= 0; bit--) {
            int val = (i >> bit) & 1;
            printf(" %d ", val);
            if (bit > 0) printf("|");
        }
        printf(" || "); 
        
        
        int out;
        scanf("%d", &out);
        
        
        if (out != 0 && out != 1) {
            printf("Error: ¡La salida debe ser 0 o 1!\n");
            free(salidas);
            return 1;
        }
        
        salidas[i] = out;
        
    
        printf("%d\n", out);
    }

    char expression[1024];
    strcpy(expression, "");
    
    int firstTerm = 1; 
    for (int i = 0; i < numFilas; i++) {
        if (salidas[i] == 1) {
            
            if (!firstTerm) {
                strcat(expression, " + ");
            } else {
                firstTerm = 0;
            }
            
    
            for (int bit = numVariables - 1; bit >= 0; bit--) {
                int val = (i >> bit) & 1;
                
                char varName = 'A' + (numVariables - 1 - bit); 
                
                if (val == 1) {
                
                    char temp[2] = {varName, '\0'};
                    strcat(expression, temp);
                } else {
                    
                    char temp[3];
                    
                    sprintf(temp, "%c'", varName);
                    strcat(expression, temp);
                }
                
                if (bit > 0) {
                    
                    strcat(expression, "*");
                }
            }
        }
    }
    
    if (strlen(expression) == 0) {
        strcpy(expression, "0");
    }
    
    printf("\nLa expresion booleana generada es: %s\n", expression);
    
    
    
    if (numVariables == 2) {
        
        
        printf("\nTabla de verdad de la expresion \n");
        printf(" A  B | A'  B' | A'*B  B'*A | S\n");
        
        for (int A = 0; A < 2; A++) {
            for (int B = 0; B < 2; B++) {
                int notA = (A == 0) ? 1 : 0;
                int notB = (B == 0) ? 1 : 0;
                
                int p1 = notA & B; 
                int p2 = notB & A; 
                int S  = p1 | p2;  
                
                
                printf(" %d  %d |", A, B);
                
                
                printf("  %d   %d |", notA, notB);
                
                
                printf("  %s%d%s   %s%d%s |",
                       GREEN, p1, RESET,
                       GREEN, p2, RESET
                      );
                
                
                printf(" %s%d%s\n", RED, S, RESET);
            }
        }
    } else {
        
        printf("\nTabla de verdad de la expresion generada: \n");
        
    }


    free(salidas);
    
    return 0;
}
