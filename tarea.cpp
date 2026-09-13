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
 * @brief Métodos para obtener los valores almacenados en las propiedades de la clase Tarea.
 */


string Tarea::obtener_titulo()
{
    return titulo;
}

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

int Tarea::obtener_id()
{
    return id;
}

/***********************************************************************/

/** 
 * @file 
 * @brief Métodos para modificar los valores almacenados en las propiedades de la clase Tarea.
 */

void Tarea::modificar_titulo(string nuevo_titulo)
{
    titulo = nuevo_titulo;
    cout << "--> El título de la tarea ha sido modificado con éxito.\n";
}

void Tarea::modificar_descripcion(string nueva_desc)
{
    descripcion = nueva_desc;
    cout << "--> La descripción de la tarea ha sido modificada con éxito.\n";
}

void Tarea::modificar_estado(string nuevo_estado)
{
    estado = nuevo_estado;
    cout << "--> El estado de la tarea ha sido modificado con éxito.\n";
}