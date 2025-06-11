/*
 Autores:
 Castro Bustos Juan Mart?n 
 Flores Ignacio
 Rodriguez Joaqu?n
 */ 
#include <avr/io.h>
#include "teclado.h"
#include "temporizador.h"
#include <time.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {ARRANCANDO, MOSTRAR, ESPERAR, COMPARAR, CORRECTO, INCORRECTO, VICTORIA, DERROTA} estado_t;

void MEF_Update();