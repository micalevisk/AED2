//
//  [preProcesso.c]
//  Created by Micael Levi on 08/11/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "preProcesso.h"
#define LOG(msg) fprintf(stderr, "[%s]\n", msg);


// [3] CRIAR/CONSTRUIR ARQUIVO COM INFORMAÇÕES AS INFORMAÇÕES NECESSÁRIAS PARA O ÍNDICE REMISSIVO
char* preProcessar(const char* path_doc){
  if(!path_doc) return NULL;
  TDicionarioDinamico* dicionarioPalavras;
  TVetorDinamico* vetorPaginas;

  LOG("PRE-PROCESSANDO ARQUIVO TEXTO");

  // [0] para criar um arquivo com o texto tratado
  char* path_arquivoTratado = processarTexto(path_doc, DIRETORIO_SCRIPTTRATADOR, NOMEARQUIVO_SCRIPTTRATADOR);
  #ifdef ERROR
    if(!path_arquivoTratado) ERROR(1, "preProcesso", "preProcessar");
  #endif

  // abrir texto tratado que será usado no povoamento
  FILE* fd_arquivoTratado = fopen(path_arquivoTratado, "r"); if(!fd_arquivoTratado) return NULL;

  unsigned nPalavras=0;
  unsigned nPaginas = qtdOcorrenciasETotalExceto_arquivo(path_arquivoTratado, ID_PAG, &nPalavras); // número de páginas, i.e., ocorrências da string ID_PAG

  // [1]
  if( !(construirEstruturasInformativas(fd_arquivoTratado, &dicionarioPalavras, &vetorPaginas, nPalavras, nPaginas)) ){
    removerArquivoDir(path_arquivoTratado);
    return NULL;
  }

  char* path_arquivoInformacoes = criarArquivoTemporario("", MASK_ARQUIVO_INFO, PERMISSAO_LEITURA_ESCRITA);
  FILE* fd_arquivoInformacoes = fopen(path_arquivoInformacoes, "w");
  if(!fd_arquivoInformacoes){
    removerArquivoDir(path_arquivoTratado);
    return NULL;
  }

  // Processo de escrita de cada palavra (re)lida com as suas devidas informações (página e TF-IDF nessa página) no arquivo de informações (usado para gerar o índice remissivo).
  char* formatacao = (char*)malloc( sizeof(char)*(MAX_N_CARACTERES_LINHA+strlen("%%s")) );
  sprintf(formatacao, "%%%us", MAX_N_CARACTERES_LINHA);
  char* palavraCorrente;
  int indice;
  char novaPagina=0;
  TDicionarioDinamico* dVetorPaginasCorrente;

  rewind(fd_arquivoTratado);
  for(indice=-1, palavraCorrente=ALOCAR_PALAVRA; (fscanf(fd_arquivoTratado, formatacao, palavraCorrente))!=EOF; palavraCorrente=ALOCAR_PALAVRA){
    if(!compararPalavras(ID_PAG, palavraCorrente)){  // se for apenas um identificador de nova página
      ++indice;
      novaPagina=1;
      continue;
    }

    if(novaPagina){
      dVetorPaginasCorrente = vetorPaginas->elemento(vetorPaginas, indice); // obtendo o dicionário de palavras da página corrente.
      novaPagina = 0;
    }

    TElemento elementoCorrente_aux = { .palavra = palavraCorrente };
    TElemento* elementoCorrente = dVetorPaginasCorrente->buscar(dVetorPaginasCorrente, &elementoCorrente_aux);

    float tfidf_corrente = TFIDF(elementoCorrente, dicionarioPalavras, dVetorPaginasCorrente, vetorPaginas);
    fprintf(fd_arquivoInformacoes, "%u:%f:%s\n", indice+1, tfidf_corrente, palavraCorrente); // <página>:<TF-IDF>:<palavra>
  }

  fclose(fd_arquivoTratado);
  fclose(fd_arquivoInformacoes);
  removerArquivoDir(path_arquivoTratado);
  // system(CMD_APAGAR_TRATADOS);

  char* comandoParaOrdenarArquivoInfo = malloc(sizeof(char)*( strlen(ORDENAR_PELO_TFIDF)+strlen(path_arquivoInformacoes)*2+strlen(" -o ") ));
  strcpy(comandoParaOrdenarArquivoInfo, ORDENAR_PELO_TFIDF); strcat(comandoParaOrdenarArquivoInfo, path_arquivoInformacoes); strcat(comandoParaOrdenarArquivoInfo, " -o "); strcat(comandoParaOrdenarArquivoInfo, path_arquivoInformacoes);
  system(comandoParaOrdenarArquivoInfo);

  destruirDicionarioDinamico(dicionarioPalavras);


  LOG("ARQUIVO PRE-PROCESSADO COM SUCESSO!");


  return path_arquivoInformacoes;
}


/************************************************************/
/*
#define DIR_DOC "../base/baseAventuras"

int main(){

  char* path_arquivoInfo = preProcessar(DIR_DOC);
  printf("arquivo a ser lido: |%s| para a construção do índice\n", path_arquivoInfo);

  return 0;
}
*/
/*
printf("arquivo CRIADO: |%s|\n", path_arquivoTratado);
int i;
for(i=5; i > 0; --i){
  printf("%d\n", i);
  system("sleep 1");
}
removerArquivoDir(path_arquivoTratado);
printf("arquivo APAGADO\n");
*/
