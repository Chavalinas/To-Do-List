#pragma once

#include <string>
#include "ListaTareas.h"

using namespace std;


// ==================== CLASE MENU ====================

class Menu
{
public:

    void mostrarMenu();

    int pedirSeleccion();
};


// ==================== FUNCIONES ====================

// Añadir tarea
void agregarTareaUI(ListaTareas& lista);

// Listar tareas
void listarTareasUI(ListaTareas& lista);

// Cambiar estado
string solicitarNuevoEstado();

void actualizarEstadoTarea(ListaTareas& lista);

// Eliminar tarea
void opcion_eliminar(ListaTareas& lista);