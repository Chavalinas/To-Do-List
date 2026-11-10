#pragma once

#include <string>

// Prioridad de una tarea.
enum class Prioridad
{
    BAJA = 0,
    ALTA = 1
};

// Convierte la prioridad a texto para mostrarla en pantalla
inline std::string prioridadATexto(Prioridad prioridad)
{
    if (prioridad == Prioridad::ALTA)
    {
        return "ALTA";
    }

    return "BAJA";
}

class Tarea
{
protected:
    std::string titulo;
    std::string descripcion;

    // 0 = pendiente, 1 = en progreso, 2 = terminada.
    int estado;

    std::string fechaCreacion;
    int id;

public:
    Tarea(
        const std::string& titulo,
        const std::string& descripcion
    );

    // Usa una fecha de creacion ya obtenida.
    Tarea(
        const std::string& titulo,
        const std::string& descripcion,
        const std::string& fechaCreacion
    );

    static std::string fechaActual();

    std::string obtenerTitulo() const;
    std::string obtenerDescripcion() const;
    int obtenerEstado() const;
    std::string obtenerFechaCreacion() const;
    int obtenerId() const;

    void modificarTitulo(const std::string& nuevoTitulo);
    void modificarDescripcion(const std::string& nuevaDescripcion);
    void modificarEstado(int nuevoEstado);

    void asignarId(int nuevoId);

    virtual ~Tarea() = default;

    virtual std::string obtenerFechaLimite() const = 0;
    virtual Prioridad obtenerPrioridad() const = 0;
    virtual std::string obtenerTipo() const = 0;

    virtual bool modificarFechaLimite(
        const std::string& nuevaFecha
    ) = 0;

    virtual void modificarPrioridad(
        Prioridad nuevaPrioridad
    ) = 0;
};