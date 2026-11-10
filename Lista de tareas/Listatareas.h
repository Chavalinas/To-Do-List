#pragma once

#include <vector>
#include <memory>

#include "../Clases Tareas/Tarea.h"

enum class TipoListado
{
    TODAS,
    PRIORIDAD,
    FECHA_LIMITE
};

class ListaTareas
{
private:
    std::vector<std::unique_ptr<Tarea>> tareas;

    // La lista genera los IDs.
    int siguienteId;

public:
    ListaTareas();

    // Regresa el ID asignado.
    int agregarTarea(std::unique_ptr<Tarea> tarea);

    bool eliminarTarea(int id);
    bool existeTarea(int id) const;

    int cantidad() const;
    int obtenerUltimoId() const;

    Tarea* buscarTarea(int id) const;

    // Entrega las tareas ordenadas.
    std::vector<Tarea*> obtenerTareas(
        TipoListado tipo
    ) const;

    bool cambiarEstado(int id, int nuevoEstado);
};