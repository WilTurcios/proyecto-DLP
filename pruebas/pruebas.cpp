#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <locale>
#include <windows.h>
#include <iomanip>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

/* COLORES(Secuencias de escape ANSI para los colores) */

const string colorBlanco = "\033[1;37m";
const string colorRojo = "\033[1;31m";
const string colorVerde = "\033[1;32m";
const string colorAzul = "\033[1;34m";
const string colorReset = "\033[0m";

/* COLORES */

/* UTILIDADES */

// Obtiene el tamaño de la consola
int obtenerAnchoConsola() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int obtenerAltoConsola() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Repite el texto las veces que se indique
string repeatText(const string& text, int count) {
    string result;
    for (int i = 0; i < count; ++i) {
        result += text;
    }
    return result;
}

string obtenerFecha() {
    time_t now = time(0);
    tm* fechaActual = localtime(&now);

    string sec = to_string(fechaActual->tm_sec);
    string min = to_string(fechaActual->tm_min);
    string hour = to_string(fechaActual->tm_hour);
    string day = to_string(fechaActual->tm_mday);
    string year = to_string(fechaActual->tm_year + 1900);  // Agregar 1900 para obtener el año actual
    string month = to_string(fechaActual->tm_mon + 1);     // Agregar 1 ya que enero es representado como 0

    // Formatear los componentes de la fecha y hora
    if (sec.length() == 1) sec = "0" + sec;
    if (min.length() == 1) min = "0" + min;
    if (hour.length() == 1) hour = "0" + hour;
    if (day.length() == 1) day = "0" + day;
    if (month.length() == 1) month = "0" + month;

    string fecha = day + "/" + month + "/" + year + " | " + hour + ":" + min + ":" + sec;
    return fecha;
}

/* UTILIDADES */

/* ESTRUCTURAS DE DATOS, VARIABLES Y VECTORES */
struct Producto {
    string nombre;
    double precio;
    string descripcion;
};

struct Factura {
    string nombreCliente;
    int numeroMesa;
    int numeroFactura;
    double total;
    string fecha;
    vector<Producto> listaProductos;
    vector<int> Cantidades;
};

vector<Producto> BebidasFrias =
{
    {"Limonada", 2.35, " Limonada casera con limones frescos y azúcar."},
    {"Granita al limone", 3.00, "Raspado de limón refrescante y ligeramente dulce."},
    {"Agua con gas", 1.50, " Agua mineral con gas."},
    {"Té helado", 2.00, "Té negro o verde frío endulzado"},
    {"Batidos de frutas", 4.35, "Mezcla de frutas frescas con leche o yogur."}
};
vector<Producto> BebidasCalientes =
{
    {"Espresso", 2.35, "Un café fuerte y concentrado servido en una taza pequeña."},
    {"Cappuccino", 3.00, "Espresso combinado con leche caliente y espuma de leche."},
    {"Latte macchiato", 1.50, "Leche caliente con una capa de espresso."},
    {"Té verde", 2.00, " Té verde caliente con aroma y sabor suave."},
    {"Chocolate caliente", 4.35, "Chocolate derretido en leche caliente, con opción de crema batida y malvaviscos."}
};
vector<Producto> BebidasAlcoholicas =
{
    {"Vino tinto Chianti", 7.50, "Vino tinto italiano de la región de Chianti, con cuerpo medio y notas frutales."},
    {"Prosecco", 8.30, "Vino espumoso italiano con burbujas refrescantes y notas afrutadas."},
    {"Aperol Spritz", 10, "Cóctel refrescante hecho con Aperol, prosecco y soda."},
    {"Negroni", 11.50, "Cóctel clásico italiano con gin, vermut rojo y Campari."},
    {"Limoncello", 7.95, " Licor italiano de limón, servido como digestivo."}
};
vector<Producto> Pizzas =
{
    {"Pizza Margherita", 13.50, "Pizza hecha con salsa de tomate, mozzarella fresca y hojas de albahaca"},
    {"Pizza Pepperoni", 14.00, "Pizza hecha con salsa de tomate, mozzarella y rodajas de pepperoni."},
    {"Pizza Hawaiana", 11.00, "Pizza hecha con salsa de tomate, mozzarella, jamón y piña"},
    {"Pizza Diavola", 13.75, "Pizza hecha con salsa de tomate, mozzarella, salchicha picante, pimientos y cebolla."},
    {"Pizza Quattro Formagg", 11.50, "Pizza hecha con salsa de tomate, mozzarella, queso azul, queso de cabra y queso parmesano"},
    {"Pizza Capricciosa", 15.75, "Pizza hecha con salsa de tomate, mozzarella, jamón, champiñones, alcachofas y aceitunas."},
    {"Pizza Prosciutto e Funghi", 13.40, "Pizza hecha con salsa de tomate, mozzarella, jamón y champiñones."},
    {"Pizza Vegetariana", 10, "Pizza hecha con salsa de tomate, mozzarella, pimientos, cebolla, champiñones, aceitunas y tomate fresco."},
    {"Pizza Calzone", 15.30, "Masa de pizza rellena de salsa de tomate, mozzarella, pepperoni, champiñones y otros ingredientes al gusto."},
    {"Pizza Marinara", 12.20, "Pizza hecha con salsa de tomate, ajo, aceite de oliva, orégano y albahaca"}
};
vector<Producto> Pastas =
{
    {"Spaghetti alla carbonara", 14.00, "Espaguetis con una salsa cremosa de huevo, panceta, queso pecorino y pimienta negra."},
    {"Penne all'arrabbiata", 11.50, "Pasta penne con una salsa picante de tomate, ajo, guindilla y aceite de oliva"},
    {"Ravioli di ricotta e spinaci", 12.35, "Raviolis rellenos de ricotta y espinacas, servidos con una salsa de tomate casera."},
    {"Fettuccine Alfredo", 15.35, "Fettuccine en una salsa cremosa de mantequilla y queso parmesano"},
    {"Linguine alle vongole", 18.00, "Linguine con almejas frescas, ajo, guindilla, perejil y un toque de vino blanco."}
};
vector<Producto> ComidasPrincipales =
{
    {"Pizza Margherita", 12.00, "Pizza clásica con salsa de tomate, mozzarella y hojas de albahaca"},
    {"Lasagna bolognesa", 12.80, "Capas de pasta, carne de res y cerdo, salsa de tomate y bechamel, gratinadas con queso."},
    {"Pollo alla cacciatora", 13.90, "Pollo guisado con tomate, vino tinto, champiñones y hierbas aromáticas."},
    {"Saltimbocca alla romana", 17.35, "Filete de ternera envuelto en jamón y salvia, cocinado en una salsa de vino blanco y mantequilla."},
    {"Risotto ai frutti di mare", 20.00, "Risotto cremoso con una selección de mariscos, como camarones, mejillones y calamares."}
};
vector<Producto> Entrantes =
{
    {"Bruschetta tradicional", 7.50, "Pan tostado con tomate fresco, ajo, albahaca y aceite de oliva"},
    {"Caprese", 10.00, "Ensalada de rodajas de tomate, mozzarella fresca y hojas de albahaca, aliñada con aceite de oliva."},
    {"Prosciutto e melone", 12.35, "Jamón serrano servido con melón maduro."},
    {"Antipasto misto", 14.50, "Tabla de embutidos y quesos italianos variados, acompañados de aceitunas y encurtidos."},
    {"Arancini", 9.00, "Croquetas de arroz rellenas de queso y ragú, empanizadas y fritas."}
};
vector<Factura> Facturas;

/* ESTRUCTURAS DE DATOS, VARIABLES Y VECTORES */

void mostrarBanner() {

    const int anchoConsola = obtenerAnchoConsola();
    string dashString = repeatText("-", anchoConsola);

    // Primera linea de texto
    const string texto1 = "Bienvenidos a";
    int cantidadEspacios1 = (anchoConsola - texto1.length() - 2) / 2;
    string whiteSpace1 = repeatText(" ", cantidadEspacios1);

    // Segunda linea de texto
    const string texto2 = "LA FARINA RESTAURANT";
    int cantidadEspacios2 = (anchoConsola - texto2.length() - 2) / 2;
    string whiteSpace2 = repeatText(" ", cantidadEspacios2);

    // Tecera linea de texto
    const string texto3 = "Somos un restaurante de comida italiana especializado en pastas.";
    int cantidadEspacios3 = (anchoConsola - texto3.length() - 2) / 2;
    string whiteSpace3 = repeatText(" ", cantidadEspacios3);

    // cuarta linea de texto
    const string texto4 = "Pero no encontrarás únicamente pastas, sino una gran variedad de platillos deliciosos";
    int cantidadEspacios4 = (anchoConsola - texto4.length() - 2) / 2;
    string whiteSpace4 = repeatText(" ", cantidadEspacios4);

    // quinta linea de texto
    const string texto5 = "para disfrutar con amigos y familia.";
    int cantidadEspacios5 = (anchoConsola - texto5.length() - 2) / 2;
    string whiteSpace5 = repeatText(" ", cantidadEspacios5);


    // Imprimir el texto en letras grandes con colores
    cout << colorVerde << dashString << colorReset << "\n\n";

    cout << "\n\n";

    cout << whiteSpace1 << colorVerde << texto1 << colorReset << whiteSpace1 << "\n\n";
    cout << whiteSpace2 << colorBlanco << texto2 << colorReset << whiteSpace2 << "\n\n";
    cout << whiteSpace3 << colorBlanco << texto3 << colorReset << whiteSpace3 << "\n\n";
    cout << whiteSpace4 << colorRojo << texto4 << colorReset << whiteSpace4 << "\n\n";
    cout << whiteSpace5 << colorRojo << texto5 << colorReset << whiteSpace5 << "\n\n";


    cout << "\n\n";

    cout << colorRojo << dashString << colorReset << "\n\n";

}

int mostrarOpciones() {
    int opcion;
    cout << "¿Qué acción deseas realizar?\n\n";
    cout << "1. Agregar un nuevo producto al menú.\n";
    cout << "2. Generar una nueva orden.\n";
    cout << "3. Mostrar facturas recientes.\n";
    cout << "4. Mostrar el menú.\n";

    cin >> opcion;

    return opcion;
}

void agregarProducto() {
    string nombre;
    double precio;
    string descripcion;
    int tipoPlatillo;

    cout << "¿Qué tipo de platillo desea agregar?" << endl;
    cout << "1. Entrante." << endl;
    cout << "2. Comida Principal." << endl;
    cout << "3. Pastas." << endl;
    cout << "4. Pizzas." << endl;
    cout << "5. Bebidas Frias." << endl;
    cout << "6. Bebidas Calientes." << endl;
    cout << "7. Bebidas Alcohólicas." << endl;
    cin >> tipoPlatillo;

    switch (tipoPlatillo)
    {
    case 1:
        cout << "Ingresa el nombre del platillo: \n";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingresa la descripción del platillo: \n";
        cin.ignore();
        getline(cin, descripcion);
        cout << "Ingresa el precio del platillo: \n";
        cin >> precio;

        Entrantes.push_back(
            { nombre, precio, descripcion }
        );

        break;
    case 2:
        cout << "Ingresa el nombre del platillo: \n";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingresa la descripción del platillo: \n";
        cin.ignore();
        getline(cin, descripcion);
        cout << "Ingresa el precio del platillo: \n";
        cin >> precio;

        ComidasPrincipales.push_back(
            { nombre, precio, descripcion }
        );

        break;
    case 3:
        cout << "Ingresa el nombre de la pasta: \n";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingresa la descripción la pasta: \n";
        cin.ignore();
        getline(cin, descripcion);
        cout << "Ingresa el precio la pasta: \n";
        cin >> precio;

        Pastas.push_back(
            { nombre, precio, descripcion }
        );

        break;
    case 4:
        cout << "Ingresa el nombre de la pizza: \n";
        cin.ignore();
        getline(cin, nombre);
        cin.ignore();
        cout << "Ingresa la descripción la pizza: \n";
        getline(cin, descripcion);
        cout << "Ingresa el precio la pizza: \n";
        cin >> precio;

        Pizzas.push_back(
            { nombre, precio, descripcion }
        );

        break;
    case 5:
        cout << "Ingresa el nombre de la bebida fría: \n";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingresa la descripción de la bebida fría: \n";
        cin.ignore();
        getline(cin, descripcion);
        cout << "Ingresa el precio de la bebida fría: \n";
        cin >> precio;

        BebidasFrias.push_back(
            { nombre, precio, descripcion }
        );

        break;
    case 6:
        cout << "Ingresa el nombre de la bebida caliente: \n";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingresa la descripción la bebida caliente: \n";
        cin.ignore();
        getline(cin, descripcion);
        cout << "Ingresa el precio la bebida caliente: \n";
        cin >> precio;

        BebidasCalientes.push_back(
            { nombre, precio, descripcion }
        );

        break;
    case 7:
        cout << "Ingresa el nombre de la bebida alcoholica: \n";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingresa la descripción la bebida alcoholica: \n";
        cin.ignore();
        getline(cin, descripcion);
        cout << "Ingresa el precio la bebida alcoholica: \n";
        cin >> precio;

        BebidasAlcoholicas.push_back(
            { nombre, precio, descripcion }
        );

        break;
    default:
        break;
    }

}

void mostrarMenu() {

    int anchoConsola = obtenerAnchoConsola();
    string dashString = repeatText("-", anchoConsola);

    // Primesa linea de texto
    const string texto1 = " Entrantes ";
    int cantidadEspacios1 = ((anchoConsola - texto1.length() - 4) / 2);
    string whiteSpace1 = repeatText("*", cantidadEspacios1);

    // Segunda linea de texto
    const string texto2 = " Platillos principales ";
    int cantidadEspacios2 = ((anchoConsola - texto2.length() - 4) / 2);
    string whiteSpace2 = repeatText("*", cantidadEspacios2);

    // Tecera linea de texto
    const string texto3 = " Pastas ";
    int cantidadEspacios3 = ((anchoConsola - texto3.length() - 4) / 2);
    string whiteSpace3 = repeatText("*", cantidadEspacios3);

    // Tecera linea de texto
    const string texto7 = " Pizzas ";
    int cantidadEspacios7 = ((anchoConsola - texto7.length() - 4) / 2);
    string whiteSpace7 = repeatText("*", cantidadEspacios7);

    // cuarta linea de texto
    const string texto4 = " Bebidas Alcohólicas ";
    int cantidadEspacios4 = ((anchoConsola - texto4.length() - 4) / 2);
    string whiteSpace4 = repeatText("*", cantidadEspacios4);

    // quinta linea de texto
    const string texto5 = " Bebidas Frías ";
    int cantidadEspacios5 = ((anchoConsola - texto5.length() - 4) / 2);
    string whiteSpace5 = repeatText("*", cantidadEspacios5);

    // sexta linea de texto
    const string texto6 = " Bebidas Calientes ";
    int cantidadEspacios6 = ((anchoConsola - texto6.length() - 4) / 2);
    string whiteSpace6 = repeatText("*", cantidadEspacios6);

    cout << "| " << whiteSpace1 << colorRojo << texto1 << colorReset << whiteSpace1 << " |" << "\n\n";
    for (int i = 0; i < Entrantes.size(); i++) {
        const auto& producto = Entrantes[i];
        cout << dashString << "\n" << endl;
        cout << colorVerde << i + 1 << ". " << producto.nombre << colorReset << endl;
        cout << colorAzul << "Precio: " << colorReset << "$" << setprecision(2) << fixed << producto.precio << endl;
        cout << colorAzul << "Descripción: " << colorReset << producto.descripcion << "\n" << endl;
        cout << dashString << "\n" << endl;
    }

    cout << "| " << whiteSpace2 << colorRojo << texto2 << colorReset << whiteSpace2 << " |" << "\n\n";
    for (int i = 0; i < ComidasPrincipales.size(); i++) {
        const auto& producto = ComidasPrincipales[i];
        cout << dashString << "\n" << endl;
        cout << colorVerde << i + 1 << ". " << producto.nombre << colorReset << endl;
        cout << colorAzul << "Precio: " << colorReset << "$" << setprecision(2) << fixed << producto.precio << endl;
        cout << colorAzul << "Descripción: " << colorReset << producto.descripcion << "\n" << endl;
        cout << dashString << "\n" << endl;
    }

    cout << "| " << whiteSpace3 << colorRojo << texto3 << colorReset << whiteSpace3 << " |" << "\n\n";
    for (int i = 0; i < Pastas.size(); i++) {
        const auto& producto = Pastas[i];
        cout << dashString << "\n" << endl;
        cout << colorVerde << i + 1 << ". " << producto.nombre << colorReset << endl;
        cout << colorAzul << "Precio: " << colorReset << "$" << setprecision(2) << fixed << producto.precio << endl;
        cout << colorAzul << "Descripción: " << colorReset << producto.descripcion << "\n" << endl;
        cout << dashString << "\n" << endl;
    }

    cout << "| " << whiteSpace7 << colorRojo << texto7 << colorReset << whiteSpace7 << " |" << "\n\n";

    for (int i = 0; i < Pizzas.size(); i++) {
        const auto& producto = Pizzas[i];
        cout << dashString << "\n" << endl;
        cout << colorVerde << i + 1 << ". " << producto.nombre << colorReset << endl;
        cout << colorAzul << "Precio: " << colorReset << "$" << setprecision(2) << fixed << producto.precio << endl;
        cout << colorAzul << "Descripción: " << colorReset << producto.descripcion << "\n" << endl;
        cout << dashString << "\n" << endl;
    }

    cout << "| " << whiteSpace4 << colorRojo << texto4 << colorReset << whiteSpace4 << " |" << "\n\n";

    for (int i = 0; i < BebidasAlcoholicas.size(); i++) {
        const auto& producto = BebidasAlcoholicas[i];
        cout << dashString << "\n" << endl;
        cout << colorVerde << i + 1 << ". " << producto.nombre << colorReset << endl;
        cout << colorAzul << "Precio: " << colorReset << "$" << setprecision(2) << fixed << producto.precio << endl;
        cout << colorAzul << "Descripción: " << colorReset << producto.descripcion << "\n" << endl;
        cout << dashString << "\n" << endl;
    }

    cout << "| " << whiteSpace5 << colorRojo << texto5 << colorReset << whiteSpace5 << " |" << "\n\n";

    for (int i = 0; i < BebidasFrias.size(); i++) {
        const auto& producto = BebidasFrias[i];
        cout << dashString << "\n" << endl;
        cout << colorVerde << i + 1 << ". " << producto.nombre << colorReset << endl;
        cout << colorAzul << "Precio: " << colorReset << "$" << setprecision(2) << fixed << producto.precio << endl;
        cout << colorAzul << "Descripción: " << colorReset << producto.descripcion << "\n" << endl;
        cout << dashString << "\n" << endl;
    }

    cout << "| " << whiteSpace6 << colorRojo << texto6 << colorReset << whiteSpace6 << " |" << "\n\n";
    for (int i = 0; i < BebidasCalientes.size(); i++) {
        const auto& producto = BebidasCalientes[i];
        cout << dashString << "\n" << endl;
        cout << colorVerde << i + 1 << ". " << producto.nombre << colorReset << endl;
        cout << colorAzul << "Precio: " << colorReset << "$" << setprecision(2) << fixed << producto.precio << endl;
        cout << colorAzul << "Descripción: " << colorReset << producto.descripcion << "\n" << endl;
        cout << dashString << "\n" << endl;
    }
}

void mostrarFactura(string nombreCliente, int numeroMesa, int numeroFactura, double total, string fecha, vector<Producto> listaProductos, vector<int> Cantidades) {
    cout << "==========================================" << endl;
    cout << "           Factura " << numeroFactura << endl;
    cout << "==========================================" << endl;
    cout << "| Fecha: " << fecha << endl;
    cout << "| Cliente: " << nombreCliente << endl;
    cout << "| Mesa: " << numeroMesa << endl;
    cout << "------------------------------------------" << endl;
    cout << "|  Producto              Cantidad  Precio  Subtotal  |" << endl;
    cout << "------------------------------------------" << endl;
    for (int i = 0; i < listaProductos.size(); i++) {
        cout << "|  ";
        cout << setw(20) << left << listaProductos[i].nombre;
        cout << setw(9) << Cantidades[i];
        cout << setw(8) << fixed << setprecision(2) << listaProductos[i].precio;
        cout << setw(10) << fixed << setprecision(2) << listaProductos[i].precio * Cantidades[i];
        cout << "  |" << endl;
    }
    cout << "------------------------------------------" << endl;
    cout << "|  Total:" << setw(27) << fixed << setprecision(2) << total << "  |" << endl;
    cout << "==========================================" << endl << endl;
}

void mostrarFacturas() {
    if (Facturas.size() == 0) {
        cout << "\nNo hay facturas por mostrar. \n\n";
    }
    else {
        for (const Factura& factura : Facturas) {
            cout << "==========================================" << endl;
            cout << "           Factura " << factura.numeroFactura << endl;
            cout << "==========================================" << endl;
            cout << "Fecha: " << factura.fecha << endl;
            cout << "Cliente: " << factura.nombreCliente << endl;
            cout << "Mesa: " << factura.numeroMesa << endl;
            cout << "------------------------------------------" << endl;
            cout << "|  Producto              Cantidad  Precio  Subtotal  |" << endl;
            cout << "------------------------------------------" << endl;
            for (int i = 0; i < factura.listaProductos.size(); i++) {
                cout << "|  ";
                cout << setw(20) << left << factura.listaProductos[i].nombre;
                cout << setw(9) << factura.Cantidades[i];
                cout << setw(8) << fixed << setprecision(2) << factura.listaProductos[i].precio;
                cout << setw(10) << fixed << setprecision(2) << factura.listaProductos[i].precio * factura.Cantidades[i];
                cout << "  |" << endl;
            }
            cout << "------------------------------------------" << endl;
            cout << "|  Total:" << setw(27) << fixed << setprecision(2) << factura.total << "  |" << endl;
            cout << "==========================================" << endl << endl;
        }
    }
}


void nuevaOrden() {
    int numeroMesa, tipoProducto, numeroProducto, numeroFactura = 1;
    bool mismoCliente = false;
    char agregarOtro = 'N';
    double total = 0.0;
    int cantidadProducto = 1;
    string nombreCliente;
    vector<Producto> Pedido;
    vector<int> Cantidades;
    Producto producto;
    string fecha;

    mostrarMenu();

AgregarOtroProducto:

    cout << "¿Que platillo o bebida deseas comprar? (Escribe el número de lista correspondiente) \n";
    cout << "1. Entrantes \n";
    cout << "2. Platillos Principales \n";
    cout << "3. Pastas \n";
    cout << "4. Pizzas \n";
    cout << "5. Bebidas Frias \n";
    cout << "6. Bebidas Calientes \n";
    cout << "7. Bebidas Alcohólicas \n";
    cin >> tipoProducto;

    switch (tipoProducto)
    {
    case 1:

        if (mismoCliente) {
            cout << "Ingresa el número del producto que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de platillos que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente:";
            cin.ignore();
            getline(cin, nombreCliente);
            cout << "Ingresa el numero de mesa: ";
            cin >> numeroMesa;
            cout << "Ingresa el número del producto que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de platillos que deseas comprar: ";
            cin >> cantidadProducto;
        }

        producto = Entrantes[numeroProducto - 1];
        Pedido.push_back({ producto });
        Cantidades.push_back(cantidadProducto);
        total += producto.precio * cantidadProducto;

        cout << "¿Desea agregar otro platillo o bebida? [S/N]\n";
        cin >> agregarOtro;

        if (agregarOtro == 's' || agregarOtro == 'S') {
            mismoCliente = true;
            cantidadProducto = 0;
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();
            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });
            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);
            total = 0.0;
            cantidadProducto = 0;
            numeroFactura++;
        }

        break;
    case 2:
        if (mismoCliente) {
            cout << "Ingresa el número del producto que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de platillos que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente:";
            cin.ignore();
            getline(cin, nombreCliente);
            cout << "Ingresa el numero de mesa: ";
            cin >> numeroMesa;
            cout << "Ingresa el número del producto que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de platillos que deseas comprar: ";
            cin >> cantidadProducto;
        }

        producto = ComidasPrincipales[numeroProducto - 1];
        Pedido.push_back({ producto });
        Cantidades.push_back(cantidadProducto);

        total += producto.precio * cantidadProducto;

        cout << "¿Desea agregar otro platillo o bebida? [S/N]\n";
        cin >> agregarOtro;

        if (agregarOtro == 's' || agregarOtro == 'S') {
            mismoCliente = true;
            cantidadProducto = 0;
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();
            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });
            mostrarFactura(nombreCliente, numeroFactura, numeroMesa, total, fecha, Pedido, Cantidades);
            total = 0.0;
            cantidadProducto = 1;
            numeroFactura++;
        }

        break;
    case 3:
        if (mismoCliente) {
            cout << "Ingresa el número del platillo que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de platillos que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente:";
            cin.ignore();
            getline(cin, nombreCliente);
            cout << "Ingresa el numero de mesa: ";
            cin >> numeroMesa;
            cout << "Ingresa el número del producto que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de platillos que deseas comprar: ";
            cin >> cantidadProducto;
        }

        producto = Pastas[numeroProducto - 1];
        Pedido.push_back({ producto });
        Cantidades.push_back(cantidadProducto);
        total += producto.precio * cantidadProducto;

        cout << "¿Desea agregar otro platillo o bebida? [S/N]\n";
        cin >> agregarOtro;

        if (agregarOtro == 's' || agregarOtro == 'S') {
            mismoCliente = true;
            cantidadProducto = 0;
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();
            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });
            numeroFactura++;
            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);
            total = 0.0;
            cantidadProducto = 0;
        }

        break;
    case 4:
        if (mismoCliente) {
            cout << "Ingresa el número de la pizza que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de pizzas que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente:";
            cin.ignore();
            getline(cin, nombreCliente);
            cout << "Ingresa el numero de mesa: ";
            cin >> numeroMesa;
            cout << "Ingresa el número de pizzas que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de pizzas que deseas comprar: ";
            cin >> cantidadProducto;
        }

        producto = Pizzas[numeroProducto - 1];
        Pedido.push_back({ producto });
        Cantidades.push_back(cantidadProducto);
        total += producto.precio * cantidadProducto;

        cout << "¿Desea agregar otro platillo o bebida? [S/N]\n";
        cin >> agregarOtro;

        if (agregarOtro == 's' || agregarOtro == 'S') {
            mismoCliente = true;
            cantidadProducto = 0;
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();

            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });

            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);

            total = 0.0;
            cantidadProducto = 0;
            numeroFactura++;
        }

        break;
    case 5:
        if (mismoCliente) {
            cout << "Ingresa el número de la bebida fría que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de bebidas que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente:";
            cin.ignore();
            getline(cin, nombreCliente);
            cout << "Ingresa el numero de mesa: ";
            cin >> numeroMesa;
            cout << "Ingresa el número de bebidas frías que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de bebidas que deseas comprar: ";
            cin >> cantidadProducto;
        }

        producto = BebidasFrias[numeroProducto - 1];
        Pedido.push_back({ producto });
        Cantidades.push_back(cantidadProducto);
        total += producto.precio * cantidadProducto;

        cout << "¿Desea agregar otro platillo o bebida? [S/N]\n";
        cin >> agregarOtro;

        if (agregarOtro == 's' || agregarOtro == 'S') {
            mismoCliente = true;
            cantidadProducto = 0;
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();

            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });
            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);

            total = 0.0;
            cantidadProducto = 0;
            numeroFactura++;
        }

        break;
    case 6:
        if (mismoCliente) {
            cout << "Ingresa el número de la bebida caliente que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de bebidas que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente:";
            cin.ignore();
            getline(cin, nombreCliente);
            cout << "Ingresa el numero de mesa: ";
            cin >> numeroMesa;
            cout << "Ingresa el número de bebidas caliente que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de bebidas que deseas comprar: ";
            cin >> cantidadProducto;
        }

        producto = BebidasCalientes[numeroProducto - 1];
        Pedido.push_back({ producto });
        Cantidades.push_back(cantidadProducto);
        total += producto.precio * cantidadProducto;

        cout << "¿Desea agregar otro platillo o bebida? [S/N]\n";
        cin >> agregarOtro;

        if (agregarOtro == 's' || agregarOtro == 'S') {
            mismoCliente = true;
            cantidadProducto = 0;
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();

            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });
            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);

            total = 0.0;
            cantidadProducto = 0;
            numeroFactura++;
        }

        break;
    case 7:
        if (mismoCliente) {
            cout << "Ingresa el número de la bebida alcohólica que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de bebidas que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente:";
            cin.ignore();
            getline(cin, nombreCliente);
            cout << "Ingresa el numero de mesa: ";
            cin >> numeroMesa;
            cout << "Ingresa el número de bebidas alcohólia que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de bebidas que deseas comprar: ";
            cin >> cantidadProducto;
        }

        producto = BebidasAlcoholicas[numeroProducto - 1];
        Pedido.push_back({ producto });
        Cantidades.push_back(cantidadProducto);
        total += producto.precio * cantidadProducto;

        cout << "¿Desea agregar otro platillo o bebida? [S/N]\n";
        cin >> agregarOtro;

        if (agregarOtro == 's' || agregarOtro == 'S') {
            mismoCliente = true;
            cantidadProducto = 0;
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();

            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });
            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);
            total = 0.0;
            cantidadProducto = 0;
            numeroFactura++;
        }

        break;
    default:
        break;
    }
}

int main() {
    char accion;

    locale::global(locale("")); //Esta linea de código permite que todo lo que se muestra en consola esté en formato UTF-8

realizarOtraAccion:
    mostrarBanner();

    int opcion = mostrarOpciones();

    switch (opcion) {
    case 1:
        agregarProducto();
        break;
    case 2:
        nuevaOrden();
        break;
    case 3:
        mostrarFacturas();
        break;
    case 4:
        mostrarMenu();
        break;
    default:
        break;
    }

    cout << "\n\n\n¿Deseas realizar una acción distinta? [S/N]" << endl;
    cin >> accion;

    if (accion == 'S' || accion == 's') {
        system("cls");
        goto realizarOtraAccion;
    }

    return 0;
}