/*
 Autores:
 Castro Bustos Juan Mart?n 
 Flores Ignacio
 Rodriguez Joaqu?n
 */ 
#ifndef JUEGO_H
#define JUEGO_H

#include <avr/io.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"
#include "temporizador.h"

void juego_init(void);
void juego_seleccionar_palabra_random(void);
const char* juego_get_contrasena(void);
uint8_t juego_chequear_caracter(char c, uint8_t position);

#endif