
#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

// Forward declarations (declaraciones anticipadas)
class ListaDeCarga;
class RotorDeMapeo;

class TramaBase {
public:

    virtual ~TramaBase() {}

    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

#endif // TRAMA_BASE_H
