#include "config_mysql.h"
#include <stdexcept>
#include <cstdlib>

Configuracion Configuracion::cargar()
{
    Configuracion config;

    const char* host = getenv("DB_HOST");
    const char* usuario = getenv("DB_USER");
    const char* password = getenv("DB_PASSWORD");
    const char* basedatos = getenv("DB_NAME");
    const char* puerto = getenv("DB_PORT");

    if (!host || !usuario || !password || !basedatos || !puerto)
    {
        throw runtime_error("No se han incluido todas las variables de entorno.");
    }

    config.host = host;
    config.usuario = usuario;
    config.password = password;
    config.basedatos = basedatos;
    config.puerto = stoi(puerto);

    return config;
}