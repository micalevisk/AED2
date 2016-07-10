/* === [ordenacaoParcial.c] === */

// ...
static short _enfileirar(TTAD* t, void* elemento){
  TDadoTAD *d = t->dado;
  if(!elemento || !d) return 0;

  int posInsercao = d->ocupacao, i;
  int posAncestral = PAI(posInsercao);
  void *elementoAncestral;

  TArrayDinamico *vet = d->vetorFila;
  unsigned tam = vet->tamanho(vet);

  if(posInsercao >= tam){
    ajustarAD(vet, tam * 2);
    t->sobrecarga++;
  }

  vet->atualizar(vet, posInsercao, elemento);
  d->ocupacao++;

  for(i=posInsercao; (i > 0)
    && COMPARAR_PRIORIDADES(elemento, vet->acessar(vet,posAncestral)); ){
      vet->atualizar(vet, i, vet->acessar(vet, posAncestral));
      vet->atualizar(vet, posAncestral, elemento);

      t->movimentacoes_enfileirar++;
      i = posAncestral;
      posAncestral = PAI(i);
  }

  return 1;
}

// ...
static void* _desenfileirar(TTAD* t){
  TDadoTAD *d = t->dado;
  int posUltimo = d->ocupacao - 1;
  void *raiz = NULL;
  TArrayDinamico *vet = d->vetorFila;

  if(posUltimo >= 0){
      raiz = vet->acessar(vet, 0);
      vet->atualizar(vet, 0, vet->acessar(vet, posUltimo));
      vet->atualizar(vet, posUltimo, raiz);

      t->movimentacoes_desenfileirar++;
      posUltimo = (--d->ocupacao) - 1;
      if(posUltimo > 0) ajustarHeap(t, 0, posUltimo);
  }

  return raiz;
}
