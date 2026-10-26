#pragma once

#include <string>

#include "Clases Tareas/Tarea.h"
#include "TareaPrioritaria.h"

class TareaFechaLimite : public Tarea
{
private:
    std::string fechaLimite;
    Prioridad prioridad;

public:
    TareaFechaLimite(
        std::string titulo,
        std::string desc,
        std::string fechaLimite,
        int id,
        Prioridad prioridad = Prioridad::BAJA
    );

    bool modificarFechaLimite(
        std::string nuevaFecha
    ) override;

    void modificarPrioridad(
        std::string nuevaPrioridad
    ) override;

    std::string obtenerFechaLimite() const override;

    std::string obtenerPrioridad() const override;

    std::string obtenerTipo() const override;
};