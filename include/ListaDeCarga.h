/**
 * @file ListaDeCarga.h
 * @brief Lista Doblemente Enlazada para almacenar el mensaje decodificado
 * @author Decodificador PRT-7 Team
 * @date 2025-11-06
 * 
 * La ListaDeCarga almacena los caracteres decodificados en orden de llegada.
 * Esta es una lista doblemente enlazada LINEAL (no circular), con inicio y fin.
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
 * @brief Lista doblemente enlazada para el mensaje decodificado
 * 
 * Esta estructura almacena los caracteres decodificados en el orden
 * en que se procesan las tramas LOAD. Es una lista LINEAL (no circular).
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
     * 
     * Este metodo es llamado por TramaLoad::procesar() para agregar
     * cada caracter decodificado al mensaje.
     * 
     * @param dato Caracter a insertar
     */
    void insertarAlFinal(char dato);
    
    /**
     * @brief Imprime el mensaje completo almacenado
     * 
     * Recorre la lista e imprime todos los caracteres en orden,
     * mostrando el mensaje oculto ensamblado.
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
