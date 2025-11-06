/**
 * @file SerialPort.cpp
 * @brief Implementacion de comunicacion serial para Windows
 * @author Decodificador PRT-7 Team
 * @date 2025-11-06
 */

#include "SerialPort.h"
#include <iostream>
#include <cstring>

/**
 * @brief Constructor - Abre y configura el puerto serial
 */
SerialPort::SerialPort(const char* portName) : conectado(false) {
    // Copiar nombre del puerto
    int len = 0;
    while (portName[len] != '\0') len++;
    puerto = new char[len + 1];
    for (int i = 0; i <= len; i++) {
        puerto[i] = portName[i];
    }
    
#ifdef WINDOWS_BUILD
    // Construir el nombre completo del puerto (ej: "\\\\.\\COM9")
    char fullPortName[20];
    fullPortName[0] = '\\'; fullPortName[1] = '\\';
    fullPortName[2] = '.'; fullPortName[3] = '\\';
    int i = 0;
    while (portName[i] != '\0') {
        fullPortName[4 + i] = portName[i];
        i++;
    }
    fullPortName[4 + i] = '\0';
    
    // Abrir el puerto serial
    hSerial = CreateFileA(
        fullPortName,
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: No se pudo abrir el puerto " << portName << std::endl;
        return;
    }
    
    // Configurar parametros del puerto (115200 baudios, 8N1)
    dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: No se pudo obtener el estado del puerto" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    
    dcbSerialParams.BaudRate = CBR_115200;  // 115200 baudios
    dcbSerialParams.ByteSize = 8;           // 8 bits de datos
    dcbSerialParams.StopBits = ONESTOPBIT;  // 1 bit de parada
    dcbSerialParams.Parity = NOPARITY;      // Sin paridad
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: No se pudo configurar el puerto" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    
    // Configurar timeouts
    timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cerr << "Error: No se pudo configurar los timeouts" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    
    conectado = true;
    std::cout << "Puerto " << portName << " abierto correctamente a 115200 baudios" << std::endl;
#else
    std::cerr << "Error: Esta version solo soporta Windows" << std::endl;
#endif
}

/**
 * @brief Destructor - Cierra el puerto
 */
SerialPort::~SerialPort() {
    cerrar();
    delete[] puerto;
}

/**
 * @brief Verifica si esta conectado
 */
bool SerialPort::estaConectado() const {
    return conectado;
}

/**
 * @brief Lee una linea del puerto serial
 */
int SerialPort::leerLinea(char* buffer, int bufferSize) {
#ifdef WINDOWS_BUILD
    if (!conectado) return 0;
    
    DWORD bytesLeidos = 0;
    int posicion = 0;
    char caracter;
    
    // Leer caracter por caracter hasta encontrar '\n'
    while (posicion < bufferSize - 1) {
        if (ReadFile(hSerial, &caracter, 1, &bytesLeidos, nullptr)) {
            if (bytesLeidos > 0) {
                // Ignorar \r
                if (caracter == '\r') {
                    continue;
                }
                
                // Fin de linea
                if (caracter == '\n') {
                    buffer[posicion] = '\0';
                    return posicion;
                }
                
                // Agregar caracter al buffer
                buffer[posicion++] = caracter;
            } else {
                // No hay datos disponibles
                break;
            }
        } else {
            // Error de lectura
            conectado = false;
            return 0;
        }
    }
    
    buffer[posicion] = '\0';
    return posicion;
#else
    buffer[0] = '\0';
    return 0;
#endif
}

/**
 * @brief Cierra el puerto serial
 */
void SerialPort::cerrar() {
#ifdef WINDOWS_BUILD
    if (conectado) {
        CloseHandle(hSerial);
        conectado = false;
        std::cout << "Puerto serial cerrado" << std::endl;
    }
#endif
}
