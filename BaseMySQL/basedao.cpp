#include "basedao.h"
#include "config_mysql.h"
#include <iostream>
#include <exception>

using namespace std;

BaseDAO::BaseDAO()
{
    conexion = mysql_init(nullptr);
    conectado = false;
}

BaseDAO::~BaseDAO()
{
    desconectar();
}

bool BaseDAO::conectar(const string& host, 
    const string& usuario, const string& passw,
    const string& db, unsigned int puerto)
{
    if (conexion == nullptr)
    {
        conexion = mysql_init(nullptr);
    }

    if (conexion == nullptr)
    {
        cerr << "\nERROR: Fallo en la inicialización de MySQL.\n";
        return false;
    }

    if (mysql_real_connect(conexion, host.c_str(), usuario.c_str(),
    passw.c_str(), db.c_str(), puerto, nullptr, 0) == nullptr)
    {
        cout << "\nFallo de conexión: " << mysql_error(conexion) << endl;
        return false;
    }

    conectado = true;
    cout << "--> Conexión exitosa a MySQL.\n";
    return true;
}

void BaseDAO::desconectar()
{
    if (conexion != nullptr)
    {
        mysql_close(conexion);
        conexion = nullptr;
        conectado = false;
    }
}

bool BaseDAO::conf_conexion()
{
    try
    {
        Configuracion config = Configuracion::cargar();

        return conectar(config.host, config.usuario, 
            config.password, config.basedatos, config.puerto);
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return false;
    }
}