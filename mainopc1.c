#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define USUARIO_CORRECTO "ariana"
#define CONTRASENA_CORRECTA "1234"


#define IVA 0.15
#define TOTAL_PRODUCTOS 10


char productos[TOTAL_PRODUCTOS][50];
float precios[TOTAL_PRODUCTOS];      
int contadorProductosVendidos[TOTAL_PRODUCTOS];
float totalVentasGlobal;


void sst() {
    
    strcpy(productos[0], "Sopa");
    strcpy(productos[1], "Ensalada");
    strcpy(productos[2], "Pollo");
    strcpy(productos[3], "Carne");
    strcpy(productos[4], "Pasta");
    strcpy(productos[5], "Helado");
    strcpy(productos[6], "Pastel");
    strcpy(productos[7], "Agua");
    strcpy(productos[8], "Refresco");
    strcpy(productos[9], "Jugo");

    
    precios[0] = 1.0f;
    precios[1] = 2.0f;
    precios[2] = 12.0f;
    precios[3] = 15.0f;
    precios[4] = 10.0f;
    precios[5] = 4.0f;
    precios[6] = 4.0f;
    precios[7] = 2.0f;
    precios[8] = 2.0f;
    precios[9] = 3.0f;

    
    for (int i = 0; i < TOTAL_PRODUCTOS; i++) {
        contadorProductosVendidos[i] = 0;
    }
    totalVentasGlobal = 0.0f;

    printf("---------------\n");
}


bool iniciarSesion() {
    char usuarioIngresado[50];
    char contrasenaIngresada[50];

    printf("=== SISTEMA DE GESTION DE PEDIDOS EN RESTAURANTE ===\n");
    printf("Por favor, inicie sesion.\n");

    printf("Usuario: ");
    fgets(usuarioIngresado, sizeof(usuarioIngresado), stdin);
    usuarioIngresado[strcspn(usuarioIngresado, "\n")] = 0; // Eliminar salto de linea

    printf("Contrasena: ");
    fgets(contrasenaIngresada, sizeof(contrasenaIngresada), stdin);
    contrasenaIngresada[strcspn(contrasenaIngresada, "\n")] = 0; // Eliminar salto de linea

    if (strcmp(usuarioIngresado, USUARIO_CORRECTO) == 0 &&
        strcmp(contrasenaIngresada, CONTRASENA_CORRECTA) == 0) {
        printf("\nBienvenido, %s!\n\n", usuarioIngresado);
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

   
    printf("\n=== REGISTRO DE UN NUEVO PEDIDO ===\n");
    for (int i = 0; i < TOTAL_PRODUCTOS; i++) {
        int cantidad;

        printf("%s ($%.2f). Ingrese cantidad: ", productos[i], precios[i]);
        scanf("%d", &cantidad);

        if (cantidad > 0) {
            totalPedido += precios[i] * cantidad;
            contadorProductosVendidos[i] += cantidad;
        }
    }

   
    printf("Posee algun descuento: Ingrese el porcentaje o presione 0 para omitir: ");
    scanf("%f", &porcentajeDescuento);
    if (porcentajeDescuento > 0) {
        totalPedido -= totalPedido * (porcentajeDescuento / 100);
        printf("Su descuento fue: %.2f%%.\n", porcentajeDescuento);
    }

   
    float montoIVA = totalPedido * IVA;
    subtotalConIVA = totalPedido + montoIVA;

    
    printf("Desea ofrecer propina por los servicios: Ingrese el porcentaje o 0 para omitir: ");
    float porcentajePropina;
    scanf("%f", &porcentajePropina);
    montoPropina = subtotalConIVA * (porcentajePropina / 100);

    float totalConPropina = subtotalConIVA + montoPropina;

    printf("\n===== DESGLOSE DEL PEDIDO =====\n");
    printf("Subtotal (sin IVA): $%.2f\n", totalPedido);
    printf("IVA (%.0f%%): $%.2f\n", IVA * 100, montoIVA);
    printf("Subtotal + IVA: $%.2f\n", subtotalConIVA);
    printf("Propina: $%.2f\n", montoPropina);
    printf("TOTAL A PAGAR: $%.2f\n", totalConPropina);
    printf("===============================\n\n");

    totalVentasGlobal += totalConPropina;
}


void reporteVentas() {
    printf("\n===== REPORTE DE VENTAS =====\n");
    printf("Total de ventas acumuladas: $%.2f\n", totalVentasGlobal);

    int maxCantidadVendida = 0;

   
    for (int i = 0; i < TOTAL_PRODUCTOS; i++) {
        if (contadorProductosVendidos[i] > maxCantidadVendida) {
            maxCantidadVendida = contadorProductosVendidos[i];
        }
    }

    if (maxCantidadVendida == 0) {
        printf("No se han vendido nada \n");
    } else {
        printf("El producto mas vendido es:\n");
        for (int i = 0; i < TOTAL_PRODUCTOS; i++) {
            if (contadorProductosVendidos[i] == maxCantidadVendida) {
                printf("- %s con %d unidades.\n", productos[i], contadorProductosVendidos[i]);
            }
        }
    }
    printf("===============================\n\n");
}


int main() {
   
    sst();

    if (!iniciarSesion()) {
        return 0;
    }

    int opcionMenu;
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
                printf("Usted va a salir del programa\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcionMenu != 3);

    return 0;
}
