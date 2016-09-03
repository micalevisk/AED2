#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct lista TLista;
typedef struct no tipoNo;

//insere e retorna um elemento no inicio:
typedef void (*TInserirListaEncadeada)(TLista*,void*);

//remove o elemento passado como parametro usando como comparador outra função:
typedef void (*TRemoverListaEncadeada)(TLista*,void*,short (*)(void*,void*));

//busca o elemento passado como parametro usando como comparador outra função:
typedef void* (*TBuscarListaEncadeada)(TLista*,void*,short (*)(void*,void*));

//percorre os elementos da lista encadeada:
typedef void (*TPercorrerListaEncadeada)(TLista*,void (*)(void*));


//TAD lista:
struct lista{
	tipoNo* prim;

	TInserirListaEncadeada inserir;
	TRemoverListaEncadeada remover;
	TBuscarListaEncadeada buscar;
	TPercorrerListaEncadeada percorrer;
};


//construtor:
TLista* criarListaEncadeada(void);

//destrutor:
void destruirListaEncadeada(TLista*);


#endif
