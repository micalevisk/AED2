//
//  [indiceRemissivo.c]
//  Created by Micael Levi on 08/11/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

// #define ERROR(number, fileBaseName, functionName){ fprintf(stderr, "\e[1;49;3%hhum" "ERRO%hhu: %s.c => %s()" "\e[0m\n", number, number, fileBaseName, functionName); exit(3); }
#include "headers/indiceRemissivo.h"


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
		printf("%u, ", *E);
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
      // printf("%s|%u\n", elementoBuscado->palavra, *pPagCorrente);
      // fprintf(stderr,"%u\n", v->ocupacao(v) );
    }
  }

  fclose(fd_arqInfo);
  removerArquivoDir(arqInfo);
  // system(CMD_APAGAR_INFOS);

  #ifdef ERROR
    // printf("ocupacao do indice remissivo: %u\n", indiceRemissivo->ocupacao);
    // printf("ULTIMO: %s|%u\n", elementoBuscado->palavra, pagCorrente);
    TElementoIndice* buscado = indiceRemissivo->buscar(indiceRemissivo, elementoBuscado);
    TVetorDinamico* vBuscado = buscado->vetorPaginas;
    printf("BUSCADO: %s\nRETORNO: %s\n", elementoBuscado->palavra, buscado->palavra);
    if(vBuscado == NULL) printf("O VETOR DE PÁGINAS NÃO EXISTE\n");
    else{
      vBuscado->imprimir(vBuscado, funcImprimir);
      printf("end. do primeiro elemento: (%p)\n",  vBuscado->elemento(vBuscado, 0));
      printf("=======================\n");
    }
  #endif

  return indiceRemissivo;
}


void imprimirElementosDoVetor(TVetorDinamico* v){
  if(!v) return;
  v->imprimir(v, funcImprimir);
}


/************************************************************/

/*
#define DIR_DOC "../base/baseAventuras"
int main(int argc, char** argv){
  TDicionarioDinamico* indice = gerarIndiceRemissivo(DIR_DOC);

  TElementoIndice elementoBuscado_aux = { .palavra = argv[1] };
  TElementoIndice* elementoBuscado = indice->buscar(indice, &elementoBuscado_aux);

  if(!elementoBuscado) printf("\"%s\" NAO ESTA NESSE DOCUMENTO\n", argv[1]);
  else{
    printf("%s: ", elementoBuscado->palavra);
    imprimirElementosDoVetor(elementoBuscado->vetorPaginas);
    printf("\n");
  }


  #ifdef ERROR
    printf("NUMERO DE PALAVRAS (sem repetições) = ocupacao do indice remissivo: %u\n", indice->ocupacao);
    if(!elementoBuscado){
      ERROR(1, "indiceRemissivo", "main");
    }else{
      printf("PALAVRA:\n(%s):", elementoBuscado->palavra);
      imprimirElementosDoVetor(elementoBuscado->vetorPaginas);
      TVetorDinamico* vBuscado = elementoBuscado->vetorPaginas;
      // printf("end. do primeiro elemento: (%p)\n", vBuscado->elemento(vBuscado, 0));
      printf("\n\n");
    }
  #endif
}
*/
