/**
 * @file TramaLoad.h
 * @brief Clase para tramas LOAD (L,X)
 * @author Elias de Jesus Zuniga de Leon
 * @date 2025-11-06
 */

#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"

/**
 * @class TramaLoad
 * @brief Trama de carga - decodifica y almacena un caracter
 */
class TramaLoad : public TramaBase {
private:
    char dato;  ///< Caracter a decodificar
    
public:
    /**
     * @brief Constructor
     * @param c Caracter recibido en la trama
     */
    TramaLoad(char c);
    
    /**
     * @brief Destructor
     */
    ~TramaLoad();
    
    /**
     * @brief Procesa la trama - decodifica el caracter y lo almacena
     * @param carga Lista donde se almacena el mensaje
     * @param rotor Rotor para decodificar
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_LOAD_H
