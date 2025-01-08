#include <stdio.h> 
#include <string.h> 

 

int main (int argc, char *argv[]) { 

 
    char texto[50]; 
    int cont = 0;  
    int max = 0, min = 50;  
    int cantidadcaracteres = 0;  
    printf("\nIngrese un texto (50 caracteres maximo): "); 
    fgets(texto, 50, stdin); 
    int len = strlen(texto);
    if (texto[len - 1] == '\n') { 
        texto[len - 1] = '\0'; 
    } 
    printf("Oracion: %s\n",texto); 

    for (int i = 0; i < len; i++) { 

        if (texto[i] == ' ' || texto[i] == '\0') { 

            if (cantidadcaracteres > 0) { 
                cont++; 
                if (cantidadcaracteres > max) { 
                    max = cantidadcaracteres; 
                } 
                if (cantidadcaracteres < min) { 
                    min = cantidadcaracteres; 
                } 
                cantidadcaracteres = 0; 
            } 
        } else { 

            cantidadcaracteres++; 
        } 
    } 
    if (cantidadcaracteres > 0) { 
        cont++; 
        if (cantidadcaracteres > max) { 
            max = cantidadcaracteres; 
        }
        if (cantidadcaracteres < min) { 
            min = cantidadcaracteres; 
        } 
    } 
     else { 
        printf("Las palabras en el texto son: %d\n", cont); 
        printf("La palabra con %d letras es la mas corta \n", min); 
        printf("La palabra con %d letras es la mas larga \n", max); 
    } 
    return 0; 

} 