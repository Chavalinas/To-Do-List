#pragma once

#include <string>

#include "Clases Tareas/Tarea.h"

class TareaFechaLimite : public Tarea
{
private:
    std::string fechaLimite;
    Prioridad prioridad;

public:
    TareaFechaLimite(
        const std::string& titulo,
        const std::string& descripcion,
        const std::string& fechaLimite,
        Prioridad prioridad = Prioridad::BAJA
    );

    // Usa una fecha de creacion ya obtenida.
    TareaFechaLimite(
        const std::string& titulo,
        const std::string& descripcion,
        const std::string& fechaLimite,
        Prioridad prioridad,
        const std::string& fechaCreacion
    );

    std::string obtenerFechaLimite() const override;

    bool modificarFechaLimite(const std::string& nuevaFecha) override;

    Prioridad obtenerPrioridad() const override;

    void modificarPrioridad(Prioridad nuevaPrioridad) override;

    std::string obtenerTipo() const override;
};