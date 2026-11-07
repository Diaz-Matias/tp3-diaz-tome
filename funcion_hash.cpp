#include "funcion_hash.h"

size_t funcion_hash(const std::string& clave) {
    size_t sumas = 0;
    for (char c : clave) {
        sumas = sumas * 31 + static_cast<size_t>(c);
    }
    return sumas;
}

size_t funcion_hash(int clave) {
    return static_cast<size_t>(clave);
}
