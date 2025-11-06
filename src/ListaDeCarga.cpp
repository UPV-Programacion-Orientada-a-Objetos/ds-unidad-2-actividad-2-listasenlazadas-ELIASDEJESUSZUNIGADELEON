/**
 * @file ListaDeCarga.cpp
 * @brief Implementacion de la ListaDeCarga
 * @author Decodificador PRT-7 Team
 * @date 2025-11-06
 */

#include "ListaDeCarga.h"
#include <iostream>

/**
 * @brief Constructor - Inicializa lista vacia
 */
ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr), tamanio(0) {
    // Lista vacia al inicio
}

/**
 * @brief Destructor - Libera toda la memoria
 */
ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = cabeza;
    
    while (actual) {
        NodoCarga* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    
    cabeza = nullptr;
    cola = nullptr;
    tamanio = 0;
}

/**
 * @brief Inserta un caracter al final de la lista
 */
void ListaDeCarga::insertarAlFinal(char dato) {
    // Crear nuevo nodo
    NodoCarga* nuevo = new NodoCarga(dato);
    
    if (estaVacia()) {
        // Primer nodo: cabeza y cola apuntan al mismo nodo
        cabeza = nuevo;
        cola = nuevo;
    } else {
        // Insertar al final
        cola->siguiente = nuevo;
        nuevo->previo = cola;
        cola = nuevo;
    }
    
    tamanio++;
    
    // Debug: mostrar el caracter agregado
    std::cout << "Fragmento '" << dato << "' decodificado como '" << dato << "'. ";
    std::cout << "Mensaje: ";
    imprimirMensajeEnLinea();
}

/**
 * @brief Imprime el mensaje completo (version final)
 */
void ListaDeCarga::imprimirMensaje() {
    if (estaVacia()) {
        std::cout << "(mensaje vacio)" << std::endl;
        return;
    }
    
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "MENSAJE OCULTO ENSAMBLADO:" << std::endl;
    
    NodoCarga* actual = cabeza;
    while (actual) {
        std::cout << actual->dato;
        actual = actual->siguiente;
    }
    
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
}

/**
 * @brief Imprime el mensaje en una linea (para debug incremental)
 * 
 * Metodo auxiliar para mostrar el progreso del mensaje mientras se decodifica.
 */
void ListaDeCarga::imprimirMensajeEnLinea() {
    std::cout << "[";
    
    NodoCarga* actual = cabeza;
    while (actual) {
        std::cout << actual->dato;
        actual = actual->siguiente;
    }
    
    std::cout << "]" << std::endl;
}

/**
 * @brief Obtiene el tamanio de la lista
 */
int ListaDeCarga::getTamanio() const {
    return tamanio;
}

/**
 * @brief Verifica si la lista esta vacia
 */
bool ListaDeCarga::estaVacia() const {
    return cabeza == nullptr;
}
