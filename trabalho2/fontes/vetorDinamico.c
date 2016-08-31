//
//	[vetorDinamico.c]
//	Created by Micael Levi on 08/11/2016
//	Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "headers/vetorDinamico.h"


typedef struct{
	void** vetor;
	unsigned ocupa;
	unsigned tamanho;
}TDadoVetorDinamico;


short ajustar(TVetorDinamico* v, unsigned novoTamanho, unsigned tamanhoInicial){
	TDadoVetorDinamico* dado = v->dado;
	// void* novoVetor = calloc(novoTamanho, sizeof(void*));
	// if(!novoVetor) return;
	// memcpy(novoVetor, dado->vetor, tamanhoInicial);
	// free(dado->vetor);
	// dado->tamanho = novoTamanho;
	// dado->vetor = novoVetor;

	void** aux = (void**)realloc(dado->vetor, sizeof(void*)*novoTamanho);
	if(!aux) return 0;
	dado->vetor = aux;
	dado->tamanho = novoTamanho;

	unsigned i;
	for(i=dado->ocupa; i < novoTamanho; ++i) dado->vetor[i] = NULL;


	return 1;
}



/* ======== [ IMPLEMENTAÇÃO DOS MÉTODOS ] ======== */

static unsigned _tamanhoVetorDinamico(TVetorDinamico* array){
		TDadoVetorDinamico* dado = array->dado;
		return dado->tamanho;
}


static void _inserirVetorDinamico(TVetorDinamico* v, unsigned pos, void* elem){
	TDadoVetorDinamico* dado = v->dado;
	unsigned N = dado->tamanho;

	if(pos >= N){
		int novoTam = pow( 2.0, ceil(log2(pos+1)) );
		if( !(ajustar(v,novoTam, N)) ) return;
	}
	if(dado->vetor[pos] == NULL) ++(dado->ocupa);
	dado->vetor[pos] = elem;
}


static void* _elementoVetorDinamico(TVetorDinamico* v, unsigned pos){
	TDadoVetorDinamico* dado = v->dado;
	if(!dado || !dado->vetor) return NULL;
	return dado->vetor[pos];
}


static unsigned _ocupacaoVetorDinamico(TVetorDinamico* v){
	TDadoVetorDinamico* dado = v->dado;
	if(!dado) return 0;
	return dado->ocupa;
}


static void _imprimirVetorDinamico(TVetorDinamico* v, void (*imprimir)(void*)){
	TDadoVetorDinamico* dado = v->dado;
	if(!dado) return;
	void** vetor = dado->vetor;
	unsigned i, n = dado->ocupa;
	for(i=0; i < n; ++i){  imprimir(vetor[i]); }
}


static void _percorrerVetorDinamico(TVetorDinamico* v, void (*acao)(void*)){
	TDadoVetorDinamico* dado = v->dado;
	if(!dado) return;
	void** vetor = dado->vetor;
	unsigned i, n = dado->ocupa;
	for(i=0; i < n; ++i) acao(vetor[i]);
}


static void* _buscarVetorDinamico(TVetorDinamico* v, void* chave, short (*cmp)(void*, void*)){
	TDadoVetorDinamico* dado = v->dado;
	if(!dado) return NULL;
	void** vetor = dado->vetor;
	unsigned i, n = dado->ocupa;
	for(i=0; i < n; ++i) if( !cmp(chave,vetor[i]) ) return vetor[i];
	return NULL;
}

/* ======== [ IMPLEMENTAÇÃO DAS FUNÇÕES PRINCIPAIS ] ======== */

static TDadoVetorDinamico* criaDadoAD(unsigned tam){
	TDadoVetorDinamico *dado = (TDadoVetorDinamico*) malloc(sizeof(TDadoVetorDinamico));
	dado->vetor = calloc(tam, sizeof(void*));
	dado->ocupa = 0;
	dado->tamanho = tam;
	return dado;
}


TVetorDinamico* criarVetorDinamico(unsigned tamanhoInicial){
	TVetorDinamico* vetor = (TVetorDinamico*) malloc(sizeof(TVetorDinamico));
	TDadoVetorDinamico* dado = criaDadoAD(tamanhoInicial);

	vetor->dado =(TDadoVetorDinamico*) dado;
	vetor->elemento = _elementoVetorDinamico;
	vetor->inserir = _inserirVetorDinamico;
	vetor->tamanho = _tamanhoVetorDinamico;
	vetor->ocupacao = _ocupacaoVetorDinamico;
	vetor->imprimir = _imprimirVetorDinamico;
	vetor->percorrer = _percorrerVetorDinamico;
	vetor->buscar = _buscarVetorDinamico;

	return vetor;
}


void destruirVetorDinamico(TVetorDinamico* v){
		if(!v) return;
		TDadoVetorDinamico* dado = v->dado;
		free(dado->vetor);
		free(dado);
		free(v);
		v = NULL;
}




/************************************************************/

/*
typedef struct louca{
	char id;
	int valor;
}TLouca;


void funcImprimir(void* elemento){
	if(!elemento) printf(" []\n");
	else{
		TLouca* E = elemento;
		printf(" %c_%d\n", E->id, E->valor);
	}
}

void funcTeste(void* elemento){
	if(!elemento) printf("[NULL]\n");
	else printf("[%p]\n", elemento);
}

int main(){

	TVetorDinamico* vet = criarVetorDinamico(2);
	vet->imprimir(vet, funcTeste);

	int i;
	char c;
	for(i=0, c='A'; i <= 4; ++i, ++c){
		TLouca* Aux = malloc(sizeof(TLouca));
		Aux->id = c;
		Aux->valor = i;
		vet->inserir(vet, i, Aux);
	}

	vet->imprimir(vet, funcImprimir);
	printf("ocupacao: %u\n\n", vet->ocupacao(vet));

	TLouca aux = {'a', 32};
	vet->inserir(vet, 0, &aux);
	vet->imprimir(vet, funcImprimir);
	printf("ocupacao: %u\n\n", vet->ocupacao(vet));

	vet->percorrer(vet, funcTeste);


	return 0;
}
*/

/*
void funcImprimir(void* elemento){
	if(!elemento) printf(" []\n");
	else{
		unsigned* E = elemento;
		printf(" %u\n", *E);
	}
}

int main(){
	TVetorDinamico* vet = criarVetorDinamico(5);
	vet->imprimir(vet, funcImprimir);

	unsigned c;
	short i;
	for(i=0, c=1; i < 5; ++i, ++c){
		unsigned* Aux = malloc(sizeof(unsigned));
		*Aux = c;
		vet->inserir(vet, i, Aux);
	}

	vet->imprimir(vet, funcImprimir);
	printf("ocupacao: %u\n\n", vet->ocupacao(vet));

}
*/
