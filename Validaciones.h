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

#endif
