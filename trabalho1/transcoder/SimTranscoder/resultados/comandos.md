<!-- Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved. -->

# *Comandos Para a Criação dos Arquivos de Resultados*

$ gcc -o transcoder !(heap|fila).c

---
### Definição das Variáveis (glob):
_caso inicial:_
```bash
TAD="FILA"            ##  (Estrutura de Dados) FILA ou HEAP
### for((i=10; i < 10000000; i *= 10)); do echo -n "$i "; done
CASOS=(10 100 1000 10000 100000 1000000 10000000)      ##  (vetor) de casos testes (instâncias)
TORDENACAO="PARCIAL"  ##  PARCIAL ou COMPLETA; define o diretório ordenacao_$TORDENACAO/...
ITERACOES="x"         ##  'x' define o número de iterações para cada teste (para calcular a média)
DIR="../resultados/ordenacao_$TORDENACAO/"
```

---
### Gerar todos os dados & filtrar resultados ("log"):
<span style="color:#00a761"> 1. Gera as x saídas (seguido do tempo de execução) do programa, salvando arquivos independentes:</span>
**../ordenacao_$TORDENACAO/tudo/instancia_${i}/${x}.log** <br>
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
    local VEZ=instancia_${i}
    ( time ./transcoder < ../Dado/$VEZ >&2 ) 2> ${DIR}/tudo/$VEZ/${x}.log
  done
done
```
<span style="color:#005270"> 2. Filtrar dados obtidos, salvando em seus respectivos diretórios: </span>

- **../ordenacao_(PARCIAL|COMPLETA)/analiticos/instancia_${i}/${x}.stats**
```bash
# Executar para cada instancia i, x vezes:
#-------------------------------------------------------------------------------------------------#
tail -8 ${DIR}/tudo/instancia_${i}/${x}.log |
head -4 > ${DIR}/analiticos/instancia_${i}/${x}.stats
sed -i -r 's/\[..?m//g' ${DIR}/analiticos/instancia_${i}/${x}.stats
```

_loop que realiza os comandos acima:_
```bash
# CURR DIR = ../src/
for i in ${CASOS[@]}; do
  for((x=1; x <= $ITERACOES; ++x)); do
    local VEZ=instancia_${i}
    local ARQ=${DIR}/analiticos/$VEZ/${x}.stats
    tail -8 ${DIR}/tudo/$VEZ/${x}.log | head -4 > $ARQ
    sed -i -r 's/\[..?m//g' $ARQ
  done
done
```


- **../ordenacao_(PARCIAL|COMPLETA)/saidas/instancia_${i}/${x}.output**


- **../ordenacao_(PARCIAL|COMPLETA)/tempos/instancia_${i}/${x}.time**
```bash
# Executar para cada instancia i, x vezes:
#---------------------------------------------------------------------------------------------------#
tail -4 ${DIR}/tudo/instancia_${i}/${x}.log |
grep 'real' > ${DIR}/analiticos/instancia_${i}/${x}.time
```
