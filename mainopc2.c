

def registrar_pedido():
    pedido = []
    while True:
        tipo = input("Tipo de producto (Entrante, Principal, Postre, Bebida): ").strip()
        nombre = input("Nombre del producto: ").strip()
        precio = float(input(f"Precio unitario de {nombre}: "))
        cantidad = int(input(f"Cantidad de {nombre}: "))
        pedido.append({"tipo": tipo, "nombre": nombre, "precio": precio, "cantidad": cantidad})
        
        continuar = input("¿Agregar otro producto? (S/N): ").strip().lower()
        if continuar != 's':
            break
    return pedido

def calcular_total(pedido, descuento, iva, propina):
    subtotal = sum(item["precio"] * item["cantidad"] for item in pedido)
    descuento_aplicado = subtotal * (descuento / 100)
    subtotal_descuento = subtotal - descuento_aplicado
    iva_calculado = subtotal_descuento * (iva / 100)
    total_con_impuestos = subtotal_descuento + iva_calculado
    propina_calculada = total_con_impuestos * (propina / 100)
    total_final = total_con_impuestos + propina_calculada
    
    return {
        "subtotal": subtotal,
        "descuento": descuento_aplicado,
        "subtotal_descuento": subtotal_descuento,
        "iva": iva_calculado,
        "propina": propina_calculada,
        "total_final": total_final
    }

def mostrar_desglose(detalles):
    print("\n--- Desglose del Pedido ---")
    for clave, valor in detalles.items():
        print(f"{clave.capitalize()}: ${valor:.2f}")
    print("---------------------------")

def generar_reporte(pedidos):
    ventas_totales = sum(pedido["total_final"] for pedido in pedidos)
    productos_vendidos = {}
    for pedido in pedidos:
        for item in pedido["detalles"]:
            if item["nombre"] in productos_vendidos:
                productos_vendidos[item["nombre"]] += item["cantidad"]
            else:
                productos_vendidos[item["nombre"]] = item["cantidad"]
    producto_mas_vendido = max(productos_vendidos, key=productos_vendidos.get)
    return ventas_totales, producto_mas_vendido

def main():
    pedidos = []
    while True:
        print("\n--- Nuevo Pedido ---")
        pedido = registrar_pedido()
        descuento = float(input("Ingrese el porcentaje de descuento (0-100): "))
        iva = float(input("Ingrese el porcentaje de IVA (0-100): "))
        propina = float(input("Ingrese el porcentaje de propina (0-100): "))
        
        detalles = calcular_total(pedido, descuento, iva, propina)
        mostrar_desglose(detalles)
        pedidos.append({"detalles": pedido, "total_final": detalles["total_final"]})
        
        continuar = input("¿Registrar otro pedido? (S/N): ").strip().lower()
        if continuar != 's':
            break

    ventas_totales, producto_mas_vendido = generar_reporte(pedidos)
    print("\n--- Reporte Final ---")
    print(f"Ventas totales: ${ventas_totales:.2f}")
    print(f"Producto más vendido: {producto_mas_vendido}")

if __name__ == "__main__":
    main()
