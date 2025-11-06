/**
 * @file RotorDeMapeo.h
 * @brief Lista Circular Doblemente Enlazada para mapeo de caracteres
 * @author Decodificador PRT-7 Team
 * @date 2025-11-06
 * 
 * El RotorDeMapeo es una lista circular que simula un "disco de cifrado"
 * similar a las maquinas Enigma. Contiene el alfabeto A-Z y un espacio,
 * y puede rotar para cambiar el mapeo de caracteres.
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
 * @brief Lista circular doblemente enlazada que actua como disco de cifrado
 * 
 * Esta estructura contiene los caracteres A-Z y espacio en orden.
 * El puntero 'cabeza' indica la posicion "cero" actual del rotor.
 * Al rotar, la cabeza se mueve, cambiando el mapeo de caracteres.
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
     * @brief Constructor - Inicializa el rotor con A-Z y espacio
     * 
     * Crea una lista circular con 27 nodos (26 letras + 1 espacio).
     * La cabeza apunta inicialmente a 'A'.
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor - Libera toda la memoria de la lista circular
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Rota el rotor N posiciones
     * 
     * Mueve el puntero 'cabeza' N posiciones en la lista circular.
     * Positivo = rotar a la derecha (siguiente)
     * Negativo = rotar a la izquierda (previo)
     * 
     * @param n Numero de posiciones a rotar
     */
    void rotar(int n);
    
    /**
     * @brief Obtiene el caracter mapeado segun la rotacion actual
     * 
     * Esta es la funcion de mapeo del rotor. Dado un caracter de entrada,
     * calcula que caracter le corresponde basado en la rotacion actual.
     * 
     * Logica:
     * 1. Buscar el caracter 'in' en el rotor
     * 2. Calcular su distancia relativa a la cabeza
     * 3. Devolver el caracter que esta en esa misma distancia desde 'A'
     * 
     * @param in Caracter a mapear
     * @return Caracter mapeado segun la rotacion actual
     */
    char getMapeo(char in);
    
    /**
     * @brief Imprime el estado actual del rotor (debug)
     */
    void imprimirRotor();
};

#endif // ROTOR_DE_MAPEO_H
