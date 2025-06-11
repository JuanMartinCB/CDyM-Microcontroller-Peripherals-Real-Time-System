/*
 Autores:
 Castro Bustos Juan Mart?n 
 Flores Ignacio
 Rodriguez Joaqu?n
 */ 
#include "timer.h"
#define F_CPU 16000000UL

// Función para inicializar el Timer0
// Configurar Timer0 en modo CTC (p.16)


//Timer 16 bits -> cuento de 0 a 65,535
//T = (OCR1A + 1) * (Prescaler / fclk)
//100ms = (OCR1A + 1) * (Prescaler / 16MHz)
//El valor que elija de prescaler debe estar dentro del rango valido del OCR1A (0;65.535)
//El valor que cumple la ecuación en este caso es 64 dándome OCR1A = 25000

// Preescalador 64


void timer_init(){
	// Configuro el timer1 en modo CTC con prescaler 64
	TCCR1A = 0;  //
	TCCR1B = 0;  //
	TCNT1  = 0;  //Inicializa el contador
	TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);   // modo CTC, prescaler de 64
	// WGM13 = 0 WGM12 = 1 WGM11 = 0 WGM10 = 0 -> CTC
	//           CSM12 = 0 CSM11 = 1 CSM10 = 1 -> prescaler 64
	
	OCR1A = 0x61A8;	// configura el contador de comparacion para 25.000 (61A8 = 25.000)
	TIMSK1 |= (1 << OCIE1A);  // habilita interrupción por igualdad de comparación
	sei(); //habilita las interrupciones para el MCU
}
