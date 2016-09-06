//
//  [main.c]
//  Created by Micael & Victor on 08/27/2016
//  Copyright (c) 2016 {mllc, wmr1}@icomp.ufam.edu.br; All rights reserved.
//

// USO:
// (na pasta "trabalho2") !!!!!!!!!!!
// - COMPILAR: basta executar 'make' na linha de comandos
// - EXECUTAR: $ ./criarIndiceRemissivo [caminho do livro] [caminho do arquivo de consultas]
// - e.g.: $ ./criarIndiceRemissivo "base/baseAventuras" "arquivoConsultas"


// COMPILAR SEM MAKEFILE:
// (na pasta "trabalho2") !!!!!!!!!!!
// - COMPILAR: $ gcc -o criarIndiceRemissivo fontes/*.c -lm

#include "main.h"

int main(int argc, char **argv)
{
  if(argc != N_ARGS) MSG_USO;
  TDicionarioDinamico* indiceRemissivo = gerarIndiceRemissivo(LIVRO);
  if(!indiceRemissivo){ printf("ERRO AO GERAR O INDICE REMISSIVO\n"); exit(1); }

  FILE* fd_consultas = fopen(PALAVRAS_CONSULTA, "r"); if(!fd_consultas){ perror("AO ABRIR O ARQUIVO DE CONSULTAS"); return 1; }
  char* palavraLida = ALOCAR_PALAVRA;

  while( (fscanf(fd_consultas, "%s", palavraLida))!=EOF ){
    strlwr(palavraLida);
    TElementoIndice elementoBuscado_aux = { .palavra = palavraLida };
    TElementoIndice* elementoBuscado = indiceRemissivo->buscar(indiceRemissivo, &elementoBuscado_aux);
    if(!elementoBuscado) printf("\"%s\" NAO ESTAH NESSE DOCUMENTO\n", palavraLida);
    else{
      printf("\"%s\": ", palavraLida);
      imprimirElementosDoVetor(elementoBuscado->vetorPaginas);
      printf("\n");
    }
  }

  return 0;
}
