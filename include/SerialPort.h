/**
 * @file SerialPort.h
 * @brief Clase para comunicacion serial en Windows
 * @author Decodificador PRT-7 Team
 * @date 2025-11-06
 * 
 * Esta clase maneja la comunicacion con el puerto COM usando Win32 API.
 * Permite abrir, configurar, leer y cerrar puertos seriales en Windows.
 */

#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#ifdef WINDOWS_BUILD
#include <windows.h>
#endif

/**
 * @class SerialPort
 * @brief Maneja la comunicacion serial con el Arduino/ESP32
 * 
 * Usa la API de Windows (HANDLE, DCB, etc.) para comunicarse
 * con dispositivos seriales conectados via USB.
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
     * @brief Lee una linea de texto del puerto serial
     * 
     * Lee caracteres hasta encontrar '\n' o llenar el buffer.
     * Elimina caracteres de control (\r, \n).
     * 
     * @param buffer Buffer donde se almacenara la linea leida
     * @param bufferSize Tamanio maximo del buffer
     * @return Numero de caracteres leidos (0 si no hay datos)
     */
    int leerLinea(char* buffer, int bufferSize);
    
    /**
     * @brief Cierra el puerto serial
     */
    void cerrar();
};

#endif // SERIAL_PORT_H
