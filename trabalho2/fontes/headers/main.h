#ifndef MAIN_H
#define MAIN_H

#include "indiceRemissivo.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N_ARGS 3
#define LIVRO argv[1]
#define PALAVRAS_CONSULTA argv[2]
#define TAM_CHARS_LINHA 56

#define MSG_USO { fprintf(stdout, "USO:\n$ %s \"caminho do livro\" < \"caminho do arquivo texto de consultas\"\n", argv[0]); return 1; }


int main(int, char**);

#endif
