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

    int estado = tarea.obtenerEstado();

    string consulta =
        "INSERT INTO tarea "
        "(nombre, descripcion, fecha_creacion, fecha_limite, "
        "prioridad, estado, tipo) "
        "VALUES (?, ?, "
        "STR_TO_DATE(?, '%d/%m/%Y'), "
        "STR_TO_DATE(NULLIF(?, ''), '%d/%m/%Y'), "
        "?, ?, ?)";

    MYSQL_BIND parametros[7]{};

    unsigned long longitudes[6]{};

    vincularTexto(parametros[0], titulo, longitudes[0]);
    vincularTexto(parametros[1], descripcion, longitudes[1]);
    vincularTexto(parametros[2], fechaCreacion, longitudes[2]);
    vincularTexto(parametros[3], fechaLimite, longitudes[3]);
    vincularTexto(parametros[4], prioridad, longitudes[4]);
    vincularEntero(parametros[5], estado);
    vincularTexto(parametros[6], tipo, longitudes[5]);

    if (!ejecutarPreparada(conexion, consulta, parametros, 7))
    {
        mysql_query(conexion, "ROLLBACK");
        return false;
    }

    // Recuperar el ID generado por AUTO_INCREMENT.
    int id_tarea = static_cast<int>(mysql_insert_id(conexion));

    string consultaRelacion =
        "INSERT INTO tarea_usuario (id_tarea, id_usuario) "
        "VALUES (?, ?)";

    MYSQL_BIND relacion[2]{};

    int idUsuario = id_usuario;

    vincularEntero(relacion[0], id_tarea);
    vincularEntero(relacion[1], idUsuario);

    if (!ejecutarPreparada(
            conexion, consultaRelacion, relacion, 2))
    {
        mysql_query(conexion, "ROLLBACK");
        return false;
    }

    if (mysql_query(conexion, "COMMIT") != 0)
    {
        mysql_query(conexion, "ROLLBACK");
        return false;
    }

    cout << "Tarea guardada correctamente." << endl;

    return true;
}

// ----------------- BUSCAR TAREA CON ID ----------------- //

unique_ptr<Tarea> TareaDAO::buscar_conId(
    int id_tarea,
    int id_usuario)
{
    MYSQL* conexion = db.obtenerConexion();

    if (conexion == nullptr)
        return nullptr;

    string consulta =
        "SELECT t.id_tarea, t.nombre, t.descripcion, "
        "DATE_FORMAT(t.fecha_creacion, '%d/%m/%Y'), "
        "COALESCE(DATE_FORMAT(t.fecha_limite, '%d/%m/%Y'), ''), "
        "t.prioridad, t.estado, t.tipo "
        "FROM tarea t "
        "INNER JOIN tarea_usuario tu "
        "ON t.id_tarea = tu.id_tarea "
        "WHERE t.id_tarea = " + to_string(id_tarea) +
        " AND tu.id_usuario = " + to_string(id_usuario) +
        " AND t.fecha_eliminacion IS NULL";

    if (mysql_query(conexion, consulta.c_str()) != 0)
    {
        cerr << mysql_error(conexion) << endl;
        return nullptr;
    }

    MYSQL_RES* resultado = mysql_store_result(conexion);

    if (resultado == nullptr)
        return nullptr;

    MYSQL_ROW fila = mysql_fetch_row(resultado);

    unique_ptr<Tarea> tarea = nullptr;

    if (fila != nullptr)
    {
        try
        {
            tarea = reconstruirTarea(fila);
        }
        catch (const exception& e)
        {
            cerr << "Error al reconstruir tarea: "
                 << e.what() << endl;
        }
    }

    mysql_free_result(resultado);

    return tarea;
}

// ----------------- OBTENER TODAS LAS TAREAS DEL USUARIO ----------------- //

vector<unique_ptr<Tarea>> TareaDAO::obtenerTareas(
    int id_usuario)
{
    vector<unique_ptr<Tarea>> tareas;

    MYSQL* conexion = db.obtenerConexion();

    if (conexion == nullptr)
        return tareas;

    string consulta =
        "SELECT t.id_tarea, t.nombre, t.descripcion, "
        "DATE_FORMAT(t.fecha_creacion, '%d/%m/%Y'), "
        "COALESCE(DATE_FORMAT(t.fecha_limite, '%d/%m/%Y'), ''), "
        "t.prioridad, t.estado, t.tipo "
        "FROM tarea t "
        "INNER JOIN tarea_usuario tu "
        "ON t.id_tarea = tu.id_tarea "
        "WHERE tu.id_usuario = " + to_string(id_usuario) +
        " AND t.fecha_eliminacion IS NULL "
        "ORDER BY t.id_tarea";

    if (mysql_query(conexion, consulta.c_str()) != 0)
    {
        cerr << "Error al consultar tareas: "
             << mysql_error(conexion) << endl;

        return tareas;
    }

    MYSQL_RES* resultado = mysql_store_result(conexion);

    if (resultado == nullptr)
        return tareas;

    MYSQL_ROW fila;

    while ((fila = mysql_fetch_row(resultado)) != nullptr)
    {
        try
        {
            unique_ptr<Tarea> tarea = reconstruirTarea(fila);

            if (tarea != nullptr)
                tareas.push_back(move(tarea));
        }
        catch (const exception& e)
        {
            cerr << "Error al recuperar tarea: "
                 << e.what() << endl;
        }
    }

    mysql_free_result(resultado);

    return tareas;
}

// ----------------- ACTUALIZAR TAREA ----------------- //

bool TareaDAO::actualizarTarea(
    const Tarea& tarea,
    int id_usuario)
{
    MYSQL* conexion = db.obtenerConexion();

    if (conexion == nullptr)
        return false;

    string titulo = tarea.obtenerTitulo();
    string descripcion = tarea.obtenerDescripcion();
    string fechaLimite = tarea.obtenerFechaLimite();
    string prioridad = prioridadATexto(tarea.obtenerPrioridad());
    string tipo = tarea.obtenerTipo();

    int estado = tarea.obtenerEstado();
    int id = tarea.obtenerId();
    int usuario = id_usuario;

    string consulta =
        "UPDATE tarea t "
        "INNER JOIN tarea_usuario tu "
        "ON t.id_tarea = tu.id_tarea "
        "SET t.nombre = ?, "
        "t.descripcion = ?, "
        "t.fecha_limite = STR_TO_DATE(NULLIF(?, ''), '%d/%m/%Y'), "
        "t.prioridad = ?, "
        "t.estado = ?, "
        "t.tipo = ? "
        "WHERE t.id_tarea = ? "
        "AND tu.id_usuario = ?";

    MYSQL_BIND parametros[8]{};

    unsigned long longitudes[5]{};

    vincularTexto(parametros[0], titulo, longitudes[0]);
    vincularTexto(parametros[1], descripcion, longitudes[1]);
    vincularTexto(parametros[2], fechaLimite, longitudes[2]);
    vincularTexto(parametros[3], prioridad, longitudes[3]);
    vincularEntero(parametros[4], estado);
    vincularTexto(parametros[5], tipo, longitudes[4]);
    vincularEntero(parametros[6], id);
    vincularEntero(parametros[7], usuario);

    if (!ejecutarPreparada(conexion, consulta, parametros, 8))
        return false;

    cout << "Tarea actualizada correctamente." << endl;

    return true;
}

// ----------------- ELIMINAR TAREA (PERMANENTE) ----------------- //

bool TareaDAO::eliminarTarea(
    int id_tarea,
    int id_usuario)
{
    MYSQL* conexion = db.obtenerConexion();

    if (conexion == nullptr)
        return false;

    if (mysql_query(conexion, "START TRANSACTION") != 0)
        return false;

    // Verificar que la tarea pertenece al usuario.
    string verificar =
        "SELECT id_tarea FROM tarea_usuario "
        "WHERE id_tarea = " + to_string(id_tarea) +
        " AND id_usuario = " + to_string(id_usuario);

    if (mysql_query(conexion, verificar.c_str()) != 0)
    {
        mysql_query(conexion, "ROLLBACK");
        return false;
    }

    MYSQL_RES* resultado = mysql_store_result(conexion);

    if (resultado == nullptr)
    {
        mysql_query(conexion, "ROLLBACK");
        return false;
    }

    bool existe = mysql_num_rows(resultado) > 0;

    mysql_free_result(resultado);

    if (!existe)
    {
        mysql_query(conexion, "ROLLBACK");
        return false;
    }

    // Eliminar la relacion del usuario con la tarea.
    string eliminarRelacion =
        "DELETE FROM tarea_usuario "
        "WHERE id_tarea = " + to_string(id_tarea) +
        " AND id_usuario = " + to_string(id_usuario);

    if (mysql_query(conexion, eliminarRelacion.c_str()) != 0)
    {
        mysql_query(conexion, "ROLLBACK");
        return false;
    }

    // Comprobar si quedan otros usuarios relacionados.
    string comprobar =
        "SELECT id_tarea FROM tarea_usuario "
        "WHERE id_tarea = " + to_string(id_tarea);

    if (mysql_query(conexion, comprobar.c_str()) != 0)
    {
        mysql_query(conexion, "ROLLBACK");
        return false;
    }

    resultado = mysql_store_result(conexion);

    if (resultado == nullptr)
    {
        mysql_query(conexion, "ROLLBACK");
        return false;
    }

    bool tieneUsuarios = mysql_num_rows(resultado) > 0;

    mysql_free_result(resultado);

    // Si no quedan usuarios, eliminar definitivamente.
    if (!tieneUsuarios)
    {
        string eliminarTarea =
            "DELETE FROM tarea WHERE id_tarea = " +
            to_string(id_tarea);

        if (mysql_query(conexion, eliminarTarea.c_str()) != 0)
        {
            mysql_query(conexion, "ROLLBACK");
            return false;
        }
    }

    if (mysql_query(conexion, "COMMIT") != 0)
    {
        mysql_query(conexion, "ROLLBACK");
        return false;
    }

    cout << "Tarea eliminada correctamente." << endl;

    return true;
}
