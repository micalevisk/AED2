//
// [ordenacaoFila.h]
//
// Created by Micael Levi on 07/08/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#define PRECISAOSTATS unsigned long long

typedef struct TADManipulacaoFila TTAD;

typedef short (*TEnfileirarTAD)(TTAD*,void*);
typedef void* (*TDesenfileirarTAD)(TTAD*);

struct TADManipulacaoFila{
  // TArrayDinamico *vetorFila;  // cada elemento possuirá uma função de comparação associada.
  void *dado;                 // define os dados necessários para a ordenação

  // estatísticas de movimentações.
  PRECISAOSTATS movimentacoes_enfileirar;
  PRECISAOSTATS movimentacoes_desenfileirar;

  // MÉTODOS:
  TEnfileirarTAD enfileirar;
  TDesenfileirarTAD desenfileirar;

};

TTAD* construirTAD(void);  // cria o vetor circular dinâmico e define o tipo de ordenacao.
void  destruirTAD(TTAD*); // libera a fila alocada e a estrutura acima.

/*
cada elemento da fila deve possuir um método "compara"

*/
