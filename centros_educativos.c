#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CICLOS 3
#define MAX_ALUMNOS 30

enum Curso_bachillerato{
    primero_BACH = 1,
    segundo_BACH = 2,
};

enum Curso_ciclos{
    primero_DAM = 1,
    segundo_DAM = 2,
};

typedef struct {
    char nombre[50];
    int edad;
    char dni[50];
    enum Curso_bachillerato cursos_bachillerato;
} Alumnos_bachillerato;

typedef struct {
    char nombre[50];
    int edad;
    char dni[50];
    enum Curso_ciclos curso_ciclos;
} Alumnos;

typedef struct {
    int cantidad_alumnos;
    Alumnos alumnos[MAX_ALUMNOS];
} Ciclo;

typedef struct {
    int cantidad_alumnos_bachillerato;
    Alumnos_bachillerato alumnos_bachillerato[MAX_ALUMNOS];
} Ciclo_bachillerato;

typedef struct {
    char nombre_centro[50];
    char supervision[2];
    int cantidad_alumnos;
    Ciclo ciclos[NUM_CICLOS];
    Ciclo_bachillerato ciclos_bachillerato[NUM_CICLOS];
} Centro;

void agregar_supervision(Centro *c, int cantidad_centros);
void agregar_centro(Centro *c, int cantidad_centros);
void mostrar_info(Centro *c, int cantidad_centros);
void recoger_info(Centro *c, int cantidad_centros);
void mostrar_info_recogida_info(Centro *c, int cantidad_centros);
void comprobando_dni(Centro *c, int centro_actual, int ciclo_actual, int alumno_actual, int es_bachillerato);

int guardar_curso_ciclo(Centro *c, int cantidad_centros);

int guardar_curso_bach(Centro *c, int cantidad_centros);

void limpiar_buffer();

int main() {
    int cantidad_centros;
    printf("Introduce el numero de centros supervisados o no por nosotros: ");
    scanf("%d", &cantidad_centros);
    Centro centro[cantidad_centros];

    agregar_supervision(centro, cantidad_centros);
    agregar_centro(centro, cantidad_centros);
    recoger_info(centro, cantidad_centros);
}

void agregar_supervision(Centro *c, int cantidad_centros) {
    for (int i = 0; i < cantidad_centros; i++) {
        c[i].supervision[0] = 'n';
    }
}

void agregar_centro(Centro *c, int cantidad_centros) {
    int contador = 0;
    char respuesta[2];
    printf("\tBIENVENIDO AL GESTOR DE CENTROS EDUCATIVOS\n");
    for (int i = 0; i < cantidad_centros; i++) {
        contador++;
        limpiar_buffer();
        printf("Introduce el nombre del centro %d: ", contador);
        fgets(c[i].nombre_centro, sizeof(c[i].nombre_centro), stdin);
        c[i].nombre_centro[strlen(c[i].nombre_centro) - 1] = '\0';

        printf("Esta bajo su supervision? (s/n)\n");
        fgets(respuesta, sizeof(respuesta), stdin);

        while (getchar() != '\n');

        if (respuesta[0] == 'n') {
            printf("Este centro no sera supervisado por el gestor de centros educativos.\n");
        } else {
            printf("Perfecto, mas tarde tendra que introducir los datos de este centro.\n");
            c[i].supervision[0] = 's';
        }
    }
    mostrar_info(c, cantidad_centros);
}

void mostrar_info(Centro *c, int cantidad_centros) {
    system("cls");
    int contador = 0;
    printf("\tCENTROS BAJO NUESTRA SUPERVISION\n");
    for (int i = 0; i < cantidad_centros; i++) {
        if (c[i].supervision[0] == 's') {
            contador++;
            printf("%d- %s\n", contador, c[i].nombre_centro);
        }
    }
}

void recoger_info(Centro *c, int cantidad_centros) {
    printf("-------------------------------------------------\n");
    for (int i = 0; i < cantidad_centros; i++) {
        if (c[i].supervision[0] != 'n') {
            printf("Ahora vamos a guardar los datos de cada ciclo en el centro %s.\n", c[i].nombre_centro);
            for (int j = 0; j < NUM_CICLOS; j++) {
                printf("Cuantos alumnos tiene el ciclo %d? ", j + 1);
                scanf("%d", &c[i].ciclos[j].cantidad_alumnos);
                limpiar_buffer();

                for (int k = 0; k < c[i].ciclos[j].cantidad_alumnos; k++) {
                    printf("Introduce el nombre del alumno de ciclo %d: ", j + 1);
                    fgets(c[i].ciclos[j].alumnos[k].nombre, sizeof(c[i].ciclos[j].alumnos[k].nombre), stdin);
                    c[i].ciclos[j].alumnos[k].nombre[strlen(c[i].ciclos[j].alumnos[k].nombre) - 1] = '\0';
                    limpiar_buffer();

                    //Saber especialidad
                    int curso = guardar_curso_ciclo(c, cantidad_centros);
                    c[i].ciclos[j].alumnos[k].curso_ciclos = curso;

                    printf("Vamos a comprobar el DNI del alumno de ciclo %d. ", j + 1);
                    comprobando_dni(c, i, j, k, 0);
                }
            }

            printf("Cuantos alumnos de bachillerato tiene el centro %s? ", c[i].nombre_centro);
            scanf("%d", &c[i].ciclos_bachillerato[0].cantidad_alumnos_bachillerato);
            limpiar_buffer();

            for (int k = 0; k < c[i].ciclos_bachillerato[0].cantidad_alumnos_bachillerato; k++) {
                printf("Introduce el nombre del alumno de bachillerato del centro %s: ", c[i].nombre_centro);
                fgets(c[i].ciclos_bachillerato[0].alumnos_bachillerato[k].nombre, sizeof(c[i].ciclos_bachillerato[0].alumnos_bachillerato[k].nombre), stdin);
                c[i].ciclos_bachillerato[0].alumnos_bachillerato[k].nombre[strlen(c[i].ciclos_bachillerato[0].alumnos_bachillerato[k].nombre) - 1] = '\0';
                
                //saber especiallidad
                int curso_bach = guardar_curso_bach(c, cantidad_centros);
                c[i].ciclos_bachillerato[0].alumnos_bachillerato[k].cursos_bachillerato = curso_bach;
                
                printf("Vamos a comprobar en DNI del alumno de bachillerato del centro %s. ", c[i].nombre_centro);
                comprobando_dni(c, i, -1, k, 1);
            }
        }
    }
    mostrar_info_recogida_info(c, cantidad_centros);
}



void mostrar_info_recogida_info(Centro *c, int cantidad_centros) {
    system("cls");
    for (int i = 0; i < cantidad_centros; i++) {
        if (c[i].supervision[0] != 'n') {
            printf("\tMOSTREMOS LOS DATOS DEL CENTRO %s\n", c[i].nombre_centro);
            for (int j = 0; j < NUM_CICLOS; j++) {
                printf("\t\nINFORMACION DEL CICLO %d:\n", j + 1);
                printf("\tAlumnos de ciclo:\n");
                int contador = 0;
                for (int k = 0; k < c[i].ciclos[j].cantidad_alumnos; k++) {
                    contador++;
                    printf("\tAlumno %d: %s\n; dni: %s, perteneciente a %dºDAM", contador, c[i].ciclos[j].alumnos[k].nombre,c[i].ciclos[j].alumnos[k].dni,c[i].ciclos[j].alumnos[k].curso_ciclos);
                }
            }

            printf("\nALUMNOS DE BACHILLERATO:\n");
            int contador = 0;
            for (int k = 0; k < c[i].ciclos_bachillerato[0].cantidad_alumnos_bachillerato; k++) {
                contador++;
                printf("\tAlumno de bachillerato %d: %s; dni: %s, perteneciente a %dºDAM\n", contador, c[i].ciclos_bachillerato[0].alumnos_bachillerato[k].nombre, c[i].ciclos_bachillerato[0].alumnos_bachillerato[k].dni,c[i].ciclos_bachillerato[0].alumnos_bachillerato[k].cursos_bachillerato);
            }
        }
    }
}

void comprobando_dni(Centro *c, int centro_actual, int ciclo_actual, int alumno_actual, int es_bachillerato){
    char dni_temporal[50];
    printf("Vamos a comprobar que el DNI dado es valido. Introduce el DNI: ");
    scanf("%s", dni_temporal);
    limpiar_buffer();

    int dni_repetido = 0;

    if (es_bachillerato == 0) {
        for (int k = 0; k < alumno_actual; k++) {
            if(strcmp(dni_temporal, c[centro_actual].ciclos[ciclo_actual].alumnos[k].dni) == 0){
                dni_repetido = 1;
                break;
            }
        }
    } else {
        for (int k = 0; k < alumno_actual; k++) {
            if(strcmp(dni_temporal, c[centro_actual].ciclos_bachillerato[0].alumnos_bachillerato[k].dni) == 0){
                dni_repetido = 1;
                break;
            }
        }
    }

    if (dni_repetido) {
        printf("El DNI dado no es valido o ya está en uso. Vuelva a introducir otro DNI.\n");
        comprobando_dni(c, centro_actual, ciclo_actual, alumno_actual, es_bachillerato);
    } else {
        printf("El DNI dado es valido.\n");
        if (es_bachillerato == 0) {
            strcpy(c[centro_actual].ciclos[ciclo_actual].alumnos[alumno_actual].dni, dni_temporal);
        } else {
            strcpy(c[centro_actual].ciclos_bachillerato[0].alumnos_bachillerato[alumno_actual].dni, dni_temporal);
        }
    }
}

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int guardar_curso_ciclo(Centro *c, int cantidad_centros){
    int respuesta;
    printf("Introduce tu eleccion (1. 1ºDAM, 2. 2ºDAM):\n");
    scanf("%d", &respuesta);
    switch(respuesta){
        case 1:
            printf("Alumno perteneciente a primero de DAM");
            return respuesta;
            break;
        case 2:
            printf("Alumno perteneciente a segundo de DAM");
            return respuesta;
            break;
        default:
            printf("Has introducido una opcion incorrecta vuelve a repetirla:\n");
            scanf("%d", &respuesta);
            return respuesta;
        }
}

int guardar_curso_bach(Centro *c, int cantidad_centros){
    int respuesta;
    printf("Introduce tu eleccion (1. 1ºBACH, 2. 2ºBACH):\n");
    scanf("%d", &respuesta);
    switch(respuesta){
        case 1:
            printf("Alumno perteneciente a primero de BACH");
            return respuesta;
            break;
        case 2:
            printf("Alumno perteneciente a segundo de BACH");
            return respuesta;
            break;
        default:
            printf("Has introducido una opcion incorrecta vuelve a repetirla:\n");
            scanf("%d", &respuesta);
            return respuesta;
        }
}
