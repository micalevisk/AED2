#ifndef DICIONARIODINAMICO_H
#define DICIONARIODINAMICO_H


#include "listaEncadeada.h"
#include "vetorDinamico.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TKEY unsigned long

typedef struct dicionarioDinamico TDicionarioDinamico;

typedef void 	(*TInserirDD)(TDicionarioDinamico*,void*);
typedef void* (*TRemoverDD)(TDicionarioDinamico*,void*);
typedef void* (*TBuscarDD)(TDicionarioDinamico*,void*);
typedef void 	(*TPercorrer)(TDicionarioDinamico*,void (*)(void*));

typedef TKEY	(*TConversaoParaChave)(void*);
typedef short (*TComparacao)(void*,void*);

struct dicionarioDinamico{
	void* dado;
	unsigned ocupacao; // incrementado a cada inserção

	TInserirDD inserir;
	TRemoverDD remover;
	TBuscarDD buscar;
	TPercorrer percorrer;

	TConversaoParaChave converteParaChave;
	TComparacao compararElementos;
};

TDicionarioDinamico* criarDicionarioDinamico(unsigned, TConversaoParaChave, TComparacao);
//                                                     ^^^^^^^^ função que recebe o elemento inserido e retorna um valor associado;
void destruirDicionarioDinamico(TDicionarioDinamico*);


// // Ao encontrar o primeiro elemento não NULO no vetor dinâmico,
// // percorre-se a lista encadeada que esse elemento guadar
// // Assim, a cada consulta de um nó não nulo o N passado é decrementado de 1
// // Então, quando N for zero, foi encontrado o N-ésimo do dicionário
// void* buscarElementoPos(unsigned N,TDicionarioDinamico);

#endif
