#include <iostream>
#include <string>
#include <vector>
#include <limits>

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

int main() {
    vector<Producto> inventario;
    int opcion;

    do {
        cout << "\n=========================================\n";
        cout << "  SISTEMA DE INVENTARIO Y BODEGA (v1.0)  \n";
        cout << "=========================================\n";
        cout << "1. Registrar Producto\n";
        cout << "2. Mostrar Inventario\n";
        cout << "3. Registrar Entrada de Stock\n";
        cout << "4. Registrar Salida de Stock\n";
        cout << "5. Salir\n";
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
        case 5: cout << "Saliendo del sistema...\n"; break;
        default: cout << "Opcion no valida.\n"; break;
        }
    } while (opcion != 5);

    return 0;
}