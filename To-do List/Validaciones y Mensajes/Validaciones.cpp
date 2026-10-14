#include "Validaciones.h"
#include "mensajes.h"

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <stdexcept>

using namespace std;

// Quita espacios al inicio y al final
static string recortar(const string& s) {
    size_t ini = s.find_first_not_of(" \t\r\n");

    if (ini == string::npos)
    {
        return "";
    }
    size_t fin = s.find_last_not_of(" \t\r\n");
    return s.substr(ini, fin - ini + 1);
}

// Lee una linea completa; si se cierra la entrada, termina el programa
static string leerLinea(const string& mensaje) {
    string linea;

    mensajes::showmessage(mensaje);   // muestra la pregunta al usuario

    if (!getline(cin, linea))
    {
        throw runtime_error("\nEntrada cerrada. Saliendo del programa.\n");
    }
    return recortar(linea);
}

int leerEntero(const string& mensaje, int minimo, int maximo) {
    while (true)
    {
        string linea = leerLinea(mensaje);

        if (linea.empty())
        {
            throw invalid_argument("\nError: no escribiste nada.\n");
        }

        size_t pos = 0;
        long valor = 0;

        try
        {
            valor = stol(linea, &pos);
        }
        catch (const exception&) {            // ej. "hola" o numero gigante
            throw invalid_argument("\nError: eso no es un numero valido.\n");
        }

        if (pos != linea.size()) {              // ej. "3abc"
            throw invalid_argument("\nError: escribe solo numeros.\n");
        }

        if (valor < minimo || valor > maximo) { // ej. opcion 7 en un menu de 1 a 5
            throw out_of_range("\nError: el numero esta fuera del rango ("
                + to_string(minimo) + " a " + to_string(maximo) + ").\n");
        }

        return static_cast<int>(valor);
    }
}

string leerTextoNoVacio(const string& mensaje, size_t maxLargo) {
    while (true)
    {
        string texto = leerLinea(mensaje);

        if (texto.empty())
        {
            throw invalid_argument("\nError: el texto no puede estar vacio.\n");
        }
        else if (texto.size() > maxLargo) {
            throw out_of_range("\nExcede el numero maximo de caracteres.\n");
        }
        else {
            return texto;
        }
    }
}

bool confirmar(const string& mensaje) {
    while (true) {
        string r = leerLinea(mensaje);
        for (char& c : r)
        {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }

        if (r == "s" || r == "si")
        {
            return true;
        }

        if (r == "n" || r == "no")
        {
            return false;
        }

        throw invalid_argument("\nError: Responda S o N.\n");
    }
}


// ---------------- NUEVAS VALIDACIONES (issue #21)

// Regresa true si el anio es bisiesto (febrero tiene 29 dias)
static bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int diasDelMes(int mes, int anio) {
    switch (mes)
    {
    case 2:
        return esBisiesto(anio) ? 29 : 28;
    case 4: case 6: case 9: case 11:
        return 30;
    default:
        return 31;
    }
}

void validarFecha(const string& fecha) {
    // 1. Formato dd/mm/aaaa: 10 caracteres, '/' en las posiciones 2 y 5
    //    y numeros en todas las demas.
    if (fecha.size() != 10 || fecha[2] != '/' || fecha[5] != '/')
    {
        throw invalid_argument("\nError: la fecha debe tener el formato dd/mm/aaaa.\n");
    }

    for (size_t i = 0; i < fecha.size(); i++)
    {
        if (i == 2 || i == 5)
        {
            continue;
        }
        if (!isdigit(static_cast<unsigned char>(fecha[i])))
        {
            throw invalid_argument("\nError: la fecha solo puede tener numeros y '/'.\n");
        }
    }

    int dia = stoi(fecha.substr(0, 2));
    int mes = stoi(fecha.substr(3, 2));
    int anio = stoi(fecha.substr(6, 4));

    // 2. Dia valido (01 a 31)
    if (dia < 1 || dia > 31)
    {
        throw out_of_range("\nError: el dia debe estar entre 01 y 31.\n");
    }

    // 3. Mes valido (01 a 12)
    if (mes < 1 || mes > 12)
    {
        throw out_of_range("\nError: el mes debe estar entre 01 y 12.\n");
    }

    if (anio < 1)
    {
        throw out_of_range("\nError: el anio no es valido.\n");
    }

    // 4. Que la fecha exista realmente (ej. 31/04 o 29/02 en anio no bisiesto)
    if (dia > diasDelMes(mes, anio))
    {
        throw out_of_range("\nError: esa fecha no existe (el mes "
            + to_string(mes) + " de " + to_string(anio) + " tiene "
            + to_string(diasDelMes(mes, anio)) + " dias).\n");
    }
}

string leerFecha(const string& mensaje) {
    string fecha = leerLinea(mensaje);

    if (fecha.empty())
    {
        throw invalid_argument("\nError: no escribiste ninguna fecha.\n");
    }

    validarFecha(fecha);
    return fecha;
}

string leerPrioridad(const string& mensaje) {
    // leerEntero lanza una excepcion si escriben algo fuera de 1 a 2
    int opcion = leerEntero(mensaje, 1, 2);

    if (opcion == 1)
    {
        return "ALTA";
    }

    return "BAJA";
}
