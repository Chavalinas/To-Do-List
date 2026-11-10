#include "tareafechalimite.h"
#include "fecha.h"
#include "Validaciones y Mensajes/Validaciones.h"

#include <stdexcept>

using namespace std;

TareaFechaLimite::TareaFechaLimite(
    const string& titulo,
    const string& descripcion,
    const string& fechaLimite,
    Prioridad prioridad
)
    : TareaFechaLimite(
        titulo,
        descripcion,
        fechaLimite,
        prioridad,
        Tarea::fechaActual()
    )
{
}

TareaFechaLimite::TareaFechaLimite(
    const string& titulo,
    const string& descripcion,
    const string& fechaLimite,
    Prioridad prioridad,
    const string& fechaCreacion
)
    : Tarea(
        titulo,
        descripcion,
        fechaCreacion
    )
{
    this->prioridad = prioridad;

    if (!modificarFechaLimite(fechaLimite))
    {
        throw invalid_argument(
            "Fecha limite invalida o anterior a la creacion."
        );
    }
}

// Getter
string TareaFechaLimite::obtenerFechaLimite() const
{
    return fechaLimite;
}

// Modificador
bool TareaFechaLimite::modificarFechaLimite(const string& nuevaFecha)
{
    if (!validarFechaLimite(nuevaFecha, obtenerFechaCreacion()))
    {
        return false;
    }

    // Enter (texto vacio) significa quitar la fecha limite
    if (nuevaFecha.empty())
    {
        fechaLimite = "";
        return true;
    }

    // Se guarda siempre con el mismo formato dd/mm/aaaa
    fechaLimite = Fecha::desdeTexto(nuevaFecha).aTexto();

    return true;
}

Prioridad TareaFechaLimite::obtenerPrioridad() const
{
    return prioridad;
}

void TareaFechaLimite::modificarPrioridad(Prioridad nuevaPrioridad)
{
    prioridad = nuevaPrioridad;
}

// Polimorfismo
string TareaFechaLimite::obtenerTipo() const
{
    return "Con fecha limite";
}