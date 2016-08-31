#ifndef VETORDINAMICO_H
#define VETORDINAMICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct vetorDinamico TVetorDinamico;

typedef void      (*TAtualizarVetorDinamico)(TVetorDinamico*,unsigned,void*);
typedef void*     (*TAcessarVetorDinamico)(TVetorDinamico*,unsigned);
typedef unsigned  (*TOcupacaoVetorDinamico)(TVetorDinamico*);
typedef unsigned  (*TTamanhoVetorDinamico)(TVetorDinamico*);
typedef void      (*TImprimirVetorDinamico)(TVetorDinamico*, void (*imprimir)(void*));

struct vetorDinamico{
	void* dado;

	TAcessarVetorDinamico elemento;   // retorna o elemento da posição passada
	TAtualizarVetorDinamico inserir;  // atualiza o elemento da posição passada
	TTamanhoVetorDinamico tamanho;    // retorna o tamanho do vetor
  TOcupacaoVetorDinamico ocupacao;  // retorna o número de elementos
  TImprimirVetorDinamico imprimir;

  void (*percorrer)(TVetorDinamico*, void (*func)(void*));
	void* (*buscar)(TVetorDinamico* v, void* chave, short (*cmp)(void* key, void*));
};

TVetorDinamico* criarVetorDinamico(unsigned);

void destruirVetorDinamico(TVetorDinamico*);


#endif
