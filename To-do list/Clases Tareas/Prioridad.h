// correccion: ARCHIVO NUEVO
#pragma once //correccion

#include <string> //correccion

// Prioridad de una tarea. //correccion
// Antes estaba dentro de TareaPrioritaria.h; se movio a su propio archivo //correccion
// para que la clase base Tarea pueda usarla sin depender de una clase hija. //correccion
enum class Prioridad //correccion
{
    BAJA = 0, //correccion
    ALTA = 1 //correccion
};

// Convierte la prioridad a texto para mostrarla en pantalla //correccion
inline std::string prioridadATexto(Prioridad prioridad) //correccion
{
    if (prioridad == Prioridad::ALTA) //correccion
    {
        return "ALTA"; //correccion
    }

    return "BAJA"; //correccion
}
