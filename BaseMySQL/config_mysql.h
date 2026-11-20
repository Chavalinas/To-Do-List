#pragma once
#include <string>

using namespace std;

struct Configuracion
{
    string host;
    string usuario;
    string password;
    string basedatos;
    unsigned int puerto;

    static Configuracion cargar();
};