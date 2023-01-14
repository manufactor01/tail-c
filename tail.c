#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "cola.h"

char *cadena_crear(char *linea, size_t capacidad){
	char *cadena = malloc(capacidad*sizeof(char));
	if(!cadena) return NULL;
	strtok(linea, "\n");
	strcpy(cadena, linea);
	return cadena;
}

void mostrar_cadenas(void *dato){
	printf("%s\n", (char *)dato);
	free(dato);
}

bool es_numero(const char *cad){
	size_t i = 0;
	while(cad[i] != '\0'){
		if(!isdigit(cad[i])) return false;
		i++;
	}
	return true;
}

int main(int argc, char const *argv[])
{
	if(argc != 2){
		fprintf(stderr, "%s\n", "Cantidad de parametros erronea");
		return 1;
	}

	if(!es_numero(argv[1])){
		fprintf(stderr, "%s\n", "Tipo de parametro incorrecto");
		return 1;
	}
	cola_t *cola = cola_crear();

	char *linea = NULL;
	size_t capacidad;
	ssize_t leidos;

	size_t n = atoi(argv[1]);
	size_t i = 0;
	while((leidos = getline(&linea, &capacidad, stdin)) != -1){
		char *cadena = cadena_crear(linea, capacidad);
		cola_encolar(cola, cadena);
		i++;
		if(i > n){
			free(cola_desencolar(cola));
		}
	}
	free(linea);
	cola_destruir(cola, mostrar_cadenas);
	return 0;
}
