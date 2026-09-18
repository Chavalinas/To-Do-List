#include <iostream>
#include <windows.h>
#include <cctype>
#include "Tarea.h"

using namespace std;

/***********************************************************************/

Tarea::Tarea(string titulo, string desc, string estado, string fecha, int id)
{
    this->titulo = titulo;
    this->descripcion = descripcion;
    this->estado = estado;
    this->fecha = fecha;

    if (estado == "pendiente" || estado == "en progreso" || estado == "completada")
    {
        this->estado = estado;
    }
    else
    {
        cout << "ERROR : Ha ingresado un estado inválido.\n";
        cout << "El estado por defecto de su tarea es ahora : PENDIENTE.\n";
        this->estado = "pendiente";
    }

    this->id = sig_id;
    sig_id++;
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
    for (int i = 0; i < nuevo_estado.length(); i++)
    {
        nuevo_estado[i] = tolower(nuevo_estado[i]);
    }

    if (nuevo_estado == "pendiente" || nuevo_estado == "en progreso" || nuevo_estado == "completada")
    {
        estado = nuevo_estado;
        cout << "--> El estado de la tarea ha sido modificado con éxito.\n";
    }
    else
    {
        cout << "ERROR : Ha ingresado un estado inválido. Intente de nuevo.\n";
    }
}

void Tarea::modificar_id(int nuevo_id)
{
    id = nuevo_id;
}

void Tarea::actualizar_siguiente_id(int nuevo_id)
{
    sig_id = nuevo_id;
}