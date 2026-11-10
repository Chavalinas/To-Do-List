#include "Listatareas.h"
#include "../fecha.h"

#include <stdexcept>
#include <utility>

using namespace std;

// CONSULTAS GENERALES

// Indica si la fecha actual debe ir despues de la siguiente.
// Las tareas sin fecha limite quedan al final.
static bool vaDespuesPorFecha(
    const string& actual,
    const string& siguiente
)
{
    if (actual.empty())
    {
        return !siguiente.empty();
    }

    if (siguiente.empty())
    {
        return false;
    }

    return Fecha::desdeTexto(siguiente)
        < Fecha::desdeTexto(actual);
}

// CONSTRUCTOR
ListaTareas::ListaTareas()
{
    siguienteId = 1;
}

// AÑADIR TAREA
int ListaTareas::agregarTarea(unique_ptr<Tarea> tarea)
{
    if (!tarea)
    {
        throw invalid_argument(
            "No se puede agregar una tarea nula."
        );
    }

    int id = siguienteId;

    tarea->asignarId(id);

    siguienteId++;

    tareas.push_back(move(tarea));

    return id;
}

// BUSCAR TAREA
Tarea* ListaTareas::buscarTarea(int id) const
{
    for (size_t i = 0; i < tareas.size(); i++)
    {
        if (tareas[i]->obtenerId() == id)
        {
            return tareas[i].get();
        }
    }

    return nullptr;
}

// ELIMINAR TAREA
// Los IDs de las demas tareas se conservan.
bool ListaTareas::eliminarTarea(int id)
{
    for (size_t i = 0; i < tareas.size(); i++)
    {
        if (tareas[i]->obtenerId() == id)
        {
            tareas.erase(tareas.begin() + i);

            return true;
        }
    }

    return false;
}

// EXISTENCIA Y CANTIDAD
bool ListaTareas::existeTarea(int id) const
{
    return buscarTarea(id) != nullptr;
}

int ListaTareas::cantidad() const
{
    return static_cast<int>(tareas.size());
}

int ListaTareas::obtenerUltimoId() const
{
    return siguienteId - 1;
}

// LISTADOS
vector<Tarea*> ListaTareas::obtenerTareas(
    TipoListado tipo
) const
{
    vector<Tarea*> vista;

    // Primero altas y despues bajas.
    if (tipo == TipoListado::PRIORIDAD)
    {
        for (size_t i = 0; i < tareas.size(); i++)
        {
            if (
                tareas[i]->obtenerPrioridad()
                == Prioridad::ALTA
                )
            {
                vista.push_back(tareas[i].get());
            }
        }

        for (size_t i = 0; i < tareas.size(); i++)
        {
            if (
                tareas[i]->obtenerPrioridad()
                == Prioridad::BAJA
                )
            {
                vista.push_back(tareas[i].get());
            }
        }

        return vista;
    }

    for (size_t i = 0; i < tareas.size(); i++)
    {
        vista.push_back(tareas[i].get());
    }

    // Ordenamiento por fecha limite con Bubble Sort.
    if (tipo == TipoListado::FECHA_LIMITE)
    {
        for (size_t i = 0; i < vista.size(); i++)
        {
            for (
                size_t j = 0;
                j + 1 < vista.size() - i;
                j++
                )
            {
                if (vaDespuesPorFecha(
                    vista[j]->obtenerFechaLimite(),
                    vista[j + 1]->obtenerFechaLimite()
                ))
                {
                    Tarea* temporal = vista[j];

                    vista[j] = vista[j + 1];

                    vista[j + 1] = temporal;
                }
            }
        }
    }

    return vista;
}

// CAMBIAR ESTADO
bool ListaTareas::cambiarEstado(
    int id,
    int nuevoEstado
)
{
    Tarea* tarea = buscarTarea(id);

    if (!tarea)
    {
        return false;
    }

    tarea->modificarEstado(nuevoEstado);

    return true;
}