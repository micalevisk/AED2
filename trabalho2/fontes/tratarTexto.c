//
//	[tratarTexto.c]
//	Created by Micael Levi on 08/10/2016
//	Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "tratarTexto.h"


char* criarArquivoTemporario(const char* dir_arquivo, const char* filename_arquivoComTemplate, mode_t modo){
	char* path_arquivoTemp = (char*)malloc( sizeof(char)*( strlen(dir_arquivo) + strlen(filename_arquivoComTemplate) ) );
	strcpy(path_arquivoTemp, dir_arquivo); strcat(path_arquivoTemp, filename_arquivoComTemplate);

	int fd_temp;
	if((fd_temp = mkstemp(path_arquivoTemp)) < 1) return NULL;
	fchmod(fd_temp, modo);
	close(fd_temp);

	return path_arquivoTemp;
}


char* processarTexto(const char* path_livro, const char* dir_script, const char* filename_script){
	char* templateArq = (char*)malloc( sizeof(char)*(strlen(MASK_ARQUIVO_TRATADO)+strlen(dir_script)+1) );
	strcpy(templateArq, dir_script); strcat(templateArq, MASK_ARQUIVO_TRATADO);

	////(2):
	templateArq = criarArquivoTemporario("",templateArq, PERMISSAO_LEITURA_ESCRITA);
	// printf(">>%s<<\n", templateArq);
	// int fd_temp;
	// if((fd_temp = mkstemp(templateArq)) < 1) return NULL;
	// fchmod(fd_temp, 0600);
	// close(fd_temp);

	////(3):
	unsigned tamStrComando = strlen(INICIO) + strlen(path_livro) + strlen(MEIO) + strlen(FINAL) + strlen(templateArq);
	char* strComando = (char*) malloc(sizeof(char) * tamStrComando);
	strcpy(strComando, INICIO); strcat(strComando, path_livro); strcat(strComando, MEIO); strcat(strComando, FINAL); strcat(strComando, templateArq);
	// printf("|%s|\n\n", strComando);

	////(4):
	FILE* execComando = popen(strComando, "r");
	pclose(execComando); // executa o comando descrito em 'strComando'

	return templateArq;
}


short removerArquivoDir(const char* path_arquivo){
	return remove(path_arquivo);
}
