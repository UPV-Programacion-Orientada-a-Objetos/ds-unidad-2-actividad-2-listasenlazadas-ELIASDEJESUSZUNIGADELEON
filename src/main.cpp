/**
 * @file main.cpp
 * @brief Punto de entrada principal del Decodificador PRT-7
 * @author Decodificador PRT-7 Team
 * @date 2025-11-06
 * 
 * Este programa implementa un decodificador para el protocolo industrial PRT-7,
 * que lee tramas desde un puerto serial (Arduino/ESP32) y ensambla mensajes ocultos
 * utilizando listas doblemente enlazadas y listas circulares.
 */

#include <iostream>
#include <cstring>
#include "SerialPort.h"
#include "TramaBase.h"
#include "TramaLoad.h"
#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

// Configuracion del puerto COM (CAMBIAR SEGUN TU SISTEMA)
const char* PUERTO_COM = "COM9";

/**
 * @brief Funcion para parsear una trama y crear el objeto correspondiente
 * 
 * Parsea una linea del tipo "L,X" o "M,N" sin usar STL.
 * Utiliza manipulacion manual de char* para extraer los datos.
 * 
 * @param linea Linea leida del puerto serial (ej: "L,H" o "M,2")
 * @return Puntero a TramaBase* (puede ser TramaLoad o TramaMap), o nullptr si es invalida
 */
TramaBase* parsearTrama(char* linea) {
    // Verificar que la linea no este vacia
    if (linea[0] == '\0') {
        return nullptr;
    }
    
    // Verificar si es trama de fin
    if (linea[0] == 'F' && linea[1] == 'I' && linea[2] == 'N') {
        return nullptr;
    }
    
    // Verificar formato minimo: "X,Y"
    int longitud = 0;
    while (linea[longitud] != '\0') longitud++;
    
    if (longitud < 3) {
        std::cerr << "Trama invalida (muy corta): " << linea << std::endl;
        return nullptr;
    }
    
    // Extraer el tipo de trama (primer caracter)
    char tipo = linea[0];
    
    // Verificar que el segundo caracter sea una coma
    if (linea[1] != ',') {
        // Ignorar silenciosamente (probablemente es texto del banner del ESP32)
        return nullptr;
    }
    
    // Extraer el dato (despues de la coma)
    char* dato = &linea[2];
    
    if (tipo == 'L') {
        // Trama LOAD: L,<caracter>
        char caracter = dato[0];
        std::cout << "\nTrama recibida: [" << linea << "] -> Procesando... -> ";
        return new TramaLoad(caracter);
        
    } else if (tipo == 'M') {
        // Trama MAP: M,<numero>
        // Convertir el string a int manualmente (atoi casero)
        int numero = 0;
        int signo = 1;
        int i = 0;
        
        // Verificar signo
        if (dato[0] == '-') {
            signo = -1;
            i = 1;
        } else if (dato[0] == '+') {
            i = 1;
        }
        
        // Convertir digitos
        while (dato[i] >= '0' && dato[i] <= '9') {
            numero = numero * 10 + (dato[i] - '0');
            i++;
        }
        
        numero *= signo;
        
        std::cout << "\nTrama recibida: [" << linea << "] -> Procesando... -> ";
        return new TramaMap(numero);
        
    } else {
        std::cerr << "Tipo de trama desconocido: " << tipo << std::endl;
        return nullptr;
    }
}

/**
 * @brief Funcion principal del programa
 */
int main() {
    // Banner de inicio
    std::cout << "========================================" << std::endl;
    std::cout << "  Decodificador de Protocolo PRT-7     " << std::endl;
    std::cout << "  Version 1.0 - Sistema de Ciberseguridad" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Iniciando Decodificador PRT-7..." << std::endl;
    std::cout << "Conectando a puerto " << PUERTO_COM << "..." << std::endl;
    
    // Crear puerto serial
    SerialPort serial(PUERTO_COM);
    
    if (!serial.estaConectado()) {
        std::cerr << "Error: No se pudo conectar al puerto serial." << std::endl;
        std::cerr << "Verifica que el ESP32 este conectado al puerto " << PUERTO_COM << std::endl;
        std::cout << "\nPresione Enter para salir..." << std::endl;
        std::cin.get();
        return 1;
    }
    
    std::cout << "Conexion establecida. Esperando tramas..." << std::endl;
    std::cout << std::endl;
    
    // Crear las estructuras de datos
    ListaDeCarga* listaCarga = new ListaDeCarga();
    RotorDeMapeo* rotor = new RotorDeMapeo();
    
    // Buffer para leer lineas
    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    
    bool decodificacionCompleta = false;
    
    // Bucle principal de lectura y decodificacion
    while (!decodificacionCompleta) {
        // Leer una linea del puerto serial
        int bytesLeidos = serial.leerLinea(buffer, BUFFER_SIZE);
        
        if (bytesLeidos > 0) {
            // Parsear la trama
            TramaBase* trama = parsearTrama(buffer);
            
            if (trama != nullptr) {
                // Procesar la trama (polimorfismo en accion!)
                trama->procesar(listaCarga, rotor);
                
                // Liberar memoria de la trama
                delete trama;
            } else {
                // Verificar si es el marcador de fin
                if (buffer[0] == 'F' && buffer[1] == 'I' && buffer[2] == 'N') {
                    decodificacionCompleta = true;
                }
            }
        }
        
        // Pequena pausa para no saturar el CPU
        // (en Windows no hay sleep estandar sin STL, asi que usamos un loop vacio)
        for (volatile int i = 0; i < 1000000; i++);
    }
    
    // Mostrar el mensaje final
    std::cout << "\n---" << std::endl;
    std::cout << "Flujo de datos terminado." << std::endl;
    listaCarga->imprimirMensaje();
    std::cout << "---" << std::endl;
    
    // Limpiar memoria
    std::cout << "\nLiberando memoria... ";
    delete listaCarga;
    delete rotor;
    serial.cerrar();
    std::cout << "Sistema apagado." << std::endl;
    
    std::cout << "\nPresione Enter para salir..." << std::endl;
    std::cin.get();
    
    return 0;
}
