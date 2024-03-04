#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Especialidad{
    matematicas = 1,
    fisica = 2,
    lengua = 3
};
typedef struct{
    int numero;
    enum Especialidad especialidad;
}Alumnos;

int main(){
    int cantidad_alumnos;
    printf("Introduce una cantidad de alumnos");
    scanf("%d",&cantidad_alumnos);
    Alumnos alumnos[cantidad_alumnos];
    
    printf("Selecciona la especialidad (1,2,3)\n");
    scanf("%d",&alumnos[0].especialidad);
    
    printf("%d",alumnos[0].especialidad);
}