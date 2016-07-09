/*
 * fila.h
 *
 *  Created on: 30/05/2016
 *      Author: cesar
 */

typedef struct fila TFila;

// declaração dos tipos Função/Método
typedef short (*TEnfileirar)(TFila*,void*);
typedef void* (*TDesenfileirar)(TFila*);
typedef short (*TVazia)(TFila*);
typedef void (*TAnalytics)(TFila*);

TFila *construirFila();					// construtor.
void destruirFila(TFila*);	// destrutor.

// Tipo Abstrato de Dados.
struct fila{
	void *dado;	// dado privado.

	// Operações sobre o dado:
	TEnfileirar enfileirar;
	TDesenfileirar desenfileirar;
	TVazia vazia;
	TAnalytics analytics;
};

void percorrer(TFila*, void (*)(void*));
