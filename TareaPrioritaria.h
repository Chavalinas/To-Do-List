#pragma once

#include <string>
#include "Clases Tareas/Tarea.h"

class TareaPrioritaria : public Tarea
{
private:
    Prioridad prioridad;
    std::string fechaLimite;

public:
    TareaPrioritaria(
        const std::string& titulo,
        const std::string& descripcion,
        Prioridad prioridad,
        const std::string& fechaLimite
    );

    //sobrecarga añadida
    TareaPrioritaria(
        const std::string& titulo,
        const std::string& descripcion,
        Prioridad prioridad
    );

    // Usa una fecha de creacion ya obtenida.
    TareaPrioritaria(
        const std::string& titulo,
        const std::string& descripcion,
        Prioridad prioridad,
        const std::string& fechaLimite,
        const std::string& fechaCreacion
    );

    Prioridad obtenerPrioridad() const override;

    void modificarPrioridad(Prioridad nuevaPrioridad) override;

    std::string obtenerFechaLimite() const override;

    bool modificarFechaLimite(const std::string& nuevaFecha) override;

    std::string obtenerTipo() const override;
};