#ifndef TRATARTEXTO_H
#define TRATARTEXTO_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

////////////////////// NÃO ALTERAR //////////////////
#define MASK_ARQUIVO_TRATADO ".textoTratado_XXXXXX"
#define MASK_ARQUIVO_INFO    ".textoInfo_XXXXXX"
#define CMD_APAGAR_TRATADOS  "rm base/.textoTratado_*"
#define CMD_APAGAR_INFOS     "rm .textoInfo_*"
#define PERMISSAO_LEITURA_ESCRITA 0666
#define PERMISSAO_LEITURA_ESCRITA_EXECUCAO 0777
/////////////////////////////////////////////////////

/*
http://www.thegeekstuff.com/2012/06/c-temporary-files/
http://pubs.opengroup.org/onlinepubs/9699919799/functions/mkstemp.html
http://stackoverflow.com/questions/25258709/changing-file-permissions-of-default-mkstemp
http://www.pmoghadam.com/homepage/HTML/c-temp-file.html
http://stackoverflow.com/questions/11840833/getting-output-of-a-system-command-from-stdout-in-c

http://ss64.com/bash/chmod.html
*/


// retorna o caminho do arquivo temporário criado, ou NULL caso ocorra erro na criação
// PARÂMETROS:
//  1º = diretório do local onde o arquivo será criado
//  2º = nome do arquivo que será criado (com os 6 X's)
//  3º = permissão (numérica) que o arquivo terá
char* criarArquivoTemporario(const char*, const char*, mode_t);


// retorna o caminho do arquivo temporário criado, ou NULL caso ocorra erro na criação
// se o script estiver no mesmo local que o livro, então 'path_script' deve ser vazio = ""
// PARÂMETROS:
//  1º = nome completo (diretório+nome) do arquivo a ser tratado
//  2º = diretório do arquivo que contém o script responsável pelo tratamento do texto
//  3º = nome do arquivo que contém o script
// (remoção de stop words, divisão de palavras por linha, palavras todas em minúsculas exceto o identificador de página)
char* processarTexto(const char*, const char*, const char*);


// PARÂMETROS:
//  1º = nome completo (caminho) do arquivo que será removido (deve ter permissão para leitura e escrita)
short removerArquivoDir(const char*);



#endif
