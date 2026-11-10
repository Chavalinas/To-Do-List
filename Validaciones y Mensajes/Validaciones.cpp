#include "Validaciones.h"

#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

// VALIDACIONES GENERALES =========================

// Quita espacios al inicio y al final.
static string recortar(const string& s)
{
    size_t ini = s.find_first_not_of(" \t\r\n");

    if (ini == string::npos)
    {
        return "";
    }

    size_t fin = s.find_last_not_of(" \t\r\n");

    return s.substr(ini, fin - ini + 1);
}

// Lee una linea completa.
static string leerLinea(const string& mensaje)
{
    cout << mensaje;

    string linea;

    if (!getline(cin, linea))
    {
        throw EntradaCerrada();
    }

    return recortar(linea);
}

// Lee un numero entero.
int leerEntero(
    const string& mensaje,
    int minimo,
    int maximo
)
{
    string linea = leerLinea(mensaje);

    if (linea.empty())
    {
        throw invalid_argument(
            "\nError: no escribiste nada.\n"
        );
    }

    size_t pos = 0;
    long valor;

    // Solo captura los errores 
    try
    {
        valor = stol(linea, &pos);
    }
    catch (const invalid_argument&)
    {
        throw invalid_argument(
            "\nError: escribe un numero entero.\n"
        );
    }
    catch (const out_of_range&)
    {
        throw out_of_range(
            "\nError: el numero es demasiado grande.\n"
        );
    }

    if (pos != linea.size())
    {
        throw invalid_argument(
            "\nError: escribe solo un numero entero.\n"
        );
    }

    if (valor < minimo || valor > maximo)
    {
        throw out_of_range(
            "\nDebes seleccionar el numero correspondiente ("
            + to_string(minimo)
            + "-"
            + to_string(maximo)
            + ").\n"
        );
    }

    return static_cast<int>(valor);
}

// Texto obligatorio
string leerTextoNoVacio(
    const string& mensaje,
    size_t maxLargo
)
{
    string texto = leerLinea(mensaje);

    if (texto.empty())
    {
        throw invalid_argument(
            "\nError: el texto no puede estar vacio.\n"
        );
    }

    if (texto.size() > maxLargo)
    {
        throw out_of_range(
            "\nExcede el numero maximo de caracteres.\n"
        );
    }

    return texto;
}

// Texto opcional
string leerTextoOpcional(
    const string& mensaje,
    size_t maxLargo
)
{
    string texto = leerLinea(mensaje);

    if (texto.size() > maxLargo)
    {
        throw out_of_range(
            "\nExcede el numero maximo de caracteres.\n"
        );
    }

    return texto;
}

// Pregunta s/n
bool confirmar(const string& mensaje)
{
    string respuesta = leerLinea(mensaje);

    for (char& c : respuesta)
    {
        c = static_cast<char>(
            tolower(static_cast<unsigned char>(c))
            );
    }

    if (respuesta == "s" || respuesta == "si")
    {
        return true;
    }

    if (respuesta == "n" || respuesta == "no")
    {
        return false;
    }

    throw invalid_argument(
        "\nError: responde S o N.\n"
    );
}

// VALIDACION DE FECHAS =========================

// Acepta dia y mes de uno o dos digitos,
// y exige un anio de cuatro digitos.
// Tambien comprueba que la fecha exista.
static bool descomponerFecha(
    const string& fecha,
    int& dia,
    int& mes,
    int& anio
)
{
    size_t primeraBarra = fecha.find('/');

    if (primeraBarra == string::npos)
    {
        return false;
    }

    size_t segundaBarra = fecha.find(
        '/',
        primeraBarra + 1
    );

    if (segundaBarra == string::npos)
    {
        return false;
    }

    if (fecha.find('/', segundaBarra + 1) != string::npos)
    {
        return false;
    }

    string textoDia = fecha.substr(0, primeraBarra);

    string textoMes = fecha.substr(
        primeraBarra + 1,
        segundaBarra - primeraBarra - 1
    );

    string textoAnio = fecha.substr(segundaBarra + 1);

    if (
        textoDia.empty() || textoDia.size() > 2 ||
        textoMes.empty() || textoMes.size() > 2 ||
        textoAnio.size() != 4
        )
    {
        return false;
    }

    // Rechaza letras, signos y espacios interiores
    for (size_t i = 0; i < fecha.size(); i++)
    {
        if (i == primeraBarra || i == segundaBarra)
        {
            continue;
        }

        if (fecha[i] < '0' || fecha[i] > '9')
        {
            return false;
        }
    }

    dia = stoi(textoDia);
    mes = stoi(textoMes);
    anio = stoi(textoAnio);

    if (anio < 1 || mes < 1 || mes > 12)
    {
        return false;
    }

    int diasPorMes[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    bool bisiesto =
        (anio % 400 == 0) ||
        (anio % 4 == 0 && anio % 100 != 0);

    if (bisiesto)
    {
        diasPorMes[1] = 29;
    }

    return dia >= 1 && dia <= diasPorMes[mes - 1];
}

bool validarFechaLimite(
    const string& nuevaFecha,
    const string& fechaCreacion
)
{
    // Enter significa que no hay fecha limite
    if (nuevaFecha.empty())
    {
        return true;
    }

    int dia;
    int mes;
    int anio;

    if (!descomponerFecha(nuevaFecha, dia, mes, anio))
    {
        return false;
    }

    int diaCreacion;
    int mesCreacion;
    int anioCreacion;

    if (!descomponerFecha(
        fechaCreacion,
        diaCreacion,
        mesCreacion,
        anioCreacion
    ))
    {
        return false;
    }

    int limite = anio * 10000 + mes * 100 + dia;

    int creacion =
        anioCreacion * 10000
        + mesCreacion * 100
        + diaCreacion;

    return limite >= creacion;
}