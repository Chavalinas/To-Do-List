#pragma once
#include <string>
#include "Tarea.h"

using namespace std;

class TareaFechaLimite : public Tarea
{
    private:
        string fecha_limite;

    public:
        TareaFechaLimite(string titulo, string desc, string fecha, string fecha_limite, string estado, int id);

        string obtener_fecha_limite();
        bool modificar_fecha_limite(string nueva_fecha);
};