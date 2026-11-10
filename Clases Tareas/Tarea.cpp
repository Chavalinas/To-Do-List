#include "Tarea.h"
#include "../fecha.h"

using namespace std;

// Funcion para obtener la fecha actual automaticamente.
string Tarea::fechaActual()
{
    return Fecha::hoy().aTexto();
}

Tarea::Tarea(
    const string& titulo,
    const string& descripcion
)
    : Tarea(titulo, descripcion, fechaActual())
{
}

Tarea::Tarea(
    const string& titulo,
    const string& descripcion,
    const string& fechaCreacion
)
{
    this->titulo = titulo;
    this->descripcion = descripcion;
    this->fechaCreacion = fechaCreacion;

    // Estado inicial: pendiente.
    this->estado = 0;

    // El ID lo asigna ListaTareas al agregar la tarea.
    this->id = 0;
}

// Getters
string Tarea::obtenerTitulo() const
{
    return titulo;
}

string Tarea::obtenerDescripcion() const
{
    return descripcion;
}

int Tarea::obtenerEstado() const
{
    return estado;
}

string Tarea::obtenerFechaCreacion() const
{
    return fechaCreacion;
}

int Tarea::obtenerId() const
{
    return id;
}

// Setters
void Tarea::modificarTitulo(const string& nuevoTitulo)
{
    titulo = nuevoTitulo;
}

void Tarea::modificarDescripcion(
    const string& nuevaDescripcion
)
{
    descripcion = nuevaDescripcion;
}

void Tarea::modificarEstado(int nuevoEstado)
{
    estado = nuevoEstado;
}

// El ID se asigna una sola vez.
void Tarea::asignarId(int nuevoId)
{
    if (id == 0)
    {
        id = nuevoId;
    }
}