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

#define INICIO "egrep -o '\\w+(-\\w+)?' "
#define FINAL   " > "
#define MEIO " | sed '/[0-9]/d' | sed '/\\<PA\\>/! { y/ABCDEFGHIJKLMNOPQRSTUVWXYZ/abcdefghijklmnopqrstuvwxyz/ ; y/ÀÁÂÃÄÅÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÇÑ/àáâãäåèéêëìíîïòóôõöùúûüçñ/ ; }' | sed '/\\<\\(a\\|à\\|adeus\\|agora\\|aí\\|ainda\\|além\\|algo\\|algumas\\|alguns\\|ali\\|ano\\|anos\\|antes\\|ao\\|aos\\|apenas\\|apoio\\|após\\|aquela\\|aquelas\\|aquele\\|aqueles\\|aqui\\|aquilo\\|área\\|as\\|às\\|assim\\|até\\|atrás\\|através\\)\\>/ d' |\
sed '/\\<\\(baixo\\|bastante\\|bem\\|boa\\|boas\\|bom\\|bons\\|breve\\)\\>/ d' |\
sed '/\\<\\(cá\\|cada\\|catorze\\|cedo\\|cento\\|certamente\\|certeza\\|cima\\|cinco\\|coisa\\|com\\|como\\|conselho\\|contra\\|custa\\)\\>/ d' |\
sed '/\\<\\(da\\|dá\\|dão\\|daquela\\|daquelas\\|daquele\\|daqueles\\|dar\\|das\\|de\\|debaixo\\|demais\\|dentro\\|depois\\|desde\\|dessa\\|dessas\\|desse\\|desses\\|desta\\|destas\\|deste\\|destes\\|deve\\|deverá\\|dez\\|dezanove\\|dezasseis\\|dezassete\\|dezoito\\|dia\\|diante\\|diz\\|dizem\\|dizer\\|do\\|dois\\|dos\\|doze\\|duas\\|dúvida\\)\\>/ d' |\
sed '/\\<\\(e\\|é\\|ela\\|elas\\|ele\\|eles\\|em\\|embora\\|entre\\|era\\|és\\|essa\\|essas\\|esse\\|esses\\|esta\\|está\\|estão\\|estar\\|estas\\|estás\\|estava\\|este\\|estes\\|esteve\\|estive\\|estivemos\\|estiveram\\|estiveste\\|estivestes\\|estou\\|eu\\|exemplo\\)\\>/ d' |\
sed '/\\<\\(faço\\|falta\\|favor\\|faz\\|fazeis\\|fazem\\|fazemos\\|fazer\\|fazes\\|fez\\|fim\\|final\\|foi\\|fomos\\|for\\|foram\\|forma\\|foste\\|fostes\\|fui\\)\\>/ d' |\
sed '/\\<\\(geral\\|grande\\|grandes\\|grupo\\)\\>/ d' |\
sed '/\\<\\(há\\|hoje\\|hora\\|horas\\)\\>/ d' |\
sed '/\\<\\(isso\\|isto\\)\\>/ d' |\
sed '/\\<\\(já\\)\\>/ d' |\
sed '/\\<\\(lá\\|lado\\|local\\|logo\\|longe\\|lugar\\)\\>/ d' |\
sed '/\\<\\(maior\\|maioria\\|mais\\|mal\\|mas\\|máximo\\|me\\|meio\\|menor\\|menos\\|mês\\|meses\\|meu\\|meus\\|mil\\|minha\\|minhas\\|momento\\|muito\\|muitos\\)\\>/ d' |\
sed '/\\<\\(na\\|nada\\|não\\|naquela\\|naquelas\\|naquele\\|naqueles\\|nas\\|nem\\|nenhuma\\|nessa\\|nessas\\|nesse\\|nesses\\|nesta\\|nestas\\|neste\\|nestes\\|nível\\|no\\|noite\\|nome\\|nos\\|nós\\|nossa\\|nossas\\|nosso\\|nossos\\|nova\\|novas\\|nove\\|novo\\|novos\\|num\\|numa\\|número\\|nunca\\)\\>/ d' |\
sed '/\\<\\(o\\|obra\\|obrigada\\|obrigado\\|oitava\\|oitavo\\|oito\\|onde\\|ontem\\|onze\\|os\\|ou\\|outra\\|outras\\|outro\\|outros\\)\\>/ d' |\
sed '/\\<\\(para\\|parece\\|parte\\|partir\\|paucas\\|pela\\|pelas\\|pelo\\|pelos\\|perto\\|pode\\|pôde\\|podem\\|poder\\|põe\\|põem\\|ponto\\|pontos\\|por\\|porque\\|porquê\\|posição\\|possível\\|possivelmente\\|posso\\|pouca\\|pouco\\|poucos\\|primeira\\|primeiras\\|primeiro\\|primeiros\\|própria\\|próprias\\|próprio\\|próprios\\|próxima\\|próximas\\|próximo\\|próximos\\|puderam\\)\\>/ d' |\
sed '/\\<\\(quáis\\|qual\\|quando\\|quanto\\|quarta\\|quarto\\|quatro\\|que\\|quê\\|quem\\|quer\\|quereis\\|querem\\|queremas\\|queres\\|quero\\|questão\\|quinta\\|quinto\\|quinze\\)\\>/ d' |\
sed '/\\<\\(relação\\)\\>/ d' |\
sed '/\\<\\(sabe\\|sabem\\|são\\|se\\|segunda\\|segundo\\|sei\\|seis\\|sem\\|sempre\\|ser\\|seria\\|sete\\|sétima\\|sétimo\\|seu\\|seus\\|sexta\\|sexto\\|sim\\|sistema\\|sob\\|sobre\\|sois\\|somos\\|sou\\|sua\\|suas\\)\\>/ d' |\
sed '/\\<\\(tal\\|talvez\\|também\\|tanta\\|tantas\\|tanto\\|tão\\|tarde\\|te\\|tem\\|têm\\|temos\\|tendes\\|tenho\\|tens\\|ter\\|terceira\\|terceiro\\|teu\\|teus\\|teve\\|tive\\|tivemos\\|tiveram\\|tiveste\\|tivestes\\|toda\\|todas\\|todo\\|todos\\|trabalho\\|três\\|treze\\|tu\\|tua\\|tuas\\|tudo\\)\\>/ d' |\
sed '/\\<\\(um\\|uma\\|umas\\|uns\\)\\>/ d' |\
sed '/\\<\\(vai\\|vais\\|vão\\|vários\\|vem\\|vêm\\|vens\\|ver\\|vez\\|vezes\\|viagem\\|vindo\\|vinte\\|você\\|vocês\\|vos\\|vós\\|vossa\\|vossas\\|vosso\\|vossos\\)\\>/ d' |\
sed '/\\<\\(zero\\)\\>/ d'"

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
