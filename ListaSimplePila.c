#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Pila.h"



nodoPila* inicNodoPila() ///Incialiaza el nodo pila
{
    return NULL;
}
nodoPila* CrearNodoPila(usuario dato)
{
    nodoPila* nuevo = (nodoPila*)malloc(sizeof(nodoPila));
    nuevo->dato = dato;
    nuevo->sig = NULL;

    return nuevo;
}

void AgregarAlprincipioPila(nodoPila** lista,nodoPila* nuevo)
{
    if((*lista) == NULL)
    {
        (*lista) = nuevo;
    }
    else
    {
        nuevo->sig = (*lista);
        (*lista) = nuevo;
    }
}

void RecorrerYmostrarListaPila (nodoPila* lista)
{
    while(lista != NULL)
    {
        mostrarUnPaciente(lista->dato);
        lista = lista->sig;
    }
}
usuario topePila(nodoPila* lista)
{
    usuario datoPaciente;
    if(lista!=NULL)
    {
        datoPaciente= lista->dato;
    }

    return datoPaciente;
}

int contarDatosListaPila (nodoPila* lista)
{
    int rta=0;

    if(lista!=NULL)
    {
        while(lista!=NULL)
        {
           rta++;
           lista=lista->sig;
        }
    }

return rta;
}
