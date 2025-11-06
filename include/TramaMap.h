/**
 * @file TramaMap.h
 * @brief Clase para tramas de tipo MAP del protocolo PRT-7
 * @author Decodificador PRT-7 Team
 * @date 2025-11-06
 * 
 * Las tramas MAP contienen una instruccion de rotacion (numero entero)
 * que modifica el estado del rotor de mapeo. Esto cambia como se
 * decodifican las tramas LOAD subsecuentes.
 */

#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"

/**
 * @class TramaMap
 * @brief Representa una trama de mapeo (M,N)
 * 
 * Esta clase almacena un valor de rotacion (positivo o negativo) que
 * se aplica al rotor de mapeo cuando se ejecuta el metodo procesar().
 */
class TramaMap : public TramaBase {
private:
    int rotacion;  ///< Cantidad de posiciones a rotar (+ o -)
    
public:
    /**
     * @brief Constructor
     * @param n Cantidad de rotacion (positivo = horario, negativo = antihorario)
     */
    TramaMap(int n);
    
    /**
     * @brief Destructor
     */
    ~TramaMap();
    
    /**
     * @brief Procesa la trama MAP
     * 
     * Aplica la rotacion al rotor de mapeo, cambiando el estado
     * del sistema de decodificacion.
     * 
     * @param carga Puntero a la lista de carga (no se usa en MAP)
     * @param rotor Puntero al rotor de mapeo que sera rotado
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_MAP_H
