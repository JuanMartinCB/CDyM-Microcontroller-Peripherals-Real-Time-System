/*
 Autores:
 Castro Bustos Juan Mart?n 
 Flores Ignacio
 Rodriguez Joaqu?n
 */ 
#include "teclado.h"


const uint8_t mapeo_teclas[4][4] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'0', '*', '#', '*'}
};


void KEYPAD_init()
{
	DDRD &= ~((1 << PIND2) | (1 << PIND3) | (1 << PIND4) | (1 << PIND5) ); // seteo como entrada los puertos D conectados al teclado
	DDRB |= ((1 << PINB0) | (1 << PINB3) | (1 << PINB4)); // seteo como salida los puertos B conectados a las filas del teclado
	DDRD |= (1 << PIND7); // seteo como salida el puerto D7 conectado a una fila del teclado
	
	PORTD |= ((1 << PIND2) | (1 << PIND3) | (1 << PIND4) | (1 << PIND5) | (1 << PIND7)); // activo pull up en puertos D conectados al teclado
	PORTB |= ((1 << PINB0) | (1 << PINB3) | (1 << PINB4)); // activo pull up en puertos B conectados al teclado 

}
uint8_t KEYPAD_Update(uint8_t *key)
{
	uint8_t fila;

	for (fila = 0; fila < 4; fila++)
	{
		// Poner todas las filas en alto antes de activar una
		PORTB |= (1 << PB0) | (1 << PB3) | (1 << PB4);
		PORTD |= (1 << PD7);

		// Activar solo una fila en bajo (escaneo)
		switch (fila)
		{
			case 0: PORTB &= ~(1 << PB4); break; // Fila A
			case 1: PORTB &= ~(1 << PB3); break; // Fila B
			case 2: PORTB &= ~(1 << PB0); break; // Fila C
			case 3: PORTD &= ~(1 << PD7); break; // Fila D
		}

		// Leer columnas
		if (!(PIND & (1 << PD3))) // Columna 1
		{
			*key = mapeo_teclas[fila][0];
			return 1;
		}
		if (!(PIND & (1 << PD5))) // Columna 2
		{
			*key = mapeo_teclas[fila][1];
			return 1;
		}
		if (!(PIND & (1 << PD4))) // Columna 3
		{
			*key = mapeo_teclas[fila][2];
			return 1;
		}
		if (!(PIND & (1 << PD2))) // Columna 4
		{
			*key = mapeo_teclas[fila][3];
			return 1;
		}
	}

	*key = 0xFF; // Ninguna tecla presionada
	return 0;
}

uint8_t KEYPAD_Scan(uint8_t *pkey)
{
	 static uint8_t Old_key, Last_valid_key=0xFF; // no hay tecla presionada;
	 uint8_t key;
	 
	 KEYPAD_Update(&key);
	 if(key==0xFF){
		 Old_key=0xFF;	// no hay tecla presionada
		 Last_valid_key=0xFF;
		 return 0; // devuelvo 0 si no se presiono ninguna tecla
	 }
	 if(key==Old_key) { //2da verificación
		 if(key!=Last_valid_key){ //evita múltiple detección
			 *pkey=key;
			 Last_valid_key = key;
			 return 1; // devuelvo 1 si se presiono una tecla nueva
		 }
	 }
	 Old_key=key; //1era verificación
	 return 0; // devuelvo 0 si la tecla es igual a la anterior

}