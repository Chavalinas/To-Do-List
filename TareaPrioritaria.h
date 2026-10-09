#pragma once
#include <string>
#include "Tarea.h"

using namespace std;

enum class Prioridad
{
    ALTA,
    BAJA
};

class TareaPrioritaria : public Tarea
{
    private:
        Prioridad prioridad;

    public:
        TareaPrioritaria(string titulo, string desc, Prioridad prioridad, int id);

        Prioridad obtener_prioridad();
        void modificar_prioridad(Prioridad nueva_prioridad);

        string obtenerPrioridad() const override;
        string obtenerTipo() const override;
};