/*
 * evento.c
 *
 *  Created on: 22/06/2016
 *      Author: cesar
 */
#include "evento.h"
#include <stdlib.h>
#include <stdio.h>
typedef struct {
	TTipoEvento tipo;
	double tempo;
}TDadoEvento;

static TDadoEvento *criarDado(TTipoEvento tipo, double tempo){
	TDadoEvento *dado = malloc(sizeof(TDadoEvento));
	dado->tempo = tempo;
	dado->tipo = tipo;

	return dado;
}


void destruirEvento(TEvento *ev){
	free(ev->dado);
	free(ev);
}

static void printEvento(TEvento *ev){
	TDadoEvento *d = ev->dado;
	printf("Tempo:%f Tipo:%d\n",d->tempo,d->tipo);
}

static double getTempoEvento(TEvento *ev){
	TDadoEvento *d = ev->dado;
	return d->tempo;
}

static TTipoEvento getTipoEvento(TEvento *ev){
	TDadoEvento *d = ev->dado;

	return d->tipo;
}
static short comparaEvento(TEvento *e1, TEvento *e2){
	if ( e1->getTempo(e1) < e2->getTempo(e2) ){
		return -1;
	} else if( e1->getTempo(e1) == e2->getTempo(e2) ){
		if ( (e1->getTipo(e1) == CHEGADA) && (e2->getTipo(e2) == TRANSCODING) )
			return 1;
		else
			return 0;

	} else
		return 1;

}
TEvento *criarEvento(TTipoEvento tipo, double tempo){
    TEvento *evento;

    evento = malloc(sizeof(TEvento));
    evento->dado = criarDado(tipo, tempo);

    evento->compara = comparaEvento;
    evento->getTempo = getTempoEvento;
    evento->getTipo = getTipoEvento;
    evento->print = printEvento;

    return evento;
}
