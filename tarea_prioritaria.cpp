#include "TareaPrioritaria.h"

TareaPrioritaria::TareaPrioritaria(string titulo, string desc, Prioridad prioridad, int id)
: Tarea(titulo, desc, fecha, estado, id)
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

// Polimorfismo
string TareaPrioritaria::obtenerPrioridad() const
{
    if (prioridad == Prioridad::ALTA)
    {
        return "ALTA";
    }

    return "BAJA";
}

string TareaPrioritaria::obtenerTipo() const
{
    return "Prioritaria";
}