//
//  [contarOcorrencias.c]
//  Created by Micael Levi on 08/07/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "headers/contarOcorrencias.h"

// verifica se "word" é igual a "key". Retorna 0 se for ou 1 caso contrário.
short compararPalavras(const char* key, char* word){

  if(!key || !word) return 0;
  unsigned posUltimoKey = strlen(key)-1;
  unsigned posUltimoWord = strlen(word)-1;

  if( (!ispunct(word[posUltimoWord])) && (word[posUltimoWord] != key[posUltimoKey]) ) return 1;
  if(ispunct(word[posUltimoWord])) word[posUltimoWord] = '\0';
  return (strcmp(word, key) == 0 ? 0 : 1);
}


unsigned qtdOcorrenciasETotalExceto_arquivo(const char* path_arquivo, const char* chave, unsigned* totalDePalavras){
  FILE* arq = fopen(path_arquivo, "r");  if(!arq) return 0;
  unsigned ocorrencias=0, totalPalavras=0;
  char* formatacao = malloc( sizeof(char)*(MAX_N_CARACTERES_LINHA+strlen("%%s")) );
  sprintf(formatacao, "%%%us", MAX_N_CARACTERES_LINHA);

  char* palavraCorrente = malloc(sizeof(char)*MAX_N_CARACTERES_LINHA);

  while((fscanf(arq, formatacao, palavraCorrente)) == 1){
    if(!compararPalavras(chave, palavraCorrente)) ++ocorrencias;
    else ++totalPalavras;
  }

  fclose(arq);

  *totalDePalavras = totalPalavras;
  return ocorrencias;
}


/************************************************************/
/*

unsigned qtdOcorrencias_arquivo(const char* dir, const char* chave){
  FILE* arq = fopen(dir, "r");  if(!arq) return 0;
  unsigned ocorrencias=0;
  // unsigned tamChave = strlen(chave);
  // char* palavraCorrente = malloc(sizeof(char)*(tamChave+2));
  // char* formatacao = malloc(sizeof(char)*6);
  // sprintf(formatacao, "%%%us", tamChave+1);

  char* palavraCorrente = malloc(sizeof(char)*51);
  char* formatacao = "%51s";

  while((fscanf(arq, formatacao, palavraCorrente)) == 1)
    ocorrencias += !compararPalavras(chave, palavraCorrente);

  if(FECHAR_ARQUIVO) fclose(arq);

  return ocorrencias;
}

unsigned qtdOcorrenciasAte_arquivo(const char* delimitador, const char* dir, const char* chave){
  FILE* arq = fopen(dir, "r");  if(!arq) return 0;
  unsigned ocorrencias=0;
  // unsigned tamChave = strlen(chave);
  // char* palavraCorrente = malloc(sizeof(char)*(tamChave+2));
  // char* formatacao = malloc(sizeof(char)*6);
  // sprintf(formatacao, "%%%us", tamChave+1);
  char* palavraCorrente = malloc(sizeof(char)*51);
  char* formatacao = "%51s";


  while((fscanf(arq, formatacao, palavraCorrente)) == 1){
    // printf("%s\n", palavraCorrente);
    if(compararPalavras(delimitador, palavraCorrente)) break;
    ocorrencias += !compararPalavras(chave, palavraCorrente);
  }
  if(FECHAR_ARQUIVO) fclose(arq);

  return ocorrencias;
}


unsigned qtdOcorrencias_descritor(FILE* arq, const char* chave){
  if(!arq) return 0;
  rewind(arq);
  unsigned ocorrencias=0;

  // unsigned tamChave = strlen(chave);
  // char* palavraCorrente = malloc(sizeof(char)*(tamChave+2));
  // char* formatacao = malloc(sizeof(char)*6);
  // sprintf(formatacao, "%%%us", tamChave+1);
  char* palavraCorrente = malloc(sizeof(char)*51);
  char* formatacao = "%51s";

  while((fscanf(arq, formatacao, palavraCorrente)) == 1){
    // printf("%s\n", palavraCorrente);
    ocorrencias += !compararPalavras(chave, palavraCorrente);
  }
  if(FECHAR_ARQUIVO) fclose(arq);

  return ocorrencias;
}

unsigned qtdOcorrenciasAte_descritor(const char* delimitador, FILE* arq, const char* dir, const char* chave){
  if(!arq) return 0;
  rewind(arq);
  unsigned ocorrencias=0;

  // unsigned tamChave = strlen(chave);
  // char* palavraCorrente = malloc(sizeof(char)*(tamChave+2));
  // char* formatacao = malloc(sizeof(char)*6);
  // sprintf(formatacao, "%%%us", tamChave+1);
  char* palavraCorrente = malloc(sizeof(char)*51);
  char* formatacao = "%51s";

  while((fscanf(arq, formatacao, palavraCorrente)) == 1){
    // printf("%s\n", palavraCorrente);
    if(!compararPalavras(delimitador, palavraCorrente)) break;
    ocorrencias += !compararPalavras(chave, palavraCorrente);
  }
  if(FECHAR_ARQUIVO) fclose(arq);

  return ocorrencias;
}


unsigned contarPalavrasAte_arquivo(const char* delimitador, const char* dir){
  FILE* arq = fopen(dir, "r");  if(!arq) return 0;
  unsigned nPalavras=0;

  char* palavraCorrente = malloc(sizeof(char)*51);
  char* formatacao = "%51s";

  while((fscanf(arq, formatacao, palavraCorrente)) == 1){
    if(!compararPalavras(delimitador, palavraCorrente)) break;
    ++nPalavras;
  }
  if(FECHAR_ARQUIVO) fclose(arq);

  return nPalavras;
}

unsigned contarPalavrasAte_descritor(FILE* arq, const char* delimitador){
  if(!arq) return 0;
  rewind(arq);
  unsigned nPalavras=0;

  char* palavraCorrente = malloc(sizeof(char)*51);
  char* formatacao = "%51s";

  while((fscanf(arq, formatacao, palavraCorrente)) == 1){
    if(!compararPalavras(delimitador, palavraCorrente)) break;
    ++nPalavras;
  }
  if(FECHAR_ARQUIVO) fclose(arq);

  return nPalavras;
}


unsigned numeroDePaginasQuePossuem_arquivo(const char* chave, const char* id, const char* dir){
  FILE* arq = fopen(dir, "r");  if(!arq) return 0;
  unsigned nPaginas=0;
  char* palavraCorrente = malloc(sizeof(char)*51);
  char* formatacao = "%51s";
  char mesmaPag=0; // flag

  while((fscanf(arq, formatacao, palavraCorrente)) == 1){
    // printf("%s\n", palavraCorrente);
    if((!mesmaPag) && !compararPalavras(chave, palavraCorrente)){
      ++nPaginas;
      mesmaPag=1;
    }
    else if(!compararPalavras(id, palavraCorrente)) mesmaPag=0;

  }
  if(FECHAR_ARQUIVO) fclose(arq);

  return nPaginas;
}

unsigned numeroDePaginasQuePossuem_descritor(const char* chave, const char* id, FILE* arq){
  if(!arq) return 0;
  rewind(arq);
  unsigned nPaginas=0;
  char* palavraCorrente = malloc(sizeof(char)*51);
  char* formatacao = "%51s";
  char mesmaPag=0; // flag

  while((fscanf(arq, formatacao, palavraCorrente)) == 1){
    // printf("%s\n", palavraCorrente);
    if((!mesmaPag) && !compararPalavras(chave, palavraCorrente)){
      ++nPaginas;
      mesmaPag=1;
    }
    else if(!compararPalavras(id, palavraCorrente)) mesmaPag=0;

  }
  if(FECHAR_ARQUIVO) fclose(arq);

  return nPaginas;
}




void contarPalavrasExceto_arquivo(const char* excecao, const char* dir, unsigned* nPalavras, unsigned* nExcecao){
  FILE* arq = fopen(dir, "r");  if(!arq) return;
  unsigned bff_nPalavras=0;
  unsigned bff_nExcecao=0;

  // unsigned tamChave = strlen(chave);
  // char* palavraCorrente = malloc(sizeof(char)*(tamChave+2));
  // char* formatacao = malloc(sizeof(char)*6);
  // sprintf(formatacao, "%%%us", tamChave+1);
  char* palavraCorrente = malloc(sizeof(char)*51);
  char* formatacao = "%51s";

  while((fscanf(arq, formatacao, palavraCorrente)) == 1){
      if( !compararPalavras(excecao, palavraCorrente) ) ++bff_nExcecao;
      else ++bff_nPalavras;
  }
  if(FECHAR_ARQUIVO) fclose(arq);

  *nPalavras = bff_nPalavras;
  if(nExcecao) *nExcecao = bff_nExcecao;
}

*/


/*
int main(int argc, char** argv){
  if(argc != 3) return 1;
  unsigned total = 0;
  unsigned ocorrencias = qtdOcorrenciasETotal_arquivo(argv[2], argv[1], &total);
  printf("quantidade de vezes que \"%s\" aparece em \"%s\": %u\n(%u palavras lidas)\n", argv[1], argv[2], ocorrencias,total);

  // unsigned nPalavras, nExcecao;
  // contarPalavrasExceto_arquivo(argv[1], argv[2], &nPalavras, &nExcecao);
  // printf("quantidade de palavras em \"%s\": %u\n", argv[2], nPalavras);
  // printf("quantidade de exceções (\"%s\") : %u\n", argv[1], nExcecao);

  // unsigned nPalavras = contarPalavrasAte_arquivo(argv[1], argv[2]);
  // printf("quantidade de palavras em \"%s\" antes do primeiro \"%s\": %u\n", argv[2], argv[1], nPalavras);
  //
  // unsigned nPaginas = numeroDePaginasQuePossuem_arquivo(argv[1], "pa", argv[2]);
  // printf("quantidade de páginas em \"%s\" que possuem ao menos uma ocorrencia de \"%s\": %u\n", argv[2], argv[1], nPaginas);


  return 0;
}
*/
