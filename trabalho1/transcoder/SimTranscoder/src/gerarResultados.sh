#!/bin/bash
#
#									transcoder_FILA|HEAP	parcial|completa
# uso verbose : ./gerarResultado.sh <nomePrograma_TAD> <tipoDeOrdenacao>
# uso execucao: ./gerarResultado.sh -e <nomePrograma_TAD> <tipoDeOrdenacao>
#
# Created by Micael Levi on 07/06/2016
# Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
#

[ "$1" -a "$2" ] || exit 1

_RESET="\033[0m"	
_GREEN="\033[40;32m"
_YELLO="\033[40;33m"
_PURPL="\033[40;35m"
_BLUE="\033[40;36m"


declare -i SO_TESTA=1
[ "$1" == "-e" ] && { SO_TESTA=0; shift; }


#-----------------[ ]-----------------------#

## nome do programa que será executado; o arquivo deve exisitir e ser executável
declare -r PROG="$1"
[ -x $PROG ] || { echo "ERRO AO ABRIR: $PROG"; exit 1; }

## 'parcial' ou 'completa'; define o diretório ordenacao_xx/...
[ "$2" == "parcial" -o "$2" == "completa" ] || exit 1
declare -r TORDENACAO="$2"

## (Estrutura de Dados) FILA ou HEAP; deve estar em maiúsculo
declare -r TAD=$(tr -dc '[A-Z]' <<< $PROG)

## array de casos testes (instâncias i)
## for((i=0; i <= 10000000; i*=10)); do echo -n "$i "; done
CASOS=(10 100 1000 10000 100000 1000000 10000000)

## (x) define o número de iterações para cada teste
declare -i ITERACOES=15

## diretório que contém as pastas de resultados
declare -r DIR="../resultados/ordenacao_$TORDENACAO"
[ -d $DIR ] || exit 1

#-----------------[ ]-----------------------#

echo "Deseja continuar? [SN]"
echo "> nome do programa : $PROG"
echo "> tipo de ordenação: $TORDENACAO"
echo "> estrutura usada  : $TAD"
echo "> número de testes : $ITERACOES"
echo "> diretório results: $DIR"
read resposta
resposta=$(tr '[:lower:]' '[:upper:]' <<< $resposta)
resposta=$(tr -d -c '[:alpha:]' <<< $resposta)
[ "$resposta" != "S" ] && exit 1
echo -e "\033c"	## limpar tela

#-----------------[ ]-----------------------#
## DIRETÓRIO CORRENTE: .../src/

declare -i i x
for i in ${CASOS[@]}; do
	VEZ="instancia_${i}"	## nome da pasta relacionada à instância corrente
		
	for((x=1; x <= 4; ++x)); do
		
		## gerando o .log
		BASE="${DIR}/tudo/$VEZ/${x}.log"
		[ $SO_TESTA -eq 0 ] && ( time ./$PROG < ../DADO/$VEZ ) 2>&1 | install -D /dev/stdin $ARQ
		echo -e $_GREEN "( time ./$PROG < ../DADO/$VEZ ) 2>&1 | install -D /dev/stdin $BASE" $_RESET

		## gerando .stats
		ARQ="${DIR}/analiticos/$VEZ/${x}.stats"
		[ $SO_TESTA -eq 0 ] && grep -Po '(?<=\[..m ).+(?=\[0m)' $BASE | install -D /dev/stdin
		echo -e $_YELLO "grep -Po '(?<=\[..m ).+(?=\[0m)' $BASE | install -D /dev/stdin" $_RESET 

		## gerando .output
		ARQ="${DIR}/saidas/$VEZ/${x}.output"
		[ $SO_TESTA -eq 0 ] && sed -n '1,/^$/p' ${BASE} | install -D /dev/stdin
		echo -e $_PURPL "sed -n '1,/^$/p' ${BASE} | install -D /dev/stdin" $_RESET

		## gerando .time
		ARQ="${DIR}/tempos/$VEZ/${x}.time"
		#echo -e $_BLUE "grep -F 'real' ${BASE} | install -D /dev/stdin" $_RESET
		[ $SO_TESTA -eq 0 ] && tail -4 ${BASE} | install -D /dev/stdin
		echo -e $_BLUE "tail -4 ${BASE} | install -D /dev/stdin" $_RESET

		echo 
	done
	
done
