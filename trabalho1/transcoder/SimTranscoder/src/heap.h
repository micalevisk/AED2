// heap.h
// Created by Micael Levi on 07/05/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.


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
