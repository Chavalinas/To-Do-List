#pragma once
#include <string>

using namespace std;

class Tarea
{
private:
    string titulo;
    string descripcion;
    string estado;
    string fecha;
    string fecha_limite;
    string prioridad;
    int id;
    static int sig_id;

    static string obtener_fecha_actual();

public:
        Tarea(string titulo, string descripcion, string estado, int id,
          string fecha_limite = "", string prioridad = "BAJA");

    string obtener_titulo();
    string obtener_descripcion();
    string obtener_estado();
    string obtener_fecha();
    string obtener_fecha_limite();
    string obtener_prioridad();
    int obtener_id();

    void modificar_titulo(string nuevo_titulo);
    void modificar_descripcion(string nueva_desc);
    void modificar_estado(string nuevo_estado);

    // (del archivo "ListaTareas.cpp")
    void modificar_id(int nuevo_id);
    static void actualizar_siguiente_id(int nuevo_id);
};