// heap.h
// Created by Micael Levi on 07/05/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.


typedef struct fila TFila;

// declaração dos tipos Função/Método
typedef short (*TEnfileirar)(TFila*,void*);
typedef void* (*TDesenfileirar)(TFila*);
typedef short (*TVazia)(TFila*);
typedef void (*TAnalytics)(TFila*);

TFila *criarFila();
void destruirFila(TFila*);

//tipo abstrato de dados
struct fila{
	void *dado;

	// métodos
	TEnfileirar enfileirar;
	TDesenfileirar desenfileirar;
	TVazia vazia;
	TAnalytics analytics;
};
void percorrer(TFila*, void (*)(void*));
