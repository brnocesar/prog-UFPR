# Primeiro Trabalho Prático - 2013/1

## Ordenação e busca

### Objetivos

Criar um índice de busca de termos em documentos ("indice invertido").

### Entrada

A entrada deve ser feita pela entrada padrão (`stdin`) indicando o nome do documento a ser indexado. Você pode assumir que os textos não terão acentuação e poderá ignorar a pontuação na construção do índice. Ademais, as palavras devem ser transformadas em sua totalidade para letras minúsculas antes da inserção no índice.

Pro exemplo, considere o documento `teste.in` com o texto a seguir:

> Sera so imaginacao?
Sera que nada vai acontecer?
Sera que e tudo isso em vao?
Sera que vamos conseguir vencer?

### Saída

A saída do programa é o arquivo de índice que deve ser feita pela saída padrão (`stdout`). Este arquivo de indice será composto por uma sequência de linhas conforme demonstrando no exemplo.

Para o arquivo de entrada descrito temos o seguinte arquivo de índice invertido chamado "teste.out":

```terminal
acontecer, 1 , {(1,1)}
conseguir, 1 , {(3,1)}
e, 1 , {(2,1)}
...
que, 3, {(1,1),(2,1),(3,1)}
...
sera, 4, {(0,1),(1,1),(2,1),(3,1)}
...
```

O arquivo de índice será composto por uma sequência ordenada de linhas. Uma linha para cada termo. Cada linha tem 3 campos separados por vírgula. O primeiro campo é o termo. Este campo que deverá ser utilizado para a ordenação. O segundo campo é a frequência do termo no documento. O terceiro campo é um conjunto de pares, onde cada par deve mostrar a linha onde o termo aparece e sua frequência na linha.

Por ex.: o termo "sera" aparece em todas as 4 linhas do texto. O termo "conseguir" aparece apenas uma vez na linha "3".

### Requisitos mínimos

O trabalho deve ser feito de forma que possa ser compilado e executado nas servidoras de computação do Departamento de Informática.

O nome do executável deve ser indice.

Não deve ter nenhuma opção de linha comando.

### O que deve ser entregue

Além dos arquivos fonte, deve acompanhar um makefile e um relatório com no máximo 2 páginas contendo a documentação sintetizada do sistema implementado. Qualquer particularidade deve estar descrita neste texto, como: algoritmo de busca e ordenação utilizados.

Para compilar será usado o comando make (sem nenhum parâmetro), portanto preparem o Makefile para fazer isso.

Para testar será executado um script como o abaixo.

```terminal
indice < teste.in > teste.out
diff teste.sol teste.out
```

Onde `teste.in` é o arquivo de entrada do teste e teste.sol é o esperado como saída.

Caso o teste seja positivo (não imprime nada) será analisado o código fonte e o
relatório.
