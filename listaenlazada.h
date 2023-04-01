#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include "node.h"

class ListaEnlazada
{
public:
    Node* head;
    ListaEnlazada();
    ~ListaEnlazada();

    void insertNode(int);
    bool deleteNode(int);
    Node* searchNode(int);
};

#endif // LISTAENLAZADA_H
