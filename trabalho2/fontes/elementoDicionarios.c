//
//  [elementoDicionarios.c]
//  Created by Micael Levi on 08/12/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//


#include "elementoDicionarios.h"

// retorna 0 se forem a mesma palavra ou 1 caso contrário
short cmpElementos(void* a, void* b){
  if(!a || !b) return 1;
  TElemento* A = a;
  TElemento* B = b;
  return compararPalavras(A->palavra, B->palavra);
}
