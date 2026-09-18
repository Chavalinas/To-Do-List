#include <iostream>
#include "menu.h"

using namespace std;


void Menu::mostrarMenu()
{
    cout << "\n========== TO-DO LIST ==========\n";
    cout << "1. Añadir tarea\n";
    cout << "2. Listar tareas\n";
    cout << "3. Cambiar estado\n";
    cout << "4. Eliminar tarea\n";
    cout << "5. Salir\n";
    cout << "================================\n";
}


int Menu::pedirSeleccion()
{
    int seleccion;

    cout << "Selecciona una opcion: ";

    cin >> seleccion;

    return seleccion;
}