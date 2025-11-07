/**
 * @file ListaDeCarga.h
 * @brief Lista doblemente enlazada para el mensaje decodificado
 * @author Elias de Jesus Zuniga de Leon
 * @date 2025-11-06
 */

#ifndef LISTA_DE_CARGA_H
#define LISTA_DE_CARGA_H

/**
 * @struct NodoCarga
 * @brief Nodo de la lista doblemente enlazada
 */
struct NodoCarga {
    char dato;              ///< Caracter decodificado almacenado
    NodoCarga* siguiente;   ///< Puntero al siguiente nodo (nullptr si es el ultimo)
    NodoCarga* previo;      ///< Puntero al nodo previo (nullptr si es el primero)
    
    /**
     * @brief Constructor del nodo
     * @param c Caracter a almacenar
     */
    NodoCarga(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class ListaDeCarga
 * @brief Lista lineal doblemente enlazada que almacena el mensaje
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza;  ///< Puntero al primer nodo (nullptr si esta vacia)
    NodoCarga* cola;    ///< Puntero al ultimo nodo (nullptr si esta vacia)
    int tamanio;        ///< Numero de caracteres almacenados
    
    /**
     * @brief Imprime el mensaje en una linea (metodo auxiliar para debug)
     */
    void imprimirMensajeEnLinea();
    
public:
    /**
     * @brief Constructor - Inicializa una lista vacia
     */
    ListaDeCarga();
    
    /**
     * @brief Destructor - Libera toda la memoria
     */
    ~ListaDeCarga();
    
    /**
     * @brief Inserta un caracter al final de la lista
     * @param dato Caracter a insertar
     */
    void insertarAlFinal(char dato);
    
    /**
     * @brief Imprime el mensaje completo almacenado
     */
    void imprimirMensaje();
    
    /**
     * @brief Obtiene el numero de caracteres en la lista
     * @return Tamanio de la lista
     */
    int getTamanio() const;
    
    /**
     * @brief Verifica si la lista esta vacia
     * @return true si esta vacia, false si tiene elementos
     */
    bool estaVacia() const;
};

#endif // LISTA_DE_CARGA_H
