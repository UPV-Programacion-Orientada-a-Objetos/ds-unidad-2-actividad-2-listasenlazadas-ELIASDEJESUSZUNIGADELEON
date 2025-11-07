/**
 * @file TramaMap.h
 * @brief Clase para tramas MAP (M,N)
 * @author Elias de Jesus Zuniga de Leon
 * @date 2025-11-06
 */

#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"

/**
 * @class TramaMap
 * @brief Trama de mapeo - rota el rotor N posiciones
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
     * @brief Procesa la trama - rota el rotor
     * @param carga No se usa en MAP
     * @param rotor Rotor a rotar
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_MAP_H
