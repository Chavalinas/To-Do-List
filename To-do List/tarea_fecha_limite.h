#include "tareafechalimite.h"
#include "Validaciones y Mensajes/Validaciones.h"
#include "fecha.h"

#include <stdexcept>

using namespace std;

TareaFechaLimite::TareaFechaLimite(
    string titulo,
    string desc,
    string fechaLimite,
    int id,
    Prioridad prioridad
)
    : Tarea(
        titulo,
        desc,
        "",
        "pendiente",
        id
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

bool TareaFechaLimite::modificarFechaLimite(
    string nuevaFecha
)
{
    if (!validarFechaLimite(nuevaFecha, obtenerFecha()))
    {
        return false;
    }

    if (nuevaFecha.empty())
    {
        fechaLimite = "";
        return true;
    }

    fechaLimite = Fecha::desdeTexto(nuevaFecha).aTexto();

    return true;
}

void TareaFechaLimite::modificarPrioridad(
    string nuevaPrioridad
)
{
    if (nuevaPrioridad == "ALTA")
    {
        prioridad = Prioridad::ALTA;
    }
    else
    {
        prioridad = Prioridad::BAJA;
    }
}

string TareaFechaLimite::obtenerFechaLimite() const
{
    return fechaLimite;
}

string TareaFechaLimite::obtenerPrioridad() const
{
    if (prioridad == Prioridad::ALTA)
    {
        return "ALTA";
    }

    return "BAJA";
}

string TareaFechaLimite::obtenerTipo() const
{
    return "Con fecha limite";
}