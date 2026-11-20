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

        bool conectar(string host, string usuario, string db, unsigned int port);
        void desconectar();
        bool conf_conexion();
};