/*
 Autores:
 Castro Bustos Juan Mart?n 
 Flores Ignacio
 Rodriguez Joaqu?n
 */ 
#include "temporizador.h"

cronometro cron;

/************************************************************************
Inicializa el temporizador 
************************************************************************/
void TEMPinit(){	
	cron.sec=0;
	cron.digitos = 1;
}

/************************************************************************
Actualiza el temporizador
************************************************************************/
void TEMPupdate(){
  cron.sec++;
  cron.digitos = (int)log10(cron.sec) + 1;
}

/************************************************************************
 Devuelve el tiempo pasado del temporizador
************************************************************************/
cronometro TEMPgetTime(){
	return cron;
}