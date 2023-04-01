#include "listaenlazada.h"

ListaEnlazada::ListaEnlazada()
{
    this->head = nullptr;
}

ListaEnlazada::~ListaEnlazada(){

}

void ListaEnlazada::insertNode(int value){
    Node* newNode = new Node(value);

    if(head == nullptr){
        head = newNode;
        return;
    }

    Node* iteratorNode = this->head;

    while(iteratorNode->next != nullptr){
        iteratorNode = iteratorNode->next;
    }

    iteratorNode->next = newNode;

    return;
}

Node* ListaEnlazada::searchNode(int value){
    if(this->head == nullptr)
        return nullptr;

    Node* iteratorNode = this->head;

    if(iteratorNode->value == value)
        return iteratorNode; //Returns head

    while(iteratorNode->next != nullptr){
        if(iteratorNode->next->value == value)
            return iteratorNode; //Returns prev Node
        else
            iteratorNode = iteratorNode->next;
    }

    return nullptr;
}

bool ListaEnlazada::deleteNode(int value){
    Node* prev = searchNode(value);
    Node* temp;

    if(prev != nullptr){
        if(prev->value == value){
            head = prev->next;
            prev->next = nullptr;
            delete prev;
            return true;
        }

        temp = prev->next;
        prev->next = prev->next->next;

        delete temp;
        return true;
    }

    return false;
}
