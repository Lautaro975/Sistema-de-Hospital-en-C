#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include "ListaSimplePila.h"
#include "medico-h.h"
#include "Usuario.h"

typedef struct{
  usuario datoUsuario;
  Medico datoMedico;
}registroArregloDePilas;

typedef struct{
   nodoPila* principio;
}PILA;


typedef struct{
  PILA PilaDePacientes;
  Medico dato;
}celdaMedicosPila;

///Pila Basica
void inicPila(PILA* pila); ///Incialiaza una pila
void apilar(PILA* pila,usuario dato); ///Apila una pila paciente
void mostrarPiladePacientes(PILA pila); ///Muestra una pila de pacientes
int pilavacia(PILA* pila); ///Retorna 0 si esta vacia y 1 si tiene datos
usuario desapilar(PILA* pila); ///Retorna el tope y elimina el tope de la pila

///Arreglo de Pilas
int AltaArregloDePilaDePacientes(celdaMedicosPila clM[],int validosArregloPilas,Medico doctorDato,usuario pacienteDato);
int BuscarPosMedicosPila(celdaMedicosPila clM[],int  validosArregloPilas, int matricula);
int AgregarUnMedicoArreglodeMedicosDePilas(Medico dato,celdaMedicosPila clM[],int  validosArregloPilas);
void mostrarArregloDePilaDePacientes(celdaMedicosPila clM[],int  validosArregloPilas);
void cargarUnNuevoMedicoArchivoArregloPilas(char nombreArchivoTurnosAtendendidos[],Medico datoMedico, usuario pacienteAtender);
int pasarRegistroAarregloPilasPacientesAtendendidos(char nombreArchivo[], celdaMedicosPila arregloMedicosPila[], int dimension);
void mostrarArchivoPilas (char nombreDelArchivo[]);
int cuantosPacientesAtendioUnMedico (celdaMedicosPila arregloPila[], int validosArregloP, int pos);
int cantDatosPila (PILA* pila);







#endif // PILA_H_INCLUDED
