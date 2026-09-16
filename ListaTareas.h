#pragma once
#include <vector>
#include "Tarea.h"

/**
 * @file
 * @brief Clase ListaTareas: administra una coleccion de objetos Tarea en memoria.
 */

class ListaTareas
{
    private:
        vector<Tarea> tareas; // Coleccion de objetos Tarea

    public:
        void agregar_tarea(const Tarea& tarea);
        bool eliminar_tarea(int id);   // Regresa true si la encontro y la borro
        bool existe_tarea(int id);
        int cantidad();
        void mostrar_resumen();        // Muestra ID y titulo de cada tarea
};

// Opcion del menu: pide el ID, valida, confirma y elimina.
void opcion_eliminar(ListaTareas& lista);
