#include <iostream>
#include <string>

#include "menu.h"
#include "ListaTareas.h"
#include "Validaciones.h"
#include "Tarea.h"

using namespace std;


// ==================== MENÚ PRINCIPAL ====================

void Menu::mostrarMenu()
{
    cout << "\n========== TO-DO LIST ==========\n";
    cout << "1. Añadir tarea\n";
    cout << "2. Listar tareas\n";
    cout << "3. Cambiar estado\n";
    cout << "4. Eliminar tarea\n";
    cout << "5. Salir\n";
    cout << "================================\n";
}


int Menu::pedirSeleccion()
{
    int seleccion;

    cout << "Selecciona una opcion: ";

    cin >> seleccion;

    return seleccion;
}

// ============ FUNCIONES ================ 

//AÑADIR TAREA

void agregarTareaUI(ListaTareas& lista)
{
    cout << "\n========== AÑADIR TAREA ==========\n";

    string titulo = leerTextoNoVacio(
        "Ingresa el titulo de la tarea: "
    );

    string descripcion = leerTextoNoVacio(
        "Ingresa la descripcion de la tarea: "
    );

    string fecha = leerTextoNoVacio(
        "Ingresa la fecha de la tarea: "
    );

    cout << "\nSelecciona el estado inicial:\n";
    cout << "1. Pendiente\n";
    cout << "2. En progreso\n";
    cout << "3. Completada\n";

    int opcionEstado = leerEntero("Opcion: ", 1, 3);
    string estado;

    switch (opcionEstado)
    {
    case 1:
        estado = "pendiente";
        break;

    case 2:
        estado = "en progreso";
        break;

    case 3:
        estado = "completada";
        break;
    }

    Tarea nuevaTarea(
        titulo,
        descripcion,
        estado,
        fecha,
        0
    );

    lista.agregar_tarea(nuevaTarea);

    cout << "\nTarea añadida correctamente.\n";

    cout << "ID asignado: "
        << nuevaTarea.obtener_id()
        << "\n";
}


//LISTAR TAREAS 

void listarTareasUI(ListaTareas& lista)
{
    lista.listarTareas();
}


// CAMBIAR ESTADO

string solicitarNuevoEstado()
{
    cout << "Selecciona el nuevo estado:\n";
    cout << "1. Pendiente\n";
    cout << "2. En progreso\n";
    cout << "3. Completada\n";

    int opcion = leerEntero(
        "Opcion: ",
        1,
        3
    );

    switch (opcion)
    {
    case 1:
        return "pendiente";

    case 2:
        return "en progreso";

    case 3:
        return "completada";

    default:
        return "";
    }
}


void actualizarEstadoTarea(ListaTareas& lista)
{
    lista.listarTareas();

    if (lista.cantidad() == 0)
    {
        return;
    }

    int idTarea = leerEntero(
        "Ingresa el ID de la tarea a modificar: ",
        1,
        1000000
    );

    if (!lista.existe_tarea(idTarea))
    {
        cout << "Error: no existe ninguna tarea con el ID "
            << idTarea
            << ".\n";

        return;
    }

    string nuevoEstado = solicitarNuevoEstado();

    if (lista.cambiar_estado(
        idTarea,
        nuevoEstado
    ))
    {
        cout << "Tarea ["
            << idTarea
            << "] actualizada correctamente a '"
            << nuevoEstado
            << "'.\n";
    }
    else
    {
        cout << "Error: no se pudo actualizar el estado.\n";
    }
}

//ELIMINAR TAREA 

void opcion_eliminar(ListaTareas& lista)
{
    if (lista.cantidad() == 0)
    {
        cout << "\nNo hay tareas para eliminar.\n";
        return;
    }

    cout << "\n========== ELIMINAR TAREA ==========\n";

    lista.mostrar_resumen();

    int id = leerEntero(
        "ID de la tarea a eliminar: ",
        1,
        1000000
    );

    if (!lista.existe_tarea(id))
    {
        cout << "No existe una tarea con ese ID.\n";
        return;
    }

    if (confirmar("¿Seguro que quieres eliminarla? (s/n): "))
    {
        lista.eliminar_tarea(id);

        cout << "Tarea eliminada correctamente.\n";
    }
    else
    {
        cout << "Operación cancelada.\n";
    }
}