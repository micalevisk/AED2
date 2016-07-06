#include "agenda.h"
#include "evento.h"
#include "comparavel.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct elemento TElemento;
struct elemento{
	void* evento;
	TElemento *prox, *ant;
};

typedef struct {
	TElemento* inicio;
	TElemento* final;
}TDadoAgenda;

TDadoAgenda *criarDadoAgenda(){
	TDadoAgenda *d = malloc(sizeof(TDadoAgenda));

	d->inicio = NULL;
	d->final = NULL;

	return d;
}

static void *proximoAgenda(TAgenda* agenda){
	TElemento *caminha;
	void *evento=NULL;

	TDadoAgenda *d = agenda->dado;

	// fila vazia?
	if (d->inicio != NULL) {
		caminha = d->inicio;

		// novo inicio
		d->inicio = d->inicio->prox;
		if(d->inicio == NULL) //
			d->final = NULL;
		else
			d->inicio->ant = NULL;

		evento = caminha->evento;

		free(caminha);
	}
	return evento;
}


static void novoAgenda(TAgenda *agenda, void *evNovo){
	TElemento *novo, *caminha;
	TDadoAgenda *d = agenda->dado;

	int achou=0;

	novo = (TElemento *)malloc(sizeof(TElemento));

	novo->evento = evNovo;
	novo->prox = NULL;
	novo->ant = NULL;

	caminha = d->inicio;
	while( (caminha!=NULL) && (!achou) ){
		TComparavel *ev = caminha->evento;
		if (ev->compara(ev, evNovo)<=0){
			caminha = caminha->prox;
		}else
			achou=1;
	}
	if(d->inicio == NULL){ // fila vazia
		d->inicio = d->final = novo;
	}else if ( (achou) && (caminha->ant == NULL)){ // no inicio
		novo->prox = d->inicio;
		d->inicio->ant = novo;
		d->inicio = novo;
	}else if(achou){ // no meio
		novo->ant = caminha->ant;
		novo->prox = caminha;
		caminha->ant->prox = novo;
		caminha->ant = novo;
	}else{ // no final
		d->final->prox = novo;
		novo->ant = d->final;
		d->final = novo;
	}
}

short vaziaAgenda(TAgenda *a){
	TDadoAgenda *d = a->dado;
	return (d->inicio == NULL);
}

TAgenda *criarAgenda(){

	TAgenda *agenda;

	agenda = (TAgenda *)malloc(sizeof(TAgenda));

	agenda->dado = criarDadoAgenda();

	agenda->proximo = proximoAgenda;
	agenda->novo = novoAgenda;
	agenda->vazia = vaziaAgenda;
	return agenda;

}

void destruirAgenda(TAgenda *a){
	free(a->dado);
	free(a);
}
/*
int main(){
    TEvento *evento;
    TAgenda *agenda;
    int i;

    agenda = criarAgenda();

    for(i=10;i>1;i--){
        evento = criarEvento(2,(float)10+i);
        agenda->novo(agenda, evento);
    }

    evento = criarEvento(3,(float)17);
    agenda->novo(agenda, evento);

    evento = criarEvento(2,(float)100);
    agenda->novo(agenda, evento);
    for(i=12;i>1;i--){
    		evento = agenda->proximo(agenda);
		printf("%lf %d\n", evento->getTempo(evento), evento->getTipo(evento));
    }

    return 0;
}
*/
