/**
 * @file RotorDeMapeo.h
 * @brief Lista circular para el rotor de mapeo de caracteres
 * @author Elias de Jesus Zuniga de Leon
 * @date 2025-11-06
 */

#ifndef ROTOR_DE_MAPEO_H
#define ROTOR_DE_MAPEO_H

/**
 * @struct NodoRotor
 * @brief Nodo de la lista circular doblemente enlazada
 */
struct NodoRotor {
    char dato;              ///< Caracter almacenado (A-Z o espacio)
    NodoRotor* siguiente;   ///< Puntero al siguiente nodo (circular)
    NodoRotor* previo;      ///< Puntero al nodo previo (circular)
    
    /**
     * @brief Constructor del nodo
     * @param c Caracter a almacenar
     */
    NodoRotor(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class RotorDeMapeo
 * @brief Lista circular con 27 nodos (A-Z + espacio) para mapear caracteres
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza;  ///< Puntero a la posicion "cero" actual del rotor
    
    /**
     * @brief Busca un nodo que contiene un caracter especifico
     * @param c Caracter a buscar
     * @return Puntero al nodo que contiene el caracter, o nullptr si no existe
     */
    NodoRotor* buscarNodo(char c);
    
    /**
     * @brief Calcula la distancia entre dos nodos en la lista circular
     * @param desde Nodo de inicio
     * @param hasta Nodo de destino
     * @return Numero de pasos desde 'desde' hasta 'hasta'
     */
    int calcularDistancia(NodoRotor* desde, NodoRotor* hasta);
    
public:
    /**
     * @brief Constructor - Crea lista circular con A-Z y espacio
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor - Libera toda la memoria de la lista circular
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Rota el rotor N posiciones
     * @param n Numero de posiciones (positivo = derecha, negativo = izquierda)
     */
    void rotar(int n);
    
    /**
     * @brief Obtiene el caracter mapeado segun la rotacion actual
     * @param in Caracter a mapear
     * @return Caracter mapeado
     */
    char getMapeo(char in);
    
    /**
     * @brief Imprime el estado actual del rotor (debug)
     */
    void imprimirRotor();
};

#endif // ROTOR_DE_MAPEO_H
