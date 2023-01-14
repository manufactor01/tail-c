#include "cola.h"
#include <stdlib.h>
#include <stddef.h>

/* Estructura para trabajar con nodos */
typedef struct nodo{
	void *dato;
	struct nodo *siguiente;
}nodo_t;

nodo_t *nodo_crear(void *dato){
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if(nodo == NULL) return NULL;
	nodo->dato = dato;
	nodo->siguiente = NULL;
	return nodo;
}

/* Primitivas de la cola */
struct cola{
	nodo_t* head;
	nodo_t* tail;
};

cola_t *cola_crear(){
	cola_t *cola = malloc(sizeof(cola_t));
	if(cola == NULL) return NULL;
	cola->head = cola->tail = NULL;
	return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void *)){
	while(!cola_esta_vacia(cola)){
		void *dato = cola_desencolar(cola);
		if(destruir_dato){
			destruir_dato(dato);
		}
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
	return cola->head == NULL;
}

bool cola_encolar(cola_t *cola, void *dato){
	nodo_t *nodo = nodo_crear(dato);
	if(nodo == NULL) return false;
	if(cola_esta_vacia(cola)){
		cola->head = nodo;
	}else{
		cola->tail->siguiente = nodo;
	}
	cola->tail = nodo;
	return true;
}

void *cola_ver_primero(const cola_t *cola){
	if(cola_esta_vacia(cola)) return NULL;
	return cola->head->dato;
}

void *cola_desencolar(cola_t *cola){
	if(cola_esta_vacia(cola)) return NULL;
	nodo_t *ptr = cola->head;
	void *dato = cola_ver_primero(cola);
	cola->head = cola->head->siguiente;
	free(ptr);
	if(cola_esta_vacia(cola)) cola->tail = NULL;
	return dato;
}
