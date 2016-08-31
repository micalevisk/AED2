//
//	[listaEncadeada.c]
//	Created by Victor Meireles on 08/07/2016
//	Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "headers/listaEncadeada.h"


struct no{
	void* d; // no dicionário dinâmico: {char* chave, unsigned info}
	tipoNo* prox;
};

static tipoNo* criarNo(void* elem){

	tipoNo* no = (tipoNo*) malloc(sizeof(tipoNo));

	no->d = elem;
	no->prox = NULL;

	return no;
}

static void _inserir(TLista* le, void* elem){
	tipoNo* novoNo = criarNo(elem);


	novoNo->prox = le->prim;
	le->prim = novoNo;
}

static void _remover(TLista* le, void* elem, short (*cmp)(void*,void*)){
	tipoNo* aux = le->prim;
	tipoNo* aux_ant = NULL;

	while(aux){
		if(!cmp(elem,aux->d)){
			if(!aux_ant) le->prim = aux->prox;
			else aux_ant->prox = aux->prox;

			free(aux);
			return;
		}
		aux_ant = aux;
		aux = aux->prox;
	}
}

static void* _buscar(TLista* le, void* elem, short (*cmp)(void*,void*)){
	tipoNo* aux = le->prim;

	while(aux){
		if(cmp(elem,aux->d)==0) return aux->d;
		aux = aux->prox;
	}

	return NULL;
}

static void _percorrer(TLista* le, void (*func)(void*)){
	tipoNo* aux = le->prim;

	while(aux){
		func(aux->d);
		aux = aux->prox;
	}
}

TLista* criarListaEncadeada(){
	TLista* lista = malloc(sizeof(TLista));

	lista->prim = NULL;

	lista->inserir = _inserir;
	lista->remover = _remover;
	lista->buscar = _buscar;
	lista->percorrer = _percorrer;

	return lista;
}

void destroirListaEnc(TLista* le){
	tipoNo* aux = le->prim;
	tipoNo* aux_prox = aux->prox;

	while(aux){
		free(aux);
		aux = aux_prox;
		aux_prox = aux_prox ? aux_prox->prox : NULL;
	}

	free(le);
}


// ============================================================================
/*
typedef struct{
	char* palavra;
	unsigned info;
}TDadoNo;

void imprimirDado(void* d){
	printf("%s:%u\n", ((TDadoNo*)d)->palavra, ((TDadoNo*)d)->info);
}

short compararPalavrasNo(void* d1, void* d2){
	TDadoNo* D1 = d1;
	TDadoNo* D2 = d2;
	return strcmp(D1->palavra, D2->palavra);
}

int main(int argc, char const *argv[]) {

	TLista* lista = criarListaEncadeada();
//
	TDadoNo x = {"joao", 12};
	TDadoNo* novo = &x;
	if(!(lista->buscar(lista, novo, compararPalavrasNo))){ // palavra não existe;
		lista->inserir(lista, novo);
	}
	++(novo->info);

	lista->percorrer(lista, imprimirDado);
	return 0;
}
*/
