#include <iostream>
#include <exception>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include "Lista de tareas/Listatareas.h"
#include "Validaciones y Mensajes/Validaciones.h"
#include "menu/menu.h"

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
        menu.ejecutar();
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
