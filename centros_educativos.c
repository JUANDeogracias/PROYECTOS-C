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
    Alumnos alumnos;
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

        // Clear input buffer
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
    int contador=0;
    printf("-------------------------------------------------\n");
    for(int i=0; i<cantidad_centros; i++){
        if(c[i].supervision[0]!='n'){
            printf("Ahora vamos a guardar los datos de cada ciclo en este centro\n");
            for(int j=0; j<NUMERO_CICLOS;j++){
                contador++;
                printf("Cuantos alumnos tiene el ciclo %d",contador);
                scanf("%d",c[i].ciclos[i].cantidad_alumnos);
            }
        }
    }
}

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


