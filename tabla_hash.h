#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include <cstddef>
#include <string>
#include <vector>
#include "funcion_hash.h"
// TAD TablaHash<K, V>: tabla de hash con direccionamiento cerrado.
//
// Guarda pares <clave, valor> repartidos en buckets: el par de una clave esta
// en el bucket numero funcion_hash(clave) % capacidad().
//
// Requisitos sobre los tipos:
//   - K: se puede copiar, comparar con == y existe funcion_hash(K).
//   - V: se puede copiar.
//
// Invariante de representacion:
//   COMPLETAR: escriban aca el invariante de la representacion que elijan.
//
// Complejidades: n es la cantidad de claves guardadas y c la capacidad.
// "Promedio" supone que la funcion de hash reparte las claves de manera
// uniforme y que calcularla (y comparar dos claves) cuesta O(1).
    template <typename K, typename V>
class TablaHash {
  private:
    // COMPLETAR: la representacion la eligen ustedes (que guardan, y que hay
    // en cada bucket). Pueden agregar tambien funciones auxiliares privadas.
    // Lo que el Iterador necesite de aca tiene que estar declarado antes que el.
    struct Par {
        K clave;
        V valor;
    };
    std::vector <std::vector<Par>> buckets;
    size_t cant;
    size_t indice(const K& clave){
        return funcion_hash(clave) % buckets.size();
    }
    void redimensionar();
  public:
    static const size_t FACTOR_DE_CARGA_MAXIMO = 2;

    // Pre:  capacidad_inicial >= 1.
    // Post: crea una tabla vacia, con capacidad_inicial buckets.
    // Costo: O(capacidad_inicial).
    TablaHash(size_t capacidad_inicial);

    // Post: libera toda la memoria pedida por la tabla.
    // Costo: O(n + c) en peor caso.
    ~TablaHash();

    // Copiar una tabla copiaria los punteros y no su contenido: lo prohibimos.
    TablaHash(const TablaHash&) = delete;
    TablaHash& operator=(const TablaHash&) = delete;

    // Pre:  la clave NO esta en la tabla.
    // Post: la tabla tiene ademas el par <clave, valor>, y
    //       cantidad() <= FACTOR_DE_CARGA_MAXIMO * capacidad().
    // Costo: O(1) amortizado (en peor caso O(n), cuando toca redimensionar).
    void insertar(const K& clave, const V& valor);

    // Pre:  la clave esta en la tabla.
    // Post: la tabla ya no tiene la clave (ni su valor).
    // Costo: O(1) en promedio, O(n) en peor caso.
    void eliminar(const K& clave);

    // Pre:  -
    // Post: si la clave esta, devuelve un puntero a su valor (que se puede
    //       usar para leerlo o modificarlo); si no, devuelve nullptr.
    //       El puntero deja de ser valido al insertar o eliminar.
    // Costo: O(1) en promedio, O(n) en peor caso.
    V* buscar(const K& clave);

    // Post: devuelve la cantidad de claves guardadas. Costo: O(1).
    size_t cantidad();

    // Post: devuelve la cantidad de buckets. Costo: O(1).
    size_t capacidad();

    // Post: devuelve la cantidad de claves que comparten bucket con alguna
    //       clave que llego antes, es decir:
    //       cantidad() - (cantidad de buckets que no estan vacios).
    // Costo: O(c) en peor caso.
    size_t colisiones();

    // Iterador de la tabla: recorre todos los pares <clave, valor>, cada uno
    // exactamente una vez, en algun orden (ver TAD Iterador en el enunciado).
    // Deja de ser valido si se inserta o se elimina en la tabla.
    //
    // Invariante de representacion:
    //   COMPLETAR: escriban aca el invariante de la representacion que elijan.
    class Iterador {
      private:
        // COMPLETAR: la representacion la eligen ustedes. Desde aca se puede
        // usar la parte privada de la tabla.

        // Para que crear_iterador() pueda armar el iterador.
        TablaHash* tabla;
        size_t bucket;
        size_t pos;
        void saltar_vacios(){
            while(bucket<tabla->buckets.size() and pos>=tabla->buckets[bucket].size()){bucket++;pos=0;}

        }
        friend class TablaHash;

      public:
        // Pre:  -
        // Post: indica si quedan pares por recorrer.
        // Costo: O(1).
        bool hay_mas() {
            return bucket<tabla->buckets.size();
        }

        // Pre:  hay_mas().
        // Post: devuelve la clave del par actual, sin modificar el iterador.
        // Costo: O(1).
        K clave() {
            return tabla->buckets[bucket][pos].clave;
        }

        // Pre:  hay_mas().
        // Post: devuelve el valor del par actual, sin modificar el iterador.
        // Costo: O(1).
        V valor() {
            return tabla->buckets[bucket][pos].valor;
        }

        // Pre:  hay_mas().
        // Post: el iterador pasa al par siguiente (o al final, si no hay mas).
        // Costo: O(c) en peor caso. Recorrer la tabla entera (crear el
        //        iterador y avanzar hasta el final) cuesta O(n + c).
        void avanzar() {
            pos++;
            saltar_vacios();
        }
    };

    // Pre:  -
    // Post: devuelve un iterador al primer par de la tabla (si la tabla esta
    //       vacia, el iterador ya esta al final).
    // Costo: O(c) en peor caso.
    Iterador crear_iterador();
};

// ---------------------------------------------------------------------------
// Implementacion. Al ser una clase template, va en el mismo .h.
// ---------------------------------------------------------------------------

template <typename K, typename V>
TablaHash<K, V>::TablaHash(size_t capacidad_inicial) : buckets(capacidad_inicial), cant(0) {
    //Esto ya crea bucket vacio asi q listo
}

template <typename K, typename V>
TablaHash<K, V>::~TablaHash() {
    //vector lo hace solo
}

template <typename K, typename V>
void TablaHash<K, V>::insertar(const K& clave, const V& valor) {
    if (cant+1> FACTOR_DE_CARGA_MAXIMO*buckets.size()) {redimensionar(); }
    size_t i= indice(clave);
    buckets[i].push_back({clave, valor});
    cant++;
}

template <typename K, typename V>
void TablaHash<K, V>::eliminar(const K& clave) {
    size_t i = indice(clave);
    for (size_t j = 0; j < buckets[i].size(); j++){
        if(buckets[i][j].clave == clave){
            buckets[i].erase(buckets[i].begin() + j);
            cant--;
            return;
        }
    }
}

template <typename K, typename V>
V* TablaHash<K, V>::buscar(const K& clave) {
    size_t i =indice(clave);
    for (Par& par: buckets[i]){
        if(par.clave == clave){return &par.valor;}
    }
    return nullptr;
}

template <typename K, typename V>
size_t TablaHash<K, V>::cantidad() {
    return cant;
}

template <typename K, typename V>
size_t TablaHash<K, V>::capacidad() {
    return buckets.size();
}

template <typename K, typename V>
size_t TablaHash<K, V>::colisiones() {
    size_t llenos= 0;
    for (size_t i=0; i<buckets.size();i++){
        if (!buckets[i].empty()){llenos+=1;}
    }
    return cant - llenos;
}

// El "typename" le avisa al compilador que TablaHash<K, V>::Iterador es un tipo.
template <typename K, typename V>
typename TablaHash<K, V>::Iterador TablaHash<K, V>::crear_iterador() {
    Iterador it;
    it.tabla = this;
    it.bucket = 0;
    it.pos = 0;
    it.saltar_vacios();
    return it;
}
//Nueva funcion para redimensionar pq lo estamos haciendo con vectores de vectores en vez de listas enlazadas pq somos chads
template <typename K, typename V>
void TablaHash<K, V>::redimensionar() {
    std::vector<std::vector<Par>> viejos = buckets;
    buckets.assign(buckets.size() * 2, {});
    cant = 0;
    for (std::vector<Par>& lista : viejos) {
        for (Par& par : lista) {
            insertar(par.clave, par.valor);
        }
    }
}
#endif
