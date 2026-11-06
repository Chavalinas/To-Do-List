#include "menu.h"

#include "../Validaciones y Mensajes/mensajes.h"
#include "../Validaciones y Mensajes/Validaciones.h"
#include "../Lista de tareas/Listatareas.h"
#include "../Clases Tareas/Tarea.h"
#include "../fecha.h"

#include "../TareaPrioritaria.h"
#include "../tareafechalimite.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <cstdlib>
#include <exception>
#include <stdexcept>

using namespace std;

// Convierte el numero del estado a texto.
static string estadoATexto(int estado)
{
    if (estado == 0)
    {
        return "pendiente";
    }

    if (estado == 1)
    {
        return "en progreso";
    }

    return "terminada";
}

// Anchos de las columnas.
const int ANCHO_ID = 6;
const int ANCHO_TITULO = 35;
const int ANCHO_ESTADO = 16;
const int ANCHO_EXTRA = 15;

// CONSTRUCTOR
Menu::Menu(ListaTareas& lista)
    : lista(lista)
{
}

// ------------------- MENUS ------------------------------

// MENU PRINCIPAL
void Menu::mostrarMenu()
{
    limpiarPantalla();
    mostrarEncabezado();

    mensajes::showmessage(
        "\n1. Añadir tarea\n"
        "2. Listar tarea\n"
        "3. Salir del programa\n"
    );
}

// Pide una opcion de 1 hasta maximo.
int Menu::pedirSeleccion(int maximo)
{
    return pedirEntero(
        "\nSelecciona una opcion: ",
        1,
        maximo
    );
}

// Ejecuta el menu principal.
void Menu::ejecutar()
{
    bool salir = false;

    while (!salir)
    {
        mostrarMenu();

        int opcion = pedirSeleccion(3);

        switch (opcion)
        {
        case 1:
            agregarTarea();

            // Desde el inicio se muestran todas.
            salir = listarTareas(false);
            break;

        case 2:
            salir = listarTareas(true);
            break;

        case 3:
            salir = true;
            break;
        }
    }

    mensajes::showmessage(
        "\nSaliendo del programa...\n"
    );
}

// MENU LISTADO
TipoListado Menu::seleccionarListado()
{
    limpiarPantalla();
    mostrarEncabezado();

    mensajes::showmessage(
        "\n1. Listar todas las tareas\n"
        "2. Listar tareas prioritarias\n"
        "3. Listar tareas por fecha limite\n"
    );

    int opcion = pedirSeleccion(3);

    switch (opcion)
    {
    case 1:
        return TipoListado::TODAS;

    case 2:
        return TipoListado::PRIORIDAD;

    default:
        return TipoListado::FECHA_LIMITE;
    }
}

// Muestra el listado seleccionado.
void Menu::mostrarListado(TipoListado tipo)
{
    limpiarPantalla();
    mostrarEncabezado();

    if (lista.cantidad() == 0)
    {
        mensajes::showmessage(
            "\nNo hay tareas registradas en la lista.\n"
        );

        return;
    }

    vector<Tarea*> vista = lista.obtenerTareas(tipo);

    ostringstream oss;

    oss << "\n";

    if (tipo == TipoListado::PRIORIDAD)
    {
        oss << "TAREAS POR PRIORIDAD\n\n";
    }
    else if (tipo == TipoListado::FECHA_LIMITE)
    {
        oss << "TAREAS POR FECHA LIMITE\n\n";
    }
    else
    {
        oss << "TODAS LAS TAREAS\n\n";
    }

    oss << left
        << setw(ANCHO_ID) << "ID"
        << setw(ANCHO_TITULO) << "Titulo"
        << setw(ANCHO_ESTADO) << "Estado";

    if (tipo == TipoListado::PRIORIDAD)
    {
        oss << setw(ANCHO_EXTRA) << "Prioridad";
    }
    else if (tipo == TipoListado::FECHA_LIMITE)
    {
        oss << setw(ANCHO_EXTRA) << "Fecha limite";
    }

    int ancho = ANCHO_ID + ANCHO_TITULO + ANCHO_ESTADO;

    if (tipo != TipoListado::TODAS)
    {
        ancho = ancho + ANCHO_EXTRA;
    }

    oss << "\n" << string(ancho, '-') << "\n";

    for (size_t i = 0; i < vista.size(); i++)
    {
        Tarea* tarea = vista[i];

        oss << left
            << setw(ANCHO_ID) << tarea->obtenerId()
            << setw(ANCHO_TITULO) << tarea->obtenerTitulo()
            << setw(ANCHO_ESTADO)
            << estadoATexto(tarea->obtenerEstado());

        if (tipo == TipoListado::PRIORIDAD)
        {
            oss << setw(ANCHO_EXTRA)
                << prioridadATexto(tarea->obtenerPrioridad());
        }
        else if (tipo == TipoListado::FECHA_LIMITE)
        {
            string fechaLimite = tarea->obtenerFechaLimite();

            if (fechaLimite.empty())
            {
                oss << setw(ANCHO_EXTRA) << "Sin fecha";
            }
            else
            {
                oss << setw(ANCHO_EXTRA) << fechaLimite;
            }
        }

        oss << "\n";
    }

    oss << string(ancho, '-') << "\n";

    mensajes::showmessage(oss.str());
}

// MENU ACCIONES
bool Menu::listarTareas(bool elegirListado)
{
    TipoListado tipo;

    if (elegirListado)
    {
        tipo = seleccionarListado();
    }
    else
    {
        tipo = TipoListado::TODAS;
    }

    while (true)
    {
        mostrarListado(tipo);

        mensajes::showmessage(
            "\n1. Añadir tarea\n"
            "2. Eliminar tarea\n"
            "3. Modificar tarea\n"
            "4. Mostrar tarea\n"
            "5. Listar tarea\n"
            "6. Salir del programa\n"
        );

        int opcion = pedirSeleccion(6);

        switch (opcion)
        {
        case 1:
            agregarTarea();
            break;

        case 2:
            eliminarTarea();
            break;

        case 3:
            modificarTarea();
            break;

        case 4:
            mostrarTarea();
            break;

        case 5:
            tipo = seleccionarListado();
            break;

        case 6:
            return true;
        }

        // Vuelve al mismo listado y limpia la pantalla.
    }
}

// --------------- FUNCIONES ----------------------

// MODIFICAR TAREA
void Menu::modificarTarea()
{
    if (lista.cantidad() == 0)
    {
        mensajes::showmessage(
            "\nNo hay tareas.\n"
        );

        pausar();
        return;
    }

    int id = solicitarId(
        "\nID de la tarea a modificar: "
    );

    modificarTareaPorId(id);
}

// MODIFICAR LA TAREA SELECCIONADA
void Menu::modificarTareaPorId(int id)
{
    Tarea* tarea = lista.buscarTarea(id);

    if (!tarea)
    {
        mensajes::showmessage(
            "\nNo existe ninguna tarea con ese ID.\n"
        );

        pausar();
        return;
    }

    limpiarPantalla();
    mostrarEncabezado();

    mensajes::showmessage(
        formatoTarea(*tarea)
    );

    mensajes::showmessage(
        "\nQue quieres modificar?\n"
        "1. Nombre\n"
        "2. Descripcion\n"
        "3. Estado\n"
        "4. Prioridad\n"
        "5. Fecha limite\n"
        "6. Regresar\n"
    );

    int opcion = pedirSeleccion(6);

    switch (opcion)
    {
    case 1:
    {
        string nombre = pedirTextoNoVacio(
            "Nuevo nombre: "
        );

        tarea->modificarTitulo(nombre);
        break;
    }

    case 2:
    {
        string descripcion = pedirTextoOpcional(
            "Nueva descripcion "
            "(Enter para dejarla vacia): "
        );

        tarea->modificarDescripcion(descripcion);
        break;
    }

    case 3:
        lista.cambiarEstado(
            id,
            solicitarNuevoEstado()
        );
        break;

    case 4:
    {
        Prioridad prioridad = solicitarPrioridad();

        tarea->modificarPrioridad(prioridad);

        break;
    }

    case 5:
    {
        string fechaLimite = solicitarFecha(
            tarea->obtenerFechaCreacion()
        );

        if (!tarea->modificarFechaLimite(fechaLimite))
        {
            mensajes::showmessage(
                "\nNo se pudo actualizar la fecha limite.\n"
            );

            pausar();
            return;
        }

        break;
    }

    case 6:
        return;
    }

    mensajes::showmessage(
        "\nTarea modificada correctamente.\n"
    );

    pausar();
}

// SOLICITAR ESTADO
int Menu::solicitarNuevoEstado()
{
    mensajes::showmessage(
        "\n1. Pendiente\n"
        "2. En progreso\n"
        "3. Terminada\n"
    );

    int opcion = pedirEntero(
        "Selecciona el estado: ",
        1,
        3
    );

    switch (opcion)
    {
    case 1:
        return 0;

    case 2:
        return 1;

    default:
        return 2;
    }
}

// FUNCIONES DE APOYO

void Menu::limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Menu::mostrarEncabezado()
{
    mensajes::showmessage(
        "========== TO-DO LIST ==========\n"
    );
}

void Menu::pausar()
{
    mensajes::showmessage(
        "\nPresiona Enter para continuar..."
    );

    string linea;

    if (!getline(cin, linea))
    {
        throw EntradaCerrada();
    }
}

// Muestra el mensaje del error.
void Menu::mostrarError(const exception& e)
{
    mensajes::showmessage(
        string("\n") + e.what() + "\n"
    );
}

// LECTURAS CON REINTENTOS

int Menu::pedirEntero(
    const string& mensaje,
    int minimo,
    int maximo
)
{
    while (true)
    {
        try
        {
            return leerEntero(mensaje, minimo, maximo);
        }
        catch (const EntradaCerrada&)
        {
            throw;
        }
        catch (const exception& e)
        {
            mostrarError(e);
        }
    }
}

string Menu::pedirTextoNoVacio(const string& mensaje)
{
    while (true)
    {
        try
        {
            return leerTextoNoVacio(mensaje);
        }
        catch (const EntradaCerrada&)
        {
            throw;
        }
        catch (const exception& e)
        {
            mostrarError(e);
        }
    }
}

string Menu::pedirTextoOpcional(const string& mensaje)
{
    while (true)
    {
        try
        {
            return leerTextoOpcional(mensaje);
        }
        catch (const EntradaCerrada&)
        {
            throw;
        }
        catch (const exception& e)
        {
            mostrarError(e);
        }
    }
}

bool Menu::pedirConfirmacion(const string& mensaje)
{
    while (true)
    {
        try
        {
            return confirmar(mensaje);
        }
        catch (const EntradaCerrada&)
        {
            throw;
        }
        catch (const exception& e)
        {
            mostrarError(e);
        }
    }
}

// SOLICITAR ID
int Menu::solicitarId(const string& mensaje)
{
    while (true)
    {
        // Los IDs ya no se renumeran.
        int id = pedirEntero(
            mensaje,
            1,
            lista.obtenerUltimoId()
        );

        if (lista.existeTarea(id))
        {
            return id;
        }

        mensajes::showmessage(
            "\nNo existe ninguna tarea con ese ID.\n"
        );
    }
}

// SOLICITAR PRIORIDAD
Prioridad Menu::solicitarPrioridad()
{
    bool alta = pedirConfirmacion(
        "Es prioritaria? (s = ALTA / n = BAJA): "
    );

    if (alta)
    {
        return Prioridad::ALTA;
    }

    return Prioridad::BAJA;
}

// SOLICITAR FECHA LIMITE
string Menu::solicitarFecha(const string& fechaCreacion)
{
    bool introducirFecha = pedirConfirmacion(
        "Deseas introducir una fecha limite? (s/n): "
    );

    if (!introducirFecha)
    {
        return "";
    }

    while (true)
    {
        int dia = pedirEntero(
            "Introduce dia: ",
            1,
            31
        );

        int mes = pedirEntero(
            "Introduce mes: ",
            1,
            12
        );

        int anio = pedirEntero(
            "Introduce año: ",
            1,
            9999
        );

        try
        {
            // Comprueba que la fecha exista.
            Fecha fecha(dia, mes, anio);

            string fechaLimite = fecha.aTexto();

            if (validarFechaLimite(
                fechaLimite,
                fechaCreacion
            ))
            {
                return fechaLimite;
            }

            mensajes::showmessage(
                "\nLa fecha es anterior a la fecha de creacion ("
                + fechaCreacion
                + ").\n"
            );
        }
        catch (const invalid_argument& e)
        {
            mostrarError(e);
        }

        bool reintentar = pedirConfirmacion(
            "Deseas intentar otra fecha? "
            "(s/n, n = sin fecha): "
        );

        if (!reintentar)
        {
            return "";
        }

        mensajes::showmessage(
            "\nIntroduce nuevamente dia, mes y año.\n"
        );
    }
}

// AÑADIR TAREA
void Menu::agregarTarea()
{
    limpiarPantalla();
    mostrarEncabezado();

    mensajes::showmessage(
        "\nAÑADIR TAREA\n\n"
    );

    string titulo = pedirTextoNoVacio(
        "Nombre: "
    );

    string descripcion = pedirTextoOpcional(
        "Descripcion (Enter sin descripcion): "
    );

    // Se obtiene automaticamente de la computadora.
    string fechaCreacion = Tarea::fechaActual();

    string fechaLimite = solicitarFecha(fechaCreacion);

    Prioridad prioridad = solicitarPrioridad();

    unique_ptr<Tarea> nuevaTarea;

    if (fechaLimite.empty())
    {
        nuevaTarea = make_unique<TareaPrioritaria>(
            titulo,
            descripcion,
            prioridad
        );
    }
    else
    {
        nuevaTarea = make_unique<TareaFechaLimite>(
            titulo,
            descripcion,
            fechaLimite,
            prioridad
        );
    }

    mensajes::showmessage(
        "\nFecha de creacion: "
        + nuevaTarea->obtenerFechaCreacion()
        + "\n"
    );

    int id = lista.agregarTarea(move(nuevaTarea));

    mensajes::showmessage(
        "\nTarea añadida correctamente."
        "\nID asignado: "
        + to_string(id)
        + "\n"
    );

    pausar();
}

// MOSTRAR TODOS LOS DATOS DE UNA TAREA
string Menu::formatoTarea(const Tarea& tarea) const
{
    string descripcion = tarea.obtenerDescripcion();
    string fechaLimite = tarea.obtenerFechaLimite();

    if (descripcion.empty())
    {
        descripcion = "Sin descripcion";
    }

    if (fechaLimite.empty())
    {
        fechaLimite = "Sin fecha limite";
    }

    ostringstream oss;

    oss << "\nID: " << tarea.obtenerId()
        << "\nTitulo: " << tarea.obtenerTitulo()
        << "\nDescripcion: " << descripcion
        << "\nEstado: " << estadoATexto(tarea.obtenerEstado())
        << "\nPrioridad: "
        << prioridadATexto(tarea.obtenerPrioridad())
        << "\nFecha de creacion: "
        << tarea.obtenerFechaCreacion()
        << "\nFecha limite: " << fechaLimite
        << "\n";

    return oss.str();
}

// MOSTRAR TAREA
void Menu::mostrarTarea()
{
    if (lista.cantidad() == 0)
    {
        mensajes::showmessage(
            "\nNo hay tareas.\n"
        );

        pausar();
        return;
    }

    int id = solicitarId(
        "\nID de la tarea a mostrar: "
    );

    limpiarPantalla();
    mostrarEncabezado();

    mensajes::showmessage(
        formatoTarea(*lista.buscarTarea(id))
    );

    bool modificar = pedirConfirmacion(
        "\nDeseas modificar algo? (s/n): "
    );

    if (modificar)
    {
        modificarTareaPorId(id);
    }

    // Al responder no, regresa al listado.
}

// ELIMINAR TAREA
void Menu::eliminarTarea()
{
    if (lista.cantidad() == 0)
    {
        mensajes::showmessage(
            "\nNo hay tareas para eliminar.\n"
        );

        pausar();
        return;
    }

    int id = solicitarId(
        "\nID de la tarea a eliminar: "
    );

    mensajes::showmessage(
        formatoTarea(*lista.buscarTarea(id))
    );

    bool eliminar = pedirConfirmacion(
        "\nSeguro que quieres eliminarla? (s/n): "
    );

    if (eliminar)
    {
        lista.eliminarTarea(id);

        mensajes::showmessage(
            "\nTarea eliminada correctamente.\n"
        );
    }
    else
    {
        mensajes::showmessage(
            "\nOperacion cancelada.\n"
        );
    }

    pausar();
}