/* === [ordenacaoCompleta.c] === */
// ...
static short _enfileirar(TTAD* t, void* elemento){
  TDadoTAD *d = t->dado;
  if(!elemento || !d) return 0;

  int posInsercao = d->posUltimo + 1, i;
  TArrayDinamico *vet = d->vetorFila;

  d->posUltimo = posInsercao;

  if(!posInsercao){
    d->posPrimeiro = posInsercao;
    vet->atualizar(vet, posInsercao, elemento);
  }
  else{
    unsigned tam = vet->tamanho(vet);
    if(posInsercao >= tam){
       ajustarAD(vet, tam * 2);
       t->sobrecarga++;
    }

    vet->atualizar(vet, posInsercao, elemento);

		for(i=posInsercao; (i > 0)
      && COMPARAR_PRIORIDADES(vet->acessar(vet, i-1), elemento); i--){
        vet->atualizar(vet, i, vet->acessar(vet, i-1));
        vet->atualizar(vet, i-1, elemento);
    }

    t->movimentacoes_enfileirar += posInsercao - i;
  }

  return 1;
}

// ...
static void* _desenfileirar(TTAD* t){
  TDadoTAD *d = t->dado;
  TArrayDinamico *vet = d->vetorFila;

  if(d->posUltimo < 0) return NULL;
  void* ultimoElemento = vet->acessar(vet, d->posUltimo);
  d->posUltimo--;

  return ultimoElemento;
}
