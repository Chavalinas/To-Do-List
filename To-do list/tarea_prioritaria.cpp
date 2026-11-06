#include "TareaPrioritaria.h"
#include "fecha.h"
#include "Validaciones y Mensajes/Validaciones.h"

#include <stdexcept>

using namespace std;

TareaPrioritaria::TareaPrioritaria(
    const string& titulo,
    const string& descripcion,
    Prioridad prioridad,
    const string& fechaLimite
)
    : Tarea(
        titulo,
        descripcion
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

//sobrecarga añadida
TareaPrioritaria::TareaPrioritaria(
    const string& titulo,
    const string& descripcion,
    Prioridad prioridad
)
    : TareaPrioritaria(titulo, descripcion, prioridad, "")
{
}

// Getter
Prioridad TareaPrioritaria::obtenerPrioridad() const
{
    return prioridad;
}

// Modificador
void TareaPrioritaria::modificarPrioridad(Prioridad nuevaPrioridad)
{
    prioridad = nuevaPrioridad;
}

string TareaPrioritaria::obtenerFechaLimite() const
{
    return fechaLimite;
}

bool TareaPrioritaria::modificarFechaLimite(const string& nuevaFecha)
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

// Polimorfismo
string TareaPrioritaria::obtenerTipo() const
{
    return "Prioritaria";
}