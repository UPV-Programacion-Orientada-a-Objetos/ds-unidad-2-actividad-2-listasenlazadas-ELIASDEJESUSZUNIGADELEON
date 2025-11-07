/**
 * @file TramaBase.h
 * @brief Clase base abstracta para todas las tramas del protocolo PRT-7
 * @author Elias de Jesus Zuniga de Leon
 * @date 2025-11-06
 * 
 * Define la interfaz comun para todos los tipos de tramas usando polimorfismo.
 */

#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

// Forward declarations
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Clase base abstracta para tramas del protocolo PRT-7
 * 
 * Esta clase no puede ser instanciada directamente. Las clases derivadas
 * (TramaLoad, TramaMap) deben implementar el metodo procesar().
 */
class TramaBase {
public:
    /**
     * @brief Destructor virtual
     * 
     * El destructor debe ser virtual para permitir la correcta destruccion
     * de objetos derivados cuando se eliminan a traves de punteros TramaBase*.
     */
    virtual ~TramaBase() {}
    
    /**
     * @brief Procesa la trama (metodo virtual puro)
     * 
     * Define como cada tipo de trama afecta al sistema de decodificacion.
     * 
     * @param carga Puntero a la lista donde se almacenan caracteres decodificados
     * @param rotor Puntero al rotor de mapeo usado para decodificar
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

#endif // TRAMA_BASE_H
