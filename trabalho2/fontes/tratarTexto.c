//
//	[tratarTexto.c]
//	Created by Micael Levi on 08/10/2016
//	Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "tratarTexto.h"



#define INICIO "egrep -o '\\w+(-\\w+)?' "
#define FINAL   " > "
#define MEIO " | sed '/[0-9]/d' | sed '/\\<PA\\>/! { y/ABCDEFGHIJKLMNOPQRSTUVWXYZ/abcdefghijklmnopqrstuvwxyz/ ; y/ÀÁÂÃÄÅÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÇÑ/àáâãäåèéêëìíîïòóôõöùúûüçñ/ ; }' | sed -r '/\\<(a|à|adeus|agora|aí|ainda|além|algo|algumas|alguns|ali|ano|anos|antes|ao|aos|apenas|apoio|após|aquela|aquelas|aquele|aqueles|aqui|aquilo|área|as|às|assim|até|atrás|através|baixo|bastante|bem|boa|boas|bom|bons|breve|cá|cada|catorze|cedo|cento|certamente|certeza|cima|cinco|coisa|com|como|conselho|contra|custa|da|dá|dão|daquela|daquelas|daquele|daqueles|dar|das|de|debaixo|demais|dentro|depois|desde|dessa|dessas|desse|desses|desta|destas|deste|destes|deve|deverá|dez|dezanove|dezasseis|dezassete|dezoito|dia|diante|diz|dizem|dizer|do|dois|dos|doze|duas|dúvida|e|é|ela|elas|ele|eles|em|embora|entre|era|és|essa|essas|esse|esses|esta|está|estão|estar|estas|estás|estava|este|estes|esteve|estive|estivemos|estiveram|estiveste|estivestes|estou|eu|exemplo|faço|falta|favor|faz|fazeis|fazem|fazemos|fazer|fazes|fez|fim|final|foi|fomos|for|foram|forma|foste|fostes|fui|geral|grande|grandes|grupo|há|hoje|hora|horas|isso|isto|já|lá|lado|local|logo|longe|lugar|maior|maioria|mais|mal|mas|máximo|me|meio|menor|menos|mês|meses|meu|meus|mil|minha|minhas|momento|muito|muitos|na|nada|não|naquela|naquelas|naquele|naqueles|nas|nem|nenhuma|nessa|nessas|nesse|nesses|nesta|nestas|neste|nestes|nível|no|noite|nome|nos|nós|nossa|nossas|nosso|nossos|nova|novas|nove|novo|novos|num|numa|número|nunca|o|obra|obrigada|obrigado|oitava|oitavo|oito|onde|ontem|onze|os|ou|outra|outras|outro|outros|para|parece|parte|partir|paucas|pela|pelas|pelo|pelos|perto|pode|pôde|podem|poder|põe|põem|ponto|pontos|por|porque|porquê|posição|possível|possivelmente|posso|pouca|pouco|poucos|primeira|primeiras|primeiro|primeiros|própria|próprias|próprio|próprios|próxima|próximas|próximo|próximos|puderam|quáis|qual|quando|quanto|quarta|quarto|quatro|que|quê|quem|quer|quereis|querem|queremas|queres|quero|questão|quinta|quinto|quinze|relação|sabe|sabem|são|se|segunda|segundo|sei|seis|sem|sempre|ser|seria|sete|sétima|sétimo|seu|seus|sexta|sexto|sim|sistema|sob|sobre|sois|somos|sou|sua|suas|tal|talvez|também|tanta|tantas|tanto|tão|tarde|te|tem|têm|temos|tendes|tenho|tens|ter|terceira|terceiro|teu|teus|teve|tive|tivemos|tiveram|tiveste|tivestes|toda|todas|todo|todos|trabalho|três|treze|tu|tua|tuas|tudo|um|uma|umas|uns|vai|vais|vão|vários|vem|vêm|vens|ver|vez|vezes|viagem|vindo|vinte|você|vocês|vos|vós|vossa|vossas|vosso|vossos|zero)\\>/ d'"

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