#include <iostream>
#include <cctype>
#include <ctime> 

#include "Tarea.h"

using namespace std;


// Se inicializa el contador de IDs en 1
int Tarea::sig_id = 1;

// Constructor para la fecha actual 
string Tarea::obtener_fecha_actual()
{
    time_t tiempo_actual = time(nullptr);
    tm tiempo_local;

    localtime_s(&tiempo_local, &tiempo_actual);

    char fecha_actual[11];

    strftime(
        fecha_actual,
        sizeof(fecha_actual),
        "%d/%m/%Y",
        &tiempo_local
    );

    return string(fecha_actual);
} 


Tarea::Tarea(string titulo, string desc, string estado,int id)
{
    this->titulo = titulo;
    this->descripcion = desc;
    this->fecha = obtener_fecha_actual();
    this->estado = "pendiente";

    // Si no se proporciona un ID, se genera automáticamente
    if (id == 0)
    {
        this->id = sig_id;
        sig_id++;
    }
    else
    {
        this->id = id;
    }
}


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


void Tarea::modificar_titulo(string nuevo_titulo)
{
    titulo = nuevo_titulo;
}


void Tarea::modificar_descripcion(string nueva_desc)
{
    descripcion = nueva_desc;
}


void Tarea::modificar_estado(string nuevo_estado)
{
    for (int i = 0; i < nuevo_estado.length(); i++)
    {
        nuevo_estado[i] = static_cast<char>(
            tolower(static_cast<unsigned char>(nuevo_estado[i]))
            );
    }

    estado = nuevo_estado;
}


//renumera los id en caso de que se elimine uno 
void Tarea::modificar_id(int nuevo_id)
{
    id = nuevo_id;
}


void Tarea::actualizar_siguiente_id(int nuevo_id)
{
    sig_id = nuevo_id;
}