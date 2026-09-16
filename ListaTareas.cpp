#include "ListaTareas.h"
#include "Validaciones.h"
#include <iostream>

void ListaTareas::agregar_tarea(const Tarea& tarea)
{
    tareas.push_back(tarea);
}

bool ListaTareas::eliminar_tarea(int id)
{
    for (size_t i = 0; i < tareas.size(); i++)
    {
        if (tareas[i].obtener_id() == id)
        {
            tareas.erase(tareas.begin() + i);
            return true;
        }
    }
    return false; // No habia ninguna tarea con ese ID
}

bool ListaTareas::existe_tarea(int id)
{
    for (size_t i = 0; i < tareas.size(); i++)
    {
        if (tareas[i].obtener_id() == id) return true;
    }
    return false;
}

int ListaTareas::cantidad()
{
    return static_cast<int>(tareas.size());
}

void ListaTareas::mostrar_resumen()
{
    for (size_t i = 0; i < tareas.size(); i++)
    {
        cout << "  [" << tareas[i].obtener_id() << "] "
             << tareas[i].obtener_titulo()
             << " (" << tareas[i].obtener_estado() << ")\n";
    }
}

void opcion_eliminar(ListaTareas& lista)
{
    if (lista.cantidad() == 0)
    {
        cout << "No hay tareas para eliminar.\n";
        return;
    }

    cout << "\n--- Eliminar tarea ---\n";
    lista.mostrar_resumen();

    int id = leerEntero("ID de la tarea a eliminar: ", 0, 1000000);

    if (!lista.existe_tarea(id))
    {
        cout << "No existe una tarea con ese ID.\n";
        return;
    }

    if (confirmar("Seguro que quieres eliminarla? (s/n): "))
    {
        lista.eliminar_tarea(id);
        cout << "Tarea eliminada.\n";
    }
    else
    {
        cout << "Operacion cancelada.\n";
    }
}
