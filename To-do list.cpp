#include <iostream>
#include <limits>
#define NOMINMAX
#include <windows.h>

#include "Tarea.h"
#include "ListaTareas.h"
#include "Validaciones.h"
#include "AnadirTarea.h"
#include "CambiarEstado.h"
#include "menu.h"

using namespace std;


void listarTareasUI(ListaTareas& lista)
{
    lista.listarTareas();
}


int main()
{

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    ListaTareas lista;

    Menu menu;

    int opcion;

    do
    {
        menu.mostrarMenu();

        opcion = menu.pedirSeleccion();


        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion)
        {
        case 1:

            //funcion de "AñadirTarea.cpp"
            agregarTareaUI(lista);

            break;


        case 2:

            //Funcion de "ListarTarea.cpp"
            listarTareasUI(lista);

            break;


        case 3:

            //Funcion de "CambiarEstado"
            actualizarEstadoTarea(lista);

            break;


        case 4:

			//Funcion de "ListaTareas.cpp"
            opcion_eliminar(lista);

            break;


        case 5:

            cout << "\nSaliendo del programa...\n";

            break;


        default:

            cout << "\nOpción inválida.\n";

            break;
        }

    } while (opcion != 5);

    return 0;
}