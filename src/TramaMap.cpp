/**
 * @file TramaMap.cpp
 * @brief Implementacion de la clase TramaMap
 * @author Elias de Jesus Zuniga de Leon
 * @date 2025-11-06
 */

#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @brief Constructor de TramaMap
 */
TramaMap::TramaMap(int n) : rotacion(n) {
    // Inicializa la cantidad de rotacion
}

/**
 * @brief Destructor de TramaMap
 */
TramaMap::~TramaMap() {
    // No hay recursos dinamicos que liberar en esta clase
}

/**
 * @brief Procesa la trama MAP
 * 
 * Logica:
 * 1. Aplicar la rotacion al rotor de mapeo
 * 2. Esto cambia el estado del sistema de decodificacion
 * 3. Las tramas LOAD subsecuentes se decodificaran de forma diferente
 */
void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // La lista de carga no se usa en tramas MAP (parametro ignorado)
    // Solo rotamos el rotor
    rotor->rotar(rotacion);
}
