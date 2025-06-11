/*
 Autores:
 Castro Bustos Juan Mart?n 
 Flores Ignacio
 Rodriguez Joaqu?n
 */ 
#include "juego.h"
//diccionario
const char *diccionario[] = { "Arbol", "Boton", "CDyMC", "ClavE", "Facil", "Gafas", "Hojas", "LiBro", "Lanza", "Nieve", "PeRro", "PecES", "PiAno", "PrYKe", "RUEDa", "SERIE", "SalUd", "Salud", "Silla", "Tecla", "Valor", "Verde", "YnHRz", "hARdD", "silla" };
	
#define DICCIONARIO_SIZE (sizeof(diccionario) / sizeof(diccionario[0]))

// palabra seleccionada actualmente
static const char* contrasena_actual;

// indice de la ultima palabra seleccionada
static uint8_t indice_ultima_palabra = 0;


void juego_init(void) {
	uint8_t i;
	i = rand() % DICCIONARIO_SIZE;
	contrasena_actual = diccionario[i];
	indice_ultima_palabra = i;
}


// selecciona una palabra aleatoria del diccionario
void juego_seleccionar_palabra_random(void) {
	uint8_t i;
	// Asegura que sea una palabra diferente a la anterior
	
	do {
		i = rand() % DICCIONARIO_SIZE;
	} while (i == indice_ultima_palabra && DICCIONARIO_SIZE > 1);
	
	contrasena_actual = diccionario[i];
	indice_ultima_palabra = i;
}

// get de la contrase�a actual
const char* juego_get_contrasena(void) {
	return contrasena_actual;
}

// Funci�n para verificar si un car�cter coincide con la posici�n en la palabra
uint8_t juego_chequear_caracter(char c, uint8_t pos) {
	// verifica que la posici�n sea v�lida
	if (pos >= 5 || !contrasena_actual) {
		return 0;
	}
	
	// Verificar que el car�cter sea una letra (A-Z, a-z) es para asegurar que el input no tenga caracteres especiales como 35 (#)
	if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
		return 0;
	}
	
	// Comparar car�cter con la posici�n en la contrase�a, respetando may�sculas y min�sculas
	return (c == contrasena_actual[pos]);
}
