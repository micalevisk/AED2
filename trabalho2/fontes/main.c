//
//  [main.c]
//  Created by Micael & Victor on 08/27/2016
//  Copyright (c) 2016 {mllc, wmr1}@icomp.ufam.edu.br; All rights reserved.
//

// USO:
// (na pasta que cotém o arquivo "makefile") !!!!!!!!!!!
// - COMPILAR: basta executar o comando 'make' na linha de comandos.
//
// - EXECUTAR: $ ./criarIndiceRemissivo [caminho do livro] < [caminho do arquivo de consultas] 2>&-
// - e.g.: $ ./criarIndiceRemissivo "base/baseAventuras" "arquivoConsultas"
//
// - EXECUTAR: $ ./criarIndiceRemissivo [caminho do livro]
// - e.g.: $ ./criarIndiceRemissivo "base/baseAventuras"

// COMPILAR SEM MAKEFILE:
// - COMPILAR: $ gcc -I fontes/headers -o criarIndiceRemissivo fontes/*.c -lm

#include "main.h"

char* str2lower(char* s){
  char* tmp = s;

  for(; *tmp; ++tmp)
    *tmp = tolower((unsigned char) *tmp);

  return s;
}

int main(int argc, char **argv)
{
  if(argc < N_ARGS) MSG_USO;
  TDicionarioDinamico* indiceRemissivo = gerarIndiceRemissivo(LIVRO);
  if(!indiceRemissivo){ fprintf(stderr,"ERRO AO GERAR O INDICE REMISSIVO\n"); exit(1); }

  char* palavraLida = ALOCAR_PALAVRA;

  fprintf(stderr,"PALAVRA: ");
  while( fscanf(stdin, "%60s", palavraLida)!=EOF ){
    palavraLida = str2lower(palavraLida);
    TElementoIndice elementoBuscado_aux = { .palavra = palavraLida };
    TElementoIndice* elementoBuscado = indiceRemissivo->buscar(indiceRemissivo, &elementoBuscado_aux);
    if(!elementoBuscado) printf("\"%s\" NAO ESTAH NESSE DOCUMENTO\n", palavraLida);
    else{
      printf("\"%s\": ", palavraLida);
      imprimirElementosDoVetor(elementoBuscado->vetorPaginas);
      printf("\n");
    }
    fprintf(stderr,"\nPALAVRA: ");
  }



  return 0;
}
