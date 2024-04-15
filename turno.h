#ifndef TURNO_H_INCLUDED
#define TURNO_H_INCLUDED
#include "medico-h.h"
#define cantTurnos 10
#define horarioInicialT 9

typedef struct
{
    char nombreYapellido[20];
    int matricula;
    int telefono;
    int consultorio;
    char especialidad[20];
    int horario;
    char fecha[20];
    int habilitado; // 0 si / 1 no
} registroTurnos;

typedef struct
{
    int horario;
    char fecha[20];
    struct nodoFechasHorarios* siguiente;
} nodoFechasHorarios;

typedef struct
{
    Medico dato;
    char especialidad[20];
    nodoFechasHorarios* turno;
} celdaTurnos; //solo medicos habilitados



///Prototipos

void cargarRegistroTurnos (char nombreArchivoTurnos[], celda arregloM[], int validos);
void copiarDatosAregistroTurnos (nodoMedicos* listaN, FILE* archi, char especialidad[]);
void mostrarUnRegistroTurno(registroTurnos dato);
void mostrarRegistroTurnos (char nombreArchiT[]);
nodoFechasHorarios* inicListaTurnos ();
nodoFechasHorarios* crearNodoTurno (char fecha[], int horario);
nodoFechasHorarios* agregarEnOrdenHorariosTurno (nodoFechasHorarios* listaT, nodoFechasHorarios* nuevoNodo);
int existeMatriculaTurno (celdaTurnos arreglo[], int validos, int matricula);
int agregarMedicoAarregloTurnos(celdaTurnos arregloT[],char nombreYapellido[20],int matricula,int telefono,int consultorio,char especialidad[20], int habilitado,int validosT);
int altaTurnos(celdaTurnos arregloT[],char nombreYapellido[20],int matricula,int telefono,int consultorio,char especialidad[20],char fecha[], int horario, int habilitado, int validosT);
int pasarRegistroTurnosArregloMedico (char nombreArchivo[], celdaTurnos arregloT[], int dimensionT);
void mostrarListaTurnosMedicosHabilitados(nodoFechasHorarios* lista);
void mostrarArregloTurnosDisponiblesMedicosHabilitados (celdaTurnos arregloT[], int validos);
void mostrarArregloTurnosMedicosHabilitadosPorMatricula (celdaTurnos arregloT[], int validos, int matricula);
void cargarUnNuevoTurnoArchivoTurnos(char nombreArchivoTurnos[], char especialidad[], char fecha[], char nombreYapellido[], int matricula, int telefono, int consultorio,  int habilitado);
int agregarDesdeRegistroTurnosAlArregloTurnosUnNuevoMedico (char nombreArchivoTurnos[], int matricula, celdaTurnos arregloT[], int validosTurnos);
int ingresarNuevosTurnosAregistroYarregloTurnos(celdaTurnos arregloTurnos,char nombreArchivoTurnos[],int validosArregloTurnos, registroArchivoMedicos nuevoM);
void actualizarDisponibilidadTurnos(FILE* archiTodosTurnos, int matricula, int horario);
registroTurnosPaciente cargarRegistroTurnoPaciente (celdaTurnos arregloT[], int pos, int dni, int horario, char fecha[], char especialidad[]);
registroTurnosPaciente elegirTurno (celdaTurnos arregloT[], int validosT, int dniP, int matricula, char fecha[], int horario, char especialidad[]);
nodoFechasHorarios* actualizarAturnoNoDisponibleLista (nodoFechasHorarios* listaT,  int horario);
void pasarDeListaTurnosAarchivoTurnos (nodoFechasHorarios* lista, Medico dato,FILE* archi, char especialidad[]);
void pasarDeArregloListasTurnosAarchivoTurnos (char nombreArchivo[], celdaTurnos arregloT[], int validos);
int validarHorarioElegidoEnListaTurnosDisponiblesMedico (nodoFechasHorarios* lista, int horarioElegido);
nodoFechasHorarios* borrarHorarioListaTurnosDeMedico (nodoFechasHorarios* lista, int horario);
nodoFechasHorarios* buscarYdevolverUnNodoFechaHorarios(nodoFechasHorarios* listaMedicos, int matricula);
#endif // TURNO_H_INCLUDED
