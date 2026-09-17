#pragma once

#include <string>
#include "ListaTareas.h"

// Funcion "CambiarEstado" que se conecta en "To-do list.cpp"
void actualizarEstadoTarea(ListaTareas& lista);

std::string solicitarNuevoEstado();

