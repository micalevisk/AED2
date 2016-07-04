/*
 * fila.h
 *
 *  Created on: 30/05/2016
 *      Author: cesar
 */

#ifndef FILA_H_
#define FILA_H_

#include "comparavel.h"

typedef struct fila TFila;

// declaração dos tipos Função/Método
typedef short (*TEnfileirar)(TFila*,void*);
typedef void* (*TDesenfileirar)(TFila*);
typedef short (*TVazia)(TFila*);
typedef void (*TAnalytics)(TFila*);

//construtor
TFila *criarFila();

//destrutor
void destruirFila(TFila*);

//tipo abstrato de dados
struct fila{
	/// dados, que são privados
	void *dado;

	// Operações sobre o dado
	TEnfileirar enfileirar;
	TDesenfileirar desenfileirar;
	TVazia vazia;
	TAnalytics analytics;
};
void percorrer(TFila*, void (*)(void*));
#endif /* FILA_H_ */
