// correccion: ARCHIVO NUEVO
// Pruebas.cpp //correccion
// Va en un proyecto aparte llamado "Pruebas" (ver seccion 8.5 del PDF). //correccion
// Se le agregan: Tarea.cpp, TareaPrioritaria.cpp, TareaFechaLimite.cpp, //correccion
// Fecha.cpp, ListaTareas.cpp, Validaciones.cpp y Mensajes.cpp //correccion
// (sin To-do list.cpp ni Menu.cpp). //correccion
#include <iostream> //correccion
#include <memory> //correccion
#include <string> //correccion
#include <vector> //correccion

#include "../Validaciones y Mensajes/Validaciones.h" //correccion
#include "../Lista de tareas/Listatareas.h" //correccion
#include "../fecha.h" //correccion
#include "../TareaPrioritaria.h" //correccion
#include "../tareafechalimite.h" //correccion

int fallos = 0; //correccion

void verificar(bool condicion, const std::string& nombre) //correccion
{
    if (condicion) //correccion
    {
        std::cout << "[OK]    " << nombre << "\n"; //correccion
    }
    else //correccion
    {
        std::cout << "[FALLO] " << nombre << "\n"; //correccion
        fallos++; //correccion
    }
}

void pruebasFechas() //correccion
{
    std::string creacion = "21/10/2026";                                    // Preparar //correccion

    verificar(validarFechaLimite("25/12/2026", creacion),                   // Actuar y verificar //correccion
              "Fecha futura es valida"); //correccion
    verificar(!validarFechaLimite("01/01/2020", creacion), //correccion
              "Fecha anterior a la creacion es invalida"); //correccion
    verificar(!validarFechaLimite("30/02/2027", creacion), //correccion
              "30 de febrero no existe"); //correccion
    verificar(validarFechaLimite("29/02/2028", creacion), //correccion
              "29 de febrero en anio bisiesto es valido"); //correccion
    verificar(validarFechaLimite("", creacion), //correccion
              "Fecha vacia significa sin fecha limite"); //correccion
    verificar(validarFechaLimite("21/10/2026", creacion), //correccion
              "La misma fecha de creacion es valida"); //correccion
}

void pruebasClaseFecha() //correccion
{
    verificar(Fecha(5, 3, 2027).aTexto() == "05/03/2027", //correccion
              "aTexto agrega ceros a la izquierda"); //correccion
    verificar(Fecha(31, 12, 2026) < Fecha(1, 1, 2027), //correccion
              "31/12/2026 es antes que 01/01/2027"); //correccion
    verificar(!(Fecha(1, 1, 2027) < Fecha(31, 12, 2026)), //correccion
              "01/01/2027 no es antes que 31/12/2026"); //correccion
    verificar(Fecha::desdeTexto("5/3/2027") == Fecha(5, 3, 2027), //correccion
              "desdeTexto acepta dia y mes de un digito"); //correccion

    bool lanzoError = false; //correccion

    try //correccion
    {
        Fecha imposible(30, 2, 2027); //correccion
    }
    catch (const std::invalid_argument&) //correccion
    {
        lanzoError = true; //correccion
    }

    verificar(lanzoError, "El constructor rechaza el 30 de febrero"); //correccion
}

void pruebasLista() //correccion
{
    ListaTareas lista;                                          // Preparar //correccion
    lista.agregarTarea(std::make_unique<TareaPrioritaria>("A", "", Prioridad::ALTA)); //correccion
    lista.agregarTarea(std::make_unique<TareaPrioritaria>("B", "", Prioridad::BAJA)); //correccion
    lista.agregarTarea(std::make_unique<TareaPrioritaria>("C", "", Prioridad::BAJA)); //correccion

    verificar(lista.cantidad() == 3, "Se agregaron 3 tareas"); //correccion

    bool eliminada = lista.eliminarTarea(2);                                // Actuar //correccion

    verificar(eliminada, "Se puede eliminar una tarea existente");      // Verificar //correccion
    verificar(lista.cantidad() == 2, "Despues de eliminar quedan 2"); //correccion
    verificar(!lista.eliminarTarea(99), "No se elimina un ID inexistente"); //correccion
    verificar(lista.existeTarea(3), "La tarea 3 conserva su ID despues de eliminar la 2"); //correccion

    ListaTareas otraLista; //correccion
    int id = otraLista.agregarTarea(std::make_unique<TareaPrioritaria>("X", "", Prioridad::BAJA)); //correccion

    verificar(id == 1, "Cada lista empieza sus IDs en 1"); //correccion
}

void pruebasOrdenPorFecha() //correccion
{
    ListaTareas lista; //correccion
    lista.agregarTarea(std::make_unique<TareaPrioritaria>("Sin fecha", "", Prioridad::BAJA)); //correccion
    lista.agregarTarea(std::make_unique<TareaFechaLimite>("Enero 2099", "", "15/01/2099")); //correccion
    lista.agregarTarea(std::make_unique<TareaFechaLimite>("Diciembre 2098", "", "31/12/2098")); //correccion

    std::vector<Tarea*> vista = lista.obtenerTareas(TipoListado::FECHA_LIMITE); //correccion

    verificar(vista[0]->obtenerTitulo() == "Diciembre 2098", "La fecha mas cercana va primero"); //correccion
    verificar(vista[1]->obtenerTitulo() == "Enero 2099", "Luego la siguiente fecha"); //correccion
    verificar(vista[2]->obtenerTitulo() == "Sin fecha", "Las tareas sin fecha van al final"); //correccion
}

void pruebasPolimorfismo() //correccion
{
    std::unique_ptr<Tarea> tarea = //correccion
        std::make_unique<TareaPrioritaria>("Estudiar", "", Prioridad::BAJA); //correccion

    bool cambio = tarea->modificarFechaLimite("31/12/2099"); //correccion

    verificar(cambio, "Se puede modificar la fecha limite"); //correccion
    verificar(tarea->obtenerFechaLimite() == "31/12/2099", //correccion
              "La fecha limite queda guardada"); //correccion

    verificar(tarea->obtenerEstado() == 0, "Estado inicial 0: pendiente");
    tarea->modificarEstado(1);
    verificar(tarea->obtenerEstado() == 1, "Estado 1: en progreso");
    tarea->modificarEstado(2);
    verificar(tarea->obtenerEstado() == 2, "Estado 2: terminada");
    verificar(tarea->obtenerFechaCreacion() == Tarea::fechaActual(), "Fecha de creacion automatica");
    verificar(tarea->modificarFechaLimite(""), "Se puede quitar la fecha con texto vacio");
    verificar(tarea->obtenerFechaLimite().empty(), "La fecha queda vacia");
    tarea->modificarFechaLimite("31/12/2099");
    tarea->modificarPrioridad(Prioridad::ALTA); //correccion

    verificar(tarea->obtenerPrioridad() == Prioridad::ALTA, //correccion
              "Se puede modificar la prioridad"); //correccion

    verificar(!tarea->modificarFechaLimite("30/02/2100"), //correccion
              "No se guarda una fecha que no existe"); //correccion
    verificar(tarea->obtenerFechaLimite() == "31/12/2099", //correccion
              "Si la fecha es invalida se conserva la anterior"); //correccion

    std::unique_ptr<Tarea> otra = //correccion
        std::make_unique<TareaFechaLimite>("Entregar", "", "01/01/2099"); //correccion

    verificar(otra->modificarFechaLimite("2/2/2099"), //correccion
              "TareaFechaLimite tambien modifica su fecha"); //correccion
    verificar(otra->obtenerFechaLimite() == "02/02/2099", //correccion
              "La fecha se guarda con formato dd/mm/aaaa"); //correccion
}

int main() //correccion
{
    pruebasFechas(); //correccion
    pruebasClaseFecha(); //correccion
    pruebasLista(); //correccion
    pruebasOrdenPorFecha(); //correccion
    pruebasPolimorfismo(); //correccion

    std::cout << "\nPruebas fallidas: " << fallos << "\n"; //correccion

    if (fallos == 0) //correccion
    {
        return 0; //correccion
    }

    return 1; //correccion
}
