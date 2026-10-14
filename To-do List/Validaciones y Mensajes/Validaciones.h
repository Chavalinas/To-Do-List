#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

// Pide un numero entero entre minimo y maximo (inclusive).
// Repite la pregunta hasta que el usuario escriba algo valido.
int leerEntero(const std::string& mensaje, int minimo, int maximo);

// Pide un texto que no este vacio ni sea solo espacios.
std::string leerTextoNoVacio(const std::string& mensaje, std::size_t maxLargo = 100);

// Pregunta s/n y regresa true si el usuario confirma.
bool confirmar(const std::string& mensaje);

// ---------------- NUEVAS VALIDACIONES (issue #21)

// Dias que tiene un mes (toma en cuenta anios bisiestos).
int diasDelMes(int mes, int anio);

// Revisa una fecha dd/mm/aaaa: formato, dia, mes y que exista realmente.
// Lanza una excepcion con el error si algo esta mal.
void validarFecha(const std::string& fecha);

// Pide la fecha limite y regresa el texto ya validado.
std::string leerFecha(const std::string& mensaje);

// Pide la prioridad (1 = Alta, 2 = Baja); rechaza cualquier otra opcion.
// Regresa "ALTA" o "BAJA".
std::string leerPrioridad(const std::string& mensaje);

#endif