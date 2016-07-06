/*
 * evento.h
 *
 *  Created on: 22/06/2016
 *      Author: cesar
 */

#ifndef EVENTO_H_
#define EVENTO_H_

typedef enum EVENTS {CHEGADA=1, TRANSCODING=2} TTipoEvento;

typedef struct evento TEvento;
typedef double (*TGetTempoEvento)(TEvento*);
typedef TTipoEvento(*TGetTipoEvento)(TEvento*);
typedef short(*TComparaEvento)(TEvento*, TEvento*);
typedef void (*TPrintEvento)(TEvento*);
struct evento{
	void *dado;
	TComparaEvento compara;
	TGetTempoEvento getTempo;
	TGetTipoEvento getTipo;
	TPrintEvento print;
};

TEvento *criarEvento(TTipoEvento, double tempo);
void destruirEvento(TEvento *);



#endif /* EVENTO_H_ */
