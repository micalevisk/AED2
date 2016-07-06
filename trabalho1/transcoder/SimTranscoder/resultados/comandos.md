<!-- Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved. stackedit.io -->

# Comandos Para a Criação dos Arquivos de Resultados
> admitindo que o diretório corrente é o 'src'
> Após compilar o programa chamando de **transcoder_PARCIAL** e **transcoder_TOTAL**. 

Definição das Variáveis (glob):
-----------------------------------------

_caso inicial:_
```bash
##  (Estrutura de Dados) FILA ou HEAP
TAD="FILA"            

## nome do programa que será chamado
PROG="transcoder_$TAD"

## vetor de casos testes (instâncias)
## 10 100 1000 10000 100000 1000000
CASOS=$( for((i=10; i < 10000000; i *= 10)); do echo -n "$i "; done )

##  PARCIAL ou COMPLETA; define o diretório ordenacao_$TORDENACAO/...
TORDENACAO="PARCIAL"  

##  'x' define o número de iterações para cada teste (para calcular a média)
ITERACOES="x"         

## diretório que contém as pastas de resultados
DIR="../resultados/ordenacao_$TORDENACAO/"
```

----------

### Gerar todos os dados & filtrar resultados ("log"):
<span style="color:#00a761"> 1. Gera as x saídas (seguido do tempo de execução) do programa, salvando arquivos independentes:</span>
**../ordenacao_(PARCIAL|COMPLETA)/tudo/instancia_i/x.log** <br>

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
<span style="color:#005270"> 2. Filtrar dados obtidos, salvando em seus respectivos diretórios: </span>
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
[TIME SKILL](http://www.thegeekstuff.com/2013/10/time-command-format/) <br>
[TIME MANUAL](http://ss64.com/bash/time.html)

```bash
# Executar para cada instancia i, x vezes:
#-------------------------------------------------#
grep -F 'real' ${DIR}/tudo/instancia_${i}/${x}.log 
> ${DIR}/tempos/instancia_${i}/${x}.time
```

_loop que realiza o comando acima:_
```bash
# CURR DIR = ../src/
for i in ${CASOS[@]}; do
  for((x=1; x <= $ITERACOES; ++x)); do
    VEZ=instancia_${i}
    ARQ=${DIR}/tempos/$VEZ/${x}.time
    
    grep -F 'real' ${DIR}/tudo/instancia_${i}/${x}.log > $ARQ
  done
done
```



<span style="color:#005270"> 3. Tudo em um só loop (gera log -> edita pra analiticos/saidas?/tempos): </span>

> Após definir o ***número de teste*** que as instâncias realizarão, ***o tipo de ordenação***, o ***vetor de casos testes*** , o ***tipo de estrutura*** 
