#pragma once

#include <string>

// Clase que encapsula una fecha (dia, mes y anio).
class Fecha
{
private:
    int dia;
    int mes;
    int anio;

public:
    // Lanza invalid_argument si la fecha no existe (por ejemplo 30/02/2027)
    Fecha(int dia, int mes, int anio);

    // Fecha de hoy, tomada de la computadora
    static Fecha hoy();

    // Convierte un texto "dd/mm/aaaa" en Fecha.
    // Lanza invalid_argument si el texto no tiene ese formato o la fecha no existe
    static Fecha desdeTexto(const std::string& texto);

    static bool esValida(int dia, int mes, int anio);
    static bool esBisiesto(int anio);

    int obtenerDia() const;
    int obtenerMes() const;
    int obtenerAnio() const;

    // Permite comparar fechas: fechaA < fechaB
    bool operator<(const Fecha& otra) const;
    bool operator==(const Fecha& otra) const;

    // Regresa la fecha como texto "dd/mm/aaaa" (siempre con dos digitos)
    std::string aTexto() const;
};