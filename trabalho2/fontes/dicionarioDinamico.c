//
//	[dicionarioDinamico.c]
//	Created by Victor Meireles on 08/12/2016
//	Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "dicionarioDinamico.h"
#define REL_AUREA 0.61803399

typedef struct{
	double fatorCarga; // = N/M
	double fatorAgrupamento;
}TStats;

typedef struct{
	TVetorDinamico* vetor;

	unsigned tamanho;
	TStats* stats;
}TDado;


/* ============= [ AUXILIARES ] ============ */
/*
static int hash(void* elem, unsigned m, TKEY (*func)(void*)){
	TKEY k = func(elem); //gera a chave a partir do elemento

	return k % m;
}
*/

static int hash(void* elem, unsigned m, TConversaoParaChave func){
	TKEY k = func(elem); //gera a chave a partir do elemento
	return floor(m*(k*REL_AUREA - floor(k*REL_AUREA)));
}

/* ====== [ IMPLEMENTAÇÃO DOS MÉTODOS ] ====== */

static void _inserirDicionario(TDicionarioDinamico* dd,void* elem){
	if(!elem) return;
	TDado* d = dd->dado;

	unsigned pos = hash(elem,d->tamanho,dd->converteParaChave);

	TVetorDinamico* v = d->vetor;
	TLista* lista = v->elemento(v,pos);
	if(!lista){
		lista = criarListaEncadeada();
		v->inserir(v, pos, lista);
	}
	lista->inserir(lista,elem);
	++(dd->ocupacao);

	// printf("INSERIU na posicao %u do dicionario\n", pos);
}

static void* _removerDicionario(TDicionarioDinamico* dd, void* elem){
	if(!elem) return NULL;
	TDado* d = dd->dado;
	if(!d) return NULL;

	int pos = hash(elem,d->tamanho,dd->converteParaChave);

	TVetorDinamico* v = d->vetor;
	TLista* lista;
	if( (lista = v->elemento(v,pos)) ){
		lista->remover(lista,elem, dd->compararElementos);
		--(dd->ocupacao);
		// printf("REMOVEU\n");
	}
	// else printf("NAO REMOVEU\n");

	return elem;
}

static void* _buscarDicionario(TDicionarioDinamico* dd, void* elem){
	if(!elem) return NULL;
	TDado* d = dd->dado;
	if(!d) return NULL;

	unsigned pos = hash(elem,d->tamanho,dd->converteParaChave);

	TVetorDinamico* v = d->vetor;
	TLista* lista = v->elemento(v,pos);
	if(!lista) return NULL;
	return lista->buscar(lista,elem,dd->compararElementos); // elemento guardado no nó da lista
}


static void _percorrerDicionario(TDicionarioDinamico* dd, void (*func)(void*)){
	TDado* d = dd->dado;
	if(!d) return;
	unsigned i, tam = d->tamanho;

	TVetorDinamico* v = d->vetor;
	if(!v) return;
	for(i=0; i < tam; ++i){
		TLista* lista = v->elemento(v,i);
		if(lista) lista->percorrer(lista,func);
	}
}

/* ========================================================== */

TDado* criarDado(unsigned tam){
	unsigned i;
	TDado* d = malloc(sizeof(TDado));
	TStats* s = malloc(sizeof(TStats));
	TVetorDinamico* vd = criarVetorDinamico(tam);

	s->fatorAgrupamento = 0.0;
	s->fatorCarga = 0.0;

	d->vetor = vd;
	d->tamanho = tam;
	d->stats = s;

	return d;
}

TDicionarioDinamico* criarDicionarioDinamico(unsigned tam, TConversaoParaChave key, TComparacao compararElementos){
	TDicionarioDinamico* dd = malloc(sizeof(TDicionarioDinamico));
	TDado* d = criarDado(tam);
	dd->ocupacao = 0;
	dd->dado = d;
	dd->inserir = _inserirDicionario;
	dd->remover = _removerDicionario;
	dd->buscar = _buscarDicionario;
	dd->percorrer = _percorrerDicionario;

	dd->converteParaChave = key;
	dd->compararElementos = compararElementos;

	return dd;
}

void destruirDicionarioDinamico(TDicionarioDinamico* dd){
	if(!dd) return;
	TDado* d = dd->dado;
	destruirVetorDinamico(d->vetor);
	free(d);
	free(dd);
	dd = NULL;
}


/*=======================A FIM DE TESTES===============================*/

/*
typedef struct{
	//char* palavra;
	long int info;
}TDadoNo;

TKEY geraKey(void* da){
	return ((TDadoNo*)da)->info;
}

void imprimirDado(void* d){
	printf("%ld ", ((TDadoNo*)d)->info);
}

short compararElementos(void* d1, void* d2){
	TDadoNo* D1 = d1;
	TDadoNo* D2 = d2;
	if(!d1 || !d2) return 2;

	if(D1->info > D2->info) return 1;
	else if(D1->info < D2->info) return -1;
	else return 0;
}


int main(int argc, char const *argv[]) {
	TDadoNo x = {15};
	TDadoNo a = {14};
	TDadoNo y = {13};
	TDadoNo z = {15};

	TDadoNo* novox = &x;
	TDadoNo* novoa = &a;
	TDadoNo* novoy = &y;
	TDadoNo* novoz = &z;

	TDicionarioDinamico* dicionario = criarDicionarioDinamico(2,geraKey);

	dicionario->inserir(dicionario,novoz);
	dicionario->inserir(dicionario,novox);
	dicionario->inserir(dicionario,novoa);
	dicionario->inserir(dicionario,novoy);

	_percorrerDicionario(dicionario,imprimirDado);
	//if(dicionario->buscar(dicionario,novox,compararElementos)) printf("encontrei\n");
	printf("==============================\n");
	//dicionario->buscar(dicionario,novoa,compararElementos);
	dicionario->remover(dicionario,novoy,compararElementos) ;
	_percorrerDicionario(dicionario,imprimirDado);

	return 0;
}
*/
