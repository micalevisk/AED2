#ifndef CALCULARTFIDF_H
#define CALCULARTFIDF_H


#include "contarOcorrencias.h"
#include "dicionarioDinamico.h"
#include "elementoDicionarios.h"
#include "vetorDinamico.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* *********************************[ EXPLICAÇÃO DO MÉTODO ]*****************************************
TF-IDF = "Term Frequency, Inverse Document Frequency"
uma maneira de pontuar a importância de palavras (ou "termos") em um
documento baseado em quão frequente ele aparece em diversos documentos.

- Se uma palavra aparece frequentemente em um documento, ela é importante = pontuação alta.
- Mas se a palavra aparece em muitos documentos, elá não é um identificador único = pontuação baixa.
***************************************************************************************************** */

/************************************************************/
// DADA UMA PALAVRA P, UMA PÁGINA DOC E UM LIVRO DOCS,
// - número de DOC's que possuem P                    [x]
// - quantidade de vezes que P aparece em cada DOC    [x]
// - número de palavras de cada DOC                   [x]
// - número total de DOC's em DOCS                    [x]
/************************************************************/


// n_containing(palavra, docs)
// retorna o número de doc's que contém a palavra.
// [2.1] Para Calcular a Quantidade de Páginas que Possuem uma Palavra
static unsigned n_containing(char* palavra, TDicionarioDinamico* dPalavras);

// tf(palavra, doc);
// computa "Frequência do Termo (palavra)", retorna o
// número de vezes que a palavra aparece no doc, dividido pelo número total de palavras no doc.
// [2.2] Para Calcular a Frequência da Palavra e o Número Total de Palavras Numa página (TF)
static float tf(TDicionarioDinamico* dVetorPaginas, TElemento* elemento);

// idf(palavra, docs)
// computa "inverse document frequency" que mede quão comum uma palavra é entre todos os documentos em docs.
// quanto mais comum for, mais baixo será o seu IDF.
// toma-se a razão entre o número total de documentos e o número de doc's que tem a palavra, e
// em seguida, toma-se o log dessa razão.
// adiciona-se 1 ao divisor para evitar divisão por zero.
// [2.3] Para Calcular o Número de Páginas que o Livro Tem e o Número de Páginas que Possuem a Palavra (IDF)
static float idf(char* palavra, TVetorDinamico* vetorPaginas, TDicionarioDinamico* dPalavas);

// TFIDF(palavra, doc, docs)
// computa o TF-IDF, que é o produto do tf e idf.
float TFIDF(TElemento* elemento, TDicionarioDinamico* dPalavras, TDicionarioDinamico* dVetorPaginas, TVetorDinamico* vetorPaginas);


#endif
