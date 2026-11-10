#pragma once

#include <string>
#include <exception>

#include "../Lista de tareas/Listatareas.h"

class Menu
{
private:
    ListaTareas& lista;

    // Menus
    void mostrarMenu();
    int pedirSeleccion(int maximo);
    TipoListado seleccionarListado();
    void mostrarListado(TipoListado tipo);
    bool listarTareas(bool elegirListado);

    // Opciones
    void agregarTarea();
    void eliminarTarea();
    void modificarTarea();
    void modificarTareaPorId(int id);
    void mostrarTarea();

    // Solicitar datos
    int solicitarId(const std::string& mensaje);
    Prioridad solicitarPrioridad();

    // fechaSinCambios se regresa si responde que no quiere introducir fecha.
    std::string solicitarFecha(
        const std::string& fechaCreacion,
        const std::string& fechaSinCambios = ""
    );

    int solicitarNuevoEstado();

    // Lecturas con reintentos
    int pedirEntero(
        const std::string& mensaje,
        int minimo,
        int maximo
    );

    std::string pedirTextoNoVacio(
        const std::string& mensaje
    );

    std::string pedirTextoOpcional(
        const std::string& mensaje
    );

    bool pedirConfirmacion(
        const std::string& mensaje
    );

    // Apoyo de pantalla
    std::string formatoTarea(const Tarea& tarea) const;
    void mostrarError(const std::exception& e);
    void limpiarPantalla();
    void mostrarEncabezado();
    void pausar();

public:
    explicit Menu(ListaTareas& lista);

    void ejecutar();
};