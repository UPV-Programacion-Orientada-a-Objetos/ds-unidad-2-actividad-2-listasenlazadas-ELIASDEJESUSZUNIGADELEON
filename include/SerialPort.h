/**
 * @file SerialPort.h
 * @brief Comunicacion serial con Arduino/ESP32 usando Win32 API
 * @author Elias de Jesus Zuniga de Leon
 * @date 2025-11-06
 */

#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#ifdef WINDOWS_BUILD
#include <windows.h>
#endif

/**
 * @class SerialPort
 * @brief Maneja la lectura del puerto COM (115200 baudios)
 */
class SerialPort {
private:
#ifdef WINDOWS_BUILD
    HANDLE hSerial;         ///< Handle del puerto serial
    DCB dcbSerialParams;    ///< Parametros de configuracion serial
    COMMTIMEOUTS timeouts;  ///< Configuracion de timeouts
#endif
    
    bool conectado;         ///< Estado de la conexion
    char* puerto;           ///< Nombre del puerto (ej: "COM9")
    
public:
    /**
     * @brief Constructor
     * @param portName Nombre del puerto COM (ej: "COM9")
     */
    SerialPort(const char* portName);
    
    /**
     * @brief Destructor - Cierra el puerto automaticamente
     */
    ~SerialPort();
    
    /**
     * @brief Verifica si el puerto esta conectado
     * @return true si esta conectado, false si no
     */
    bool estaConectado() const;
    
    /**
     * @brief Lee una linea del puerto serial
     * @param buffer Buffer para almacenar la linea
     * @param bufferSize Tamanio del buffer
     * @return Numero de caracteres leidos
     */
    int leerLinea(char* buffer, int bufferSize);
    
    /**
     * @brief Cierra el puerto serial
     */
    void cerrar();
};

#endif // SERIAL_PORT_H
