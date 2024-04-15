#ifndef LISTASDOBLEFILA_H_INCLUDED
#define LISTASDOBLEFILA_H_INCLUDED
#include "Usuario.h"


typedef struct nodoDobleFila{
  struct nodoDobleFila* sig;
  struct nodoDobleFila* ante;
  usuario dato;
}nodoDobleFila;


nodoDobleFila* inicListaDobleFila();
nodoDobleFila* CrearNodoDobleFila(usuario dato);
nodoDobleFila* buscarUltimoNodoDobleFila (nodoDobleFila* lista);
nodoDobleFila* agregarAlFinalNodoDobleFila (nodoDobleFila* lista, nodoDobleFila* nuevoN);
nodoDobleFila* borrarPrimero(nodoDobleFila* lista);
usuario verElPrimeroNodoDoble (nodoDobleFila* lista);
void mostrarLaListaDoble(nodoDobleFila* lista);

#endif // LISTASDOBLEFILA_H_INCLUDED
