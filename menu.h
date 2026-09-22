#pragma once

#include <string>
#include "ListaTareas.h"


class Menu
{
public:

    void mostrarMenu();

    int pedirSeleccion();
};


// Añadir tarea
void agregarTareaUI(ListaTareas& lista);


// Listar tareas
void listarTareasUI(ListaTareas& lista);


// Cambiar estado
void actualizarEstadoTarea(ListaTareas& lista);

std::string solicitarNuevoEstado();


// Eliminar tarea
void opcion_eliminar(ListaTareas& lista);