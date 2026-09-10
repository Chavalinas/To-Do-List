#pragma once
#include <string>

using namespace std;

/** 
 * @file 
 * @brief Funciones (métodos) disponibles de la clase Estudiante. Cada instancia u objeto de la clase
 * Estudiante cuenta con cinco propiedades privadas (nombre, carrera, promedio, matrícula y número de 
 * materias cursando). Sus métodos facilitan el visualizar la información general del estudiante. 
 */

class Tarea
{
    private:
        string titulo;
        string descripcion;
        string estado;
        string fecha;
        int id;

    public:
        Tarea(string titulo, string descripcion, string estado, string fecha, int id);

        string obtener_descripcion();
        string obtener_estado();
        string obtener_fecha_creacion();

        void modificar_descripcion(string desc);
        void modificar_estado(string status);
        void modificar_fecha(string nueva_fecha);
};

