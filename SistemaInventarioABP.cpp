#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

// Estructura principal del Producto
struct Producto {
    int id;
    string nombre;
    string categoria;
    int cantidad;
    double precio;
};

// Limpieza de buffer para evitar errores de entrada en C++
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Función para registrar un nuevo producto con validaciones
void registrarProducto(vector<Producto>& inventario) {
    Producto p;
    cout << "\n=== REGISTRO DE NUEVO PRODUCTO ===\n";

    cout << "Ingrese ID del producto (numero): ";
    while (!(cin >> p.id) || p.id <= 0) {
        cout << "Error: Ingrese un ID valido (entero positivo): ";
        limpiarBuffer();
    }

    // Verificar si el ID ya existe
    for (const auto& prod : inventario) {
        if (prod.id == p.id) {
            cout << "Error: El ID " << p.id << " ya existe en el inventario.\n";
            return;
        }
    }

    limpiarBuffer();
    cout << "Ingrese Nombre del producto: ";
    getline(cin, p.nombre);

    cout << "Ingrese Categoria: ";
    getline(cin, p.categoria);

    cout << "Ingrese Cantidad inicial: ";
    while (!(cin >> p.cantidad) || p.cantidad < 0) {
        cout << "Error: Ingrese una cantidad valida (0 o mayor): ";
        limpiarBuffer();
    }

    cout << "Ingrese Precio unitario: ";
    while (!(cin >> p.precio) || p.precio < 0.0) {
        cout << "Error: Ingrese un precio valido: ";
        limpiarBuffer();
    }

    inventario.push_back(p);
    cout << ">> Producto registrado exitosamente.\n";
}

// Función para mostrar el inventario actual
void mostrarInventario(const vector<Producto>& inventario) {
    cout << "\n=== INVENTARIO DE BODEGA ===\n";
    if (inventario.empty()) {
        cout << "El inventario esta vacio.\n";
        return;
    }

    cout << "ID\t| Nombre\t\t| Categoria\t| Cantidad\t| Precio\n";
    cout << "----------------------------------------------------------------------\n";
    for (const auto& p : inventario) {
        cout << p.id << "\t| " << p.nombre << "\t\t| "
            << p.categoria << "\t| " << p.cantidad << "\t\t| $" << p.precio << "\n";
    }
}

// Registrar entrada/salida de existencias
void gestionarStock(vector<Producto>& inventario, bool esEntrada) {
    int id, cant;
    cout << "\n=== " << (esEntrada ? "ENTRADA DE STOCK" : "SALIDA DE STOCK") << " ===\n";
    cout << "Ingrese ID del producto: ";
    if (!(cin >> id)) {
        cout << "ID invalido.\n";
        limpiarBuffer();
        return;
    }

    for (auto& p : inventario) {
        if (p.id == id) {
            cout << "Producto encontrado: " << p.nombre << " (Stock actual: " << p.cantidad << ")\n";
            cout << "Ingrese cantidad a " << (esEntrada ? "agregar: " : "retirar: ");
            while (!(cin >> cant) || cant <= 0) {
                cout << "Cantidad invalida. Ingrese entero mayor a 0: ";
                limpiarBuffer();
            }

            if (!esEntrada && cant > p.cantidad) {
                cout << "Error: Stock insuficiente. No se puede realizar la salida.\n";
                return;
            }

            if (esEntrada) p.cantidad += cant;
            else p.cantidad -= cant;

            cout << ">> Stock actualizado correctamente. Nuevo stock: " << p.cantidad << "\n";
            return;
        }
    }
    cout << "Error: Producto con ID " << id << " no encontrado.\n";
}

// Nueva Funcionalidad 1: Buscar producto por ID
void buscarProducto(const vector<Producto>& inventario) {
    int id;
    cout << "\n=== BUSCAR PRODUCTO POR ID ===\n";
    cout << "Ingrese el ID del producto a buscar: ";
    if (!(cin >> id)) {
        cout << "ID invalido.\n";
        limpiarBuffer();
        return;
    }

    for (const auto& p : inventario) {
        if (p.id == id) {
            cout << "\n>> Producto Encontrado:\n";
            cout << "ID: " << p.id << "\n";
            cout << "Nombre: " << p.nombre << "\n";
            cout << "Categoria: " << p.categoria << "\n";
            cout << "Cantidad en stock: " << p.cantidad << "\n";
            cout << "Precio unitario: $" << p.precio << "\n";
            return;
        }
    }
    cout << "Error: No se encontro ningun producto con el ID " << id << ".\n";
}

// Nueva Funcionalidad 2: Eliminar producto
void eliminarProducto(vector<Producto>& inventario) {
    int id;
    cout << "\n=== ELIMINAR PRODUCTO ===\n";
    cout << "Ingrese el ID del producto que desea eliminar: ";
    if (!(cin >> id)) {
        cout << "ID invalido.\n";
        limpiarBuffer();
        return;
    }

    for (auto it = inventario.begin(); it != inventario.end(); ++it) {
        if (it->id == id) {
            cout << "Producto encontrado: " << it->nombre << ". Esta seguro de eliminarlo? (1. Si / 2. No): ";
            int confirmacion;
            cin >> confirmacion;
            if (confirmacion == 1) {
                inventario.erase(it);
                cout << ">> Producto eliminado exitosamente.\n";
            }
            else {
                cout << "Operacion cancelada.\n";
            }
            return;
        }
    }
    cout << "Error: Producto con ID " << id << " no encontrado.\n";
}

// Nueva Funcionalidad 3: Calcular valor total del inventario
void calcularValorInventario(const vector<Producto>& inventario) {
    cout << "\n=== VALOR TOTAL DEL INVENTARIO ===\n";
    if (inventario.empty()) {
        cout << "El inventario esta vacio.\n";
        return;
    }

    double valorTotal = 0.0;
    int totalItems = 0;
    for (const auto& p : inventario) {
        valorTotal += (p.cantidad * p.precio);
        totalItems += p.cantidad;
    }

    cout << "Total de unidades en bodega: " << totalItems << "\n";
    cout << "Valor economico total del inventario: $" << valorTotal << "\n";
}

// Nueva Funcionalidad 4: Reporte de stock bajo (<= 5 unidades)
void reporteStockBajo(const vector<Producto>& inventario) {
    cout << "\n=== REPORTE DE PRODUCTOS CON STOCK BAJO (<= 5) ===\n";
    if (inventario.empty()) {
        cout << "El inventario esta vacio.\n";
        return;
    }

    bool encontrado = false;
    cout << "ID\t| Nombre\t\t| Categoria\t| Cantidad\n";
    cout << "--------------------------------------------------------\n";
    for (const auto& p : inventario) {
        if (p.cantidad <= 5) {
            cout << p.id << "\t| " << p.nombre << "\t\t| "
                << p.categoria << "\t| " << p.cantidad << "\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "Excelente! No hay productos con stock bajo en este momento.\n";
    }
}

int main() {
    vector<Producto> inventario;
    int opcion;

    do {
        cout << "\n=================================================\n";
        cout << "    SISTEMA DE INVENTARIO Y BODEGA (v2.0)        \n";
        cout << "=================================================\n";
        cout << "1. Registrar Producto\n";
        cout << "2. Mostrar Inventario\n";
        cout << "3. Registrar Entrada de Stock\n";
        cout << "4. Registrar Salida de Stock\n";
        cout << "5. Buscar Producto por ID\n";
        cout << "6. Eliminar Producto\n";
        cout << "7. Ver Valor Total del Inventario\n";
        cout << "8. Reporte de Stock Bajo\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "Opcion invalida. Intente de nuevo.\n";
            limpiarBuffer();
            continue;
        }

        switch (opcion) {
        case 1: registrarProducto(inventario); break;
        case 2: mostrarInventario(inventario); break;
        case 3: gestionarStock(inventario, true); break;
        case 4: gestionarStock(inventario, false); break;
        case 5: buscarProducto(inventario); break;
        case 6: eliminarProducto(inventario); break;
        case 7: calcularValorInventario(inventario); break;
        case 8: reporteStockBajo(inventario); break;
        case 9: cout << "Saliendo del sistema...\n"; break;
        default: cout << "Opcion no valida.\n"; break;
        }
    } while (opcion != 9);

    return 0;
}
