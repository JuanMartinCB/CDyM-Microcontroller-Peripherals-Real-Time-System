/*
 Autores:
 Castro Bustos Juan Mart�n 
 Flores Ignacio
 Rodriguez Joaqu�n
 */ 

#define F_CPU 16000000UL
#include "MEF.h"
#include "juego.h"
#include "lcd.h"
#include <string.h> // Para memset
#include <stdlib.h> // Para atoi

#define LIMPIAR_LINEA_INFERIOR {LCDGotoXY(0, 1); LCDstring((uint8_t*)"                ", 16);}
	
// Variables
estado_t estado = ARRANCANDO;
uint8_t key;
//globales para luego reiniciarlas con una funcion simple en lugar de hacerlas estaticas dentro del update y reiniciarlas con una funcion y 7 parametros 
uint8_t buffer_indice = 0; //indica longitud o indice del buffer de digitos
char caracter_ingresado_ascii = 0; //caracter ingresado en formato ascii
uint8_t posicion_contrasena_actual = 0; //indice actual de contrase�a
uint8_t caracteres_adivinados_count = 0; //contador de aciertos
uint8_t errores = 0; //contador de errores
uint8_t buffer_digitos[3] = {0}; //buffer de digitos
char palabra_display[6] = {"_____"}; //guarda la palabra que se ira mostrando
cronometro tiempo_transcurrido;

void reiniciar_variables() {
	buffer_indice = 0;
	caracter_ingresado_ascii = 0;	
	posicion_contrasena_actual = 0;
	caracteres_adivinados_count = 0;
	errores = 0;
	memset(buffer_digitos, 0, sizeof(buffer_digitos));
	memset(palabra_display, '_', 5);
	palabra_display[5] = '\0';
}

void mostrar_errores(uint8_t errores) {
	LCDcursorOFF();
	LCDGotoXY(0, 1);
	char error_char = errores + '0'; // Convierte 1 a '1', 2 a '2', etc. para poder mostrarlos en el display
	LCDstring((uint8_t*)"Errores: ", 9); // Mostrar cantidad de errores
	LCDsendChar(error_char);
	_delay_ms(1000);
	LIMPIAR_LINEA_INFERIOR;
}

void esperar_semilla_aleatoria() {
	uint8_t semilla = 0;
	while (1) {
		semilla = TCNT1;
		if (KEYPAD_Scan(&key) && key == '*') {
			srand(semilla);  
			break;
		}
	}
}

void MEF_Update()	
{
		
	switch(estado)
	{
		case ARRANCANDO:
			LCDclr();
			LCDGotoXY(0,0);
			LCDstring((uint8_t*)"Presione *", 10);
			esperar_semilla_aleatoria();
			LCDclr();
			juego_seleccionar_palabra_random();	//selecciona palabra random
			reiniciar_variables();
			estado = MOSTRAR;
			LCDclr();
			break;

		
		case MOSTRAR:				
			LCDGotoXY(0, 1);
			LCDstring((uint8_t*)juego_get_contrasena(), 5); //muestra la palabra a escribir durante 2 segundos
			_delay_ms(2000);
			LCDclr();
			LCDGotoXY(0, 0);
			LCDstring((uint8_t*)palabra_display, 5); //muestra _ _ _ _ _ donde iran los caracteres
			TEMPinit();
			LCDGotoXY(0,1);
			LCDcursorOnBlink();
			estado = ESPERAR;
			break;
			
		case ESPERAR: //Esperando a que escriban algo en el teclado
			if (KEYPAD_Scan(&key)) {
				if (key >= '0' && key <= '9') {
					if (buffer_indice < 3) { //<3 porque los ascii necesarios van de 2 a 3 cifras
						buffer_digitos[buffer_indice] = (char)key; // Agregar digito al buffer. Aca se guarda lo presionado
						buffer_indice++; //suma 1 al indice usado para mostrar el digito a continuacion
						LCDGotoXY(0, 1);
						for (uint8_t i = 0; i < buffer_indice; i++) {
							LCDsendChar(buffer_digitos[i]); //muestra lo guardado
						}
					}
					} else if (key == '#') {
					caracter_ingresado_ascii = (char)atoi((char*)buffer_digitos); //transforma el contenido del array en un entero con atoi, luego con el casteo lo transforma a su valor ascii. ejemplo: {7,6} -> 76 -> "76" = "L"
					buffer_indice = 0; //reinicia el indice para el proximo digito
					memset(buffer_digitos, 0, sizeof(buffer_digitos)); // al presionar # vac�a el buffer de caracteres para procesar lo proximo
					LIMPIAR_LINEA_INFERIOR; //macro para "limpiar" la linea inferior del LCD
					estado = COMPARAR;
				}
			}
			break;
			
		case COMPARAR:
			LCDcursorOFF();
			if (juego_chequear_caracter(caracter_ingresado_ascii, posicion_contrasena_actual)){ //verifica que el caracter ingresado sea correcto
				estado=CORRECTO;
			} else {
				estado = INCORRECTO;
			}
			break;
		case CORRECTO:
			palabra_display[posicion_contrasena_actual] = caracter_ingresado_ascii; //si es correcto lo agrega a la variable que muestra el display
			posicion_contrasena_actual++;
			caracteres_adivinados_count++;
			LCDGotoXY(0,0);
			LCDstring((uint8_t*)palabra_display, 5); //actualiza el display
			if (caracteres_adivinados_count == 5) {
				estado = VICTORIA;
				} else {
				LCDGotoXY(0,1);
				LCDcursorOnBlink();
				estado = ESPERAR;
			}
			caracter_ingresado_ascii = 0; // Limpiar el caracter procesado
		break;
		case INCORRECTO:
			errores++;
			mostrar_errores(errores);
			if (errores == 3){
				estado = DERROTA;
				} else {
				LCDGotoXY(0,1);
				LCDcursorOnBlink();
				estado = ESPERAR;
			}
			caracter_ingresado_ascii = 0; // Limpiar el caracter procesado
		break;
		case VICTORIA: //display de victoria 
			LCDcursorOFF();
			LCDclr();
			LCDGotoXY(0,0);
			LCDstring((uint8_t*)"Victoria",8);
			LCDGotoXY(0,1);
			LCDstring((uint8_t*)"Tiempo: ",8);
			tiempo_transcurrido = TEMPgetTime();
			LCDescribeDato(tiempo_transcurrido.sec, tiempo_transcurrido.digitos);
			LCDsendChar('s');
			_delay_ms(5000);
			estado = ARRANCANDO;
			break;
		case DERROTA: //display de derrota
			LCDclr();
			LCDGotoXY(0,0);
			LCDstring((uint8_t*)"Derrota",7);
			_delay_ms(5000);
			estado = ARRANCANDO;
			break;
		

	}
				
}