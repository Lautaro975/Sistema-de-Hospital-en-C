#include "programaEjecutar.h"

#define dim 30
void menuSistema()
{
    system("cls");
    printf("\n| SISTEMA |\n");
    printf("\n");
    printf("MENU DE OPCIONES:\n");
    printf("1. Opcion 1: Mostrar todos los datos de medicos\n");
    printf("2. Opcion 2: Mostrar todos los datos de medicos habilitados\n");
    printf("3. Opcion 3: Mostrar medicos por especialidad\n");
    printf("4. Opcion 4: Ingresar un nuevo medico al sistema\n");
    printf("5. Opcion 5: Mostrar todos los medicos y sus turnos\n");
    printf("6. Opcion 6: Mostrar turnos disponibles por medico\n");
    printf("7. Opcion 7: Registrar paciente con turno\n");
    printf("8. Opcion 8: Mostrar todos los medicos y la fila de pacientes por atender\n");
    printf("9. Opcion 9: Atender a un paciente\n");
    printf("10. Opcion 10: Ver todos los pacientes atendidos\n");
    printf("11. Opcion 11: Ver cantidad de pacientes atendidos por medico\n");
    printf("12. Opcion 12: Modificar un medico habilitado\n");
    printf("13. Opcion 13: Deshabilitar un medico\n");
    printf("14. Opcion 14: si desea mostrar todo los pacientes y turnos\n");
    printf("\nSelecciona una opcion: \n");
}

void MostrarMedicosPorEspecialidad(celda arregloMedicos[], int validosArregloMedicos)
{
    int flagEspecialidad;
    char especialidadAbuscar[20];

    mostrarEspecialidadesBaseDatos (arregloMedicos, validosArregloMedicos);
    do
    {
        printf("\n Ingrese una especialidad: ");
        fflush(stdin);
        scanf("%s", &especialidadAbuscar);
        flagEspecialidad=  existeEspecialidadPosicion(arregloMedicos, especialidadAbuscar, validosArregloMedicos);
    }
    while(flagEspecialidad==-1);

    mostrarArregloListaMedicoPorEspecialidad (arregloMedicos, validosArregloMedicos, especialidadAbuscar);
}

void MostrarTurnosDisponiblesPorMedico(celda arregloMedicos[], int validosArregloMedicos, celdaTurnos arregloTurnos[], int validosArregloTurnos)
{
    int matriculaIngresada;

    mostrarDatosBasicosMedicos(arregloMedicos, validosArregloMedicos);
    printf("\nIngrese un numero de matricula: ");
    scanf("%i",&matriculaIngresada);
    system("cls");
    mostrarArregloTurnosMedicosHabilitadosPorMatricula (arregloTurnos, validosArregloTurnos, matriculaIngresada);
}


void mostrarArregloDePilaDePaciente(celdaMedicosPila clM[],int  validosArregloPilas)
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

void verCantidadDePacientesAtendidosPorMedico (celdaMedicosPila arregloPilas[], int validosArregloPila)
{
    int cantPacientesAtendido, matriculaIngresada;
    do
    {
        printf("\nIngrese la matricula del medico: ");
        scanf("%i",&matriculaIngresada);
        matriculaIngresada= BuscarPosMedicosPila(arregloPilas, validosArregloPila, matriculaIngresada);
    }
    while (matriculaIngresada==-1);

    cantPacientesAtendido= cuantosPacientesAtendioUnMedico (arregloPilas, validosArregloPila, matriculaIngresada);

    if(cantPacientesAtendido==0)
    {
        printf("\nNo se ha atendido ningun paciente con el medico indicado");
    }
    else
    {
        printf("\nCantidad de pacientes atendidos por el medico %s , matricula: %i | %i", arregloPilas[matriculaIngresada].dato.nombreYapellido, arregloPilas[matriculaIngresada].dato.matricula, cantPacientesAtendido);
    }
}


void mostrarPacientePorDni(NodoUsuario* arbolUsuario)
{
    int dni;
    printf("Ingrese el DNI del paciente: ");
    scanf("%i",&dni);

    NodoUsuario* aux = BuscarXdni(arbolUsuario,dni); ///Busca un dni y retorna NULL si no lo encontro y el nodo si es asi
    if(aux == NULL)
    {
        printf("\n No hay ningun paciente con este DNI \n");
    }
    else
    {
        mostrarUnArbol(aux);
    }
}

registroTurnosPaciente elegirUnTurnoPaciente (NodoUsuario* arbolUsuario, celdaTurnos arregloTurnos[], int validosArregloTurnos, celda arregloMedicos[], int validosArregloMedicos)
{
    int dni, posEspecialidadArreglo, horarioElegirTurnos, posMatriculaArreglo, matriculaElegirTurno, flagHorarios;
    char especialidadElegirTurno[20];
    registroTurnosPaciente nuevoTurnoPaciente;
    NodoUsuario* aux;

    printf("Ingrese el DNI\n");
    scanf("%i",&dni);

    aux = BuscarXdni(arbolUsuario,dni); ///Busca un dni y retorna NULL si no lo encontro y el nodo si es asi

    if(aux == NULL)
    {
        printf("\n No hay ningun paciente con este DNI \n");
    }
    else
    {

        system("cls");
        mostrarEspecialidadesBaseDatos(arregloMedicos, validosArregloMedicos);

        do
        {
            printf("\n Ingrese la especialidad deseada: ");
            fflush(stdin);
            scanf("%s", &especialidadElegirTurno);
            posEspecialidadArreglo=existeEspecialidadPosicion(arregloMedicos,especialidadElegirTurno,validosArregloMedicos);
        }
        while(posEspecialidadArreglo==-1);


        system("cls");
        mostrarArregloListaMedicoPorEspecialidad(arregloMedicos, validosArregloMedicos, especialidadElegirTurno);


        do
        {
            printf("\n Ingrese la matricula del medico que desee: ");
            scanf("%i", &matriculaElegirTurno);
            posMatriculaArreglo= existeMatriculaTurno(arregloTurnos, validosArregloTurnos, matriculaElegirTurno);
        }
        while(posMatriculaArreglo==-1);

        printf("\nPos matricula %i", posMatriculaArreglo);

        system("cls");
        mostrarArregloTurnosMedicosHabilitadosPorMatricula(arregloTurnos, validosArregloTurnos,matriculaElegirTurno);


        do
        {
            printf("\nIngrese el horario elegido: ");
            scanf("%i", &horarioElegirTurnos);
            flagHorarios=validarHorarioElegidoEnListaTurnosDisponiblesMedico (arregloTurnos[posMatriculaArreglo].turno, horarioElegirTurnos);
        }
        while(flagHorarios==0);

        nuevoTurnoPaciente=elegirTurno(arregloTurnos, validosArregloTurnos,dni,matriculaElegirTurno, "27/11/23", horarioElegirTurnos,especialidadElegirTurno);

        arregloTurnos[posMatriculaArreglo].turno= borrarHorarioListaTurnosDeMedico (arregloTurnos[posMatriculaArreglo].turno,horarioElegirTurnos);
        agregarAlistaTurnos(&(aux->listaTurnos),nuevoTurnoPaciente);
        mostrarUnaLista(aux->listaTurnos);
    }
    return nuevoTurnoPaciente;
}

void mostrarTodosLosDatosPacienteYTurnosPorDni (NodoUsuario* arbolUsuario)
{
    int dni;
    printf("Ingrese el DNI\n");
    scanf("%i",&dni);

    NodoUsuario* aux = BuscarXdni(arbolUsuario,dni); ///Busca un dni y retorna NULL si no lo encontro y el nodo si es asi

    if(aux == NULL)
    {
        printf("\n No hay ningun paciente con este DNI \n");
    }
    else
    {
        mostrarTodoArbol(aux);
    }
}
void opcionesMenu()  /// FUNCION PARA MOSTRAR POR PANTALLA LAS OPCIONES, ESTA RETORNA UN VALOR QUE ES ALMACENADO EN EL MENU PARA CONTINUAR CON EL FUNCIONAMIENTO DEL PROGRAMA.
{

    gotoxy(40,8);
    printf("1.Modo Sistema \n");
    gotoxy(40,9);
    printf("2.Modo Usuario\n");

    gotoxy(40,14);
    printf("Seleccione una opcion: ");

}
void gotoxy(int x, int y) /// FUNCION UTILIZADA PARA UBICAR EL CURSOR (NOSOTROS LA UTILIZAMOS PARA CENTRAR EL TEXTO).
{

    HANDLE manipulador;
    COORD coordenadas;
    manipulador = GetStdHandle(STD_OUTPUT_HANDLE);
    coordenadas.X = x;
    coordenadas.Y = y;

    SetConsoleCursorPosition(manipulador, coordenadas);
}

void menuPrincipio()
{
    int anchoPantalla = 110;
    int longitudMensaje = 40;

    int x = (anchoPantalla - longitudMensaje) / 2;
    int y = 8;

    gotoxy(x, y);
    printf("*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    gotoxy(x, y + 1);
    printf("*                                            *");
    gotoxy(x, y + 2);
    printf("*         Bienvenido al Hospital ANLA        *");
    gotoxy(x, y + 3);
    printf("*                                            *");
    gotoxy(x, y + 4);
    printf("*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *\n\n");

    gotoxy(x+7, y+7);
    printf("Presione cualquier tecla\n");
    getch();

    system("cls");
}

void menuEjecutar()
{
    celda arregloMedicos[numMaxEspecialidades];
    celdaTurnos arregloTurnos[numMaxMedicos];
    char registoDeMedicos[20];
    strcpy(registoDeMedicos, "archivoMedicos");
    int validosArregloMedicos;
    int validosArregloTurnos;
    char registroDeTurnosMedico[20];
    strcpy(registroDeTurnosMedico, "archivoTurnosDisponiblesMedicos");
    nodoMatriculas* listaMatriculas= inicListaMatriculas();
    int matriculaIngresada;
    char especialidadAbuscar[20];
    char especialidadElegirTurno[20];
    int horarioElegirTurnos;
    int matriculaElegirTurno;
    int opcion;
    char verMenu='s';
    char verMenuPaciente='s';
    int dniPaciente;
    int matriculaPaciente;
    int horarioPaciente;
    int posMedicos;
    int posTurnos;
    char contraseniaIngresada[30];
    char contraseniaSistema[30];
    strcpy(contraseniaSistema,"programacion");

    celdaMedicosFila arregloDeMedicosFilaPacientes[50];
    int validosArregloFilas;
    char archivoMedicosYpacientesPorAtenderFila [20];
    strcpy(archivoMedicosYpacientesPorAtenderFila, "archivoMedicosyPacientesPorAtenderFila");

    celdaMedicosPila arregloPilas[30];
    int validosArregloPila;
    char archivoArregloPilasP [20];
    strcpy(archivoArregloPilasP, "archivoArregloPilas");

    int opc,flag=0, dni;
    turnos tr;
    NodoVerificacion* listaVerificacion = inicListaVerificacion();///Inicializa la lista de verificacion
    NodoUsuario* aux;
    NodoUsuario* arbolUsuario = inicArbolUsuario();///Inicializa un arbol
    FILE* archi; ///Archivo de usuario
    FILE* archiTurnos; ///Archivo de turnos
    char cont[5];
    int verMenuSistemOpaciente;
    strcpy(cont,"si");
    char id[MaxCaracteres], clave[MaxCaracteres];
    int opcUsuario, flagUsuario;

    validosArregloMedicos= pasarRegistroMedicosAarregloListasMedico(registoDeMedicos, arregloMedicos, numMaxEspecialidades);

    listaMatriculas= pasarDelArregloAlistaDeMatriculasMedicos (arregloMedicos, validosArregloMedicos, listaMatriculas);
    validosArregloTurnos= pasarRegistroTurnosArregloMedico(registroDeTurnosMedico,arregloTurnos,numMaxMedicos);

    registroAarbol("Registro de paciente",&arbolUsuario);///Pasa de un registro a un arbol
    registroTurnosAarbol("Registro de Turnos",&arbolUsuario);
    validosArregloFilas= pasarRegistroAarregloFilasPacientesPorAtender(archivoMedicosYpacientesPorAtenderFila, arregloDeMedicosFilaPacientes, 30);
    validosArregloPila= pasarRegistroAarregloPilasPacientesAtendendidos(archivoArregloPilasP, arregloPilas, 30);


    menuPrincipio();

    opcionesMenu();

    do
    {
        system("cls");
        opcionesMenu();
        scanf("%i", &verMenuSistemOpaciente);
        if(verMenuSistemOpaciente!=1 && verMenuSistemOpaciente!=2)
        {
            system("cls");
            while (getchar() != '\n');
        }
    }while(verMenuSistemOpaciente!=1 && verMenuSistemOpaciente!=2);


    if(verMenuSistemOpaciente==1)
    {
        system("cls");
        printf("\nIngrese la clave: ");
        fflush(stdin);
        gets(contraseniaIngresada);
     if(strcmp(contraseniaIngresada, contraseniaSistema)==0)
     {
        while(verMenu =='s')
        {
            menuSistema();
            scanf(" %i", &opcion);

            switch (opcion)
            {
            case 1:
                system("cls");
                mostrarArregloDeTodosLosMedicos(arregloMedicos, validosArregloMedicos);
                break;

            case 2:
                system("cls");
                mostrarArregloDeMedicosHabilitados(arregloMedicos, validosArregloMedicos);
                break;

            case 3:
                system("cls");
                MostrarMedicosPorEspecialidad(arregloMedicos, validosArregloMedicos);

                break;

            case 4:
                system("cls");
                registroArchivoMedicos nuevoMedico= cargaDatosUnMedico(listaMatriculas);
                validosArregloMedicos= ingresarNuevoMedicoAlArchivoYarregloMedicos(arregloMedicos,registoDeMedicos, validosArregloMedicos, nuevoMedico);
                cargarUnNuevoTurnoArchivoTurnos(registroDeTurnosMedico, nuevoMedico.especialidad, "27/11/23", nuevoMedico.nombreYapellido, nuevoMedico.matricula, nuevoMedico.telefono, nuevoMedico.consultorio, nuevoMedico.habilitado);
                validosArregloTurnos= agregarDesdeRegistroTurnosAlArregloTurnosUnNuevoMedico(registroDeTurnosMedico,nuevoMedico.matricula,arregloTurnos,validosArregloTurnos);
                break;

            case 5:
                system("cls");
                mostrarArregloTurnosDisponiblesMedicosHabilitados(arregloTurnos,validosArregloTurnos);
                break;

            case 6:
                system("cls");

                MostrarTurnosDisponiblesPorMedico(arregloMedicos, validosArregloMedicos, arregloTurnos, validosArregloTurnos);

                break;

            case 7:

                printf("\nIngrese el dni del paciente: ");
                scanf("%i",&dniPaciente);
                int flagMatricula, flagHorario;
                NodoUsuario*  nodoUsuarioAux= BuscarXdni(arbolUsuario, dniPaciente);

                int validarTurno;

                if(nodoUsuarioAux==NULL)
                {
                    printf("\nEl dni ingresado no pertenece a un paciente registrado");
                }
                else
                {
                    mostrarUnaLista(nodoUsuarioAux->listaTurnos);

                    do
                    {
                        printf("\nIngrese la matricula del medico: ");
                        scanf("%i", &matriculaPaciente);
                        flagMatricula=validarMatriculaMedicoEnListaDeTurnosPaciente(nodoUsuarioAux->listaTurnos,matriculaPaciente);
                    }
                    while (flagMatricula==0);

                    do
                    {
                        printf("\nIngrese el horario del turno: ");
                        scanf("%i", &horarioPaciente);
                        flagHorario=validarHorarioEnListaDeTurnosPaciente(nodoUsuarioAux->listaTurnos,horarioPaciente);
                    }
                    while (flagHorario==0);


                    nodoTurnosPaciente* nodoTurnoDelPaciente= devolverNodoTurnoPacienteDeMedicoYHorarioBuscado(nodoUsuarioAux->listaTurnos, matriculaPaciente,horarioPaciente); ///CONTIENE LOS DATOS DEL TURNO MEDICO PARA AGREGAR AL ARREGLO (MEDICOS) FILAS (TURNOS)
                    Medico datoMedico = nodoTurnoDelPaciente->dato.doctor;

                    nodoUsuarioAux->listaTurnos= borrarTurnoDeListaTurnosPaciente(nodoUsuarioAux->listaTurnos, matriculaPaciente,horarioPaciente);

                    ///  Guardar los cambios
                    archi = fopen("Registro de paciente","wb");
                    archiTurnos = fopen("Registro de Turnos","wb");
                    arbolAregistro(arbolUsuario,archi,archiTurnos);
                    fclose(archi);
                    fclose(archiTurnos);

                    validosArregloFilas=  ingresarDatosTurnoAlArchivoYarregloDeFilasPacientes(arregloDeMedicosFilaPacientes,archivoMedicosYpacientesPorAtenderFila,validosArregloFilas, datoMedico, nodoUsuarioAux->dato);
                }
                break;

            case 8:
                printf("\nArreglo de medicos y fila de pacientes a atender\n");
                mostrarArregloDeFilaDePacientes(arregloDeMedicosFilaPacientes, validosArregloFilas);

                break;

            case 9:
                mostrarArregloDeFilaDePacientes(arregloDeMedicosFilaPacientes, validosArregloFilas);
                do
                {
                    printf("\nIngrese la matricula del medico: ");
                    scanf("%i",&matriculaIngresada);
                    matriculaIngresada= BuscarPosMedicosFila(arregloDeMedicosFilaPacientes, validosArregloFilas, matriculaIngresada);
                }
                while (matriculaIngresada==-1);


                usuario datoP = extraerFila(&(arregloDeMedicosFilaPacientes[matriculaIngresada].FilaDePacientes));

                cargarUnNuevoMedicoArchivoArregloPilas(archivoArregloPilasP, arregloDeMedicosFilaPacientes[matriculaIngresada].dato, datoP);

                validosArregloPila= pasarRegistroAarregloPilasPacientesAtendendidos(archivoArregloPilasP, arregloPilas, 30);

                break;

            case 10:
                mostrarArregloDePilaDePaciente(arregloPilas, validosArregloPila);
                break;

            case 11:
                system("cls");
                verCantidadDePacientesAtendidosPorMedico (arregloPilas,validosArregloPila);
                break;

            case 12:
                mostrarEspecialidadesBaseDatos (arregloMedicos, validosArregloMedicos);
                do
                {
                    printf("\nIngrese la especialidad\n");
                    fflush(stdin);
                    gets(especialidadAbuscar);
                    posMedicos = existeEspecialidadPosicion(arregloMedicos,especialidadAbuscar,validosArregloMedicos);
                }
                while(posMedicos == -1);

                mostrarArregloListaMedicoPorEspecialidad(arregloMedicos, validosArregloMedicos, especialidadAbuscar);
                do
                {
                    printf("\nIngrese la matricula\n");
                    scanf("%i",&matriculaIngresada);
                    flag = VerificarMedicoHabilitado(arregloMedicos[posMedicos].listaMedicos,matriculaIngresada);
                }
                while(flag == 0);

                arregloMedicos[posMedicos].listaMedicos = modificarDatosMedico(arregloMedicos[posMedicos].listaMedicos,matriculaIngresada);

                posTurnos = existeMatriculaTurno(arregloTurnos,validosArregloTurnos,matriculaIngresada);
                if(posTurnos != -1)
                {
                    arregloTurnos[posTurnos].dato = arregloMedicos[posMedicos].listaMedicos->dato;
                }
                pasarDeArregloListasTurnosAarchivoTurnos(registroDeTurnosMedico,arregloTurnos,validosArregloTurnos);
                arreglodemedicosAarchivo(registoDeMedicos,validosArregloMedicos,arregloMedicos);
                break;

            case 13:
                mostrarEspecialidadesBaseDatos (arregloMedicos, validosArregloMedicos);
                do
                {
                    printf("\nIngrese la especialidad: ");
                    fflush(stdin);
                    gets(especialidadAbuscar);
                    posMedicos = existeEspecialidadPosicion(arregloMedicos,especialidadAbuscar,validosArregloMedicos);
                }
                while(posMedicos == -1);

                mostrarArregloListaMedicoPorEspecialidad(arregloMedicos, validosArregloMedicos, especialidadAbuscar);
                do
                {
                    printf("\nIngrese la matricula: ");
                    scanf("%i",&matriculaIngresada);
                    flag = VerificarMedicoHabilitado(arregloMedicos[posMedicos].listaMedicos,matriculaIngresada);
                }
                while(flag == 0);

                posTurnos = existeMatriculaTurno(arregloTurnos,validosArregloTurnos,matriculaIngresada);


                if(posTurnos!=1)
                {
                    int verificarSiSeDehabilitaMedico= verificarSiMedicoTieneTurnosTomados (arregloTurnos[posTurnos].turno);
                    if(verificarSiSeDehabilitaMedico==1)
                    {

                        arregloMedicos[posMedicos].listaMedicos = deshabilitarUnMedicoListaMedicos (arregloMedicos[posMedicos].listaMedicos, matriculaIngresada);

                        arregloTurnos[posTurnos].dato = arregloMedicos[posMedicos].listaMedicos->dato;
                        pasarDeArregloListasTurnosAarchivoTurnos(registroDeTurnosMedico,arregloTurnos,validosArregloTurnos);
                        arregloDeEspecialidadesAarchivo(registoDeMedicos,validosArregloMedicos,arregloMedicos);

                    }
                    else
                    {
                        printf("\nERROR: El medico indicado no puede deshabilitarse debido a que tiene turnos agendados");
                    }
                }
                 break;
            case 14:
                 system("cls");
                 mostrarTodoArbol(arbolUsuario);

            }

            do
            {
                printf("\nPara ver nuevamente el menu presione 's': ");
                fflush(stdin);
                scanf("%s",&verMenu);
            }
            while(verMenu!='s');


        }
     }else{
       printf("Acceso denegado\n");
     }
    }
    else
    {
        system("cls");
        printf("\n1.Registrarse\n");
        printf("\n2.Iniciar sesion\n");
        scanf("%i",&opcUsuario);

        if(opcUsuario == 1)
        {
            system("cls");
            RgTOlista("Registro de paciente",&listaVerificacion);///Pasa del registro a una lista de verificacion

            CargarRegistro("Registro de paciente",&listaVerificacion);///Carga un registro

            registroAarbol("Registro de paciente",&arbolUsuario);///Pasa de un registro a un arbol

        }
        else
        {
            do{
            printf("Ingrese el id\n");
            fflush(stdin);
            gets(id);

            printf("Ingrese la contraseña:\n");
            fflush(stdin);
            gets(clave);

            flagUsuario = existeIdYclave(arbolUsuario,id,clave);
            }while(flagUsuario == 0);
            while(verMenuPaciente =='s')
            {
                system("cls");
                printf("\nMENU DE OPCIONES\n");
                printf("\nOpcion '1' mostrar mis datos\n");
                printf("\nOpcion '2' modificar mis datos\n");
                printf("\nOpcion '3' solicitar un Turno\n");
                printf("\nOpcion '4' mostrar mis turnos\n");


                scanf("%i",&opc);
                switch(opc)
                {
                case 1:
                    system("cls");
                    mostrarPacientePorDni(arbolUsuario);

                    break;

                case 2:
                    system("cls");
                    printf("Ingrese el DNI\n");
                    scanf("%i",&dni);

                    aux = modificarDatosUsuario(&arbolUsuario,dni,listaVerificacion);
                    mostrarUnArbol(aux);
                    break;

                case 3:
                    system("cls");
                    registroTurnosPaciente nuevoTurnoPaciente;

                    nuevoTurnoPaciente=elegirUnTurnoPaciente (arbolUsuario,arregloTurnos, validosArregloTurnos, arregloMedicos, validosArregloMedicos);
                    pasarDeArregloListasTurnosAarchivoTurnos(registroDeTurnosMedico, arregloTurnos, validosArregloTurnos);

                    ///  Guardar los cambios
                    archi = fopen("Registro de paciente","wb");
                    archiTurnos = fopen("Registro de Turnos","wb");
                    arbolAregistro(arbolUsuario,archi,archiTurnos);
                    fclose(archi);
                    fclose(archiTurnos);

                    break;

                case 4:
                    system("cls");
                    mostrarTodosLosDatosPacienteYTurnosPorDni (arbolUsuario);
                    break;

                default:
                    system("cls");
                    printf("\nERROR\n");
                    break;
                }

                /// Para Guardar los cambios
                archi = fopen("Registro de paciente","wb");
                archiTurnos = fopen("Registro de Turnos","wb");
                arbolAregistro(arbolUsuario,archi,archiTurnos);
                fclose(archi);
                fclose(archiTurnos);

                do
                {
                    printf("\nPara ver nuevamente el menu presione 's': \n");
                    fflush(stdin);
                    scanf("%c",&verMenuPaciente);
                }
                while(verMenuPaciente!= 's');

            }
        }


    }

}
