#include "ListaTareas.h"
#include "Validaciones.h"

#include <iostream>
#include <iomanip>

using namespace std;



  // ------------------ ARY


void ListaTareas::agregar_tarea(const Tarea& tarea)
{
    tareas.push_back(tarea);
	//funcion  que ordena las tareas (si hay una tarea1 y se crea una tarea2, la tarea2 se coloca despues de la tarea1)
}



bool ListaTareas::eliminar_tarea(int id)
{
    for (size_t i = 0; i < tareas.size(); i++)
    {
        if (tareas[i].obtener_id() == id)
        {
            tareas.erase(tareas.begin() + i);

            
            for (size_t j = 0; j < tareas.size(); j++)
            {
                tareas[j].modificar_id(static_cast<int>(j + 1));
            }

      
            Tarea::actualizar_siguiente_id(
                static_cast<int>(tareas.size()) + 1
            );

            return true;
			//condicion que resta el id de las tareas cuando una se elimina
        }
    }

    return false; // No había ninguna tarea con ese ID.
}


bool ListaTareas::existe_tarea(int id)
{
    for (size_t i = 0; i < tareas.size(); i++)
    {
        if (tareas[i].obtener_id() == id)
        {
            return true;
        }
    }

    return false;
    // busca si existe una tarea con el ID ingresado. Si la encuentra devuelve true; si no, devuelve false
}

int ListaTareas::cantidad()
{
    return static_cast<int>(tareas.size());
}

void ListaTareas::mostrar_resumen()
{
    for (size_t i = 0; i < tareas.size(); i++)
    {
        cout << "  ["
            << tareas[i].obtener_id()
            << "] "
            << tareas[i].obtener_titulo()
            << " ("
            << tareas[i].obtener_estado()
            << ")\n";
    }

//cuenta la cantidad de tareas para mostrar el resumen de todas las tareas y para saber si hay tareas antes de cambiar o eliminar alguna tarea
}


  // ------------------- PAULINA


void ListaTareas::listarTareas()
{
    if (tareas.empty())
    {
        cout << "\nNo hay tareas registradas en la lista.\n";
        return;
    }

	//Tabla de la lista de tareas
    cout << "\n==================== LISTA DE TAREAS ====================\n\n";

    cout << left
        << setw(5) << "ID"
        << setw(35) << "Descripción"
        << setw(20) << "Estado"
        << setw(15) << "Fecha"
        << "\n";

    cout << string(75, '-') << "\n";

    for (size_t i = 0; i < tareas.size(); i++)
    {
        cout << left
            << setw(5) << tareas[i].obtener_id()
            << setw(35) << tareas[i].obtener_descripcion()
            << setw(20) << tareas[i].obtener_estado()
            << setw(15) << tareas[i].obtener_fecha()
            << "\n";
    }

    cout << string(75, '-') << "\n";
}



// ---------------- CONEXIÓN EL ARCHIVO "CambiarEstado.cpp"


bool ListaTareas::cambiar_estado(int id, string nuevo_estado)
{
    for (size_t i = 0; i < tareas.size(); i++)
    {
        if (tareas[i].obtener_id() == id)
        {
            tareas[i].modificar_estado(nuevo_estado);
            return true;
        }
    }

    return false;
    //busca la tarea con el ID para cambiar el estado 
}


