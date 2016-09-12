//
//  [indiceRemissivo.c]
//  Created by Micael Levi on 08/11/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "indiceRemissivo.h"


// retorna 0 se forem o mesmo elemento ou 1 caso o contrario
static short cmpElementosIndice(void* a, void* b){
  TElementoIndice* A = a;
  TElementoIndice* B = b;
  return compararPalavras(A->palavra, B->palavra);
}


static void funcImprimir(void* elemento){
	if(!elemento) return;
	else{
		unsigned* E = elemento;
		printf("%u", *E);
	}
}


TDicionarioDinamico* gerarIndiceRemissivo(const char* path_livro){
  char* arqInfo = preProcessar(path_livro);
  if(!arqInfo){ perror("\a"); return NULL; }
  TDicionarioDinamico* indiceRemissivo = criarDicionarioDinamico(TAMANHO_TABELA, converterParaNumero, cmpElementosIndice);
  FILE* fd_arqInfo = fopen(arqInfo, "r"); if(!fd_arqInfo) return NULL;

  unsigned pagCorrente=0;
  float tfidfCorrente=0;
  char* palavraCorrente;
  TElementoIndice* elementoBuscado;

  // Dada uma palavra PALAVRA, o número da página PAG em que ela aparece e o seu tf-idf T,
  // o arquivo com as informações possui todas as ocorrências de PALAVRA com a sua PAG e seu T (chave de ordenação)
  // A leitura deve ser feita linha por linha (ou palavra por palavra)
  // A cada dado lido, a inserção da palavra (com a página em que ocorre) deve ser efetivada somente se a página lida não estiver no vetor de páginas dessa palavra.
  for(palavraCorrente=ALOCAR_PALAVRA; (fscanf(fd_arqInfo, "%u:%f:%s", &pagCorrente, &tfidfCorrente, palavraCorrente ))!=EOF; palavraCorrente=ALOCAR_PALAVRA){
    TElementoIndice* elementoCorrente = malloc(sizeof(TElementoIndice));
    elementoCorrente->palavra = palavraCorrente; elementoCorrente->vetorPaginas = NULL;

    elementoBuscado = indiceRemissivo->buscar(indiceRemissivo, elementoCorrente);

    if(!elementoBuscado){
      elementoCorrente->vetorPaginas = criarVetorDinamico(5);
      elementoBuscado = elementoCorrente;
      indiceRemissivo->inserir(indiceRemissivo, elementoBuscado);
    }
    TVetorDinamico* v = elementoBuscado->vetorPaginas;

    unsigned posInsercao = v->ocupacao(v);
    if(posInsercao < 5){
      unsigned* pPagCorrente = malloc(sizeof(unsigned)); *pPagCorrente = pagCorrente;
      v->inserir(v, posInsercao, pPagCorrente);
    }
  }

  fclose(fd_arqInfo);
  removerArquivoDir(arqInfo);
  // system(CMD_APAGAR_INFOS);

  return indiceRemissivo;
}


void imprimirElementosDoVetor(TVetorDinamico* v){
  if(!v) return;
  v->imprimir(v, funcImprimir);
}
