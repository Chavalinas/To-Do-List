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

// Reconstruye un objeto derivado a partir de una fila MySQL.
static unique_ptr<Tarea> reconstruirTarea(MYSQL_ROW fila)
{
    if (fila == nullptr)
    {
        return nullptr;
    }

    int id = atoi(fila[0]);
    string titulo = fila[1] ? fila[1] : "";
    string descripcion = fila[2] ? fila[2] : "";
    string fechaCreacion = fila[3] ? fila[3] : "";
    string fechaLimite = fila[4] ? fila[4] : "";
    string prioridadTexto = fila[5] ? fila[5] : "BAJA";
    int estado = fila[6] ? atoi(fila[6]) : 0;
    string tipo = fila[7] ? fila[7] : "";

    Prioridad prioridad =
        (prioridadTexto == "ALTA")
        ? Prioridad::ALTA
        : Prioridad::BAJA;

    unique_ptr<Tarea> tarea;

    if (tipo == "Prioritaria")
    {
        tarea = make_unique<TareaPrioritaria>(
            titulo,
            descripcion,
            prioridad,
            fechaLimite,
            fechaCreacion
        );
    }
    else if (tipo == "Con fecha limite")
    {
        tarea = make_unique<TareaFechaLimite>(
            titulo,
            descripcion,
            fechaLimite,
            prioridad,
            fechaCreacion
        );
    }
    else
    {
        cerr << "Tipo de tarea desconocido: "
             << tipo << endl;
        return nullptr;
    }

    tarea->asignarId(id);
    tarea->modificarEstado(estado);

    return tarea;
}

// ----------------- CONSTRUCTOR ----------------- //
TareaDAO::TareaDAO(BaseDAO& conexion) : db(conexion)
{}

// ----------------- INSERTAR TAREA ----------------- //

bool TareaDAO::insertar(
    const Tarea& tarea,
    int id_usuario)
{
    MYSQL* conexion = db.obtenerConexion();

    if (conexion == nullptr)
        return false;

    if (mysql_query(conexion, "START TRANSACTION") != 0)
        return false;

    string titulo = tarea.obtenerTitulo();
    string descripcion = tarea.obtenerDescripcion();
    string fechaCreacion = tarea.obtenerFechaCreacion();
    string fechaLimite = tarea.obtenerFechaLimite();
    string prioridad = prioridadATexto(tarea.obtenerPrioridad());
    string tipo = tarea.obtenerTipo();
}