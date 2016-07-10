#include "arrayDinamicoGenerico.h"

#include <stdlib.h>
#include <string.h>

typedef struct{
	void** vetor;
	unsigned tamanho;
}TDado;


void ajustarAD(TArrayDinamico* ad, unsigned novoTamanho){
	TDado* d = ad->dado;
	d->vetor = realloc(d->vetor, sizeof(void*) * novoTamanho);
	d->tamanho = novoTamanho;
}


/*--------------- IMPLEMENTAÇÃO DOS MÉTODOS -------------------------*/

// Insere em 'pos'; deve ser sempre válido!
static void _atualizar(TArrayDinamico* ad, int pos, void* elem){
	TDado* d = ad->dado;
	d->vetor[pos] = elem; // insere na posição passada.
}

// Retorna o elemento da posição 'pos'; deve ser sempre válido!
static void* _acessar(TArrayDinamico* ad, int pos){
	TDado* d = ad->dado;
	if(pos >= d->tamanho) return NULL;
	return d->vetor[pos];
}

// Retorna o número de elementos que estão no array.
static unsigned _tamanho(TArrayDinamico* ad){
	if(!ad) return 0;
	return ((TDado*)ad->dado)->tamanho;
}

/*-----------------------------------------------------------------*/

TDado* criaDadoAD(unsigned tamanho){
	TDado *d = malloc(sizeof(TDado));
	d->tamanho = tamanho;
	d->vetor = malloc(sizeof(void*) * tamanho);
	return d;
}


TArrayDinamico* construirAD(unsigned tamanho){
	TArrayDinamico* vetor = malloc(sizeof(TArrayDinamico));
	TDado* d = criaDadoAD(tamanho);

	vetor->dado = d;
	vetor->acessar	 = _acessar;
	vetor->atualizar = _atualizar;
	vetor->tamanho	 = _tamanho;
	return vetor;
}

void destruirAD(TArrayDinamico* ad){
	free(ad->dado);
	free(ad);
	ad=NULL;
}
