/*
http://www.ime.usp.br/~pf/mac0122-2002/aulas/hashing.html
Utiliza o método de Horner para calcular de forma eficiênte o número correspondente à uma cadeia de caracteres.
Método de Horner:   2x3 + 3x2 + 4x + 5  =  ((2x + 3)x + 4)x + 5
*/

#ifndef WORDTOINT_H
#define WORDTOINT_H

#include "elementoDicionarios.h"
#include <string.h>

unsigned long converterParaNumero(void* str);

#endif
