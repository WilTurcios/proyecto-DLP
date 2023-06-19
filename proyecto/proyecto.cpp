#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <locale>
#include <windows.h>
#include <iomanip>

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(supress : 4996)
#pragma warning(disable : 4996)


using namespace std;

/* COLORES (Secuencias de escape ANSI para los colores) */

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

// Repite el texto las veces que se indique
string repeatText(const string& text, int count) {
    string result;
    for (int i = 0; i < count; ++i) {
        result += text;
    }
    return result;
}

// Obtiene la fecha
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

int autoIncrement() {
    static int value = 1;
    return value++;
}
/* UTILIDADES */

/* ESTRUCTURAS DE DATOS, VARIABLES Y VECTORES */

// Establece los tipos de datos que debe tener un vector de productos
struct Producto {
    string nombre;
    double precio;
    string descripcion;
};

// Establece los tipos de datos que debe tener el vector de facturas
struct Factura {
    string nombreCliente;
    int numeroMesa;
    int numeroFactura;
    double total;
    string fecha;
    vector<Producto> listaProductos;
    vector<int> Cantidades;
};

// Todos los vectores de productos con la estructura de datos correspondientes
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

// El vector de factura con la estructura de datos correspondiente
vector<Factura> Facturas;

/* ESTRUCTURAS DE DATOS, VARIABLES Y VECTORES */

/* FUNCTIONES */

// Muestra el banner del negocio
void centrarTexto(string color, string texto) {
    const int anchoConsola = obtenerAnchoConsola();


    int cantidadEspacios = (anchoConsola - texto.length() - 2) / 2;
    string whiteSpace = repeatText(" ", cantidadEspacios);

    cout << whiteSpace << color << texto << colorReset << whiteSpace << "\n\n";
}

void mostrarBanner() {
    const int anchoConsola = obtenerAnchoConsola();
    string dashString = repeatText("-", anchoConsola);

    // Imprimir el texto en letras grandes con colores
    cout << colorVerde << dashString << colorReset << "\n\n";
    
    cout << "\n\n";

    centrarTexto(colorVerde, "Bienvenidos a");
    centrarTexto(colorBlanco, "LA FARINA RESTAURANT");
    centrarTexto(colorBlanco, "Somos un restaurante de comida italiana especializado en pastas.");
    centrarTexto(colorRojo, "Pero no encontrarás únicamente pastas, sino una gran variedad de platillos deliciosos");
    centrarTexto(colorRojo, "para disfrutar con amigos y familia.");


    cout << "\n\n";

    cout << colorRojo << dashString << colorReset << "\n\n";

}

// muestra las acciones que se pueden realizar dentro del programa
int mostrarOpciones() {
    int opcion;
    cout << "¿Qué acción deseas realizar?\n\n";
    cout << "1. Agregar un nuevo producto al menú.\n";
    cout << "2. Generar una nueva orden.\n";
    cout << "3. Mostrar facturas recientes.\n";

    cin >> opcion;

    return opcion;
}

// Agrega un producto a su vector correspondiente
void agregarProducto(int tipoProducto) {
    string nombre;
    double precio;
    string descripcion;
    cout << "Ingresa el nombre del platillo: \n";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingresa la descripción del platillo: \n";
    cin.ignore();
    getline(cin, descripcion);
    cout << "Ingresa el precio del platillo: \n";
    cin >> precio;

    switch (tipoProducto)
    {
    case 1: 
        Entrantes.push_back({ nombre, precio, descripcion });
        break;
    case 2:
        ComidasPrincipales.push_back({ nombre, precio, descripcion });
        break;
    case 3:
        Pastas.push_back({ nombre, precio, descripcion });
        break;
    case 4:
        Pizzas.push_back({ nombre, precio, descripcion });
        break;
    case 5:
        BebidasFrias.push_back({ nombre, precio, descripcion });
        break;
    case 6:
        BebidasCalientes.push_back({ nombre, precio, descripcion });
        break;
    case 7:
        BebidasAlcoholicas.push_back({ nombre, precio, descripcion });
        break;
    default:
        break;
    }
}

// Ejecuta la función agregarProducto y le pasa como parametro un numero que hace referencia al vector al que debe agregarse el producto nuevo
void agregarProductos() {
    int tipoProducto;

    cout << "¿Qué tipo de platillo desea agregar? (Escriba el número de lista correspondiente)." << endl;
    cout << "1. Entrantes." << endl;
    cout << "2. Comidas Principales." << endl;
    cout << "3. Pastas." << endl;
    cout << "4. Pizzas." << endl;
    cout << "5. Bebidas Frías." << endl;
    cout << "6. Bebidas Calientes." << endl;
    cout << "7. Bebidas Alcohólicas." << endl;
    cin >> tipoProducto;

    agregarProducto(tipoProducto);
}

// Recorre el vector de productos y los imprime en consola
void mostrarProductos(vector<Producto> Productos, string dashString) {
    for (int i = 0; i < Productos.size(); i++) {
        const auto& producto = Productos[i];
        cout << dashString << "\n" << endl;
        cout << colorVerde << i + 1 << ". " << producto.nombre << colorReset << endl;
        cout << colorAzul << "Precio: " << colorReset << "$" << setprecision(2) << fixed << producto.precio << endl;
        cout << colorAzul << "Descripción: " << colorReset << producto.descripcion << "\n" << endl;
        cout << dashString << "\n" << endl;
    }
}

void mostrarListaProductos(string tituloCategoria, vector<Producto> listaProductos) {
    int anchoConsola = obtenerAnchoConsola();
    string dashString = repeatText("-", anchoConsola);

    int cantidadEspacios1 = ((anchoConsola - tituloCategoria.length() - 4) / 2);
    string whiteSpace1 = repeatText("*", cantidadEspacios1);

    cout << "| " << whiteSpace1 << colorRojo << tituloCategoria << colorReset << whiteSpace1 << " |" << "\n\n";
    mostrarProductos(listaProductos, dashString);
}

// Imprime una factura generada con los productos que el cliente ha seleccionado
void mostrarFactura(
    string nombreCliente, 
    int numeroMesa, 
    int numeroFactura,
    double total,
    string fecha,
    vector<Producto> listaProductos,
    vector<int> Cantidades
) {
    string cadenaNumFactura = "Factura " + to_string(numeroFactura);
    string whiteSpaceNumFactura = repeatText(" ", ((68 - cadenaNumFactura.length())/2));
    string cadenaFecha = "| Fecha: " + fecha;
    string cadenaNombreCliente = "| Cliente: " + nombreCliente;
    string cadenaMesa = "| Mesa: " + to_string(numeroMesa);

    string cadenaIgual = repeatText("=", 70);
    string cadenaGuion = repeatText("-", 70);

        cout << cadenaIgual << endl;
        cout << "|" << whiteSpaceNumFactura << cadenaNumFactura << whiteSpaceNumFactura << "|" << endl;
        cout << cadenaIgual << endl;
        cout << setw(69) << left << cadenaFecha << "|" << endl;
        cout << setw(69) << left << cadenaNombreCliente << "|" << endl;
        cout << setw(69) << left << cadenaMesa << "|" << endl;
        cout << cadenaGuion << endl;
        cout << "|  ";
        cout << setw(35) << left << "Producto";
        cout << setw(10) << left << "Cantidad";
        cout << setw(10) << left << "Precio";
        cout << setw(10) << left << "Subtotal";
        cout << " |" << endl;
        cout << cadenaGuion << endl;
        for (int i = 0; i < listaProductos.size(); i++) {
            cout << "|  ";
            cout << setw(35) << left << listaProductos[i].nombre;
            cout << setw(10) << Cantidades[i];
            cout << "$" << setw(9) << fixed << setprecision(2) << listaProductos[i].precio;
            cout << "$" << setw(9) << fixed << setprecision(2) << listaProductos[i].precio * Cantidades[i];
            cout << " |" << endl;
        }
        cout << cadenaGuion << endl;
        cout << "|  Total: $" << setw(57) << fixed << setprecision(2) << total << " |" << endl;
        cout << cadenaIgual << endl << endl;
}

// Recolecta los datos necesario de una orden realizada por un cliente y luego se los pasa a la función mostrarFactura para generar una factura para el usuario
void nuevaOrden() {
    int numeroMesa, tipoProducto, numeroProducto;
    int numeroFactura = autoIncrement();
    bool mismoCliente = false;
    char agregarOtro = 'N';
    double total = 0.0;
    int cantidadProducto = 1;
    string nombreCliente;
    vector<Producto> Pedido;
    vector<int> Cantidades;
    Producto producto;
    string fecha;

AgregarOtroProducto:

    mostrarBanner();
    
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
        mostrarListaProductos(" Entrantes ", Entrantes);
        if (mismoCliente) {
            cout << "Ingresa el número del producto que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de platillos que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente: ";
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
            system("cls");
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();
            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });
            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);
            total = 0.0;
            cantidadProducto = 0;
        }

        break;
    case 2:
        mostrarListaProductos(" Platillos Principales ", ComidasPrincipales);

        if (mismoCliente) {
            cout << "Ingresa el número del producto que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de platillos que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente: ";
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
            system("cls");
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();
            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });
            mostrarFactura(nombreCliente, numeroFactura, numeroMesa, total, fecha, Pedido, Cantidades);
            total = 0.0;
            cantidadProducto = 1;
        }

        break;
    case 3:
        mostrarListaProductos(" Pastas ", Pastas);
        if (mismoCliente) {
            cout << "Ingresa el número del platillo que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de platillos que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente: ";
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
            system("cls");
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();
            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades});
            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);
            total = 0.0;
            cantidadProducto = 0;
        }

        break;
    case 4:
        mostrarListaProductos(" Pizzas ", Pizzas);

        if (mismoCliente) {
            cout << "Ingresa el número de la pizza que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de pizzas que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente: ";
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
            system("cls");
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();

            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });

            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);

            total = 0.0;
            cantidadProducto = 0;
        }

        break;
    case 5:
        mostrarListaProductos(" Bebidas Frías ", BebidasFrias);

        if (mismoCliente) {
            cout << "Ingresa el número de la bebida fría que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de bebidas que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente: ";
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
            system("cls");
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();

            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });
            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);

            total = 0.0;
            cantidadProducto = 0;
        }

        break;
    case 6:
        mostrarListaProductos(" Bebidas Calientes ", BebidasCalientes);

        if (mismoCliente) {
            cout << "Ingresa el número de la bebida caliente que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de bebidas que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente: ";
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
            system("cls");
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();

            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });
            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);

            total = 0.0;
            cantidadProducto = 0;
        }

        break;
    case 7:
        mostrarListaProductos(" Bebidas Alcohólicas ", BebidasAlcoholicas);

        if (mismoCliente) {
            cout << "Ingresa el número de la bebida alcohólica que deseas comprar: ";
            cin >> numeroProducto;
            cout << "Ingresa la cantidad de bebidas que deseas comprar: ";
            cin >> cantidadProducto;
        }
        else {
            cout << "Ingresa el nombre del cliente: ";
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
            system("cls");
            goto AgregarOtroProducto;
        }
        else {
            fecha = obtenerFecha();

            Facturas.push_back({ nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades });
            mostrarFactura(nombreCliente, numeroMesa, numeroFactura, total, fecha, Pedido, Cantidades);
            total = 0.0;
            cantidadProducto = 0;
        }

        break;
    default:
        break;
    }
}

/* FUNCTIONES */

/* FUNCIÓN PRINCIPAL DEL PROGRAMA */

int main() {
    char accion;

    locale::global(locale("")); //Esta linea de código permite que todo lo que se muestra en consola esté en formato UTF-8

realizarOtraAccion:
    // Muestra el banner
    mostrarBanner();

    // Muestra las acciones que se pueden realizar y guarda la seleccionada en una variables
    int opcion = mostrarOpciones();


    // Ejecuta una función según la acción que se desea realizar

    switch (opcion) {
    case 1:
        agregarProductos();
        break;
    case 2:
        nuevaOrden();
        break;
    case 3:
        if (Facturas.size() > 0) {
            for (const Factura& factura : Facturas) {
                mostrarFactura(
                    factura.nombreCliente,
                    factura.numeroMesa,
                    factura.numeroFactura,
                    factura.total,
                    factura.fecha,
                    factura.listaProductos,
                    factura.Cantidades
                );
            }
        }
        else {
            cout << "\n\nNo se ha facturado el pedido de ningun cliente. Por favor, realice un nuevo pedido primero.\n\n";
        }
        
        break;
    default:
        cout << "\n\nError: La opción ingresada no existe.\n";
        break;
    }

    // Pregunta al usuario si desea realizar una acción más y de ser el caso los regresa de nuevo al puntero indicado
    cout << "\n\n¿Deseas realizar una acción distinta? [S/N]" << endl;
    cin >> accion;

    if (accion == 'S' || accion == 's') {
        system("cls");
        goto realizarOtraAccion;
    }

    return 0;
}

/* FUNCIÓN PRINCIPAL DEL PROGRAMA */
