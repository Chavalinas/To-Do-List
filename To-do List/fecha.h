#pragma once

#include <string>

class Fecha
{
private:
    int dia;
    int mes;
    int anio;

public:
    Fecha(int dia, int mes, int anio);

    static Fecha hoy();

    static Fecha desdeTexto(const std::string& texto);

    static bool esValida(int dia, int mes, int anio);
    static bool esBisiesto(int anio);

    int obtenerDia() const;
    int obtenerMes() const;
    int obtenerAnio() const;

    bool operator<(const Fecha& otra) const;
    bool operator==(const Fecha& otra) const;

    std::string aTexto() const;
};