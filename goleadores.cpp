#include "goleadores.h"
#include <cstddef>
#include <vector>
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

struct Entrada {
    std::string nombre;
    int goles;
};

bool va_antes(Entrada a, Entrada b, bool por_goles){
    if (!por_goles) { return a.nombre < b.nombre; }
    if(a.goles!=b.goles){return a.goles>b.goles;}
    return a.nombre<b.nombre;
}

void merge(std::vector<Entrada>& v, int izq, int medio, int der, bool por_goles) {
    std::vector<Entrada> aux;
    int i = izq;
    int j = medio + 1;
    while (i <= medio && j <= der) {
        if (!va_antes(v[j], v[i], por_goles)) {
            aux.push_back(v[i]);
            i++;
        } else {
            aux.push_back(v[j]);
            j++;
        }
    }
    while (i <= medio) {
        aux.push_back(v[i]);
        i++;
    }
    while (j <= der) {
        aux.push_back(v[j]);
        j++;
    }
    for (int k = 0; k < (int)aux.size(); k++) {
        v[izq + k] = aux[k];
    }
}

void merge_sort(std::vector<Entrada>& v, int izq, int der, bool por_goles) {
    if (izq >= der) {
        return;
    }
    int medio = izq + (der - izq) / 2;
    merge_sort(v, izq, medio, por_goles);
    merge_sort(v, medio + 1, der, por_goles);
    merge(v, izq, medio, der, por_goles);
}  

void Goleadores::imprimir_por_nombre() {
    std::vector<Entrada> lista;
    auto it = goles_por_jugador.crear_iterador();
    while (it.hay_mas()){
        lista.push_back({it.clave(), it.valor()});
        it.avanzar();
    }
    merge_sort(lista, 0, (int)lista.size() - 1, false);
    for (size_t i = 0; i<lista.size();i++){
        auto e = lista[i];
        std::cout << e.nombre << ": " << e.goles << std::endl;
    }
}

void Goleadores::imprimir_por_goles() {
    std::vector<Entrada> lista;
    auto it = goles_por_jugador.crear_iterador();
    while (it.hay_mas()){
        lista.push_back({it.clave(), it.valor()});
        it.avanzar();
    }
    merge_sort(lista, 0, (int)lista.size() - 1, true);
    for (size_t i = 0; i<lista.size();i++){
        auto e = lista[i];
        std::cout << e.nombre << ": " << e.goles << std::endl;
    }
}
