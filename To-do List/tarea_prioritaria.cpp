#pragma once

#include <string>
#include "Clases Tareas/Tarea.h"

enum class Prioridad
{
    BAJA = 0,
    ALTA = 1
};

class TareaPrioritaria : public Tarea
{
private:
    Prioridad prioridad;
    std::string fechaLimite;

public:
    TareaPrioritaria(
        std::string titulo,
        std::string desc,
        Prioridad prioridad,
        int id,
        std::string fechaLimite = ""
    );

    TareaPrioritaria(
        std::string titulo,
        std::string desc,
        Prioridad prioridad
    );

    bool modificarFechaLimite(
        std::string nuevaFecha
    ) override;

    void modificarPrioridad(
        std::string nuevaPrioridad
    ) override;

    std::string obtenerPrioridad() const override;

    std::string obtenerFechaLimite() const override;

    std::string obtenerTipo() const override;
};