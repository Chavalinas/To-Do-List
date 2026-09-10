#pragma once
#include <string>

using namespace std;

class Tarea
{
    private:
        string descripcion;
        string estado;
        string fecha;

    public:
        Tarea(string descripcion, string estado, string fecha_creacion);

        void obtener_informacion();
        string obtener_descripcion();
        string obtener_estado();
        string obtener_fecha_creacion();

        void modificar_descripcion(string desc);
        void modificar_estado(string status);
        void modificar_fecha(string nueva_fecha);
};

