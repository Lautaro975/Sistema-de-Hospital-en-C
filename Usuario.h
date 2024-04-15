#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include "turno.h"
#include "medico-h.h"
#define MaxTurnos 10
#define MaxCaracteres 30

typedef struct turnos{
   int horario;
   Medico doctor;
   char especialidad[20];
   char fecha[MaxCaracteres];
}turnos;

typedef struct nodoTurnosPaciente{
  struct nodoTurnosPaciente* sig;
  turnos dato;
}nodoTurnosPaciente;

typedef struct{
  char ID[MaxCaracteres]; ///verificar
  char mail[MaxCaracteres];
  char contrasena[MaxCaracteres];///verificar
  int DNI;///verificar
  char telefono[MaxCaracteres];
  char nombre[MaxCaracteres];
}usuario;

typedef struct NodoUsuario{
  struct NodoUsuario* izq;
  struct NodoUsuario* der;
  struct nodoTurnosPaciente* listaTurnos;
  usuario dato;
}NodoUsuario;

typedef struct RegistroUsuario{
  usuario dato;
}RegistroUsuario;

typedef struct RegistroTurnos{
  turnos dato;
  int dni;
}RegistroTurnos;


typedef struct NodoVerificacion{
  char ID[MaxCaracteres]; ///verificar
  char contrasena[MaxCaracteres];///verificar
  int DNI;///verificar
  struct NodoVerificacion* sig;
}NodoVerificacion;

///Lista verificacion
NodoVerificacion* inicListaVerificacion();///Inicializa un nodo de verificacion
NodoVerificacion* crearNodoVerificacion(char contrasena[],char ID[],int DNI);///Crea un nodo de verificacion
int verificarDNI(NodoVerificacion* lista, int DNI);///retorna 1 si lo encuentra en la lista y 0 si no
int verificarNombre(NodoVerificacion* lista, char nombre[]);///retorna 1 si lo encuentra en la lista y 0 si no
int verificarContra(NodoVerificacion* lista, char contrasena[]);///retorna 1 si lo encuentra en la lista y 0 si no
void mostrarListaVerificacion(NodoVerificacion* lista);///Muestra una lista de verificacion
void AgregarAlprincipio(NodoVerificacion** lista, NodoVerificacion* nuevo);///Agrega al princpio un nodo a una lista


///Registro de Usuario y Turnos
void CargarRegistro(char nombre[],NodoVerificacion** lista);///Carga un registro y pasa la lista de verificacion
void RgTOlista(char nombre[],NodoVerificacion** lista);///Pasa de un registro ya cargado a una lista
void UnRegistro(RegistroUsuario* rg,NodoVerificacion** lista);///Carga una registro y verifica quee no se hayan usado los datos
void mostrarRegistro(char nombre[]);///Muestra un registro
NodoUsuario* CrearArbolUsuario(RegistroUsuario rg);///Crea un nodo de arbol
void registroAarbol(char nombre[],NodoUsuario** arbolUsuario);///De registro a Arbol
void registroTurnosAarbol(char nombre[],NodoUsuario** arbolUsuario);

///Arbol de listas
NodoUsuario* inicArbolUsuario();///Inicializa un Arbol
void mostrarArbol(NodoUsuario* arbol);///Muestra un arbol
void cargarListadeTurnos(nodoTurnosPaciente** lista,turnos dato);
void cargarArbol(RegistroUsuario rg,NodoUsuario** arbolUsuario);///Carga un Arbol
NodoUsuario* BuscarXdni(NodoUsuario* arbol, int DNI);///Busca un dni y retona nodo si lo encuentra y NULL sino
void mostrarUnArbol(NodoUsuario* arbol);///Muestra un arbol
void agregarAlistaTurnos(nodoTurnosPaciente** listas,registroTurnosPaciente datoTurno);///Agregar la lista de turnos
nodoTurnosPaciente* CrearNodoTurno(int horario,char fecha[],Medico datoDoctor, char especialidad[]);///Crear nodo de turnos
NodoUsuario* modificarDatosUsuario(NodoUsuario** arbol, int DNI, NodoVerificacion* lista);///Modificar los datos de Usuarios
void AgregarAlFinalUsuario(nodoTurnosPaciente** lista,nodoTurnosPaciente* nuevo);///Agregar el usuario al final de la lista de turnos
void arbolAregistro(NodoUsuario* arbol,FILE* archi,FILE* archi2);///Arbol a registro
void RecorrerYguardarLaLista(nodoTurnosPaciente* lista,FILE* archiTurn, int dni);///Recorrer la lista
int validarHorarioEnListaDeTurnosPaciente (nodoTurnosPaciente* lista, int horario);
int validarMatriculaMedicoEnListaDeTurnosPaciente (nodoTurnosPaciente* lista, int matricula);
nodoTurnosPaciente* devolverNodoTurnoPacienteDeMedicoYHorarioBuscado (nodoTurnosPaciente* lista, int matricula, int horario);
nodoTurnosPaciente* borrarTurnoDeListaTurnosPaciente (nodoTurnosPaciente* lista, int matricula, int horario);
void mostrarUnPaciente(usuario dato);
int existeIdYclave (NodoUsuario* arbol, char iD[], char clave[]);



#endif // USUARIO_H_INCLUDED
