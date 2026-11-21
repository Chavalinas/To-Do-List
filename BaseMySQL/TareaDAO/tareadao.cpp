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

// Ejecuta una consulta preparada.
static bool ejecutarPreparada(
    MYSQL* conexion,
    const string& consulta,
    MYSQL_BIND* parametros,
    unsigned long cantidad)
{
    MYSQL_STMT* stmt = mysql_stmt_init(conexion);

    if (stmt == nullptr)
    {
        cerr << "Error al inicializar consulta: "
             << mysql_error(conexion) << endl;
        return false;
    }

    if (mysql_stmt_prepare(
            stmt, consulta.c_str(),
            static_cast<unsigned long>(consulta.size())) != 0)
    {
        cerr << "Error al preparar consulta: "
             << mysql_stmt_error(stmt) << endl;

        mysql_stmt_close(stmt);
        return false;
    }

    if (cantidad > 0 &&
        mysql_stmt_bind_param(stmt, parametros) != 0)
    {
        cerr << "Error al vincular parametros: "
             << mysql_stmt_error(stmt) << endl;

        mysql_stmt_close(stmt);
        return false;
    }

    if (mysql_stmt_execute(stmt) != 0)
    {
        cerr << "Error al ejecutar consulta: "
             << mysql_stmt_error(stmt) << endl;

        mysql_stmt_close(stmt);
        return false;
    }

    mysql_stmt_close(stmt);
    return true;
}
