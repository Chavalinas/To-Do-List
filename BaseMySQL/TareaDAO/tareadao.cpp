#include "TareaDAO.h"
#include "TareaPrioritaria.h"
#include "tareafechalimite.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// ----------------- FUNCIONES AUXILIARES ----------------- //

// Vincula una cadena a un parametro SQL.
static void vincularTexto(
    MYSQL_BIND& parametro,
    string& valor,
    unsigned long& longitud)
{
    longitud = static_cast<unsigned long>(valor.size());

    parametro.buffer_type = MYSQL_TYPE_STRING;
    parametro.buffer = const_cast<char*>(valor.c_str());
    parametro.buffer_length = longitud;
    parametro.length = &longitud;
}

// Vincula un entero a un parametro SQL.
static void vincularEntero(
    MYSQL_BIND& parametro,
    int& valor)
{
    parametro.buffer_type = MYSQL_TYPE_LONG;
    parametro.buffer = &valor;
}
