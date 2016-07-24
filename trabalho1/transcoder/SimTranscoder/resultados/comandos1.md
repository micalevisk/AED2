<!-- Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved. -->
<!-- https://stackedit.io/editor -->

# <i class="icon-cog"></i> Comandos Para a Criação dos Arquivos de Resultados
> admitindo que o diretório corrente é o 'src'
> Após compilar o programa chamando de **transcoder_parcial** e **transcoder_completa**.

Definição das Variáveis (glob):
------------------------------------------

```bash
## nome do programa que será executado
declare -r PROG="$1"

##  PARCIAL ou COMPLETA; define o diretório ordenacao_$TORDENACAO/...
declare -r TORDENACAO="$2"  

##  (Estrutura de Dados) FILA ou HEAP; deve estar em maiúsculo
declare -r TAD=$(tr -dc '[A-Z]' <<< $PROG)            

## vetor de casos testes (instâncias i)
## for((i=10; i <= 10000000; i *= 10)); do echo -n "$i "; done
CASOS=(10 100 1000 10000 100000 1000000 10000000)

##  (x) define o número de iterações para cada teste (para calcular a média)
declare -i ITERACOES=15

## diretório que contém as pastas de resultados
declare -r DIR="../resultados/ordenacao_$TORDENACAO/"
```

----------

## Gerar todos os dados & filtrar resultados ("log"):

### <i class="icon-file"></i> 1. Gera as 'x' saídas (seguido do tempo de execução) do programa, salvando arquivos independentes:
**../ordenacao_(parcial|completa)/tudo/instancia.i/x.log** <br>

- Onde **TORDENACAO** define se a ordenacao é "parcial" ou "completa"   
- Onde **i** é o número da instância (de acordo com o número de elementos)
- Onde **x** é o número da iteração  (vai de **1** até **ITERACOES**)

```bash
# Executar para cada instancia i, x vezes:
#----------------------------------------------------------#
( time ./transcoder < [dir_instância] ) 2>&1 |
sed -nr  's/real\t// ; 1,6p' |
install -D /dev/stdin ${DIR}/tudo/instancia.${i}/${x}.log
#----------------------------------------------------------#
( time [cmd] >&2 ) 2> ${DIR}/tudo/instancia.${i}/${x}.log
## >&2  Conecta a STDOUT de [cmd] na STDERR.
## 2>   Redireciona a STDERR.
#----------------------------------------------------------#
( (time [cmd]) 2>&1 ) > ${DIR}/tudo/instancia.${i}/${x}.log
## 2>&1 Conecta a STDERR na STDOUT.
## >    Redireciona a STDOUT.
```


### <i class="icon-upload"></i> 2. Filtrar dados obtidos, salvando em seus respectivos diretórios:
**../ordenacao_TORDENACAO/analiticos/instancia.i/x.stats**
```bash
# Executar para cada instancia i, x vezes:
#-------------------------------------------------------------------#
head -n4 ${DIR}/tudo/instancia.${i}/${x}.log |
tr -d -c '[:digit:]\n' |
install -D /dev/stdin/ ${DIR}/analiticos/instancia.${i}/${x}.stats
```

**../ordenacao_TORDENACAO/tempos/instancia.i/x.time** <br>
http://www.thegeekstuff.com/2013/10/time-command-format/ _(exemplos do time com opções)_
http://ss64.com/bash/time.html _(manual do comando time)_

```bash
# Executar para cada instancia i, x vezes:
#----------------------------------------------------------#
tail -n1 ${DIR}/tudo/instancia.${i}/${x}.log |
tr 'm.' ':' |
awk -F: '{ print ($1 * 60) + $2 + ($3 / 1000) }' |
tr '.' ',' |
install -D /dev/stdin ${DIR}/tempos/instancia.${i}/${x}.time
```

### <i class="icon-refresh"></i> 3. Tudo em um só loop:

> Após definir o ***número de testes*** que as instâncias realizarão, ***o tipo de ordenação***, o ***vetor de casos testes*** , e o ***tipo de estrutura*** ;
>
> #### O script a seguir irá realizar o seguinte algoritmo:
> - Equanto não for a última instância (i), fazer:
>  * Enquanto não for a última iteração (x), fazer: 		
>        * executar com 'time' e salvar na pasta da instância e com nome _x.log_ 		
>        * ler o _x.log_ e capturar analítico salvando na pasta da instância e com nome _x.stats_ 		
>        * ler _x.log_ e capturar 'time' (sem cor) salvando na pasta da instância e com nome _x.time_


```bash
#!/bin/bash
## uso verbose : ./gerarResultado.sh <nomePrograma> <tipoDeOrdenacao>
## uso execucao: ./gerarResultado.sh -e <nomePrograma> <tipoDeOrdenacao>

[ "$1" -a "$2" ] || exit 1

_RESET="\033[0m"
_GREEN="\033[40;32m"
_YELLO="\033[40;33m"
_PURPL="\033[40;35m"
_BLUE="\033[40;36m"

#---------------------[ DEFINIÇÃO DAS VARIÁVEIS GLOBAIS ]-----------------------#

## define se irá executar o comando (além de exibi-lo)
declare -i SO_TESTA=1
[ "$1" == "-e" ] && { SO_TESTA=0; shift; }

## nome do programa que será executado; o arquivo deve exisitir e ser executável
declare -r PROG="$1"
[ -x $PROG ] || { echo "ERRO ARQUIVO: $PROG NÃO EXISTE/EXECUTÁVEL"; exit 1; }

## 'parcial' ou 'completa'; define o diretório ordenacao_xx/...
[ "$2" == "parcial" -o "$2" == "completa" ] || exit 1
declare -r TORDENACAO="$2"

## array de casos testes (instâncias i)
## for((i=0; i <= 10000000; i*=10)); do echo -n "$i "; done
CASOS=(10 100 1000 10000 100000)
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

for i in ${CASOS[@]}; do #
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
		fi
		echo -ne $_BLUE
		echo "echo -n $tempo | install -D /dev/stdin $ARQ"

		echo
	done

done

echo -ne $_RESET
```



----------
http://github.com/micalevisk/AED2
