#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "medico-h.h"
#include "Usuario.h"
#include "turno.h"

nodoMedicos* inicListaMedicos() //se inicializa la lista de medicos en NULL
{
    return NULL;
}

nodoMatriculas* inicListaMatriculas() //se inicializa la lista de matriculas en NULL
{
    return NULL;
}

nodoMedicos* crearNodoMedicos (char nombreYapellido[],int matricula,int telefono, int consultorio, int habilitado)
{
    nodoMedicos* nuevoN= (nodoMedicos*) malloc (sizeof(nodoMedicos));

    strcpy(nuevoN->dato.nombreYapellido,nombreYapellido);
    nuevoN->dato.consultorio=consultorio;
    nuevoN->dato.matricula=matricula;
    nuevoN->dato.telefono=telefono;
    nuevoN->dato.habilitado=habilitado;
    nuevoN->siguiente=NULL;

    return nuevoN;
}

nodoMatriculas* crearNodoMatriculas(int matricula)
{
   nodoMatriculas* nuevoN= (nodoMatriculas*) malloc (sizeof(nodoMatriculas));


    nuevoN->matricula= matricula;
    nuevoN->siguiente=NULL;

    return nuevoN;
}

nodoMedicos* agregarAlPpioMedicos (nodoMedicos* lista, nodoMedicos* nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente=lista;
        lista=nuevoNodo;
    }
    return lista;
}

nodoMatriculas* agregarAlPpioListaMatriculas (nodoMatriculas* lista, nodoMatriculas* nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente=lista;
        lista=nuevoNodo;
    }
    return lista;
}

nodoMedicos* agregarEnOrdenMedicosPorMatricula (nodoMedicos* lista, nodoMedicos* nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        if(nuevoNodo->dato.matricula < lista->dato.matricula)
        {
            nuevoNodo->siguiente=lista;
            lista=nuevoNodo;
        }
        else
        {
            nodoMedicos* anterior=lista;
            nodoMedicos* seg= lista->siguiente;

            while((seg!=NULL) && (lista->dato.matricula < nuevoNodo->dato.matricula))
            {
                anterior=seg;
                seg=seg->siguiente;
            }
            nuevoNodo->siguiente=seg;
            anterior->siguiente=nuevoNodo;
        }
    }

    return lista;
}

nodoMatriculas* pasarDelArregloAlistaDeMatriculasMedicos (celda arregloM[], int validos, nodoMatriculas* listaMatriculas)
{
    nodoMedicos* seg;
    nodoMatriculas* aux;
    for (int i=0; i<validos; i++)
    {
       seg=arregloM[i].listaMedicos;

       while(seg!=NULL)
       {
           aux= crearNodoMatriculas(seg->dato.matricula);
           listaMatriculas= agregarAlPpioListaMatriculas(listaMatriculas, aux);
           seg=seg->siguiente;
       }
    }
return listaMatriculas;
}
///Esta funcion busca dentro del arreglo, si se encuentra la especialidad buscada retornando la posicion o -1 si no se encontro
int existeEspecialidadPosicion (celda arregMedicos[], char especialidad[], int validos)
{
    int rta=-1;
    int i=0;

    while(i<validos && (rta== -1))
    {
        if(strcmp(arregMedicos[i].especialidad,especialidad)==0)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}

int agregarEspecialidadAlArreglo(celda adl[],char especialidad[], int validos)
{
    strcpy(adl[validos].especialidad,especialidad);  //copia el nombre de la especialidad
    adl[validos].listaMedicos=inicListaMedicos(); //inicializa la lista asociada a la especialidad
    validos++; //incrementa la cantidad

    return validos;
}

/**Esta funcion evalua si la especialidad que queremos agregar se encuentra o no en el arreglo
si la especialidad se encuentra busca la posicion en el arreglo y por ultimo agrega al principio de la lista
los datos, si no se encuentra la especialidad , primero la agrega al arreglo y luego carga los datos del medico
**/

int altaMedicos(celda adl[],char nombreYapellido[], int matricula, int telefono, int consultorio, int validos, char especialidad[], int habilitado)
{

    nodoMedicos* aux=crearNodoMedicos(nombreYapellido, matricula, telefono, consultorio, habilitado);

    int pos=existeEspecialidadPosicion(adl, especialidad, validos); //devuelve la posicion de la especialidad si la encontro y si no devuelve -1


    if(pos==-1) //si la especialidad no existe, la agrega al arreglo y luego carga los datos del medico
    {
        validos=agregarEspecialidadAlArreglo(adl,especialidad, validos);
        pos=validos-1;
        //setea la posicion de la nueva materia
    }
    adl[pos].listaMedicos= agregarEnOrdenMedicosPorMatricula(adl[pos].listaMedicos,aux); //si la especialidad existe, agrega los datos a la lista correspondiente

    return validos;
}

int existeMatriculaListaMatriculas(int matricula, nodoMatriculas* listaMatriculas)
{
    nodoMatriculas* seg=listaMatriculas;
    int flag=0;


    while(seg!=NULL && flag==0)
    {
        if(seg->matricula==matricula)
        {
            flag=1;
        }
        seg=seg->siguiente;
    }

return flag;
}

registroArchivoMedicos cargaDatosUnMedico(nodoMatriculas* listaMatriculas)
{
    registroArchivoMedicos datoM;
    int flag;

    printf("\n...Carga datos medico...\n");
    printf("Ingrese la especialidad: ");
    fflush(stdin);
    scanf("%s",&datoM.especialidad);

    do
    {

    printf("Ingrese el numero de matricula: "); //verificar que no halla un medico cargado con la misma matricula
    scanf("%i",&datoM.matricula);
    flag=existeMatriculaListaMatriculas(datoM.matricula, listaMatriculas);

    }while(flag==1);

    printf("Ingrese el nombre y apellido: ");
    fflush(stdin);
    gets(datoM.nombreYapellido);
    printf("Ingrese el numero de telefono:");
    fflush(stdin);
    scanf("%i", &datoM.telefono);
    printf("Habilitado (0 habilitado | 1 no habilitado): ");
    scanf("%i",&datoM.habilitado);
    printf("Ingrese el consultorio ( 1- Belgrano 2478, 2- Mitre 1489): ");
    scanf("%i",&datoM.consultorio);
    printf("\n......................\n");

    return datoM;
}

void mostrarRegistroMedico(registroArchivoMedicos dato)
{
    printf("\n...Datos Medico...\n");
    printf("\nEspecialidad | %s",dato.especialidad);
    printf("\nMatricula | %i",dato.matricula);
    printf("\nNombre y apellido | %s",dato.nombreYapellido);

    if(dato.consultorio==1)
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
    printf("\n...........................\n");
}

void mostrarTodosRegistroMedicos (char nombreArchivo[20])
{
    registroArchivoMedicos datoM;
    FILE* archi= fopen(nombreArchivo, "rb");

    if(archi!=NULL)
    {
        while(fread(&datoM, sizeof(registroArchivoMedicos),1,archi)>0)
        {
            mostrarRegistroMedico(datoM);
        }
        fclose(archi);
    }
}

void mostrarRegistroMedicosHabilitados (char nombreArchivo[20])
{
    registroArchivoMedicos datoM;
    FILE* archi= fopen(nombreArchivo, "rb");

    if(archi!=NULL)
    {
        while(fread(&datoM, sizeof(registroArchivoMedicos),1,archi)>0)
        {
            if(datoM.habilitado==0)
            {
                mostrarRegistroMedico(datoM);
            }
        }
        fclose(archi);
    }
}

int pasarRegistroMedicosAarregloListasMedico (char nombreArchivo[], celda listaMedicos[], int dimension)
{
    registroArchivoMedicos datoM;
    FILE* archi= fopen(nombreArchivo, "rb");
    int i=0;

    if(archi!=NULL)
    {
        while( (fread(&datoM, sizeof(registroArchivoMedicos), 1, archi)>0) && i<dimension)
        {
            i= altaMedicos(listaMedicos, datoM.nombreYapellido,datoM.matricula, datoM.telefono, datoM.consultorio,i, datoM.especialidad, datoM.habilitado);

        }
        fclose(archi);
    }

    return i;
}


//Funcion que muestra el arreglo por especialidad de listas de medicos

void mostrarDatosUnMedico(Medico dato)
{
    printf("\nMatricula | %i",dato.matricula);
    printf("\nNombre y apellido | %s",dato.nombreYapellido);
    if(dato.consultorio==1)
    {
        printf("\nConsultorio| Belgrano 2478 ");
    }
    else
    {
        printf("\nConsultorio| Mitre 1489 ");
    }
    printf("\nTelefono | %i", dato.telefono);
    if(dato.habilitado == 0)
    {
       printf("\nHablitado\n");
    }
    else{
        printf("\nNo hablitado\n");
    }

    printf("\n........................\n");
}

void mostrarListaMedicos(nodoMedicos* lista)
{
    nodoMedicos* seg= lista;
    if(seg !=NULL)
    {
        while(seg!=NULL)
        {
            mostrarDatosUnMedico(seg->dato);
            seg=seg->siguiente;
        }
    }
}

void mostrarListaMedicosHabilitados(nodoMedicos* lista, char especialidad[])
{
    nodoMedicos* seg= lista;
    if(seg !=NULL)
    {
        while(seg!=NULL)
        {
            if(seg->dato.habilitado==0)
            {

                printf("\n ESPECIALIDAD | %s \n", especialidad);
                mostrarDatosUnMedico(seg->dato);
            }
            seg=seg->siguiente;
        }
    }
}

void mostrarArregloDeTodosLosMedicos (celda arregloMedicos[], int validos)
{
    for(int i=0; i<validos; i++)
    {
        printf("\n | DATOS MEDICO |\n");
        printf("\nEspecialidad | %s \n", arregloMedicos[i].especialidad);
        mostrarListaMedicos(arregloMedicos[i].listaMedicos);
    }
}

void mostrarArregloDeMedicosHabilitados (celda arregloMedicos[], int validos)
{
    for(int i=0; i<validos; i++)
    {
        mostrarListaMedicosHabilitados(arregloMedicos[i].listaMedicos, arregloMedicos[i].especialidad);
        printf("\n");
    }
}

void cargarUnNuevoMedicoArchivo (char nombreDelArchivo[], registroArchivoMedicos nuevoDatosMedico)
{

    FILE* archi= fopen(nombreDelArchivo, "ab");

    if(archi!=NULL)
    {
        fwrite(&nuevoDatosMedico, sizeof(registroArchivoMedicos),1,archi);
        fclose(archi);
    }
}

int ingresarNuevoMedicoAlArchivoYarregloMedicos(celda arregloMedicos[],char nombreArchivoMedicos[],int validosAregloMedicos, registroArchivoMedicos nuevoM)
{

    cargarUnNuevoMedicoArchivo (nombreArchivoMedicos, nuevoM);
    validosAregloMedicos= altaMedicos(arregloMedicos, nuevoM.nombreYapellido, nuevoM.matricula, nuevoM.telefono, nuevoM.consultorio, validosAregloMedicos, nuevoM.especialidad, nuevoM.habilitado);

    return validosAregloMedicos;
}

//funcion que me muestre los medicos de la especialidad establecida

void mostrarArregloListaMedicoPorEspecialidad(celda arregloM[], int validos, char especialidadP[])
{
    int i=0;

    while(i<validos)
    {
        if(strcmp(arregloM[i].especialidad,especialidadP)==0)
        {
            mostrarListaMedicosHabilitados(arregloM[i].listaMedicos, especialidadP);
        }

        i++;
    }
}

void mostrarDatosBasicosMedicosUnMedico(Medico dato)
{
    printf("\nMatricula | %i",dato.matricula);
    printf("\nNombre y apellido | %s",dato.nombreYapellido);
    printf("\n........................\n");
}

void mostrarListaDatosBasicosMedicosHabilitados(nodoMedicos* listaM)
{
nodoMedicos* seg= listaM;
    if(seg !=NULL)
    {
        while(seg!=NULL)
        {
            if(seg->dato.habilitado==0)
            {
               mostrarDatosBasicosMedicosUnMedico(seg->dato);
            }
            seg=seg->siguiente;
        }
    }
}

void mostrarDatosBasicosMedicos(celda arregloMedicos[], int validos)
{
        for(int i=0; i<validos; i++)
    {
        printf("\n ESPECIALIDAD | %s \n",arregloMedicos[i].especialidad);
        mostrarListaDatosBasicosMedicosHabilitados(arregloMedicos[i].listaMedicos);
        printf("\n");
    }
}

void mostrarEspecialidadesBaseDatos (celda arregloM[], int validos)
{
    printf("\nLista Especialidades\n");
    for (int i=0; i<validos; i++)
    {
        printf("\n- %s", arregloM[i].especialidad);
    }
}

nodoMedicos* buscarYdevolverUnNodoMedico(nodoMedicos* listaMedicos, int matricula)
{
    nodoMedicos* aux= NULL;

    if(listaMedicos!=NULL)
    {
        while(listaMedicos!=NULL)
        {
            if(listaMedicos->dato.matricula== matricula)
            {
                aux=listaMedicos;
            }
        listaMedicos=listaMedicos->siguiente;
        }
    }
return aux;
}
///Preguntar Especialiad
nodoMedicos* modificarDatosMedico(nodoMedicos* listaMedicos, int matricula)
{
   nodoMedicos* aux=  buscarYdevolverUnNodoMedico(listaMedicos, matricula);
   int consultorio, deshabilitar;
   int opc;

   if(aux!=NULL)
   {
            printf("\nElige las siguientes opciones:\n");
            printf("\nOpcion '1' si desea modificar el telefono\n");
            printf("\nOpcion '2' si desea modificar la direccion del consultorio \n");
            printf("\nOpcion '3' si deshabilitar el medico\n");
            scanf("%i",&opc);

            switch(opc)
            {
            case 1:
                printf("\nIngrese el nuevo numero de telefono\n");
                scanf("%i", &(aux->dato.telefono));

                break;
            case 2:
                do
                {
                printf("\nIngrese el numero que corresponde al consultorio deseado(1- Belgrano 2478, 2- Mitre 1489): ");
                scanf("\n %i", &consultorio);
                }while (consultorio!=1 && consultorio!=2);

                aux->dato.consultorio=consultorio;
                break;

            default:
                printf("\nERROR\n");
                break;
            }
    }


return aux;
}
void arreglodemedicosAarchivo(char nombreArchivo[],int validos,celda clM[])
{
    FILE* archi = fopen(nombreArchivo,"wb");
    if(archi!=NULL)
    {
        for(int i = 0 ; i<validos ; i++)
        {
            recorrerlistamedicosYguardararchivo(clM[i].listaMedicos,archi,clM[i].especialidad);
        }
        fclose(archi);
    }
}
void recorrerlistamedicosYguardararchivo(nodoMedicos* lista,FILE* archi,char especialidad[])
{
    registroArchivoMedicos rgM;
    while(lista != NULL)
    {
        strcpy((rgM).especialidad,especialidad);
        strcpy((rgM).nombreYapellido,lista->dato.nombreYapellido);
        (rgM).consultorio = lista->dato.consultorio;
        (rgM).habilitado = lista->dato.habilitado;
        (rgM).matricula = lista->dato.matricula;
        (rgM).telefono = lista->dato.telefono;

        fwrite(&rgM,sizeof(registroArchivoMedicos),1,archi);
        lista = lista->siguiente;
    }
}

int VerificarMedicoHabilitado(nodoMedicos* listaM,int matricula)
{
    nodoMedicos* seg= listaM;
    int flag = 0;
    while(seg!=NULL)
    {
        if(seg->dato.matricula == matricula && seg->dato.habilitado==0)
        {
            flag = 1;
        }
        seg=seg->siguiente;
    }
    return flag;
}
nodoMedicos* deshabilitarUnMedicoListaMedicos (nodoMedicos* listaMedicos, int matricula)
{
    int flag=0;
    nodoMedicos* seg=listaMedicos;
    while(seg!=NULL && flag==0)
    {

        if(seg->dato.matricula == matricula)
        {

            seg->dato.habilitado= 1;//se deshabilita el medico de la matricula indicada
            flag=1;
        }
    seg=seg->siguiente;
    }

return listaMedicos;
}
void arregloDeEspecialidadesAarchivo(char nombreArchivo[],int validos,celda clM[])// arreglo especialidad
{
    FILE* archi = fopen(nombreArchivo,"wb");
    if(archi!=NULL)
    {
        for(int i = 0 ; i<validos ; i++)
        {
            recorrerlistaDeMedicosYguardararchivo(clM[i].listaMedicos,archi,clM[i].especialidad);
        }
        fclose(archi);
    }
}

void recorrerlistaDeMedicosYguardararchivo(nodoMedicos* lista,FILE* archi,char especialidad[])
{
    registroArchivoMedicos rgM;
    while(lista != NULL)
    {
        strcpy((rgM).especialidad,especialidad);
        strcpy((rgM).nombreYapellido,lista->dato.nombreYapellido);
        (rgM).consultorio = lista->dato.consultorio;
        (rgM).habilitado = lista->dato.habilitado;
        (rgM).matricula = lista->dato.matricula;
        (rgM).telefono = lista->dato.telefono;

        fwrite(&rgM,sizeof(registroArchivoMedicos),1,archi);
        lista = lista->siguiente;
    }
}
