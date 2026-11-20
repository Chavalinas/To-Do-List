#pragma once
#include <mysql.h>
#include <string>

using namespace std;

class BaseDAO
{
    private:
        MYSQL* conexion;
        bool conectado;

    public:
        BaseDAO();
        ~BaseDAO();

        bool conectar(const string& host, const string& usuario, const string& passw,
                    const string& db, unsigned int puerto);
        void desconectar();
        bool conf_conexion();
};