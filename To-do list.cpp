#include <iostream>
#include <exception>
#include <dotenv.h>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include "Lista de tareas/Listatareas.h"
#include "Validaciones y Mensajes/Validaciones.h"
#include "menu/menu.h"

#include "BaseMySQL/config_mysql.h"
#include "BaseMySQL/basedao.h"
#include "BaseMySQL/TareaDAO/tareadao.h"

using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    ListaTareas lista;
    Menu menu(lista);

    try
    {
        dotenv::init(); 
        Configuracion config = Configuracion::cargar();
        BaseDAO db;

        if (!db.conectar(
                config.host,
                config.usuario,
                config.password,
                config.basedatos,
                config.puerto))
        {
            throw runtime_error(
                "No fue posible conectar con MySQL."
            );
        }

        TareaDAO tareaDAO(db);

        // menu debe incluir tareadao tambien.
        menu.ejecutar();
        db.desconectar();
    }
    catch (const EntradaCerrada& e)
    {
        cout << "\n" << e.what() << "\n";
    }
    catch (const exception& e)
    {
        cout << "\nError: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
