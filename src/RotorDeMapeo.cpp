/**
 * @file RotorDeMapeo.cpp
 * @brief Implementacion del RotorDeMapeo (Lista Circular)
 * @author Decodificador PRT-7 Team
 * @date 2025-11-06
 */

#include "RotorDeMapeo.h"
#include <iostream>

/**
 * @brief Constructor - Crea la lista circular con A-Z y espacio
 */
RotorDeMapeo::RotorDeMapeo() {
    // Alfabeto completo: A-Z + espacio (27 caracteres)
    const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    const int tamanio = 27;
    
    // Crear el primer nodo (A)
    cabeza = new NodoRotor(alfabeto[0]);
    NodoRotor* actual = cabeza;
    
    // Crear los demas nodos (B-Z y espacio)
    for (int i = 1; i < tamanio; i++) {
        NodoRotor* nuevo = new NodoRotor(alfabeto[i]);
        
        // Enlazar: actual <-> nuevo
        actual->siguiente = nuevo;
        nuevo->previo = actual;
        
        actual = nuevo;
    }
    
    // Cerrar el circulo: ultimo nodo <-> primer nodo
    actual->siguiente = cabeza;
    cabeza->previo = actual;
}

/**
 * @brief Destructor - Libera toda la memoria
 */
RotorDeMapeo::~RotorDeMapeo() {
    if (!cabeza) return;
    
    // Romper el circulo para evitar loops infinitos
    NodoRotor* ultimo = cabeza->previo;
    ultimo->siguiente = nullptr;
    
    // Eliminar todos los nodos
    NodoRotor* actual = cabeza;
    while (actual) {
        NodoRotor* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    
    cabeza = nullptr;
}

/**
 * @brief Busca un nodo que contiene un caracter
 */
NodoRotor* RotorDeMapeo::buscarNodo(char c) {
    if (!cabeza) return nullptr;
    
    NodoRotor* actual = cabeza;
    
    // Recorrer toda la lista circular
    do {
        if (actual->dato == c) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    return nullptr;  // No encontrado
}

/**
 * @brief Calcula la distancia entre dos nodos
 */
int RotorDeMapeo::calcularDistancia(NodoRotor* desde, NodoRotor* hasta) {
    if (!desde || !hasta) return 0;
    
    int distancia = 0;
    NodoRotor* actual = desde;
    
    // Contar cuantos pasos se necesitan para llegar de 'desde' a 'hasta'
    while (actual != hasta) {
        actual = actual->siguiente;
        distancia++;
        
        // Seguridad: evitar loops infinitos (no deberia pasar)
        if (distancia > 100) break;
    }
    
    return distancia;
}

/**
 * @brief Rota el rotor N posiciones
 */
void RotorDeMapeo::rotar(int n) {
    if (!cabeza) return;
    
    // Normalizar n para evitar rotaciones innecesarias
    // (27 posiciones = una vuelta completa)
    n = n % 27;
    
    if (n > 0) {
        // Rotar a la derecha (siguiente)
        for (int i = 0; i < n; i++) {
            cabeza = cabeza->siguiente;
        }
    } else if (n < 0) {
        // Rotar a la izquierda (previo)
        for (int i = 0; i > n; i--) {
            cabeza = cabeza->previo;
        }
    }
    
    // Debug: mostrar la rotacion
    std::cout << "\n>>> ROTANDO ROTOR " << (n >= 0 ? "+" : "") << n 
              << " (Ahora 'A' se mapea a '" << getMapeo('A') << "')" << std::endl;
}

/**
 * @brief Obtiene el caracter mapeado
 * 
 * LOGICA COMPLEJA DEL MAPEO:
 * 
 * Ejemplo: Si el rotor esta rotado +2:
 *   Rotor original: A B C D E F G ...
 *   Cabeza en:      C (rotado +2)
 * 
 *   Si llega 'A':
 *   1. Buscar 'A' en el rotor (siempre esta en su posicion original)
 *   2. Calcular distancia desde cabeza (C) hasta 'A'
 *      C -> D -> E -> ... -> Z -> espacio -> A = 25 pasos
 *   3. Buscar el nodo 'A' original (sin rotacion)
 *   4. Avanzar 25 pasos desde 'A' original
 *   5. Resultado: 'A' + 25 = 'Z' (overflow circular)
 *   
 *   Simplificado: 'A' rotado +2 = 'C'
 */
char RotorDeMapeo::getMapeo(char in) {
    // Caso especial: caracter no esta en el rotor
    NodoRotor* nodoOriginal = buscarNodo(in);
    if (!nodoOriginal) {
        return in;  // Devolver sin modificar
    }
    
    // Calcular la posicion del caracter relativa a la cabeza actual
    int distancia = calcularDistancia(cabeza, nodoOriginal);
    
    // Encontrar el nodo 'A' original (referencia fija)
    NodoRotor* nodoA = buscarNodo('A');
    if (!nodoA) return in;
    
    // Avanzar la misma distancia desde 'A'
    NodoRotor* resultado = nodoA;
    for (int i = 0; i < distancia; i++) {
        resultado = resultado->siguiente;
    }
    
    return resultado->dato;
}

/**
 * @brief Imprime el rotor (debug)
 */
void RotorDeMapeo::imprimirRotor() {
    if (!cabeza) {
        std::cout << "Rotor vacio" << std::endl;
        return;
    }
    
    std::cout << "Rotor (cabeza en '" << cabeza->dato << "'): ";
    
    NodoRotor* actual = cabeza;
    do {
        std::cout << actual->dato;
        if (actual->siguiente != cabeza) {
            std::cout << " -> ";
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    std::cout << " (circular)" << std::endl;
}
