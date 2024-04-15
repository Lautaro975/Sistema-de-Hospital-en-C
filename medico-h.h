#ifndef MEDICO-H_H_INCLUDED
#define MEDICO-H_H_INCLUDED
#define numMaxEspecialidades 30
#define numMaxMedicos 30

typedef struct
{
    char nombreYapellido[30];
    int matricula;
    int telefono;
    int consultorio; // 1- Belgrano 2478, 2- Mitre 1489
    int habilitado; // 0 si / 1 no
} Medico;

typedef struct
{
    Medico datoT;
    int horario;
    char fecha[20];
    int dni;
    char especialidad[20];
} registroTurnosPaciente;


typedef struct
{
    Medico dato;
    struct nodoMedicos* siguiente;

} nodoMedicos;

typedef struct
{
    char especialidad[20];
    nodoMedicos* listaMedicos;
} celda; //arreglo

typedef struct
{
    char nombreYapellido[20];
    int matricula;
    int telefono;
    int consultorio;
    char especialidad[20];
    int habilitado; // 0 no / 1 si
} registroArchivoMedicos;

typedef struct
{
    int matricula;
    struct nodoMatriculas* siguiente;

} nodoMatriculas;


///Prototipo

nodoMedicos* inicListaMedicos();
nodoMatriculas* inicListaMatriculas();
nodoMedicos* crearNodoMedicos (char nombreYapellido[],int matricula,int telefono, int consultorio, int habilitado);
nodoMatriculas* crearNodoMatriculas(int matricula);
nodoMedicos* agregarAlPpioMedicos (nodoMedicos* lista, nodoMedicos* nuevoNodo);
nodoMatriculas* agregarAlPpioListaMatriculas (nodoMatriculas* lista, nodoMatriculas* nuevoNodo);
nodoMedicos* agregarEnOrdenMedicosPorMatricula (nodoMedicos* lista, nodoMedicos* nuevoNodo);
nodoMatriculas* pasarDelArregloAlistaDeMatriculasMedicos (celda arregloM[], int validos, nodoMatriculas* listaMatriculas);
int existeEspecialidadPosicion (celda arregMedicos[], char especialidad[], int validos);
int agregarEspecialidadAlArreglo(celda adl[],char especialidad[], int validos);
int altaMedicos(celda adl[],char nombreYapellido[], int matricula, int telefono, int consultorio, int validos, char especialidad[], int habilitado);
int existeMatriculaListaMatriculas(int matricula, nodoMatriculas* listaMatriculas);
registroArchivoMedicos cargaDatosUnMedico(nodoMatriculas* listaMatriculas);
void mostrarRegistroMedico(registroArchivoMedicos dato);
void mostrarTodosRegistroMedicos (char nombreArchivo[20]);
void mostrarRegistroMedicosHabilitados (char nombreArchivo[20]);
int pasarRegistroMedicosAarregloListasMedico (char nombreArchivo[], celda listaMedicos[], int dimension);
void mostrarDatosUnMedico(Medico dato);
void mostrarListaMedicos(nodoMedicos* lista);
void mostrarListaMedicosHabilitados(nodoMedicos* lista, char especialidad[]);
void mostrarArregloDeTodosLosMedicos (celda arregloMedicos[], int validos);
void mostrarArregloDeMedicosHabilitados (celda arregloMedicos[], int validos);
void mostrarArregloListaMedicoPorEspecialidad  (celda arregloM[], int validos, char especialidadP[]);
void mostrarEspecialidadesBaseDatos (celda arregloM[], int validos);
void cargarUnNuevoMedicoArchivo (char nombreDelArchivo[], registroArchivoMedicos nuevoDatosMedico);
int ingresarNuevoMedicoAlArchivoYarregloMedicos(celda arregloMedicos[],char nombreArchivoMedicos[],int validosAregloMedicos, registroArchivoMedicos nuevoM);
void mostrarDatosBasicosMedicosUnMedico(Medico dato);
void mostrarListaDatosBasicosMedicosHabilitados(nodoMedicos* listaM);
void mostrarDatosBasicosMedicos(celda arregloMedicos[], int validos);
nodoMedicos* buscarYdevolverUnNodoMedico (nodoMedicos* listaMedicos, int matricula);
nodoMedicos* modificarDatosMedico(nodoMedicos* listaMedicos, int matricula);
void arreglodemedicosAarchivo(char nombreArchivo[],int validos,celda clM[]);
void recorrerlistamedicosYguardararchivo(nodoMedicos* lista,FILE* archi,char especialidad[]);
int VerificarMedicoHabilitado(nodoMedicos* listaM,int matricula);
nodoMedicos* deshabilitarUnMedicoListaMedicos (nodoMedicos* listaMedicos, int matricula);
void arregloDeEspecialidadesAarchivo(char nombreArchivo[],int validos,celda clM[]);// arreglo especialidad
void recorrerlistaDeMedicosYguardararchivo(nodoMedicos* lista,FILE* archi,char especialidad[]);
#endif // MEDICO-H_H_INCLUDED
