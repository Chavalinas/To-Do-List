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
    int id;
    static int sig_id;

    static string obtener_fecha_actual();

public:
    Tarea(string titulo, string descripcion, string estado, int id);

    string obtener_titulo();
    string obtener_descripcion();
    string obtener_estado();
    string obtener_fecha();
    int obtener_id();

    void modificar_titulo(string nuevo_titulo);
    void modificar_descripcion(string nueva_desc);
    void modificar_estado(string nuevo_estado);

   // (del archivo "ListaTareas.cpp")
    void modificar_id(int nuevo_id);
    static void actualizar_siguiente_id(int nuevo_id);
};