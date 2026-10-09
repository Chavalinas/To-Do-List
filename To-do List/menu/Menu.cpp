#include "mensajes.h"

#include <stdexcept>
#include <string>
#include <exception>

#include "menu.h"
#include "ListaTareas.h"
#include "Validaciones.h"
#include "Tarea.h"

using namespace std;


// ==================== MENÚ PRINCIPAL ====================

void Menu::mostrarMenu()
{
    mensajes::showmessage("\n========== TO-DO LIST ==========\n");
    mensajes::showmessage("1. Añadir tarea\n");
    mensajes::showmessage("2. Listar tareas\n");
    mensajes::showmessage("3. Cambiar estado\n");
    mensajes::showmessage("4. Eliminar tarea\n");
    mensajes::showmessage("5. Salir\n");
    mensajes::showmessage("================================\n");
}


int Menu::pedirSeleccion()
{
    while (true)
    {
        try
        {
            return leerEntero(
                "Selecciona una opcion: ",
                1,
                5
            );
        }
        catch (const exception& e)
        {
            mensajes::showmessage(e.what());
        }
    }
}


// ==================== AÑADIR TAREA ====================

void agregarTareaUI(ListaTareas& lista)
{
    mensajes::showmessage(
        "\n========== AÑADIR TAREA ==========\n"
    );

    string titulo;

    while (true)
    {
        try
        {
            titulo = leerTextoNoVacio(
                "Ingresa el titulo de la tarea: "
            );

            break;
        }
        catch (const exception& e)
        {
            mensajes::showmessage(e.what());
        }
    }


    string descripcion;

    while (true)
    {
        try
        {
            descripcion = leerTextoNoVacio(
                "Ingresa la descripcion de la tarea: "
            );

            break;
        }
        catch (const exception& e)
        {
            mensajes::showmessage(e.what());
        }
    }


    string estado = "pendiente";

    Tarea nuevaTarea(
        titulo,
        descripcion,
        estado,
        0
    );

    lista.agregar_tarea(nuevaTarea);

    mensajes::showmessage(
        "\nTarea añadida correctamente.\n"
    );

    mensajes::showmessage(
        "ID asignado: "
        + to_string(nuevaTarea.obtener_id())
        + "\n"
    );
}


// ==================== LISTAR TAREAS ====================

void listarTareasUI(ListaTareas& lista)
{
    try
    {
        mensajes::showmessage(
            lista.listarTareas()
        );
    }
    catch (const exception& e)
    {
        mensajes::showmessage(
            string("\n") + e.what() + "\n"
        );
    }
}


// ==================== CAMBIAR ESTADO ====================

string solicitarNuevoEstado()
{
    mensajes::showmessage(
        "\nSelecciona el nuevo estado:\n"
    );

    mensajes::showmessage("1. Pendiente\n");
    mensajes::showmessage("2. En progreso\n");
    mensajes::showmessage("3. Completada\n");


    while (true)
    {
        try
        {
            int opcion = leerEntero(
                "Opcion: ",
                1,
                3
            );

            switch (opcion)
            {
            case 1:
                return "pendiente";

            case 2:
                return "en progreso";

            case 3:
                return "completada";
            }
        }
        catch (const exception& e)
        {
            mensajes::showmessage(e.what());
        }
    }
}


void actualizarEstadoTarea(ListaTareas& lista)
{
    if (lista.cantidad() == 0)
    {
        mensajes::showmessage(
            "\nNo hay tareas registradas en la lista.\n"
        );

        return;
    }


    try
    {
        mensajes::showmessage(
            lista.listarTareas()
        );
    }
    catch (const exception& e)
    {
        mensajes::showmessage(
            string("\n") + e.what() + "\n"
        );

        return;
    }


    int idTarea;

    while (true)
    {
        try
        {
            idTarea = leerEntero(
                "Ingresa el ID de la tarea a modificar: ",
                1,
                1000000
            );

            if (!lista.existe_tarea(idTarea))
            {
                throw invalid_argument(
                    "Error: no existe ninguna tarea con ese ID.\n"
                );
            }

            break;
        }
        catch (const exception& e)
        {
            mensajes::showmessage(e.what());
        }
    }


    string nuevoEstado = solicitarNuevoEstado();


    try
    {
        lista.cambiar_estado(
            idTarea,
            nuevoEstado
        );

        mensajes::showmessage(
            "Tarea ["
            + to_string(idTarea)
            + "] actualizada correctamente a '"
            + nuevoEstado
            + "'.\n"
        );
    }
    catch (const exception& e)
    {
        mensajes::showmessage(
            string("\n") + e.what() + "\n"
        );
    }
}


// ==================== ELIMINAR TAREA ====================

void opcion_eliminar(ListaTareas& lista)
{
    if (lista.cantidad() == 0)
    {
        mensajes::showmessage(
            "\nNo hay tareas para eliminar.\n"
        );

        return;
    }


    mensajes::showmessage(
        "\n========== ELIMINAR TAREA ==========\n"
    );


    try
    {
        mensajes::showmessage(
            lista.mostrar_resumen()
        );
    }
    catch (const exception& e)
    {
        mensajes::showmessage(
            string("\n") + e.what() + "\n"
        );

        return;
    }


    int id;

    while (true)
    {
        try
        {
            id = leerEntero(
                "ID de la tarea a eliminar: ",
                1,
                1000000
            );

            if (!lista.existe_tarea(id))
            {
                throw invalid_argument(
                    "Error: no existe una tarea con ese ID.\n"
                );
            }

            break;
        }
        catch (const exception& e)
        {
            mensajes::showmessage(e.what());
        }
    }


    bool eliminar = false;

    while (true)
    {
        try
        {
            eliminar = confirmar(
                "Seguro que quieres eliminarla? (s/n): "
            );

            break;
        }
        catch (const exception& e)
        {
            mensajes::showmessage(e.what());
        }
    }


    if (eliminar)
    {
        try
        {
            lista.eliminar_tarea(id);

            mensajes::showmessage(
                "Tarea eliminada correctamente.\n"
            );
        }
        catch (const exception& e)
        {
            mensajes::showmessage(
                string("\n") + e.what() + "\n"
            );
        }
    }
    else
    {
        mensajes::showmessage(
            "Operacion cancelada.\n"
        );
    }
}