#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int numero;
}Curso;

typedef struct{
    int edad;
    Curso curso;
    enum{
        LUNES,
        MARTES,
        MIERCOLES,
    }dias_semana;
}Empleados;

void funcion_prueba(Empleados *empleados,int cantidad);
void probando_enum(Empleados *empleados,int cantidad,char *dia);
int main(){
    int cantidad;
    printf("INTRODUCE UN NUMERO");
    scanf("%d",&cantidad);
    Empleados empleados[cantidad];
    funcion_prueba(empleados,cantidad);
}

void funcion_prueba(Empleados *empleados,int cantidad){
    char dia[50];
    int contador=0;
    for(int i=0;i<cantidad;i++){
        contador ++;
        printf("\nintroduce la edad del empleado %d",contador);
        scanf("%d",&empleados[i].edad);
        printf("\nahora introduce el numero de el curso a el que pertenece");
        scanf("%d",&empleados[i].curso.numero);
        printf("Introduce el dia de la semana que prefieres");
        fgets(dia,sizeof(dia),stdin);
        dia[strlen(dia)-1]='\0';
        probando_enum(empleados,cantidad,dia);

    }
}

void probando_enum(Empleados *empleados, int cantidad, char *dia) {
    printf("Es ");
    switch (dia[0]) {
        case 'L':
            printf("lunes\n");
            break;
        case 'M':
            if (dia[1] == 'A') {
                printf("martes\n");
            } else {
                printf("miércoles\n");
            }
            break;
        default:
            printf("No es un día válido\n");
            break;
    }
}