##
##	[makefile]
##	Created by Micael Levi on 09/06/2016
##	Copyright (c) 2016 mllc@icomp.ufam.edu.br; All rights reserved.
##

#
#	(em relação ao arquivo 'makefile')
#	MAIN		=	nome do programa executavel
#	SRCSDIR		=	caminho dos arquivos .c
#	INCDIR		=	caminho dos arquivos .h	(deve estar na mesma pasta que os códigos-fonte)
#	INCLUDES 	=	opção para incluir arquivos cabeçalhos de outros diretórios
#	CC			=	comando para compilar (o arroba faz sumprimir a saída do make)
#	CFLAGS		=	flags para o 'CC'
#	LIBS		=	bibliotecas importadas
#	SRCS		=	nome dos arquivos de código-fonte com extensão '.c'
#	_OBJS		=	nome dos objetos que serão gerados (um para cada .c)
#

MAIN = criarIndiceRemissivo
SRCSDIR = fontes/
INCDIR = $(SRCSDIR)headers/
INCLUDES = -I $(INCDIR)
CC = @gcc
CFLAGS = -w -g
LIBS = -lm
SRCS = calcularTFIDF.c construirEDs.c contarOcorrencias.c dicionarioDinamico.c elementoDicionarios.c indiceRemissivo.c listaEncadeada.c main.c preProcesso.c tratarTexto.c vetorDinamico.c wordToInt.c
_OBJS = $(SRCSDIR)calcularTFIDF.c $(SRCSDIR)construirEDs.c $(SRCSDIR)contarOcorrencias.c $(SRCSDIR)dicionarioDinamico.c $(SRCSDIR)elementoDicionarios.c $(SRCSDIR)indiceRemissivo.c $(SRCSDIR)listaEncadeada.c $(SRCSDIR)main.c $(SRCSDIR)preProcesso.c $(SRCSDIR)tratarTexto.c $(SRCSDIR)vetorDinamico.c $(SRCSDIR)wordToInt.c
OBJS = $(_OBJS:.c=.o)


.PHONY: depend clean

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o  $@ $^ $(LIBS)
	@echo  USO: ./$(MAIN) [caminho do livro] [caminho do arquivo de consultas]

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJS) $(MAIN)
	@echo ARQUIVOS REMOVIDOS: $(OBJS) $(MAIN)

clean-objs:
	@$(RM) $(OBJS)
	@echo OBJETOS REMOVIDOS: $(OBJS)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
