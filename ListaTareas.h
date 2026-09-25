#pragma once

#include <vector>
#include <string>
#include "Tarea.h"

using namespace std;

/**
 * @file
 * @brief Clase ListaTareas que administra la colección de tareas.
 */

class ListaTareas
{
private:

    vector<Tarea> tareas;

public:

    // ----------- ARY 

    // Añade tareas
    void agregar_tarea(const Tarea& tarea);

    // Elimina una tarea por ID.
    bool eliminar_tarea(int id);

    // Verifica si existe una tarea por ID (validacion)
    bool existe_tarea(int id);

    // Devuelve la cantidad de tareas
    int cantidad();


    // ---------------- PAULINA 

    string listarTareas();

    string mostrar_resumen();


    // (del archivo "CambiarEstado.cpp") 

    // Conecta el cambio de estado con ListaTareas
    bool cambiar_estado(int id, string nuevo_estado);
};

// Controla el proceso completo de eliminación.
void opcion_eliminar(ListaTareas& lista);