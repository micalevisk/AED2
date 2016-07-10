#!/bin/bash
#
# uso verbose : ./gerarResultado.sh <nomePrograma> <tipoDeOrdenacao>
# uso execucao: ./gerarResultado.sh -e <nomePrograma> <tipoDeOrdenacao>
#
# Created by Micael Levi on 07/06/2016
# Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
#
#	{ > arq.log  ./transcoder [...] ; echo [...] >> arq.log  }
#	./gerarResultados2.sh -e transcoder_completa completa
#

[ "$1" -a "$2" ] || exit 1

_RESET="\033[0m"
_GREEN="\033[40;32m"
_YELLO="\033[40;33m"
_PURPL="\033[40;35m"
_BLUE="\033[40;36m"


declare -i SO_TESTA=1
[ "$1" == "-e" ] && { SO_TESTA=0; shift; }


#---------------------[ DEFINIÇÃO DAS VARIÁVEIS GLOBAIS ]-----------------------#

## nome do programa que será executado; o arquivo deve exisitir e ser executável
declare -r PROG="$1"
[ -x $PROG ] || { echo "ERRO ARQUIVO: $PROG NÃO EXISTE/EXECUTÁVEL"; exit 1; }

## 'parcial' ou 'completa'; define o diretório ordenacao_xx/...
[ "$2" == "parcial" -o "$2" == "completa" ] || exit 1
declare -r TORDENACAO="$2"

## array de casos testes (instâncias i)
## for((i=0; i <= 10000000; i*=10)); do echo -n "$i "; done
CASOS=(10 100 1000 10000 100000) ## 1000000 10000000
# CASOS=(10 100 1000 10000 100000 1000000 10000000)

## (x) define o número de iterações para cada teste
declare -i ITERACOES=1

## diretório que contém as pastas de resultados
declare -r DIR="../resultados/ordenacao_$TORDENACAO"
[ -d $DIR ] || exit 1

#--------[ INTERAÇÃO COM O USUÁRIO ]----------------#
echo "Deseja continuar? [sn]"
echo "> nome do programa : $PROG"
echo "> tipo de ordenação: $TORDENACAO"
echo "> número de testes : $ITERACOES"
echo "> diretório results: $DIR"
read resposta
resposta=$(tr -d 'sS' <<< $resposta)
[[ $resposta =~ [nN] ]] && exit 1
echo -e "\033c"	## limpar tela

#--------------------------------------[ LOOP GERADOR ]--------------------------------------------#
## DIRETÓRIO CORRENTE: .../src/

declare -i i x	## contadores

for i in 1000000; do #${CASOS[@]}
	VEZ="instancia.${i}"	## nome da pasta relacionada à instância corrente

	for((x=1; x <= $ITERACOES; ++x)); do

		## gerando o .log
		BASE="${DIR}/tudo/$VEZ/${x}.log"
		if [ $SO_TESTA -eq 0 ]; then
			( time ./$PROG < ../Dado/$VEZ ) 2>&1 | sed -nr 's/real\t// ; 1,6p' | install -D /dev/stdin $BASE
		fi
		echo -ne $_GREEN
		echo "( time ./$PROG < ../Dado/$VEZ ) 2>&1 | sed -nr 's/real\t// ; 1,6p' | install -D /dev/stdin $BASE"

		## gerando .stats
		ARQ="${DIR}/analiticos/$VEZ/${x}.stats"
		if [ $SO_TESTA -eq 0 ]; then
			head -n 4 $BASE | tr -d -c '[:digit:]\n' | install -D /dev/stdin $ARQ
		fi
		echo -ne $_YELLO
		echo "head -n 4 $BASE | tr -d -c '[:digit:]\n' | install -D /dev/stdin $ARQ"

		## gerando .time
		ARQ="${DIR}/tempos/$VEZ/${x}.time"
		if [ $SO_TESTA -eq 0 ]; then
			tempo=$(tail -n1 $BASE | tr 'm.' ':' | awk -F: '{ print ($1 * 60) + $2 + ($3 / 1000) }' | tr '.' ',')
			echo -n $tempo | install -D /dev/stdin $ARQ
			# tail -n1 $BASE | tr -d '[:alpha:]' | tr '.' ',' | install -D /dev/stdin $ARQ
		fi
		echo -ne $_BLUE
		echo "echo -n $tempo | install -D /dev/stdin $ARQ"

		## converte (.log) do formato UNIX para DOS
		[ $SO_TESTA -eq 0 ] && sed -i 's/$/\r/' $BASE
		echo
	done

done

echo -ne $_RESET
