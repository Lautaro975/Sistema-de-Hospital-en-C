#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ListasDobleFila.h"
#include "Fila.h"
#include "Usuario.h"


void inicFila(Fila* fila)
{
    fila->principio = NULL;
    fila->ultimo = NULL;
}

//Esta funcion inserta un nuevo paciente al final de la fila
void InsertarFila(Fila* fila,usuario dato)
{
    nodoDobleFila* nuevo = CrearNodoDobleFila(dato);
    if(fila->principio == NULL)
    {
        fila->principio = nuevo;
    }else
    {

        fila->principio= agregarAlFinalNodoDobleFila(fila->principio, nuevo);
    }
    fila->ultimo = nuevo;
}

usuario extraerFila(Fila* fila)
{
    usuario auxiliarUsuario;

    if(fila->principio != NULL)
    {
        auxiliarUsuario = verElPrimeroNodoDoble(fila->principio);
        fila->principio = borrarPrimero(fila->principio);

        if(fila->principio == NULL)
        {
            fila->ultimo = NULL;
        }
    }
    return auxiliarUsuario;
}

int AltaArregloDeFilaDePacientes(celdaMedicosFila clM[],int validosArregloFilas,Medico doctorDato,usuario pacienteDato)
{
    int posMedicos = BuscarPosMedicosFila(clM, validosArregloFilas,doctorDato.matricula);

    if(posMedicos == -1)
    {
        validosArregloFilas= AgregarArreglodeMedicosDeFilas(doctorDato ,clM, validosArregloFilas);
        posMedicos = ( validosArregloFilas)-1;
    }
    InsertarFila(&(clM[posMedicos].FilaDePacientes),pacienteDato);

return  validosArregloFilas;

}

int BuscarPosMedicosFila(celdaMedicosFila clM[],int  validosArregloFilas,int matricula)
{
    int flag = -1;
    int i=0;

    while(i< validosArregloFilas && flag== -1)
    {
        if(matricula == clM[i].dato.matricula)
        {
            flag = i;
        }
        i++;
    }
    return flag;
}

int AgregarArreglodeMedicosDeFilas(Medico dato,celdaMedicosFila clM[],int  validosArregloFilas)
{
    clM[ validosArregloFilas].dato = dato;

    inicFila(&(clM[validosArregloFilas].FilaDePacientes));

     validosArregloFilas++;

return  validosArregloFilas;
}

void mostrarArregloDeFilaDePacientes(celdaMedicosFila clM[],int  validosArregloFilas)
{
    int i=0;
    while(i< validosArregloFilas)
    {
        printf("\n...................DOCTOR..................\n");
        mostrarDatosUnMedico(clM[i].dato);
        mostrarFilaDePacientes (clM[i].FilaDePacientes);
        i++;
    }
}

void mostrarFilaDePacientes (Fila filaP)
{
     mostrarLaListaDoble(filaP.principio);
}

void cargarUnNuevoMedicoArchivoArregloFilas (char nombreArchivoTurnosPorAtender[],Medico datoMedico, usuario pacienteAtender)
{
    FILE* archi= fopen(nombreArchivoTurnosPorAtender, "ab");
    registroArregloDeFilas nuevoDato;

    if(archi!=NULL)
    {
        nuevoDato.datoMedico=datoMedico;
        nuevoDato.datoPaciente= pacienteAtender;

        fwrite(&nuevoDato, sizeof(registroArregloDeFilas),1,archi);
        fclose(archi);
    }
}

int ingresarDatosTurnoAlArchivoYarregloDeFilasPacientes(celdaMedicosFila arregloMedicosFila[],char nombreArchivoTurnosPorAtender[],int validosAregloFilas, Medico datoMedico, usuario pacienteAtender)
{
    cargarUnNuevoMedicoArchivoArregloFilas (nombreArchivoTurnosPorAtender, datoMedico, pacienteAtender);
    validosAregloFilas= AltaArregloDeFilaDePacientes(arregloMedicosFila, validosAregloFilas, datoMedico, pacienteAtender);
    return validosAregloFilas;
}

int pasarRegistroAarregloFilasPacientesPorAtender(char nombreArchivo[], celdaMedicosFila arregloMedicosFila[], int dimension)
{
    registroArregloDeFilas datoN;

    FILE* archi= fopen(nombreArchivo, "rb");
    int i=0;

    if(archi!=NULL)
    {
        while((fread(&datoN, sizeof(registroArregloDeFilas), 1, archi)>0) && i<dimension)
        {
            i= AltaArregloDeFilaDePacientes(arregloMedicosFila,i, datoN.datoMedico, datoN.datoPaciente);

        }
        fclose(archi);
    }

    return i;
}



usuario AtenderUnPaciente(celdaMedicosFila clM[],int  validosArregloFilas,Medico dato,celdaMedicosPila clpila[], int validosArregloPilas)
{
    int pos = BuscarPosMedicosFila(clM, validosArregloFilas,dato.matricula);
    usuario paciente = extraerFila(&(clM[pos].FilaDePacientes));

    int posPila = BuscarPosMedicosPila(clpila,validosArregloPilas,dato.matricula);
    apilar(&(clpila[posPila].PilaDePacientes),paciente);


    return paciente;
}
