/*
 Autores:
 Castro Bustos Juan Mart?n 
 Flores Ignacio
 Rodriguez Joaqu?n
 */ 
#include <avr/io.h>
#include <time.h>
#include <stdio.h>



void KEYPAD_init();
uint8_t KEYPAD_Update(uint8_t *key);//Si hay una tecla presionada en el teclado, devuelve el valor de la letra
									// devuelve 1 si se presiono una tecla | devuelve 0 si no se presiono una tecla
uint8_t KEYPAD_Scan(uint8_t *key); // Anti-rebote