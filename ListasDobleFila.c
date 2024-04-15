#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ListasDobleFila.h"
#include "Fila.h"


nodoDobleFila* inicListaDobleFila()
{
    return NULL;
}
nodoDobleFila* CrearNodoDobleFila(usuario dato)
{
    nodoDobleFila* nuevo = (nodoDobleFila*)malloc(sizeof(nodoDobleFila));
    nuevo->dato = dato;
    nuevo->sig = NULL;
    nuevo->ante = NULL;

    return nuevo;
}

nodoDobleFila* buscarUltimoNodoDobleFila (nodoDobleFila* lista)
{
  nodoDobleFila* ultimo=lista;

    if(lista!=NULL)//si la lista tiene elementos
    {
        while(ultimo->sig!=NULL)//llego hasta el anteultimo
        {
            ultimo=ultimo->sig;
        }
    }
    return ultimo;
}


nodoDobleFila* agregarAlFinalNodoDobleFila(nodoDobleFila* lista, nodoDobleFila* nuevoN)
{
    if(lista==NULL)
    {
        lista=nuevoN;
    }else
    {
        nodoDobleFila* ultimo= buscarUltimoNodoDobleFila(lista);
        ultimo->sig=nuevoN;
        nuevoN->ante=ultimo;
    }
return lista;
}
nodoDobleFila* borrarPrimero(nodoDobleFila* lista)
{
    nodoDobleFila* aux = lista;
    if(lista!=NULL)
    {
        lista = lista->sig;
        if(lista!=NULL)
        {
            lista->ante = NULL;
        }
        free(aux);
    }
    return lista;
}

usuario verElPrimeroNodoDoble (nodoDobleFila* lista)
{
    usuario datoPaciente;

    if(lista!=NULL)
    {
        datoPaciente= lista->dato;
    }

return datoPaciente;
}


void mostrarLaListaDoble(nodoDobleFila* lista)
{
    if(lista!=NULL)
    {
        printf("\nID: %s\n",lista->dato.ID);

        printf("\nContrasena: %s\n",lista->dato.contrasena);

        printf("\nNombre:%s\n",lista->dato.nombre);

        printf("\nDNI:%i\n",lista->dato.DNI);

        printf("\nMail:%s\n",lista->dato.mail);

        printf("\nTelefono:%s\n",lista->dato.telefono);

        lista =lista->sig;
    }
}
