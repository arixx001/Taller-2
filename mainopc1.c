#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define USUARIO_CORRECTO "ariana"
#define CONTRASENA_CORRECTA "1234"


#define IVA 0.15
#define Propina_opc 0.10


#define TOTAL_PRODUCTOS 10


const char *productos[TOTAL_PRODUCTOS] = {
    "Sopa",      
    "Ensalada",  
    "Pollo",     
    "Carne",     
    "Pasta",     
    "Helado",    
    "Pastel",    
    "Agua",      
    "Refresco",  
    "Jugo"       
};

float precios[TOTAL_PRODUCTOS] = {
    1.0,  
    2.0,  
    12.0, 
    15.0, 
    10.0, 
    4.0,  
    4.0,  
    2.0,  
    2.0,  
    3.0   
};
int contadorProductosVendidos[TOTAL_PRODUCTOS] = {0};
float totalVentasGlobal = 0.0;

bool iniciarSesion() {
    char usuarioIngresado[50];
    char contrasenaIngresada[50];

    printf("=== SISTEMA DE GESTION DE PEDIDOS EN RESTAURANTE ===\n");
    printf("Por favor, inicie sesion.\n");

    printf("Usuario: ");
    scanf("%s", usuarioIngresado);

    printf("Contrasena: ");
    scanf("%s", contrasenaIngresada);

    
    if ((strcmp(usuarioIngresado, USUARIO_CORRECTO) == 0) &&
        (strcmp(contrasenaIngresada, CONTRASENA_CORRECTA) == 0)) 
    {
        printf("\nBienvenido, %s\n\n", usuarioIngresado);
        return true;
    } else {
        printf("\nCredenciales invalidas. Fin del programa.\n");
        return false;
    }
}


void mostrarMenu() {
    printf("----- Menu Principal -----\n");
    printf("1. Ingresar un nuevo pedido\n");
    printf("2. Ver reporte de ventas\n");
    printf("3. Salir\n");
    printf("Opcion: ");
}

void nuevoPedido() {
    float totalPedido = 0.0f;
    float subtotalConIVA = 0.0f;
    float montoPropina = 0.0f;
    float porcentajeDescuento = 0.0f;
    bool aplicarDescuento = false;

    printf("\n=== REGISTRO DE UN NUEVO PEDIDO ===\n");
    for (int i = 0; i < TOTAL_PRODUCTOS; i++) {
        int cantidad;
        printf("%s ($%.2f). Cuanta cantidad va a comprar: ", productos[i], precios[i]);
        scanf("%d", &cantidad);

        if (cantidad > 0) {
            totalPedido += precios[i] * cantidad;
            contadorProductosVendidos[i] += cantidad; 
        }
    }

    char respuestaDescuento;
    printf("Desea aplicar algun descuento: ");
    scanf(" %c", &respuestaDescuento); 

    if (respuestaDescuento == 'S' || respuestaDescuento == 's') {
        aplicarDescuento = true;
        printf("Ingrese el porcentaje de descuento que tiene:(por ejemplo 15 para 15%%  \n)");
        scanf("%f", &porcentajeDescuento);
        porcentajeDescuento /= 100.0f; 
    }

    if (aplicarDescuento) {
        totalPedido -= (totalPedido * porcentajeDescuento);
    }

    float montoIVA = totalPedido * IVA;
    subtotalConIVA = totalPedido + montoIVA;

    char respuestaPropina;
    printf("Dara propina por la atencion recibida:  ");
    scanf(" %c", &respuestaPropina) ;

    if (respuestaPropina == 'S' || respuestaPropina == 's') {
        montoPropina = subtotalConIVA * Propina_opc;
    }

    float totalConPropina = subtotalConIVA + montoPropina;

    printf("\n===== DESGLOSE DEL PEDIDO =====\n");
    printf("Subtotal (sin IVA): $%.2f\n", totalPedido);
    printf("IVA (%.0f%%): $%.2f\n", IVA * 100, montoIVA);

    if (aplicarDescuento) {
        printf("Descuento aplicado: %.2f%%\n", porcentajeDescuento * 100);
    }

    printf("Subtotal + IVA: $%.2f\n", subtotalConIVA);
    printf("Propina: $%.2f\n", montoPropina);
    printf("TOTAL A PAGAR: $%.2f\n", totalConPropina);
    printf("==============================\n\n");


    totalVentasGlobal += totalConPropina;
}

void reporteVentas() {
    printf("\n------- REPORTE DE VENTAS --------\n");
    printf("Su reporte es: $%.2f\n", totalVentasGlobal);

    
    int maxCantidadVendida = 0;
    
    for (int i = 0; i < TOTAL_PRODUCTOS; i++) {
        if (contadorProductosVendidos[i] > maxCantidadVendida) {
            maxCantidadVendida = contadorProductosVendidos[i];
        }
    }

    
    if (maxCantidadVendida == 0) {
        printf("No ha comprado ningun producto\n");
    } else {
        printf("Los productos mas vendidos son:\n");
        for (int i = 0; i < TOTAL_PRODUCTOS; i++) {
            if (contadorProductosVendidos[i] == maxCantidadVendida) {
                printf("- %s con %d unidades vendidas.\n", productos[i], maxCantidadVendida);
            }
        }
    }
    printf("----------------------------\n\n");
}


int main() {
    
    if (!iniciarSesion()) {
    
        return 0;
    }


    int opcionMenu = 0;
    do {
        mostrarMenu();
        scanf("%d", &opcionMenu);

        switch (opcionMenu) {
            case 1:
                
                nuevoPedido();
                break;
            case 2:
                
                reporteVentas();
                break;
            case 3:
            
                printf("Esta usted saliendo del programa\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n\n");
                break;
        }
    } while (opcionMenu != 3);

    return 0;
}
