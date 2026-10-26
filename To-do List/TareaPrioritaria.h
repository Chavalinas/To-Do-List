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

    //sobrecarga añadida
    TareaPrioritaria(
        std::string titulo,
        std::string desc,
        Prioridad prioridad
    );

    // Misma firma que en Tarea + override
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