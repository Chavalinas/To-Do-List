#include "basedao.h"
#include "config_mysql.h"
#include <iostream>
#include <exception>

using namespace std;

BaseDAO::BaseDAO()
{
    conexion = mysql_init(nullptr);
}