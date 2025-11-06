#include <Arduino.h>

// Definicion de los mensajes a enviar (secuencia de prueba)
const char* tramas[] = {
    "L,H",      // Load H
    "L,O",      // Load O
    "L,L",      // Load L
    "M,2",      // Map +2 (rotar rotor)
    "L,A",      // Load A (se decodificara como C)
    "L, ",      // Load espacio
    "L,W",      // Load W (se decodificara como Y)
    "M,-2",     // Map -2 (regresar rotor)
    "L,O",      // Load O
    "L,R",      // Load R
    "L,L",      // Load L
    "L,D",      // Load D
    "FIN"       // Marcador de fin
};

const int numTramas = sizeof(tramas) / sizeof(tramas[0]);
int tramaActual = 0;
bool transmisionCompleta = false;

void setup() {
    // Inicializar comunicacion serial a 115200 baudios
    Serial.begin(115200);
    
    // Esperar a que el puerto serial este listo
    delay(2000);
    
    // Banner de inicio
    Serial.println("========================================");
    Serial.println("  ESP32 - Transmisor Protocolo PRT-7   ");
    Serial.println("  Sistema de Telemetria Industrial     ");
    Serial.println("========================================");
    Serial.println();
    Serial.println("Iniciando transmision de tramas...");
    Serial.println("Velocidad: 115200 baudios");
    Serial.println();
    
    delay(1000);
}

void loop() {
    if (!transmisionCompleta) {
        if (tramaActual < numTramas) {
            // Enviar la trama actual
            Serial.println(tramas[tramaActual]);
            
            // Mensaje de debug (opcional, comentar si causa problemas)
            // Serial.print(">>> Trama enviada: ");
            // Serial.println(tramas[tramaActual]);
            
            tramaActual++;
            
            // Esperar 1 segundo entre tramas
            delay(1000);
        } else {
            // Transmision completada
            transmisionCompleta = true;
            Serial.println();
            Serial.println("========================================");
            Serial.println("  Transmision completada               ");
            Serial.println("========================================");
        }
    }
    
    // Una vez completado, no hacer nada mas (idle)
    delay(1000);
}
