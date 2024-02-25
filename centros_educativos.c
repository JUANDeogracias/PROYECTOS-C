#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMERO_CICLOS 3

typedef struct {
    char nombre[50];
    int edad;
}Alumnos;

typedef struct {
    int cantidad_alumnos;
    enum Curso {
        PRIMERO,
        SEGUNDO,
    }curso;
    Alumnos alumnos[30];
}Ciclos;

typedef struct {
    char nombre_centro[50];
    char supervision[2];
    int cantidad_alumnos;
    Ciclos ciclos[NUMERO_CICLOS];
} Centro;

void agregar_supervision(Centro *c, int cantidad_centros);
void agregar_centro(Centro *c, int cantidad_centros);
//mostrar la informacion de los centros que estan bajo su supervision
void mostrar_info(Centro *c, int cantidad_centros);

//Agregar toda la informacion
void recoger_info(Centro *c, int cantidad_centros);

//mostrar informacion de recogida_info
void mostrar_info_recogidainfo(Centro *c, int cantidad_centros);
//void limpiar_buffer();
void limpiar_buffer();
int main() {
    int cantidad_centros;
    printf("Introduce el numero de centros sean supervisados o no por nosotros\n");
    scanf("%d",&cantidad_centros);
    Centro centro[cantidad_centros];


    agregar_supervision(centro, cantidad_centros);
    agregar_centro(centro, cantidad_centros);
    recoger_info(centro, cantidad_centros);



}

void agregar_supervision(Centro *c, int cantidad_centros) {
    for (int i = 0; i < cantidad_centros; i++) {
        c[i].supervision[0] = 'n'; // Asignamos a supervision el caracter n es decir sería falso por defecto
    }
}

void agregar_centro(Centro *c, int cantidad_centros) {
    int contador = 0;
    char respuesta[2];
    printf("\tBIENVENIDO A EL GESTOR DE CENTROS EDUCATIVOS\n");
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
            printf("Este centro no sera supervisado por el gestor de centros educativos\n");
        } else {
            printf("Perfecto, mas tarde tendra que introducir los datos de este centro\n");
            c[i].supervision[0] = 's';
        }
    }
    mostrar_info(c, cantidad_centros);
}

void mostrar_info(Centro *c, int cantidad_centros){
    system("cls");
    int contador=0;
    printf("\tCENTROS BAJO NUESTRA SUPERVISION\n");
    for (int i = 0; i < cantidad_centros; i++) {
        if(c[i].supervision[0]=='s'){
            contador++;
            printf("%d- %s\n",contador,c[i].nombre_centro);
        }
    }
}

void recoger_info(Centro *c, int cantidad_centros){
    printf("-------------------------------------------------\n");
    for(int i = 0; i < cantidad_centros; i++){
        if(c[i].supervision[0] != 'n'){
            printf("Ahora vamos a guardar los datos de cada ciclo en el centro %s\n", c[i].nombre_centro);
            for(int j = 0; j < NUMERO_CICLOS; j++){
                printf("Cuantos alumnos tiene el ciclo %d: ", j + 1);
                scanf("%d", &c[i].ciclos[j].cantidad_alumnos);
                limpiar_buffer();

                for(int k = 0; k < c[i].ciclos[j].cantidad_alumnos; k++){
                    printf("Introduce el nombre del alumno %d: ", k + 1);
                    fgets(c[i].ciclos[j].alumnos[k].nombre, sizeof(c[i].ciclos[j].alumnos[k].nombre), stdin);
                    c[i].ciclos[j].alumnos[k].nombre[strlen(c[i].ciclos[j].alumnos[k].nombre)-1] = '\0';
                    limpiar_buffer();
                }
            }
        }
    }
    mostrar_info_recogidainfo(c, cantidad_centros);
}



void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


//mostrar informacion de recogida info
void mostrar_info_recogidainfo(Centro *c, int cantidad_centros){
    system("cls");
    for(int i = 0; i < cantidad_centros; i++){
        if(c[i].supervision[0] != 'n'){
            printf("\tMOSTREMOS LOS DATOS DEL CENTRO %s\n", c[i].nombre_centro);
            for(int j = 0; j < NUMERO_CICLOS; j++){
                printf("\t\nINFORMACION DEL CICLO %d:\n", j + 1);
                int contador = 0; // Reiniciamos el contador en cada ciclo
                for(int k = 0; k < c[i].ciclos[j].cantidad_alumnos; k++){
                    contador++; // Incrementamos el contador para cada alumno
                    printf("Alumno %d: %s\n", contador, c[i].ciclos[j].alumnos[k].nombre);
                }
            }
        }
    }
}
