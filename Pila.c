#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Pila.h"


void inicPila(PILA* pila) ///Incialiaza una pila
{
    pila->principio = inicNodoPila();
}

void apilar(PILA* pila,usuario dato) ///Apila una pila
{
    PILA* nuevo = CrearNodoPila(dato);

    AgregarAlprincipioPila((&pila->principio),nuevo);

}

void mostrarPiladePacientes(PILA pila)///Muestra una pila
{

    printf("\n..................|PILA DE PACIENTES ATENDIDOS|.......................\n");
    if(pila.principio != NULL)
    {
      RecorrerYmostrarListaPila (pila.principio);
    }
    printf("\n...............................................\n");

}
/// Funcion de cuantas personas tiene a la pila

int cuantosPacientesAtendioUnMedico (celdaMedicosPila arregloPila[], int validosArregloP, int pos)
{
    int rdo=0;

    int flag;
    flag=pilavacia(&(arregloPila[pos].PilaDePacientes));
        if(flag!=0)
        {
            rdo= cantDatosPila(&(arregloPila[pos].PilaDePacientes));
        }

return rdo;
}

int cantDatosPila (PILA* pila)
{
    int cantPacientes = 0;

    cantPacientes= contarDatosListaPila(pila->principio);

    return cantPacientes;
}



int pilavacia(PILA* pila)///Retorna 0 si esta vacia y 1 si tiene datos
{
    int flag = 0;

    if(pila->principio != NULL)
    {
        flag = 1;
    }

    return flag;
}

usuario desapilar(PILA* pila) ///Retorna el tope y elimina el tope de la pila
{
    usuario tope;
    if(pilavacia(pila) == 1)
    {
        tope = topePila(pila->principio);
        PILA* aux = pila;
        pila->principio = (pila->principio)->sig;
        free(aux);
    }
    return tope;
}

int AltaArregloDePilaDePacientes(celdaMedicosPila clM[],int validosArregloPilas,Medico doctorDato,usuario pacienteDato)
{
    int posMedicos = BuscarPosMedicosPila(clM, validosArregloPilas,doctorDato.matricula);

    if(posMedicos == -1)
    {
        validosArregloPilas= AgregarUnMedicoArreglodeMedicosDePilas(doctorDato ,clM, validosArregloPilas);
        posMedicos = validosArregloPilas-1;
    }

    apilar(&(clM[posMedicos].PilaDePacientes),pacienteDato);

return  validosArregloPilas;

}

int BuscarPosMedicosPila(celdaMedicosPila clM[],int  validosArregloPilas, int matricula)
{
    int flag = -1;
    int i=0;

    while(i< validosArregloPilas && flag== -1)
    {
        if(matricula == clM[i].dato.matricula)
        {
            flag = i;
        }
        i++;
    }
    return flag;
}

int AgregarUnMedicoArreglodeMedicosDePilas(Medico dato,celdaMedicosPila clM[],int  validosArregloPilas)
{
    clM[ validosArregloPilas].dato = dato;

    inicPila(&(clM[validosArregloPilas].PilaDePacientes));

     validosArregloPilas++;

return  validosArregloPilas;
}

void mostrarArregloDePilaDePacientes(celdaMedicosPila clM[],int  validosArregloPilas)
{
    int i=0;
    while(i< validosArregloPilas)
    {
        printf("\n...................DOCTOR..................\n");
        mostrarDatosUnMedico(clM[i].dato);
        mostrarPiladePacientes(clM[i].PilaDePacientes);
        i++;
    }
}

void cargarUnNuevoMedicoArchivoArregloPilas(char nombreArchivoTurnosAtendendidos[],Medico datoMedico, usuario pacienteAtender)
{
    FILE* archi= fopen(nombreArchivoTurnosAtendendidos, "ab");
    registroArregloDePilas nuevoDato;

    if(archi!=NULL)
    {
        nuevoDato.datoMedico=datoMedico;
        nuevoDato.datoUsuario= pacienteAtender;
        fwrite(&nuevoDato, sizeof(registroArregloDePilas),1,archi);
    fclose(archi);
    }

}

int pasarRegistroAarregloPilasPacientesAtendendidos(char nombreArchivo[], celdaMedicosPila arregloMedicosPila[], int dimension)
{
    FILE* archi= fopen(nombreArchivo,"rb");
    registroArregloDePilas dato;
    int i=0;

    if(archi!=NULL)
    {
        while((fread(&dato, sizeof(registroArregloDePilas), 1, archi)>0) && i<dimension)
        {
            i = AltaArregloDePilaDePacientes(arregloMedicosPila, i, dato.datoMedico, dato.datoUsuario);

        }
        fclose(archi);
    }
    return i;
}



void mostrarArchivoPilas (char nombreDelArchivo[])
{

    FILE* archi= fopen(nombreDelArchivo,"rb");
    registroArregloDePilas dato;
    if(archi!=NULL)
    {
        while((fread(&dato, sizeof(registroArregloDePilas), 1, archi)>0) )
        {
           printf("\n%i", dato.datoMedico.matricula);
           printf("\nNombre Paciente %s", dato.datoUsuario.nombre);

        }
        fclose(archi);
    }

}



