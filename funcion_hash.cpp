#include "funcion_hash.h"
size_t hash_suma_mod10(const std::string& clave) {
    size_t suma = 0;
    for (char c : clave) {
        suma = suma + static_cast<size_t>(c);
    }
    return suma % 10;
}

size_t hash_suma(const std::string& clave) {
    size_t suma = 0;
    for (char c : clave) {
        suma = suma + static_cast<size_t>(c);
    }
    return suma;
}

size_t hash_bueno(const std::string& clave) {
    size_t h = 0;
    for (char c : clave) {
        h = h * 31 + static_cast<size_t>(c);
    }
    return h;
}


size_t funcion_hash(const std::string& clave) {
    return hash_bueno(clave);
}

size_t funcion_hash(int clave) {
    return static_cast<size_t>(clave);
}
