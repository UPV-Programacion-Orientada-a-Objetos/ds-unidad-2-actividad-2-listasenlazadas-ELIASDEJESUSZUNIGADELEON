/**
 * @file TramaLoad.cpp
 * @brief Implementacion de la clase TramaLoad
 * @author Decodificador PRT-7 Team
 * @date 2025-11-06
 */

#include "TramaLoad.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @brief Constructor de TramaLoad
 */
TramaLoad::TramaLoad(char c) : dato(c) {
    // Inicializa el dato a decodificar
}

/**
 * @brief Destructor de TramaLoad
 */
TramaLoad::~TramaLoad() {
    // No hay recursos dinamicos que liberar en esta clase
}

/**
 * @brief Procesa la trama LOAD
 * 
 * Logica:
 * 1. Obtener el caracter almacenado
 * 2. Usar el rotor para decodificar el caracter
 * 3. Insertar el caracter decodificado en la lista de carga
 */
void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // Obtener el caracter decodificado usando el rotor
    char decodificado = rotor->getMapeo(dato);
    
    // Insertar el caracter decodificado en la lista de carga
    carga->insertarAlFinal(decodificado);
}
