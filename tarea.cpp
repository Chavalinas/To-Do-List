#include <iostream>
#include <windows.h>
#include "Tarea.h"

using namespace std;

/***********************************************************************/

Tarea::Tarea(string titulo, string descripcion, string estado, string fecha, int id)
{
    this->titulo = titulo;
    this->descripcion = descripcion;
    this->estado = estado;
    this->fecha = fecha;
    this->id = id;
}

/***********************************************************************/

/** 
 * @file 
 * @brief Funciones (métodos) disponibles de la clase Estudiante. Cada instancia u objeto de la clase
 * Estudiante cuenta con cinco propiedades privadas (nombre, carrera, promedio, matrícula y número de 
 * materias cursando). Sus métodos facilitan el visualizar la información general del estudiante. 
 */


string Tarea::obtener_descripcion()
{
    return descripcion;
}
string Tarea::obtener_estado()
{
    return estado;
}
string Tarea::obtener_fecha()
{
    return fecha;
}

void Tarea::modificar_descripcion(string nueva_desc)
{
    descripcion = nueva_desc;
}
void Tarea::modificar_estado(string nuevo_estado)
{
    estado = nuevo_estado;
}
void Tarea::modificar_fecha(string nueva_fecha)
{
    fecha = nueva_fecha;
}