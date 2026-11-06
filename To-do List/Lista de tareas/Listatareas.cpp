#include "ListaTareas.h"
#include "Validaciones.h"

#include <iostream>
#include <iomanip>
#include <sstream>

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

string ListaTareas::mostrar_resumen()
{
    std::ostringstream oss;

    for (size_t i = 0; i < tareas.size(); i++)
    {
        oss << "  ["
            << tareas[i].obtener_id()
            << "] "
            << tareas[i].obtener_titulo()
            << " ("
            << tareas[i].obtener_estado()
            << ")\n";
    }

    //cuenta la cantidad de tareas para mostrar el resumen de todas las tareas y para saber si hay tareas antes de cambiar o eliminar alguna tarea
    return oss.str();
}


// ------------------- PAULINA


string ListaTareas::listarTareas()
{
    std::ostringstream oss;

    if (tareas.empty())
    {
        oss << "\nNo hay tareas registradas en la lista.\n";
        return oss.str();
    }

    //Tabla de la lista de tareas
    oss << "\n==================== LISTA DE TAREAS ====================\n\n";

    oss << left
        << setw(5) << "ID"
        << setw(35) << "Descripción"
        << setw(20) << "Estado"
        << setw(15) << "Fecha"
        << "\n";

    oss << string(75, '-') << "\n";

    for (size_t i = 0; i < tareas.size(); i++)
    {
        oss << left
            << setw(5) << tareas[i].obtener_id()
            << setw(35) << tareas[i].obtener_descripcion()
            << setw(20) << tareas[i].obtener_estado()
            << setw(15) << tareas[i].obtener_fecha()
            << "\n";
    }

    oss << string(75, '-') << "\n";

    return oss.str();
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

// ------------------ LISTAR FECHA LIMITE
void ListaTareas::listarFechaLimite() {
    cout << "\n===== TAREAS CON FECHA LIMITE =====\n";
    cout << "Nombre de la tarea\tFecha limite\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < tareas.size(); i++) {
        cout << tareas[i].obtener_titulo() << "\t\t"
             << tareas[i].obtener_fecha_limite() << endl;
    }
}

// ------------------ LISTAR TAREAS PRIORITARIAS
void ListaTareas::listarTareasPrioritarias() {
    cout << "\n===== TAREAS PRIORITARIAS =====\n";
    cout << "Nombre de la tarea\tPrioridad\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < tareas.size(); i++) {
        if (tareas[i].obtener_prioridad() == "ALTA") {
            cout << tareas[i].obtener_titulo() << "\t\t"
                 << tareas[i].obtener_prioridad() << endl;
        }
    }
}
