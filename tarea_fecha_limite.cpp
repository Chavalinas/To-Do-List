#include <ctime>
#include <cstdio>
#include "TareaFechaLimite.h"

TareaFechaLimite::TareaFechaLimite(string titulo, string desc, string fecha, string fecha_limite, string estado, int id)
: Tarea(titulo, desc, fecha, estado, id)
{
    this->fecha_limite = fecha_limite;
}

string TareaFechaLimite::obtener_fecha_limite()
{
    return fecha_limite;
}

bool TareaFechaLimite::modificar_fecha_limite(string nueva_fecha)
{
    if (nueva_fecha.length() != 10)
    {
        return false;
    }

    // Verifica que la separación de la fecha sea a partir de '/'.
    if (nueva_fecha[2] != '/' || nueva_fecha[5] != '/')
    {
        return false;
    }

    int dia, mes, año;

    // Extrae día, mes y año de la fecha límite.
    if (sscanf_s(nueva_fecha.c_str(), "%2d/%2d/%4d", &dia, &mes, &año) != 3)
    {
        return false;
    }

    // ------ VALIDACIONES ------
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || año < 1)
    {
        return false;
    }

    // ------ VALIDACIONES (Comprueba si es real la fecha) ------
    tm fecha_validada = {};

    fecha_validada.tm_mday = dia;
    fecha_validada.tm_mon = mes - 1;
    fecha_validada.tm_year = año - 1900;

    time_t fecha_convertida = mktime(&fecha_validada);

    if (fecha_convertida == -1)
    {
        return false;
    }

    // Se obtiene la fecha de creación.
    int dia_creacion, mes_creacion, año_creacion;

    if (sscanf_s(fecha.c_str(), "%2d/%2d/%4d", &dia_creacion, &mes_creacion, &año_creacion) != 3)
    {
        return false;
    }

    // Compara ambas fechas ya que la fecha límite no puede ser antes de la fecha de creación.
    if (año < año_creacion)
    {
        return false;
    }

    if (año == año_creacion && mes < mes_creacion)
    {
        return false;
    }

    if (año == año_creacion && mes == mes_creacion && dia < dia_creacion)
    {
        return false;
    }
    
    fecha_limite = nueva_fecha;
    return true; // Al enviar true, permite comprobar el éxito de la modificación, sino envia falso.
}