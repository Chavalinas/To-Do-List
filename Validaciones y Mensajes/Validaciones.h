#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <stdexcept>

// Permite distinguir el cierre de entrada de un dato incorrecto
class EntradaCerrada : public std::runtime_error
{
public:
    EntradaCerrada()
        : std::runtime_error(
            "Entrada cerrada. Saliendo del programa."
        )
    {
    }
};

// Pide un entero entre minimo y maximo
int leerEntero(
    const std::string& mensaje,
    int minimo,
    int maximo
);

// Pide texto obligatorio
std::string leerTextoNoVacio(
    const std::string& mensaje,
    std::size_t maxLargo = 100
);

// Permite dejar el texto vacio con Enter
std::string leerTextoOpcional(
    const std::string& mensaje,
    std::size_t maxLargo = 100
);

// Acepta s/si y n/no, sin distinguir mayusculas
bool confirmar(
    const std::string& mensaje
);

// Permite fecha vacia o dia/mes/anio.
// La fecha no puede ser anterior a la creacion
bool validarFechaLimite(
    const std::string& nuevaFecha,
    const std::string& fechaCreacion
);

#endif