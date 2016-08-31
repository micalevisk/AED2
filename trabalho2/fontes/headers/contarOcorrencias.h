#ifndef CONTAROCORRENCIAS_H
#define CONTAROCORRENCIAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_N_CARACTERES_LINHA 61 // = número maximo de caraceters numa linha + 1


// verifica se "word" é igual a "key". Retorna 1 se for e 0 caso contrário.
short compararPalavras(const char* key, char* word);

// retorna o número de ocorrências de 'chave' no arquivo 'path_arquivo' e computa o total (de palavras) lidas em 'totalDePalavras'
unsigned qtdOcorrenciasETotalExceto_arquivo(const char* path_arquivo, const char* chave, unsigned* totalDePalavras);


/**********************************************************************************************************************/
/*
#define FECHAR_ARQUIVO 1 // (0=false) executar fclose no arquivo que foi aberto / descritor já aberto.
// retorna o número de ocorrências de uma palavra em um arquivo texto.
unsigned qtdOcorrencias_arquivo(const char* dir, const char* chave);
// conta as ocorrências até encontrar o delimitador ou fim do arquivo;
unsigned qtdOcorrenciasAte_arquivo(const char* delimitador, const char* dir, const char* chave);


// (descritor de arquivo aberto para leitura)
unsigned qtdOcorrencias_descritor(FILE* arq, const char* chave);
unsigned qtdOcorrenciasAte_descritor(const char* delimitador, FILE* arq, const char* dir, const char* chave);

// verifica cada palavra (podendo ser letra, etc), [pode ser usada para contar todas as palavras, fazendo nExcecao = NULL]
// se for igual a "excecao" então incrementa no segundo contador (nExcecao) <<<<< será zerado no início
// se for qualquer outra diferente de "excecao" então incrementa no primeiro contador (nPalavras) <<<<< será zerado no início.
void contarPalavrasExceto_arquivo(const char* excecao, const char* dir, unsigned* nPalavras, unsigned* nExcecao);

// Percorre de palavra em palavra e incrementa um contador caso a palavra não seja o "delimitador", se for, para a contagem.
unsigned contarPalavrasAte_arquivo(const char* delimitador, const char* dir);
unsigned contarPalavrasAte_descritor(FILE* arq, const char* delimitador);

// Pecorre de palavra em palavra verificando se é igual a chave e só conta uma por página ("id" identifica início de página)
unsigned numeroDePaginasQuePossuem_arquivo(const char* chave, const char* id, const char* dir);
unsigned numeroDePaginasQuePossuem_descritor(const char* chave, const char* id, FILE* arq);
*/



#endif
