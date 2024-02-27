#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int nombre;
}Persona;

int main(){
    int cantidad;
    printf("hola introduce la cantidad de empleados que quieras : ");
    scanf("%d",&cantidad);
    Persona persona[cantidad];

}