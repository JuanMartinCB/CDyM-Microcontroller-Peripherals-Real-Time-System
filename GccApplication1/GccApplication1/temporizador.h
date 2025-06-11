/*
 Autores:
 Castro Bustos Juan Mart?n 
 Flores Ignacio
 Rodriguez Joaqu?n
 */ 


#ifndef TEMPORIZADOR_H_
#define TEMPORIZADOR_H_
#include <avr/io.h>
#include <math.h>
typedef struct
{
	uint8_t digitos;
	uint8_t sec;
} cronometro;
void TEMPinit();
void TEMPupdate();
cronometro TEMPgetTime();

#endif /* TEMPORIZADOR_H_ */