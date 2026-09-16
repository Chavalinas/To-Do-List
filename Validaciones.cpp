#include "Validaciones.h"

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

// Quita espacios al inicio y al final
static string recortar(const string& s) {
    size_t ini = s.find_first_not_of(" \t\r\n");
    if (ini == string::npos) return "";
    size_t fin = s.find_last_not_of(" \t\r\n");
    return s.substr(ini, fin - ini + 1);
}

// Lee una linea completa; si se cierra la entrada, termina el programa
static string leerLinea(const string& mensaje) {
    string linea;
    cout << mensaje;
    if (!getline(cin, linea)) {
        cout << "\nEntrada cerrada. Saliendo del programa.\n";
        exit(0);
    }
    return recortar(linea);
}

int leerEntero(const string& mensaje, int minimo, int maximo) {
    while (true) {
        string linea = leerLinea(mensaje);

        if (linea.empty()) {
            cout << "  Error: no escribiste nada.\n";
            continue;
        }

        try {
            size_t pos = 0;
            long valor = stol(linea, &pos);

            if (pos != linea.size()) {          // ej. "3abc"
                cout << "  Error: escribe solo numeros.\n";
            } else if (valor < minimo || valor > maximo) {
                cout << "  Error: el numero debe estar entre "
                     << minimo << " y " << maximo << ".\n";
            } else {
                return static_cast<int>(valor);
            }
        } catch (const exception&) {            // ej. "hola" o numero gigante
            cout << "  Error: eso no es un numero valido.\n";
        }
    }
}

string leerTextoNoVacio(const string& mensaje, size_t maxLargo) {
    while (true) {
        string texto = leerLinea(mensaje);

        if (texto.empty()) {
            cout << "  Error: el texto no puede estar vacio.\n";
        } else if (texto.size() > maxLargo) {
            cout << "  Error: maximo " << maxLargo << " caracteres.\n";
        } else {
            return texto;
        }
    }
}

bool confirmar(const string& mensaje) {
    while (true) {
        string r = leerLinea(mensaje);
        for (char& c : r) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

        if (r == "s" || r == "si") return true;
        if (r == "n" || r == "no") return false;
        cout << "  Error: responde s o n.\n";
    }
}
