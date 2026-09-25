#include "Validaciones.h"

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

        try
        {
            size_t pos = 0;
            long valor = stol(linea, &pos);

            if (pos != linea.size()) {          // ej. "3abc"
                throw invalid_argument("\nError: escribe solo numeros.\n");
            }
            else if (valor < minimo || valor > maximo) {
                throw out_of_range("\nEl numero esta fuera del rango.");
            }
            else {
                return static_cast<int>(valor);
            }
        }
        catch (const exception&) {            // ej. "hola" o numero gigante
            throw invalid_argument("\nError: eso no es un numero valido.\n");
        }
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