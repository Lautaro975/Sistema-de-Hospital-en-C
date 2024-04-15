#ifndef LISTASIMPLEPILA_H_INCLUDED
#define LISTASIMPLEPILA_H_INCLUDED
#include "Pila.h"
#include "Usuario.h"

typedef struct nodoPila{
  struct nodoPila* sig;
  usuario dato;
}nodoPila;

nodoPila* inicNodoPila(); ///Incialiaza el nodo pila
nodoPila* CrearNodoPila(usuario dato);
void AgregarAlprincipioPila(nodoPila** lista,nodoPila* nuevo);
void RecorrerYmostrarListaPila (nodoPila* lista);
usuario topePila(nodoPila* lista);
int contarDatosListaPila (nodoPila* lista);

#endif // LISTASIMPLEPILA_H_INCLUDED
