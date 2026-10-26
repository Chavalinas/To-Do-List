#include "fecha.h"

#include <ctime>
#include <stdexcept>

using namespace std;

Fecha::Fecha(int dia, int mes, int anio)
{
    if (!esValida(dia, mes, anio))
    {
        throw invalid_argument(
            "Error: la fecha no existe."
        );
    }

    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
}

Fecha Fecha::hoy()
{
    time_t tiempoActual = time(nullptr);
    tm tiempoLocal;

#ifdef _WIN32
    localtime_s(&tiempoLocal, &tiempoActual);
#else
    localtime_r(&tiempoActual, &tiempoLocal);
#endif

    return Fecha(
        tiempoLocal.tm_mday,
        tiempoLocal.tm_mon + 1,
        tiempoLocal.tm_year + 1900
    );
}

Fecha Fecha::desdeTexto(const string& texto)
{
    size_t primeraBarra = texto.find('/');

    if (primeraBarra == string::npos)
    {
        throw invalid_argument(
            "Error: usa el formato dia/mes/año."
        );
    }

    size_t segundaBarra = texto.find(
        '/',
        primeraBarra + 1
    );

    if (segundaBarra == string::npos)
    {
        throw invalid_argument(
            "Error: usa el formato dia/mes/año."
        );
    }

    if (texto.find('/', segundaBarra + 1) != string::npos)
    {
        throw invalid_argument(
            "Error: usa el formato dia/mes/año."
        );
    }

    string textoDia = texto.substr(0, primeraBarra);

    string textoMes = texto.substr(
        primeraBarra + 1,
        segundaBarra - primeraBarra - 1
    );

    string textoAnio = texto.substr(segundaBarra + 1);

    if (
        textoDia.empty() || textoDia.size() > 2 ||
        textoMes.empty() || textoMes.size() > 2 ||
        textoAnio.size() != 4
        )
    {
        throw invalid_argument(
            "Error: usa dia y mes de uno o dos digitos "
            "y año de cuatro digitos."
        );
    }

    for (size_t i = 0; i < texto.size(); i++)
    {
        if (i == primeraBarra || i == segundaBarra)
        {
            continue;
        }

        if (texto[i] < '0' || texto[i] > '9')
        {
            throw invalid_argument(
                "Error: la fecha solo puede tener numeros y '/'."
            );
        }
    }

    return Fecha(
        stoi(textoDia),
        stoi(textoMes),
        stoi(textoAnio)
    );
}

bool Fecha::esBisiesto(int anio)
{
    return (anio % 400 == 0)
        || (anio % 4 == 0 && anio % 100 != 0);
}

bool Fecha::esValida(int dia, int mes, int anio)
{
    if (
        anio < 1 || anio > 9999 ||
        mes < 1 || mes > 12
        )
    {
        return false;
    }

    int diasPorMes[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (esBisiesto(anio))
    {
        diasPorMes[1] = 29;
    }

    return dia >= 1 && dia <= diasPorMes[mes - 1];
}

int Fecha::obtenerDia() const
{
    return dia;
}

int Fecha::obtenerMes() const
{
    return mes;
}

int Fecha::obtenerAnio() const
{
    return anio;
}

bool Fecha::operator<(const Fecha& otra) const
{
    if (anio != otra.anio)
    {
        return anio < otra.anio;
    }

    if (mes != otra.mes)
    {
        return mes < otra.mes;
    }

    return dia < otra.dia;
}

bool Fecha::operator==(const Fecha& otra) const
{
    return dia == otra.dia
        && mes == otra.mes
        && anio == otra.anio;
}

string Fecha::aTexto() const
{
    string texto = "";

    if (dia < 10)
    {
        texto += "0";
    }

    texto += to_string(dia) + "/";

    if (mes < 10)
    {
        texto += "0";
    }

    texto += to_string(mes) + "/";

    string textoAnio = to_string(anio);

    while (textoAnio.size() < 4)
    {
        textoAnio = "0" + textoAnio;
    }

    texto += textoAnio;

    return texto;
}