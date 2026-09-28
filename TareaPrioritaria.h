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
        TareaPrioritaria(string titulo, Prioridad prioridad, string descripcion, string estado, int id);

        string obtener_prioridad();
        void modificar_prioridad(Prioridad nueva_prioridad);
};

