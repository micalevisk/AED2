//
//	[tratarTexto.c]
//	Created by Micael Levi on 08/10/2016
//	Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "headers/tratarTexto.h"

#define INICIO "./"
#define MEIO   " > "


char* criarArquivoTemporario(const char* dir_arquivo, const char* filename_arquivoComTemplate, mode_t modo){
	char* path_arquivoTemp = (char*)malloc( sizeof(char)*( strlen(dir_arquivo) + strlen(filename_arquivoComTemplate) ) );
	strcpy(path_arquivoTemp, dir_arquivo); strcat(path_arquivoTemp, filename_arquivoComTemplate);
	// memset(path_arquivoTemp, '\0', strlen(dir_arquivo) + strlen(filename_arquivoComTemplate) );

	int fd_temp;
	if((fd_temp = mkstemp(path_arquivoTemp)) < 1) return NULL;
	fchmod(fd_temp, modo);
	close(fd_temp);

	return path_arquivoTemp;
}


char* processarTexto(const char* path_livro, const char* dir_script, const char* filename_script){
	char* templateArq = (char*)malloc( sizeof(char)*(strlen(MASK_ARQUIVO_TRATADO)+strlen(dir_script)+1) );
	strcpy(templateArq, dir_script); strcat(templateArq, MASK_ARQUIVO_TRATADO);

	////(1):
	char* path_script = (char*)malloc( sizeof(char)* (strlen(dir_script) + strlen(filename_script)) );
	strcpy(path_script, dir_script); strcat(path_script, filename_script);
	if( chmod(path_script, PERMISSAO_LEITURA_ESCRITA_EXECUCAO) ) return NULL; // erro ao alterar a permissão.

	////(2):
	templateArq = criarArquivoTemporario("",templateArq, PERMISSAO_LEITURA_ESCRITA);
	// printf(">>%s<<\n", templateArq);
	// int fd_temp;
	// if((fd_temp = mkstemp(templateArq)) < 1) return NULL;
	// fchmod(fd_temp, 0600);
	// close(fd_temp);

	////(3):
	unsigned tamStrComando = strlen(INICIO) + strlen(path_script) + 4 + strlen(path_livro) + strlen(MEIO) + strlen(templateArq);
	char* strComando = (char*) malloc(sizeof(char) * tamStrComando);
	strcpy(strComando, INICIO); strcat(strComando, path_script); strcat(strComando, " "); strcat(strComando, path_livro); strcat(strComando, MEIO); strcat(strComando, templateArq);

	////(4):
	FILE* execComando = popen(strComando, "r");
	pclose(execComando); // executa o comando descrito em 'strComando'

	return templateArq;
}


short removerArquivoDir(const char* path_arquivo){
	return remove(path_arquivo);
}



/*
int main(){

	char* arq1 = criarArquivoTemporario("", MASK_ARQUIVO_INFO, PERMISSAO_LEITURA_ESCRITA);
	char* arq2 = criarArquivoTemporario("../base/", MASK_ARQUIVO_TRATADO, PERMISSAO_LEITURA_ESCRITA_EXECUCAO);

	sleep(5);
	removerArquivoDir(arq1);
	removerArquivoDir(arq2);

	char* arqTratado = processarTexto("../base/baseAventuras", "../base/", "tratarTexto.sh");
	sleep(20);
	removerArquivoDir(arqTratado);



	return 0;
}
*/
