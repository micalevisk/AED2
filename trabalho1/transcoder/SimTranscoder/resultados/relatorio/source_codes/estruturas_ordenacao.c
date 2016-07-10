/* === [ordenacaoCompleta.c] === */
#include "ordenacaoFila.h"
#include <stdlib.h>

typedef struct{
  TArrayDinamico *vetorFila;
  int posPrimeiro;
  int posUltimo;

}TDadoTAD;

/* === [ordencaoParcial.c] === */
#include "ordenacaoFila.h"
#include <stdlib.h>

#define PAI(i) (((i)-1)/2)

typedef struct{
  TArrayDinamico *vetorFila;
  int ocupacao;

}TDadoTAD;
