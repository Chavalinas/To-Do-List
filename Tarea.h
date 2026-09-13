#pragma once
#include <string>

using namespace std;

/** 
 * @file 
 * @brief Funciones (métodos) disponibles de la clase Tarea. Cada instancia u objeto de la clase
 * Tarea cuenta con cinco propiedades privadas (título, descripción, estado, fecha e ID). 
 * Sus métodos facilitan el visualizar la información de la tarea. 
 */

class Tarea
{
    private:
        string titulo;
        string descripcion;
        string estado;
        string fecha;
        int id; // Al ser dinámico, cada tarea cuenta con un ID único.

        static int sig_id; // Al ser estático, actúa como un contador para todas las tareas durante la ejecución del programa.

    public:
        Tarea(string titulo, string descripcion, string estado, string fecha, int id);

        string obtener_titulo();
        string obtener_descripcion();
        string obtener_estado();
        string obtener_fecha();
        int obtener_id();

        void modificar_titulo(string nuevo_titulo);
        void modificar_descripcion(string nueva_desc);
        void modificar_estado(string nuevo_estado);
};

