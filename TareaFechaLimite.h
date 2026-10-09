#pragma once
#include <string>
#include "Tarea.h"

using namespace std;

class TareaFechaLimite : public Tarea
{
    private:
        string fecha_limite;

    public:
        TareaFechaLimite(string titulo, string desc, string fecha_limite, int id);

        string obtener_fecha_limite() const;
        bool modificar_fecha_limite(string nueva_fecha);

        string obtenerFechaLimite() const override;
        string obtenerTipo() const override;
};