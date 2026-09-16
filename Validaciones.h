#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

int leerEntero(const std::string& mensaje, int minimo, int maximo);

std::string leerTextoNoVacio(const std::string& mensaje, std::size_t maxLargo = 100);

bool confirmar(const std::string& mensaje);

#endif
