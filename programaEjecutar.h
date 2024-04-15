#ifndef PROGRAMAEJECUTAR_H_INCLUDED
#define PROGRAMAEJECUTAR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "windows.h"
#include "medico-h.h"
#include "Usuario.h"
#include "turno.h"
#include "Fila.h"
#include "ListasDobleFila.h"
#include "Pila.h"
#include "ListaSimplePila.h"

void menuSistema();
void menuEjecutar();
void MostrarMedicosPorEspecialidad(celda arregloMedicos[], int validosArregloMedicos);
void MostrarTurnosDisponiblesPorMedico(celda arregloMedicos[], int validosArregloMedicos, celdaTurnos arregloTurnos[], int validosArregloTurnos);
void mostrarArregloDePilaDePaciente(celdaMedicosPila clM[],int  validosArregloPilas);
void verCantidadDePacientesAtendidosPorMedico (celdaMedicosPila arregloPilas[], int validosArregloPila);
void mostrarPacientePorDni(NodoUsuario* arbolUsuario);
registroTurnosPaciente elegirUnTurnoPaciente (NodoUsuario* arbolUsuario, celdaTurnos arregloTurnos[], int validosArregloTurnos, celda arregloMedicos[], int validosArregloMedicos);
void mostrarTodosLosDatosPacienteYTurnosPorDni (NodoUsuario* arbolUsuario);
void opcionesMenu();
void gotoxy(int x, int y); /// FUNCION UTILIZADA PARA UBICAR EL CURSOR (NOSOTROS LA UTILIZAMOS PARA CENTRAR EL TEXTO).
void menuPrincipio();
#endif // PROGRAMAEJECUTAR_H_INCLUDED
