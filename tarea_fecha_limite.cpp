#include <ctime>
#include <cstdio>
#include "TareaFechaLimite.h"
#include "Validaciones.h"

TareaFechaLimite::TareaFechaLimite(string titulo, string desc, string fecha_limite,  int id)
: Tarea(titulo, desc, fecha, id)
{
    this->fecha_limite = fecha_limite;
}

string TareaFechaLimite::obtener_fecha_limite() const
{
    return fecha_limite;
}


bool TareaFechaLimite::modificar_fecha_limite(string nueva_fecha)
{
    // Verifica la longitud y el formato DD/MM/YYYY.
    if (nueva_fecha.length() != 10)
    {
        return false;
    }

    if (nueva_fecha[2] != '/' || nueva_fecha[5] != '/')
    {
        return false;
    }

    // Verifica que todos los caracteres, excepto '/', sean dígitos.
    for (int i = 0; i < nueva_fecha.length(); i++)
    {
        if (i != 2 && i != 5 && 
            (nueva_fecha[i] < '0' || nueva_fecha[i] > '9'))
        {
            return false;
        }
    }

    int dia, mes, anio;

    // Extrae el día, el mes y el año.
    if (sscanf_s(nueva_fecha.c_str(), "%2d/%2d/%4d",
                 &dia, &mes, &anio) != 3)
    {
        return false;
    }

    // Verifica los rangos generales.
    if (dia < 1 || mes < 1 || mes > 12 || anio < 1)
    {
        return false;
    }

    // Días máximos de cada mes.
    int dias_mes[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    // Comprueba si el año es bisiesto.
    bool bisiesto = (anio % 4 == 0 && anio % 100 != 0)
                    || (anio % 400 == 0);

    if (bisiesto)
    {
        dias_mes[1] = 29;
    }

    // Verifica los días permitidos para el mes seleccionado.
    if (dia > dias_mes[mes - 1])
    {
        return false;
    }

    // Obtiene los componentes de la fecha de creación.
    int dia_creacion, mes_creacion, anio_creacion;

    if (sscanf_s(fecha.c_str(), "%2d/%2d/%4d",
                 &dia_creacion, &mes_creacion, &anio_creacion) != 3)
    {
        return false;
    }

    // La fecha límite no puede ser anterior a la fecha de creación.
    if (anio < anio_creacion)
    {
        return false;
    }

    if (anio == anio_creacion && mes < mes_creacion)
    {
        return false;
    }

    if (anio == anio_creacion &&
        mes == mes_creacion &&
        dia < dia_creacion)
    {
        return false;
    }

    // La fecha es válida: se actualiza el atributo.
    fecha_limite = nueva_fecha;

    return true;
}
