#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "time.h"
#include "turno.h"
#include "medico-h.h"
#include "Usuario.h"
#define cantTurnos 10

const char fecha[]= "27/11/23";

//Funcion que carga datos en un registro de turnos a partir del arreglo de listas de medicos
void cargarRegistroTurnos (char nombreArchivoTurnos[], celda arregloM[], int validos)
{
    FILE* archi=fopen(nombreArchivoTurnos, "wb");
    int i=0;

    if(archi!=NULL)
    {
        while(i<validos)
        {
            copiarDatosAregistroTurnos (arregloM[i].listaMedicos, archi, arregloM[i].especialidad);
            i++;
        }
        fclose(archi);
    }
}


void copiarDatosAregistroTurnos (nodoMedicos* listaN, FILE* archi, char especialidad[])
{
    registroTurnos nuevoR;
    int horarioInicial= horarioInicialT;

    while(listaN != NULL)
    {
        for (int t=0; t<cantTurnos; t++)
        {
            strcpy( nuevoR.especialidad,especialidad);
            strcpy(nuevoR.nombreYapellido, listaN->dato.nombreYapellido);
            nuevoR.matricula= listaN->dato.matricula;
            nuevoR.telefono=listaN->dato.telefono;
            nuevoR.consultorio=listaN->dato.consultorio;
            strcpy(nuevoR.fecha,fecha);
            nuevoR.habilitado=listaN->dato.habilitado;
            nuevoR.horario=horarioInicial;
            fwrite(&nuevoR, sizeof(registroTurnos),1,archi);
            horarioInicial++;
        }

        horarioInicial=horarioInicialT;

        listaN= listaN->siguiente;
    }

}


void mostrarUnRegistroTurno(registroTurnos dato)
{
    printf("\n...Datos Medico Turno...\n");
    printf("\nEspecialidad | %s",dato.especialidad);
    printf("\nMatricula | %i",dato.matricula);
    printf("\nNombre y apellido | %s",dato.nombreYapellido);

    if(dato.habilitado==1)
    {
        printf("\nConsultorio | Belgrano 2478 ");
    }
    else
    {
        printf("\nConsultorio | Mitre 1489 ");
    }

    if(dato.habilitado==0)
    {
        printf("\nHabilitado");
    }
    else
    {
        printf("\nNO habilitado");
    }

    printf("\nTelefono | %i", dato.telefono);
    printf("\n...Datos Turno....");
    printf("\nFecha turno | %s",dato.fecha);
    printf("\nHorario turno| %i hs", dato.horario);
    printf("\n...........................\n");
}

void mostrarRegistroTurnos (char nombreArchiT[])
{
    printf("\n TURNOS \n");
    registroTurnos datoM;
    FILE* archi= fopen(nombreArchiT, "rb");

    if(archi!=NULL)
    {
        while(fread(&datoM, sizeof(registroTurnos),1,archi)>0)
        {
            mostrarUnRegistroTurno(datoM);
        }
        fclose(archi);
    }
}

nodoFechasHorarios* inicListaTurnos ()
{
    return NULL;
}

nodoFechasHorarios* crearNodoTurno (char fecha[], int horario)
{
    nodoFechasHorarios* aux= (nodoFechasHorarios*)malloc(sizeof(nodoFechasHorarios));

    strcpy(aux->fecha, fecha);
    aux->horario= horario;

    aux->siguiente=NULL;

    return aux;
}

nodoFechasHorarios* agregarEnOrdenHorariosTurno (nodoFechasHorarios* listaT, nodoFechasHorarios* nuevoNodo)
{
    if(listaT==NULL)
    {
        listaT=nuevoNodo;
    }
    else
    {
        if(nuevoNodo->horario < listaT->horario)
        {
            nuevoNodo->siguiente=listaT;
            listaT=nuevoNodo;
        }
        else
        {
            nodoFechasHorarios* ante=listaT;
            nodoFechasHorarios* seg= listaT->siguiente;

            while(seg!=NULL && (seg->horario < nuevoNodo->horario))
            {
                ante= seg;
                seg=seg->siguiente;
            }

            nuevoNodo->siguiente=seg;
            ante->siguiente=nuevoNodo;
        }
    }

    return listaT;
}

//esta funcion busca en un arreglo de  turnos de medicos si encuentra la matricula del medico buscado, si lo encuentra retorna la posicion, sino devuelve -1
int existeMatriculaTurno (celdaTurnos arreglo[], int validos, int matricula)
{
    int rta=-1;
    int i=0;


    while(i<validos)
    {
        if(arreglo[i].dato.matricula == matricula)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}

int agregarMedicoAarregloTurnos(celdaTurnos arregloT[],char nombreYapellido[20],int matricula,int telefono,int consultorio,char especialidad[20], int habilitado,int validosT)
{
    strcpy(arregloT[validosT].especialidad,especialidad);
    strcpy(arregloT[validosT].dato.nombreYapellido,nombreYapellido);
    arregloT[validosT].dato.consultorio=consultorio;
    arregloT[validosT].dato.matricula=matricula;
    arregloT[validosT].dato.telefono=telefono;
    arregloT[validosT].dato.habilitado=habilitado;
    arregloT[validosT].turno=inicListaTurnos();
    validosT++; //incrementa la cantidad

    return validosT;
}

int altaTurnos(celdaTurnos arregloT[],char nombreYapellido[20],int matricula,int telefono,int consultorio,char especialidad[20],char fecha[], int horario, int habilitado, int validosT)
{
    nodoFechasHorarios* aux=crearNodoTurno (fecha, horario);

    int pos= existeMatriculaTurno(arregloT, validosT, matricula); //devuelve la posicion de la especialidad si la encontro y si no devuelve -1

    if(pos==-1) //si la especialidad no existe, la agrega al arreglo y luego carga los datos del medico
    {
        validosT=agregarMedicoAarregloTurnos(arregloT, nombreYapellido, matricula,telefono,consultorio,especialidad, habilitado,validosT);
        pos=validosT-1;
        //setea la posicion de la nueva materia
    }
    arregloT[pos].turno= agregarEnOrdenHorariosTurno(arregloT[pos].turno,aux); //si la especialidad existe, agrega los datos a la lista correspondiente

    return validosT;
}


int pasarRegistroTurnosArregloMedico (char nombreArchivo[], celdaTurnos arregloT[], int dimensionT)
{
    registroTurnos datoT;
    FILE* archi= fopen(nombreArchivo, "rb");
    int i=0;

    if(archi!=NULL)
    {
        while( (fread(&datoT, sizeof(registroTurnos), 1, archi)>0) && i<dimensionT)
        {
            i= altaTurnos(arregloT, datoT.nombreYapellido, datoT.matricula, datoT.telefono, datoT.consultorio, datoT.especialidad, datoT.fecha, datoT.horario,datoT.habilitado, i);
        }
        fclose(archi);
    }

    return i;
}

void mostrarListaTurnosMedicosHabilitados(nodoFechasHorarios* lista)
{
    printf("\n..Turnos disponibles..\n");

    nodoFechasHorarios* seg= lista;
    if(seg!=NULL)
    {
        while(seg!=NULL)
        {
            printf("\nFecha | %s hs", seg->fecha);
            printf("\nHorario | %i hs", seg->horario);
            printf("\n................................\n");
            seg=seg->siguiente;
        }

    }else
    {
        printf("\nNo hay turnos disponibles\n");
    }


}

void mostrarArregloTurnosDisponiblesMedicosHabilitados (celdaTurnos arregloT[], int validos)
{
    for (int i=0; i<validos; i++)
    {
        if(arregloT[i].dato.habilitado==0)
        {
            mostrarDatosUnMedico (arregloT[i].dato);
            printf("\nEspecialidad | %s", arregloT[i].especialidad);
            mostrarListaTurnosMedicosHabilitados(arregloT[i].turno);
        }
    }
}

void mostrarArregloTurnosMedicosHabilitadosPorMatricula (celdaTurnos arregloT[], int validos, int matricula)
{
    int i=0;
    int flag=0;

    while(i<validos && flag==0)
    {
        if(arregloT[i].dato.matricula== matricula)
        {
            if(arregloT[i].dato.habilitado==0 )
            {
                mostrarDatosUnMedico (arregloT[i].dato);
                printf("\nEspecialidad | %s", arregloT[i].especialidad);
                mostrarListaTurnosMedicosHabilitados(arregloT[i].turno);
                flag=1;
            }
        }
        i++;
    }
}


void cargarUnNuevoTurnoArchivoTurnos(char nombreArchivoTurnos[], char especialidad[], char fecha[], char nombreYapellido[], int matricula, int telefono, int consultorio,  int habilitado)
{
    FILE* archi= fopen(nombreArchivoTurnos, "ab");
    registroTurnos nuevoT;
    int horario=horarioInicialT;

    if(archi!=NULL)
    {
        for(int i=0; i<cantTurnos; i++)
        {
            strcpy( nuevoT.especialidad,especialidad);
            strcpy(nuevoT.nombreYapellido, nombreYapellido);
            nuevoT.matricula= matricula;
            nuevoT.telefono=telefono;
            nuevoT.consultorio=consultorio;
            strcpy(nuevoT.fecha, fecha);
            nuevoT.habilitado=habilitado;
            nuevoT.horario=horario;
            fwrite(&nuevoT, sizeof(registroTurnos),1, archi);
            horario++;
        }
        fclose(archi);
    }
}

int agregarDesdeRegistroTurnosAlArregloTurnosUnNuevoMedico (char nombreArchivoTurnos[], int matricula, celdaTurnos arregloT[], int validosTurnos)
{
    FILE* archi= fopen (nombreArchivoTurnos, "rb");
    registroTurnos datoT;

    if(archi!=NULL)
    {
        while(fread(&datoT, sizeof(registroTurnos),1,archi)>0)
        {
            if(datoT.matricula==matricula)
            {
                validosTurnos=altaTurnos(arregloT,datoT.nombreYapellido,matricula, datoT.telefono, datoT.consultorio, datoT.especialidad,fecha,datoT.horario, datoT.habilitado, validosTurnos);
            }
        }
        fclose(archi);
    }
    return validosTurnos;
}


registroTurnosPaciente cargarRegistroTurnoPaciente (celdaTurnos arregloT[], int pos, int dni, int horario, char fecha[], char especialidad[])
{
    registroTurnosPaciente datoP;

    datoP.datoT.consultorio= arregloT[pos].dato.consultorio;
    datoP.datoT.habilitado= 0;
    datoP.datoT.matricula= arregloT[pos].dato.matricula;
    strcpy(datoP.datoT.nombreYapellido, arregloT[pos].dato.nombreYapellido);
    datoP.datoT.telefono=arregloT[pos].dato.telefono;
    strcpy(datoP.fecha, fecha);
    datoP.horario=horario;
    strcpy(datoP.especialidad, especialidad);
    datoP.dni=dni;

    return datoP;
}


registroTurnosPaciente elegirTurno (celdaTurnos arregloT[], int validosT, int dniP, int matricula, char fecha[], int horario, char especialidad[])
{
    int pos= existeMatriculaTurno(arregloT, validosT, matricula);
    registroTurnosPaciente datoP;

    if(pos!=-1)
    {
        datoP= cargarRegistroTurnoPaciente(arregloT, pos, dniP, horario, fecha, especialidad);
    }

    return  datoP;
}


void pasarDeListaTurnosAarchivoTurnos (nodoFechasHorarios* lista, Medico dato,FILE* archi, char especialidad[])
{
    nodoFechasHorarios* seg=lista;
    registroTurnos datoT;

    if(seg!=NULL)
    {
        while(seg!=NULL)
        {
            strcpy(datoT.nombreYapellido, dato.nombreYapellido);
            strcpy(datoT.especialidad, especialidad);
            datoT.matricula= dato.matricula;
            datoT.telefono=dato.telefono;
            datoT.habilitado=dato.habilitado;

            strcpy(datoT.fecha,seg->fecha);
            datoT.horario=seg->horario;

            fwrite(&datoT, sizeof(registroTurnos),1,archi);
            seg=seg->siguiente;
        }
    }

}



nodoFechasHorarios* borrarHorarioListaTurnosDeMedico (nodoFechasHorarios* lista, int horario)
{
    nodoFechasHorarios* aBorrar;

    if(lista!=NULL)
    {
        if(lista->horario==horario)
        {
            aBorrar= lista;
            lista=lista->siguiente;
            free(aBorrar);
        }
        else
        {

            nodoFechasHorarios* ante=lista;
            nodoFechasHorarios* seg=lista->siguiente;

            while (seg!=NULL && (seg->horario!=horario))
            {
                ante=seg;
                seg=seg->siguiente;
            }
            if(seg!=NULL)
            {
                aBorrar=seg;
                ante->siguiente=seg->siguiente;
                free(aBorrar);
            }
        }
    }
    return lista;
}

void pasarDeArregloListasTurnosAarchivoTurnos (char nombreArchivo[], celdaTurnos arregloT[], int validos)
{
    FILE* archi=fopen(nombreArchivo, "wb");
    registroTurnos datoT;


    if(archi!=NULL)
    {
        for(int i=0; i<validos; i++)
        {
            pasarDeListaTurnosAarchivoTurnos (arregloT[i].turno, arregloT[i].dato,archi, arregloT[i].especialidad);
        }
        fclose(archi);
    }
    else
    {
        printf("\nError al abrir el archivo");
    }
}


int validarHorarioElegidoEnListaTurnosDisponiblesMedico (nodoFechasHorarios* lista, int horarioElegido)
{
    int flag=0;
    nodoFechasHorarios* seg=lista;

    if(seg!=NULL)
    {
        while(seg!=NULL)
        {
            if(seg->horario==horarioElegido)
            {
                flag=1;
            }
            seg=seg->siguiente;
        }
    }
    return flag;
}


int cantTurnosDisponiblesMedico (nodoFechasHorarios* listaTurnos)
{
    int i=0;

    if(listaTurnos!=NULL)
    {
        while(listaTurnos!=NULL)
        {
            i++;
            listaTurnos=listaTurnos->siguiente;
        }
    }
return i;
}

int verificarSiMedicoTieneTurnosTomados (nodoFechasHorarios* listaTurnos)
{
    int cantT= cantTurnosDisponiblesMedico(listaTurnos);
    int flag=0;

    if(cantT==cantTurnos) //si la cantidad de turnos disponibles es igual a la cantidad de turnos por medicos se retorna 1
    {
        flag=1;
    }

return flag;
}

