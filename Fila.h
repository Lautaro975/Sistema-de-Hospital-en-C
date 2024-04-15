#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include "ListasDobleFila.h"
#include "Pila.h"

typedef struct{
  Medico datoMedico;
  usuario datoPaciente;
}registroArregloDeFilas;

typedef struct{
  nodoDobleFila* principio;
  nodoDobleFila* ultimo;
}Fila;


typedef struct{
  Fila FilaDePacientes;
  Medico dato;
}celdaMedicosFila;

void inicFila(Fila* fila);
void InsertarFila(Fila* fila,usuario dato);
usuario extraerFila(Fila* fila);

/// Arreglo de filas

int AltaArregloDeFilaDePacientes(celdaMedicosFila clM[],int validosArregloFilas,Medico doctorDato,usuario pacienteDato);
int BuscarPosMedicosFila(celdaMedicosFila clM[],int  validosArregloFilas, int matricula);
int AgregarArreglodeMedicosDeFilas(Medico dato,celdaMedicosFila clM[],int  validosArregloFilas);
void mostrarArregloDeFilaDePacientes(celdaMedicosFila clM[],int  validosArregloFilas);
void RecorrerYmostrarLaFila(nodoDobleFila* lista);
void cargarUnNuevoMedicoArchivoArregloFilas (char nombreArchivoTurnosPorAtender[],Medico datoMedico, usuario pacienteAtender);
int ingresarDatosTurnoAlArchivoYarregloDeFilasPacientes(celdaMedicosFila arregloMedicosFila[],char nombreArchivoTurnosPorAtender[],int validosAregloFilas, Medico datoMedico, usuario pacienteAtender);
int pasarRegistroAarregloFilasPacientesPorAtender (char nombreArchivo[], celdaMedicosFila arregloMedicosFila[], int dimension);
usuario AtenderUnPaciente(celdaMedicosFila clM[],int  validosArregloFilas,Medico dato,celdaMedicosPila clpila[], int validosArregloPilas);

#endif // FILA_H_INCLUDED
