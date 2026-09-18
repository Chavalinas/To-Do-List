#include <iostream>
#include <string>

#include "CambiarEstado.h"
#include "Validaciones.h"

using namespace std;


// Funcion "CambiarEstado" (se conecta con To-do list.cpp)
string solicitarNuevoEstado()
{
    cout << "Selecciona el nuevo estado:\n";
    cout << "1. Pendiente\n";
    cout << "3. Completada\n";

    // Validaciones (del archivo validaciones.h)
    int opcion = leerEntero( "Opcion: ", 1,3 );

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


// Funcion "CambiarEstado"
void actualizarEstadoTarea(ListaTareas& lista)
{
    // (del archivo "ListaTareas.h") 
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

	// del archivo "CambiarEstado.h"
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
