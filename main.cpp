#include <iostream>
#include <string>

#include "goleadores.h"

// Cambiar a true si hicieron la parte optativa (los dos listados).
const bool CON_LISTADOS = false;

// Lee de la entrada estandar la lista de goles del grupo (un gol por linea:
// el nombre del jugador que lo hizo) e imprime el resumen.
//
// Uso: ./goleadores < datos/ejemplo.txt
int main() {
    Goleadores goleador;
    std::string jugador;
    while (std::getline(std::cin, jugador)) {
        if (jugador != "") {
            goleador.anotar_gol(jugador);
        }
    }
    std::cout << "Jugadores con goles: " << goleador.cantidad_de_jugadores() << std::endl;
    if (goleador.cantidad_de_jugadores() > 0){
        std::cout << "Maximo goleador: " << goleador.maximo_goleador() << " (" << goleador.goles(goleador.maximo_goleador()) << " goles)" << std::endl;
    }
    if (CON_LISTADOS) {
        std::cout << std::endl;
        std::cout << "Goleadores por nombre:"  << std::endl;
        // OPTATIVO: imprimir el listado por nombre.
        std::cout << std::endl;
        std::cout << "Goleadores por goles:" << std::endl;
        // OPTATIVO: imprimir el listado por goles.
    }
    return 0;
}
