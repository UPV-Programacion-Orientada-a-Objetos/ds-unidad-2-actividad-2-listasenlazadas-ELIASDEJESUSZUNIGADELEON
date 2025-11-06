/**
 * @file TramaLoad.h
 * @brief Clase para tramas de tipo LOAD del protocolo PRT-7
 * @author Decodificador PRT-7 Team
 * @date 2025-11-06
 * 
 * Las tramas LOAD contienen un fragmento de dato (un caracter) que debe
 * ser decodificado usando el rotor de mapeo actual y almacenado en la
 * lista de carga.
 */

#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"

/**
 * @class TramaLoad
 * @brief Representa una trama de carga (L,X)
 * 
 * Esta clase almacena un caracter recibido del puerto serial y lo
 * decodifica usando el estado actual del rotor de mapeo cuando se
 * ejecuta el metodo procesar().
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
     * @brief Procesa la trama LOAD
     * 
     * Toma el caracter almacenado, lo decodifica usando el rotor,
     * y almacena el resultado en la lista de carga.
     * 
     * @param carga Puntero a la lista donde se almacena el mensaje decodificado
     * @param rotor Puntero al rotor de mapeo para decodificar el caracter
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_LOAD_H
