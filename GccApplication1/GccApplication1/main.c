/*
 Autores:
 Castro Bustos Juan Mart?n 
 Flores Ignacio
 Rodriguez Joaqu?n
 */ 
#define F_CPU 16000000UL
#include "lcd.h"
#include "teclado.h"
#include "timer.h"
#include "juego.h"
#include "MEF.h"
#include "temporizador.h"
#include <avr/io.h>
#include <time.h>
int FLAG_TIMER=0;
int FLAG_TEMPORIZADOR=0;

int main(void)
{
	srand(time(NULL));
	LCDinit();
	timer_init();
	KEYPAD_init();
	juego_init();
	TEMPinit();
    while (1) 
    {
		if(FLAG_TEMPORIZADOR){ //Flag del temporizador en 1
			FLAG_TEMPORIZADOR=0; // Pone el flag del temporizador en 0
			TEMPupdate(); // Actualiza el temporizador
		}
		if(FLAG_TIMER){
			MEF_Update();	
			FLAG_TIMER=0;
		}
    }
}

ISR(TIMER1_COMPA_vect)
{
	static uint8_t count=0; //Contador para contar hasta 10
	FLAG_TIMER = 1;
	count++; //Sumo 1 al contador
	if(count==10){ //10 * 0,1s (100ms) =  1 s
		count=0; //Reseteo el contador
		FLAG_TEMPORIZADOR=1;//Flag del reloj en 1
	}
}
