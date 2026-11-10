// Pruebas.cpp
// Va en un proyecto aparte llamado "Pruebas" (ver seccion 8.5 del PDF).
// Se le agregan: Tarea.cpp, TareaPrioritaria.cpp, TareaFechaLimite.cpp,
// Fecha.cpp, ListaTareas.cpp, Validaciones.cpp y Mensajes.cpp
// (sin To-do list.cpp ni Menu.cpp).
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Validaciones.h"
#include "../Lista de tareas/Listatareas.h"
#include "../fecha.h"
#include "../TareaPrioritaria.h"
#include "../tareafechalimite.h"

int fallos = 0;

void verificar(bool condicion, const std::string& nombre)
{
    if (condicion)
    {
        std::cout << "[OK]    " << nombre << "\n";
    }
    else
    {
        std::cout << "[FALLO] " << nombre << "\n";
        fallos++;
    }
}

void pruebasFechas()
{
    std::string creacion = "21/10/2026";                                    // Preparar

    verificar(validarFechaLimite("25/12/2026", creacion),                   // Actuar y verificar
              "Fecha futura es valida");
    verificar(!validarFechaLimite("01/01/2020", creacion),
              "Fecha anterior a la creacion es invalida");
    verificar(!validarFechaLimite("30/02/2027", creacion),
              "30 de febrero no existe");
    verificar(validarFechaLimite("29/02/2028", creacion),
              "29 de febrero en anio bisiesto es valido");
    verificar(validarFechaLimite("", creacion),
              "Fecha vacia significa sin fecha limite");
    verificar(validarFechaLimite("21/10/2026", creacion),
              "La misma fecha de creacion es valida");
}

void pruebasClaseFecha()
{
    verificar(Fecha(5, 3, 2027).aTexto() == "05/03/2027",
              "aTexto agrega ceros a la izquierda");
    verificar(Fecha(31, 12, 2026) < Fecha(1, 1, 2027),
              "31/12/2026 es antes que 01/01/2027");
    verificar(!(Fecha(1, 1, 2027) < Fecha(31, 12, 2026)),
              "01/01/2027 no es antes que 31/12/2026");
    verificar(Fecha::desdeTexto("5/3/2027") == Fecha(5, 3, 2027),
              "desdeTexto acepta dia y mes de un digito");

    bool lanzoError = false;

    try
    {
        Fecha imposible(30, 2, 2027);
    }
    catch (const std::invalid_argument&)
    {
        lanzoError = true;
    }

    verificar(lanzoError, "El constructor rechaza el 30 de febrero");
}

void pruebasLista()
{
    ListaTareas lista;                                          // Preparar
    lista.agregarTarea(std::make_unique<TareaPrioritaria>("A", "", Prioridad::ALTA));
    lista.agregarTarea(std::make_unique<TareaPrioritaria>("B", "", Prioridad::BAJA));
    lista.agregarTarea(std::make_unique<TareaPrioritaria>("C", "", Prioridad::BAJA));

    verificar(lista.cantidad() == 3, "Se agregaron 3 tareas");

    bool eliminada = lista.eliminarTarea(2);                                // Actuar

    verificar(eliminada, "Se puede eliminar una tarea existente");      // Verificar
    verificar(lista.cantidad() == 2, "Despues de eliminar quedan 2");
    verificar(!lista.eliminarTarea(99), "No se elimina un ID inexistente");
    verificar(lista.existeTarea(3), "La tarea 3 conserva su ID despues de eliminar la 2");

    ListaTareas otraLista;
    int id = otraLista.agregarTarea(std::make_unique<TareaPrioritaria>("X", "", Prioridad::BAJA));

    verificar(id == 1, "Cada lista empieza sus IDs en 1");
}

void pruebasOrdenPorFecha()
{
    ListaTareas lista;
    lista.agregarTarea(std::make_unique<TareaPrioritaria>("Sin fecha", "", Prioridad::BAJA));
    lista.agregarTarea(std::make_unique<TareaFechaLimite>("Enero 2099", "", "15/01/2099"));
    lista.agregarTarea(std::make_unique<TareaFechaLimite>("Diciembre 2098", "", "31/12/2098"));

    std::vector<Tarea*> vista = lista.obtenerTareas(TipoListado::FECHA_LIMITE);

    verificar(vista[0]->obtenerTitulo() == "Diciembre 2098", "La fecha mas cercana va primero");
    verificar(vista[1]->obtenerTitulo() == "Enero 2099", "Luego la siguiente fecha");
    verificar(vista[2]->obtenerTitulo() == "Sin fecha", "Las tareas sin fecha van al final");
}

void pruebasPolimorfismo()
{
    std::unique_ptr<Tarea> tarea =
        std::make_unique<TareaPrioritaria>("Estudiar", "", Prioridad::BAJA);

    bool cambio = tarea->modificarFechaLimite("31/12/2099");

    verificar(cambio, "Se puede modificar la fecha limite");
    verificar(tarea->obtenerFechaLimite() == "31/12/2099",
              "La fecha limite queda guardada");

    verificar(tarea->obtenerEstado() == 0, "Estado inicial 0: pendiente");
    tarea->modificarEstado(1);
    verificar(tarea->obtenerEstado() == 1, "Estado 1: en progreso");
    tarea->modificarEstado(2);
    verificar(tarea->obtenerEstado() == 2, "Estado 2: terminada");
    verificar(tarea->obtenerFechaCreacion() == Tarea::fechaActual(), "Fecha de creacion automatica");
    verificar(tarea->modificarFechaLimite(""), "Se puede quitar la fecha con texto vacio");
    verificar(tarea->obtenerFechaLimite().empty(), "La fecha queda vacia");
    tarea->modificarFechaLimite("31/12/2099");
    tarea->modificarPrioridad(Prioridad::ALTA);

    verificar(tarea->obtenerPrioridad() == Prioridad::ALTA,
              "Se puede modificar la prioridad");

    verificar(!tarea->modificarFechaLimite("30/02/2100"),
              "No se guarda una fecha que no existe");
    verificar(tarea->obtenerFechaLimite() == "31/12/2099",
              "Si la fecha es invalida se conserva la anterior");

    std::unique_ptr<Tarea> otra =
        std::make_unique<TareaFechaLimite>("Entregar", "", "01/01/2099");

    verificar(otra->modificarFechaLimite("2/2/2099"),
              "TareaFechaLimite tambien modifica su fecha");
    verificar(otra->obtenerFechaLimite() == "02/02/2099",
              "La fecha se guarda con formato dd/mm/aaaa");
}

void pruebasFechaCreacion()
{
    // Una tarea empezada otro dia conserva la fecha con la que se valido.
    std::string creacion = "21/10/2026";

    TareaFechaLimite conFecha("Entregar", "", creacion, Prioridad::BAJA, creacion);

    verificar(conFecha.obtenerFechaCreacion() == creacion,
              "TareaFechaLimite usa la fecha de creacion indicada");
    verificar(conFecha.obtenerFechaLimite() == creacion,
              "El limite igual a la creacion indicada no lanza error");

    TareaPrioritaria sinFecha("Estudiar", "", Prioridad::ALTA, "", creacion);

    verificar(sinFecha.obtenerFechaCreacion() == creacion,
              "TareaPrioritaria usa la fecha de creacion indicada");
}

int main()
{
    pruebasFechas();
    pruebasClaseFecha();
    pruebasLista();
    pruebasOrdenPorFecha();
    pruebasPolimorfismo();
    pruebasFechaCreacion();

    std::cout << "\nPruebas fallidas: " << fallos << "\n";

    if (fallos == 0)
    {
        return 0;
    }

    return 1;
}
