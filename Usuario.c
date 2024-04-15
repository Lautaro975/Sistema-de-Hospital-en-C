#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Usuario.h"
#include "turno.h"
#include "medico-h.h"
#include "Fila.h"
#include "ListasDobleFila.h"

void CargarRegistro(char nombre[],NodoVerificacion** lista)
{
    FILE* archi = fopen(nombre,"ab");
    RegistroUsuario rg;
    char cont[20];
    strcpy(cont,"si");
    printf("\n........................Bienvenido.......................\n");
    if(archi!=NULL)
    {
        while(strcmpi(cont,"si")==0)
        {
            UnRegistro(&rg,lista);

            fwrite(&rg,sizeof(RegistroUsuario),1,archi);

            printf("\n¿Quiere cargar otro registro?(si/no)\n");
            fflush(stdin);
            gets(cont);
        }
        fclose(archi);
    }
}

void UnRegistro(RegistroUsuario* rg,NodoVerificacion** lista)
{

    char nombre[MaxCaracteres],contrasena[MaxCaracteres];
    int DNI=0, flag=0;

    do
    {
        if(flag == 1)
        {
            printf("Ya esta en uso este ID");

        }
        printf("\nNombre de Usuario:\n");
        fflush(stdin);
        gets(nombre);
        flag = verificarNombre(*lista,nombre);
    }
    while(flag==1);
    strcpy((*rg).dato.ID,nombre);


    flag=0;
    do
    {
        if(flag == 1)
        {
            printf("Ya esta en uso la contraseña");
        }
        printf("\nIngrese una contraseña:\n");
        fflush(stdin);
        gets(contrasena);
        flag = verificarContra(*lista,contrasena);
    }
    while(flag==1);
    strcpy((*rg).dato.contrasena,contrasena);

    printf("\nMail:\n");
    fflush(stdin);
    gets((*rg).dato.mail);

    printf("\nNombre:\n");
    fflush(stdin);
    gets((*rg).dato.nombre);

    flag=0;
    do
    {
        if(flag == 1)
        {
            printf("\nYa esta en uso este DNI\n");
            printf("Ingrese de nuevo\n");
        }
        printf("DNI:\n");
        scanf("%i",&DNI);
        flag=verificarDNI(*lista,DNI);
    }
    while(flag==1);
    (*rg).dato.DNI = DNI;

    printf("\nTelefono:\n");
    fflush(stdin);
    gets((*rg).dato.telefono);

    NodoVerificacion* nuevo = crearNodoVerificacion(contrasena,nombre,DNI);
    AgregarAlprincipio(lista,nuevo);

}

void RgTOlista(char nombre[],NodoVerificacion** lista)
{
    FILE* archi = fopen(nombre,"rb");
    RegistroUsuario rg;
    if(archi!=NULL)
    {
        while(fread(&rg,sizeof(RegistroUsuario),1,archi)>0)
        {
            NodoVerificacion* nuevo = crearNodoVerificacion(rg.dato.contrasena,rg.dato.ID,rg.dato.DNI);
            AgregarAlprincipio(lista,nuevo);
        }
    }
    fclose(archi);
}

void AgregarAlprincipio(NodoVerificacion** lista, NodoVerificacion* nuevo)
{
    if(*lista == NULL)
    {
        *lista = nuevo;
    }
    else
    {
        nuevo->sig = *lista;
        *lista = nuevo;
    }
}

NodoVerificacion* inicListaVerificacion()
{
    return NULL;
}

NodoVerificacion* crearNodoVerificacion(char contrasena[],char ID[],int DNI)
{
    NodoVerificacion* nuevo = (NodoVerificacion*)malloc(sizeof(NodoVerificacion));
    strcpy(nuevo->contrasena,contrasena);
    strcpy(nuevo->ID,ID);
    nuevo->DNI = DNI;
    nuevo->sig = NULL;

    return nuevo;
}

int verificarDNI(NodoVerificacion* lista, int DNI)
{
    int veri = 0;
    if(lista != NULL)
    {
        if(lista->DNI == DNI)
        {
            veri = 1;
        }
        else
        {
            veri = veri +verificarDNI(lista->sig,DNI);
        }
    }
    return veri;
}

int verificarNombre(NodoVerificacion* lista, char nombre[])
{
    int veri = 0;
    if(lista != NULL)
    {
        if(strcmp(lista->ID,nombre)==0)
        {
            veri = 1;
        }
        else
        {
            veri = veri + verificarNombre(lista->sig,nombre);
        }
    }
    return veri;
}

int verificarContra(NodoVerificacion* lista, char contrasena[])
{
    int veri = 0;
    if(lista != NULL)
    {
        if(strcmp(lista->contrasena,contrasena)==0)
        {
            veri = 1;
        }
        else
        {
            veri = veri + verificarContra(lista->sig,contrasena);
        }
    }
    return veri;
}

void mostrarRegistro(char nombre[])
{
    FILE* archi = fopen(nombre,"rb");
    RegistroUsuario rg;
    if(archi!=NULL)
    {;
        while(fread(&rg,sizeof(RegistroUsuario),1,archi)>0)
        {
            printf("\n.................Paciente.................\n");

            printf("\nID: %s\n",rg.dato.ID);

            printf("\nContrasena: %s\n",rg.dato.contrasena);

            printf("\nNombre:%s\n",rg.dato.nombre);

            printf("\nDNI:%i\n",rg.dato.DNI);

            printf("\nMail:%s\n",rg.dato.mail);

            printf("\nTelefono:%s\n",rg.dato.telefono);

        }
        fclose(archi);
    }
}

void registroAarbol(char nombre[],NodoUsuario** arbolUsuario)
{
    FILE* archi = fopen(nombre,"rb");
    RegistroUsuario rg;
    if(archi!=NULL)
    {
        while(fread(&rg,sizeof(RegistroUsuario),1,archi)>0)
        {
            cargarArbol(rg,arbolUsuario);
        }
        fclose(archi);
    }
}

void registroTurnosAarbol(char nombre[],NodoUsuario** arbolUsuario)
{
    FILE* archi = fopen(nombre,"rb");
    RegistroTurnos rg;
    if(archi!=NULL)
    {
        while(fread(&rg,sizeof(RegistroTurnos),1,archi)>0)
        {
            NodoUsuario* aux = BuscarXdni(*arbolUsuario,rg.dni);
            cargarListadeTurnos(&(aux->listaTurnos),rg.dato);
        }
        fclose(archi);
    }
}

void cargarListadeTurnos(nodoTurnosPaciente** lista,turnos dato)
{
    nodoTurnosPaciente* nuevo = CrearNodoTurno(dato.horario,dato.fecha,dato.doctor,dato.especialidad);
    AgregarAlFinalUsuario(lista,nuevo);
}

void cargarArbol(RegistroUsuario rg,NodoUsuario** arbolUsuario)
{
    if(*arbolUsuario == NULL)
    {
        *arbolUsuario = CrearArbolUsuario(rg);
    }
    else
    {
        if(rg.dato.DNI<(*arbolUsuario)->dato.DNI)
        {
            cargarArbol(rg,&((*arbolUsuario)->der));
        }
        else
        {
            cargarArbol(rg,&((*arbolUsuario)->izq));
        }
    }
}

NodoUsuario* CrearArbolUsuario(RegistroUsuario rg)
{
    NodoUsuario* nuevo = (NodoUsuario*)malloc(sizeof(NodoUsuario));
    nuevo->dato = rg.dato;
    nuevo->der = NULL;
    nuevo->izq = NULL;
    nuevo->listaTurnos = NULL;

    return nuevo;
}

NodoUsuario* inicArbolUsuario()
{
    return NULL;
}

void mostrarArbol(NodoUsuario* arbol)
{
    if(arbol!=NULL)
    {
        mostrarArbol(arbol->izq);
        printf("\n........................Usuario........................\n");
        printf("\nID: %s\n",arbol->dato.ID);

        printf("\nContrasena: %s\n",arbol->dato.contrasena);

        printf("\nNombre:%s\n",arbol->dato.nombre);

        printf("\nDNI:%i\n",arbol->dato.DNI);

        printf("\nMail:%s\n",arbol->dato.mail);

        printf("\nTelefono:%s\n",arbol->dato.telefono);

        mostrarArbol(arbol->der);
    }
}

void mostrarUnArbol(NodoUsuario* arbol)
{
    printf("\nID: %s\n",arbol->dato.ID);

    printf("\nContrasena: %s\n",arbol->dato.contrasena);

    printf("\nNombre:%s\n",arbol->dato.nombre);

    printf("\nDNI:%i\n",arbol->dato.DNI);

    printf("\nMail:%s\n",arbol->dato.mail);

    printf("\nTelefono:%s\n",arbol->dato.telefono);

}

void mostrarListaVerificacion(NodoVerificacion* lista)
{
    if(lista!=NULL)
    {
        printf("\nNombre:%s\n",lista->ID);
        printf("DNI: %i\n",lista->DNI);
        printf("\nContrasena:%s\n",lista->contrasena);

        mostrarListaVerificacion(lista->sig);

    }
}

NodoUsuario* BuscarXdni(NodoUsuario* arbol, int DNI)
{
    NodoUsuario* aux = NULL;
    if(arbol!=NULL)
    {
        if(arbol->dato.DNI==DNI)
        {
            aux = arbol;
        }
        else if(arbol->dato.DNI < DNI)
        {
            aux = BuscarXdni(arbol->izq,DNI);
        }
        else
        {
            aux = BuscarXdni(arbol->der,DNI);
        }
    }
    return aux;
}

void agregarAlistaTurnos(nodoTurnosPaciente** listas,registroTurnosPaciente datoTurno)
{

        nodoTurnosPaciente* nuevo = CrearNodoTurno(datoTurno.horario, datoTurno.fecha, datoTurno.datoT, datoTurno.especialidad);
        AgregarAlFinalUsuario(listas,nuevo);
}

nodoTurnosPaciente* inicTurnosPaciente()
{
    return NULL;
}

nodoTurnosPaciente* CrearNodoTurno(int horario,char fecha[],Medico datoDoctor, char especialidad[])
{
    nodoTurnosPaciente* nuevo = (nodoTurnosPaciente*)malloc(sizeof(nodoTurnosPaciente));
    strcpy(nuevo->dato.fecha,fecha);
    nuevo->dato.horario = horario;
    nuevo->dato.doctor= datoDoctor;
    strcpy(nuevo->dato.especialidad, especialidad);
    nuevo->sig = NULL;

    return nuevo;
}

void AgregarAlFinalUsuario(nodoTurnosPaciente** lista,nodoTurnosPaciente* nuevo)
{
    if(*lista == NULL)
    {
        *lista = nuevo;
    }
    else
    {
        nodoTurnosPaciente* seg = *lista;
        while(seg->sig != NULL)
        {
            seg = seg->sig;
        }
        if(seg!=NULL)
        {
            seg->sig = nuevo;
        }
    }
}
void mostrarUnPaciente(usuario dato)
{
    printf("\nID: %s\n",dato.ID);

    printf("\nContrasena: %s\n",dato.contrasena);

    printf("\nNombre:%s\n",dato.nombre);

    printf("\nDNI:%i\n",dato.DNI);

    printf("\nMail:%s\n",dato.mail);

    printf("\nTelefono:%s\n",dato.telefono);
}

NodoUsuario* modificarDatosUsuario(NodoUsuario** arbol, int DNI, NodoVerificacion* lista)
{
    NodoUsuario* aux = BuscarXdni(*arbol,DNI);
    if(aux!=NULL)
    {

        int opc, flag=0;
        char nombre[30];
        while(opc!=5)
        {
            printf("\nElige las siguientes opciones:\n");
            printf("\nOpcion '1' si desea modificar el ID.\n");
            printf("\nOpcion '2' si desea modificar el mail.\n");
            printf("\nOpcion '3' si desea modificar el telefono.\n");
            printf("\nOpcion '4' si desea modificar todas las opciones anteriores.\n");
            printf("\nOpcion '5' si desea salir.\n");
            scanf("%i",&opc);

            switch(opc)
            {
            case 1:
                do
                {
                    if(flag == 1)
                    {
                        printf("Ya esta en uso este ID");

                    }
                    printf("\nNombre de Usuario:\n");
                    fflush(stdin);
                    gets(nombre);
                    flag = verificarNombre(lista,nombre);
                }
                while(flag==1);
                strcpy(aux->dato.ID,nombre);
                break;
            case 2:
                printf("\nMail:\n");
                fflush(stdin);
                gets(aux->dato.mail);
                break;
            case 3:
                printf("\nTelefono:\n");
                fflush(stdin);
                gets(aux->dato.telefono);
                break;
            case 4:
                do
                {
                    if(flag == 1)
                    {
                        printf("Ya esta en uso este ID");

                    }
                    printf("\nNombre de Usuario:\n");
                    fflush(stdin);
                    gets(nombre);
                    flag = verificarNombre(lista,nombre);
                }
                while(flag==1);
                strcpy(aux->dato.nombre,nombre);

                printf("\nMail:\n");
                fflush(stdin);
                gets(aux->dato.mail);

                printf("\nTelefono:\n");
                fflush(stdin);
                gets(aux->dato.telefono);
                break;

            case 5:
                break;

            default:
                printf("\nERROR\n");
                break;
            }
            printf("\n¿Quiere salir?(Ingrese 5)\n");
            scanf("%i",&opc);
        }
    }
    else
    {
        printf("\nNo se encontro ninguna persona con el DNI ingresado\n");
    }
    return aux;
}

void arbolAregistro(NodoUsuario* arbol,FILE* archi,FILE* archi2)
{
    RegistroUsuario rg;
    if(arbol!=NULL)
    {
        rg.dato = arbol->dato;
        RecorrerYguardarLaLista(arbol->listaTurnos,archi2,arbol->dato.DNI);
        fwrite(&rg,sizeof(RegistroUsuario),1,archi);
        arbolAregistro(arbol->der,archi,archi2);
        arbolAregistro(arbol->izq,archi,archi2);
    }
}

void RecorrerYguardarLaLista(nodoTurnosPaciente* lista,FILE* archiTurn, int dni)
{
    RegistroTurnos rgTurn;
    while(lista!=NULL)
    {
        rgTurn.dni = dni;
        rgTurn.dato = lista->dato;
        fwrite(&rgTurn,sizeof(RegistroTurnos),1,archiTurn);
        lista = lista->sig;
    }

}

void mostrarTodoArbol(NodoUsuario* arbol)
{
    if(arbol!=NULL)
    {
        printf("\n.................Paciente.................\n");
        mostrarUnArbol(arbol);
        printf("\n.................Turnos.................\n");
        mostrarUnaLista(arbol->listaTurnos);
        mostrarTodoArbol(arbol->izq);
        mostrarTodoArbol(arbol->der);
    }
}

void mostrarUnaLista(nodoTurnosPaciente* lista)
{
    if(lista!=NULL)
    {
        printf("\n");
        printf("\nEspecialidad: %s", lista->dato.especialidad);
        printf("\nDoctor:%s",lista->dato.doctor.nombreYapellido);
        printf("\nMatricula: %i", lista->dato.doctor.matricula);
        printf("\nTelefono: %i", lista->dato.doctor.telefono);
        if(lista->dato.doctor.consultorio==1)
        {
            printf("\nConsultorio | Belgrano 2478 ");
        }
        else
        {
            printf("\nConsultorio | Mitre 1489 ");
        }
        printf("\nFecha: %s", lista->dato.fecha);
        printf("\nHorario: %i", lista->dato.horario);
        printf("\n");
        mostrarUnaLista(lista->sig);
    }

}

void mostrarRegistroTurno(char nombre[])
{
    FILE* archi = fopen(nombre,"rb");
    RegistroTurnos rgT;
    if(archi!=NULL)
    {
        while(fread(&rgT,sizeof(RegistroTurnos),1,archi)>0)
        {
            printf("\n.................TURNOS.................\n");
            printf("\nDNI:%i\n",rgT.dni);
            printf("\nDoctor:%s\n",rgT.dato.doctor);
        }
    }
}

int validarHorarioEnListaDeTurnosPaciente (nodoTurnosPaciente* lista, int horario)
{
    int flag=0;

    nodoTurnosPaciente* seg=lista;

    if(seg!=NULL)
    {
        while(seg!=NULL)
        {
            if (seg->dato.horario==horario)
            {
                flag=1;
            }
            seg=seg->sig;
        }
    }
return flag;
}

int validarMatriculaMedicoEnListaDeTurnosPaciente (nodoTurnosPaciente* lista, int matricula)
{
    int flag=0;

    nodoTurnosPaciente* seg=lista;

    if(seg!=NULL)
    {
        while(seg!=NULL)
        {
            if (seg->dato.doctor.matricula == matricula)
            {
                flag=1;
            }
            seg=seg->sig;
        }
    }
return flag;
}

//Esta funcion devuelve el primero de la lista
nodoTurnosPaciente* devolverNodoTurnoPacienteDeMedicoYHorarioBuscado (nodoTurnosPaciente* lista, int matricula, int horario)
{
    nodoTurnosPaciente* nodoBuscado=NULL;

    if(lista!=NULL)
    {
        if((lista->dato.doctor.matricula==matricula) && (lista->dato.horario==horario))
        {
            nodoBuscado=lista;
            nodoBuscado->sig=NULL;
        }else
        {
            nodoTurnosPaciente* ante=lista;
            nodoTurnosPaciente* seg=lista->sig;

            while(seg!=NULL && (seg->dato.horario!=horario) && (seg->dato.doctor.matricula!=matricula))
            {
                ante=seg;
                seg=seg->sig;
            }

            if(seg!=NULL)
            {
                nodoBuscado=seg;
                nodoBuscado->sig=NULL;
            }
        }
    }

return nodoBuscado;
}

nodoTurnosPaciente* borrarTurnoDeListaTurnosPaciente (nodoTurnosPaciente* lista, int matricula, int horario) //borra de la lista de turnos del paciente el nodo del turno correspondiente
{
    nodoTurnosPaciente* nodoAborrar;

    if(lista!=NULL)
    {
        if((lista->dato.doctor.matricula==matricula) && (lista->dato.horario==horario))
        {
            nodoAborrar= lista;
            lista=lista->sig;
            free(nodoAborrar);
        }
        else
        {

            nodoTurnosPaciente* ante=lista;
            nodoTurnosPaciente* seg=lista->sig;

            while (seg!=NULL && (seg->dato.doctor.matricula!=matricula) && (seg->dato.horario!=horario))
            {
                ante=seg;
                seg=seg->sig;
            }
            if(seg!=NULL)
            {
                nodoAborrar=seg;
                ante->sig=seg->sig;
                free(nodoAborrar);
            }
        }
    }

    return lista;
}
int existeIdYclave (NodoUsuario* arbol, char iD[], char clave[])
{
   int flag=0;

   if(arbol!=NULL)
   {
       if((strcmp(arbol->dato.ID, iD)==0) && (strcmp(arbol->dato.contrasena, clave)==0))
       {
           flag=1;
       }else
       {
           flag= flag + existeIdYclave(arbol->izq, iD,clave);
           flag= flag + existeIdYclave (arbol->der, iD, clave);
       }
   }
return flag;
}








