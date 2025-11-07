/**
 * @mainpage Decodificador de Protocolo Industrial PRT-7
 * 
 * @section intro Introduccion
 * 
 * Sistema de decodificacion de telemetria industrial que implementa el protocolo PRT-7.
 * El proyecto integra comunicacion serial con ESP32, estructuras de datos avanzadas
 * y programacion orientada a objetos.
 * 
 * @section features Caracteristicas Principales
 * 
 * - Comunicacion serial via puerto COM con ESP32
 * - POO con herencia, polimorfismo y clases abstractas
 * - Lista doblemente enlazada para almacenar el mensaje
 * - Lista circular para el rotor de mapeo (cifrado)
 * - Gestion manual de memoria (sin STL)
 * 
 * @section arch Arquitectura
 * 
 * El sistema consta de dos partes:
 * 
 * 1. **Transmisor (ESP32):** Envia tramas por serial
 * 2. **Decodificador (C++):** Lee y procesa las tramas
 * 
 * @section protocol Protocolo PRT-7
 * 
 * El protocolo usa dos tipos de tramas:
 * 
 * - **LOAD (L,X):** Carga un caracter a decodificar
 * - **MAP (M,N):** Rota el rotor N posiciones
 * 
 * @section classes Clases Principales
 * 
 * - TramaBase: Clase base abstracta
 * - TramaLoad: Procesa tramas de carga
 * - TramaMap: Procesa tramas de mapeo
 * - ListaDeCarga: Lista doble para el mensaje
 * - RotorDeMapeo: Lista circular para cifrado
 * - SerialPort: Comunicacion serial Windows
 * 
 * @section author Autor
 * 
 * Elias de Jesus Zuniga de Leon
 * Universidad Politecnica de Victoria
 * Programacion Orientada a Objetos
 * 
 * @date Noviembre 2025
 * @version 1.0
 */
