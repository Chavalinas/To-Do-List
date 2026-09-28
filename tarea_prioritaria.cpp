#include <iostream>
#include "TareaPrioritaria.h"

TareaPrioritaria::TareaPrioritaria(string titulo, Prioridad prioridad, string desc, string estado, int id)
: Tarea(titulo, desc, estado, id)
{
    this->prioridad = prioridad;
}


Prioridad TareaPrioritaria::obtener_prioridad()
{
    return prioridad;
}

void TareaPrioritaria::modificar_prioridad(Prioridad nueva_prioridad)
{
    prioridad = nueva_prioridad;
}