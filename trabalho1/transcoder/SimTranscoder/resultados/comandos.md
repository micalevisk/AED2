<!-- Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved. -->
<!-- https://stackedit.io/editor -->

# <i class="icon-cog"></i> Comandos Para a Criação dos Arquivos de Resultados
> admitindo que o diretório corrente é o 'src'
> Após compilar o programa chamando de **transcoder_PARCIAL** e **transcoder_TOTAL**.

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
**../ordenacao_(parcial|completa)/tudo/instancia_i/x.log** <br>

- Onde **TORDENACAO** define se a ordenacao é "PARCIAL" ou "TOTAL"   
- Onde **i** é o número da instância (de acordo com o número de elementos)
- Onde **x** é o número da iteração  (vai de **1** até **ITERACOES**)

```bash
# Executar para cada instancia i, x vezes:
#----------------------------------------------------------#
( time [cmd] >&2 ) 2> ${DIR}/tudo/instancia_${i}/${x}.log
## >&2  Conecta a STDOUT de [cmd] na STDERR.
## 2>   Redireciona a STDERR.
#----------------------------------------------------------#
( (time [cmd]) 2>&1 ) > ${DIR}/tudo/instancia_${i}/${x}.log
## 2>&1 Conecta a STDERR na STDOUT.
## >    Redireciona a STDOUT.
```

_loop que realiza todo o processo descrito acima:_
```bash
# CURR DIR = ../src/
for i in ${CASOS[@]}; do
  for((x=1; x <= $ITERACOES; ++x)); do
    VEZ=instancia_${i}
    ARQ=${DIR}/tudo/$VEZ/${x}.log

    ( time $PROG < ../Dado/$VEZ >&2 ) 2> $ARQ
  done
done
```
### <i class="icon-upload"></i> 2. Filtrar dados obtidos, salvando em seus respectivos diretórios:
**../ordenacao_TORDENACAO/analiticos/instancia_i/x.stats**
```bash
# Executar para cada instancia i, x vezes:
#-------------------------------------------------------------------#
grep -Po '(?<=\[..m ).+(?=\[0m)' ${DIR}/tudo/instancia_${i}/${x}.log
> ${DIR}/analiticos/instancia_${i}/${x}.stats
```

_loop que realiza os comandos acima:_
```bash
# CURR DIR = ../src/
for i in ${CASOS[@]}; do
  for((x=1; x <= $ITERACOES; ++x)); do
    VEZ=instancia_${i}
    ARQ=${DIR}/analiticos/$VEZ/${x}.stats

    grep -Po '(?<=\[..m ).+(?=\[0m)' ${DIR}/tudo/instancia_${i}/${x}.log > $ARQ
  done
done
```


**../ordenacao_TORDENACAO/saidas/instancia_i/x.output**
```bash
# Executar para cada instancia i, x vezes:
#----------------------------------------------------#
sed -n '1,/^$/ p' ${DIR}/tudo/instancia_${i}/${x}.log
> ${DIR}/saidas/instancia_${i}/${x}.output
```

_loop que realiza o comando acima:_
```bash
# CURR DIR = ../src/
for i in ${CASOS[@]}; do
  for((x=1; x <= $ITERACOES; ++x)); do
    VEZ=instancia_${i}
    ARQ=${DIR}/saidas/$VEZ/${x}.output

    sed -n '1,/^$/ p' ${DIR}/tudo/instancia_${i}/${x}.log > $ARQ
  done
done
```


**../ordenacao_TORDENACAO/tempos/instancia_i/x.time** <br>
http://www.thegeekstuff.com/2013/10/time-command-format/ _(exemplos do time com opções)_
http://ss64.com/bash/time.html _(manual do comando time)_

```bash
# Executar para cada instancia i, x vezes:
#-------------------------------------------------#
#grep -F 'real' ${DIR}/tudo/instancia_${i}/${x}.log
tail -n4 ${DIR}/tudo/instancia_${i}/${x}.log
> ${DIR}/tempos/instancia_${i}/${x}.time
```

_loop que realiza o comando acima:_
```bash
# CURR DIR = ../src/
for i in ${CASOS[@]}; do
  for((x=1; x <= $ITERACOES; ++x)); do
    VEZ=instancia_${i}
    ARQ=${DIR}/tempos/$VEZ/${x}.time

    tail -n4 ${DIR}/tudo/instancia_${i}/${x}.log > $ARQ
  done
done
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

## o primeiro e o segundo parâmetros devem existir
[ "$1" -a "$2" ] || exit 1

_RESET="\033[0m"
_GREEN="\033[40;32m"
_YELLO="\033[40;33m"
_BLUE="\033[40;36m"


declare -i SO_TESTA=1
[ "$1" == "-e" ] && { SO_TESTA=0; shift; }


#---------------------[ DEFINIÇÃO DAS VARIÁVEIS GLOBAIS ]-----------------------#

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

#--------[ INTERAÇÃO COM O USUÁRIO ]----------------#

echo "Deseja continuar? [sn]"
echo "> nome do programa : $PROG"
echo "> tipo de ordenação: $TORDENACAO"
echo "> estrutura usada  : $TAD"
echo "> número de testes : $ITERACOES"
echo "> diretório results: $DIR"
read resposta
resposta=$(tr '[:upper:]' '[:lower:]' <<< $resposta)
resposta=$(tr -d -c '[:alpha:]' <<< $resposta)
[ "$resposta" != "s" ] && exit 1
echo -e "\033c"	## limpar tela

#----------------[ LOOP GERADOR ]-----------------------#
## DIRETÓRIO CORRENTE: .../src/

declare -i i x
for i in ${CASOS[@]}; do
	VEZ="instancia_${i}"	## nome da pasta relacionada à instância corrente

	for((x=1; x <= $ITERACOES; ++x)); do

		## gerando o .log
		BASE="${DIR}/tudo/$VEZ/${x}.log"
		[ $SO_TESTA -eq 0 ] &&
			( time ./$PROG < ../DADO/$VEZ ) 2>&1 | install -D /dev/stdin $BASE
		echo -e $_GREEN "( time ./$PROG < ../DADO/$VEZ ) 2>&1 | install -D /dev/stdin $BASE" $_RESET

		## gerando .stats
		ARQ="${DIR}/analiticos/$VEZ/${x}.stats"
		[ $SO_TESTA -eq 0 ] &&
			grep -Po '(?<=\[..m ).+(?=\[0m)' $BASE | install -D /dev/stdin $ARQ
		echo -e $_YELLO "grep -Po '(?<=\[..m ).+(?=\[0m)' $BASE | install -D /dev/stdin $ARQ" $_RESET

		## gerando .time
		ARQ="${DIR}/tempos/$VEZ/${x}.time"
		[ $SO_TESTA -eq 0 ] &&
			tail -4 ${BASE} | install -D /dev/stdin $ARQ
		echo -e $_BLUE "tail -4 ${BASE} | install -D /dev/stdin $ARQ" $_RESET

		echo
	done

done

```



----------
http://github.com/micalevisk/AED2
