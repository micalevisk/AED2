/*
 * servico.c
 *
 *  Created on: 25/06/2016
 *      Author: cesar
 */
#include "fila.h"
#include "job.h"

#include "servico.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct {
  TFila *fila;
  int nroServidores;
  int nroOcupados;
}TDadoServico;

static TDadoServico *criarDado(int nroServidores){
	TDadoServico *d = malloc(sizeof(TDadoServico));

	d->nroOcupados=0;
	d->nroServidores = nroServidores;
	d->fila = construirFila();

	return d;
}



void* saidaServico(TServico* oServico){
  //retirar servico da fila

  TDadoServico *d = oServico->dado;

  TFila *f = d->fila;

  // void* demanda = f->desenfileirar(f);
  return f->desenfileirar(f);
}

void chegadaServico(TServico* oServico, void *demanda){
  //colocar servico na fila
  TDadoServico *d = oServico->dado;

  TFila *f = d->fila;
  f->enfileirar(f, demanda);
}

void runTranscodingServico(TServico *oServico, void *v ){
	TDadoServico *d = oServico->dado;

	d->nroOcupados++;

	TJob *_v = v;
	_v->setTempoTranscoding(_v,_v->getDuracao(_v));
}

void stopTranscodingServico(TServico *oServico){
	TDadoServico *d = oServico->dado;

	d->nroOcupados--;

}

static void estatisticaServico(TServico *oServico){
  TDadoServico *d = oServico->dado;
  TFila *f = d->fila;

  f->analytics(f);
}


static short ociosoServico(TServico *oServico){
	TDadoServico *d = oServico->dado;
	return (d->nroOcupados < d->nroServidores);
}

TServico* criarServico(int nroServidores){
  TServico* servico;

  servico = (TServico *) malloc(sizeof(TServico));

  servico->dado = criarDado(nroServidores);
  servico->chegada = chegadaServico;
  servico->analytics = estatisticaServico;
  servico->saida = saidaServico;
  servico->runTranscoding = runTranscodingServico;
  servico->stopTranscoding = stopTranscodingServico;
  servico->ocioso = ociosoServico;
  return servico;
}
