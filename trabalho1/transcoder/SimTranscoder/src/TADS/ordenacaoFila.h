//
// [ordenacaoFila.h]
//
// Created by Micael Levi on 07/08/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "arrayDinamicoGenerico.h"
#include "../comparavel.h"

#define PRECISAOSTATS unsigned long long
#define TAM 10  // tamanho inicial da fila (vetor)

// A prioridade de 'a' é maior que a de 'b' ?
#define COMPARAR_PRIORIDADES(a,b) (comparar((a), (b)) > 0)

typedef struct TADManipulacaoFila TTAD;

typedef short (*TEnfileirarTAD)(TTAD*,void*);
typedef void* (*TDesenfileirarTAD)(TTAD*);

struct TADManipulacaoFila{
  void *dado;

  // MÉTODOS:
  TEnfileirarTAD enfileirar;
  TDesenfileirarTAD desenfileirar;

  // ESTATÍSTICAS:
  PRECISAOSTATS movimentacoes_enfileirar;
  PRECISAOSTATS movimentacoes_desenfileirar;
  PRECISAOSTATS sobrecarga;
};

TTAD* construirTAD(void);  // cria o vetor circular dinâmico e define o tipo de ordenacao.
void  destruirTAD(TTAD*); // libera a fila alocada e a estrutura acima.

/*
cada elemento da fila deve possuir um método "compara"

*/
