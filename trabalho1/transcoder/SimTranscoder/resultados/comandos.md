<!-- Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved. -->

# *Comandos Para a Criação dos Arquivos de Resultados*

---
### Definição das Variáveis (glob):
_caso inicial:_
```bash
TAD="FILA"            ##  (ED) FILA ou HEAP
CASOS=(10 15 20)      ##  (vetor) de casos testes (instâncias)
TORDENACAO="PARCIAL"  ##  PARCIAL ou COMPLETA; define o diretório ordenacao_$TORDENACAO/...
ITERACOES="x"         ##  'x' define o número de iterações para cada teste (para calcular a média)
```

---
### Gerar todos os dados & filtrar resultados:
1. _Gera as x saídas (seguido do tempo de execução) do programa, salvando arquivos independentes:_ **../ordenacao_(PARCIAL|COMPLETA)/tudo/instancia_x/x.log**
```bash
( time [cmd] >&2 ) 2> instancia_[x].log
## >&2  Conecta a STDOUT (1) de [cmd] na STDERR (2)
## 2>   Redireciona a STDERR
```
_loop que realiza todo o processo:__
```bash
```

2. _Filtrar dados obtidos, salvando em seus respectivos diretórios:_
- **../ordenacao_(PARCIAL|COMPLETA)/analiticos/instancia_x/**


- **../ordenacao_(PARCIAL|COMPLETA)/saidas/instancia_x/**

- **../ordenacao_(PARCIAL|COMPLETA)/tempos/instancia_x/**
