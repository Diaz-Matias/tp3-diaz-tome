#include "goleadores.h"

#include <iostream>

Goleadores::Goleadores() {
    // COMPLETAR (si hace falta)
}

void Goleadores::anotar_gol(const std::string& jugador) {
    int nuevo_gol = goles(jugador) + 1;
    if (cantidad_de_jugadores() ==0 || nuevo_gol > goles(maximo)){
        maximo = jugador;
    }
    goles_por_jugador.insertar(jugador, nuevo_gol);
}

int Goleadores::goles(const std::string& jugador) {
    if (goles_por_jugador.pertenece(jugador)){
        return goles_por_jugador.obtener(jugador);
    }
    return 0;
}

size_t Goleadores::cantidad_de_jugadores() {
    return goles_por_jugador.cantidad();
}

std::string Goleadores::maximo_goleador() {
    return maximo;
}

void Goleadores::imprimir_por_nombre() {
    // OPTATIVO
}

void Goleadores::imprimir_por_goles() {
    // OPTATIVO
}
