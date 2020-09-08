# Segundo Trabalho Prático - 2013/1

## Controle de linha de montagem de carros

A MooCars cresceu muito nos últimos anos e está aumentando a sua linha de carros produzidos. Três modelos de carro diferentes são produzidos, mas existe apenas uma linha de montagem de carroceria e pintura. Na primeira etapa as carrocerias são montadas, onde cada carroceria tem um tempo diferente de produção. Na segunda etapa as carrocerias chegam para pintura, contudo existe apenas um equipamento de pintura. Existe um pequeno pátio de espera com capacidade para 5 carrocerias que pode ser usado a qualquer momento. O objetivo é diminuir o uso deste pátio para que as carrocerias sejam montadas e pintadas mais rápidamente para a produção final do carro.

As regras são as seguintes:

- o tempo é contado em minutos (implementado por ciclos, onde cada ciclo = 1 min);
- a linha de montagem inicia vazia e comporta até 3 carros ao mesmo tempo;
- o tempo de montagem depende da carroceria;
- existe apenas 1 equipamento de pintura que demora 5 minutos para pintar uma carroceria por vez;
- o pátio pode armazenar até 5 carrocerias e pode ser usado como uma fila de espera;
- a fila de espera não deve crescer muito devido o tamanho do pátio (para isso deve­se pensar em uma lista de prioridade);
- caso o pátio fique cheio o tempo de montagem de uma carroceria deve ser acrescido do tempo que ela ficou parada (veja exemplo abaixo);
- o modelo OXX é o mais vendido e tem prioridade, assim que sua carroceria chega ao pátio deve ser pintada o mais rápido possível, contudo, a prioridade das carrocerias que estão no pátio deve aumentar para não ficarem muito tempo esperando. Cada aluno deverá definir sua política de prioridade e descreve­la no relatório final (veja exemplo abaixo);
- o sistema suportará apenas uma operação por minuto (montar ou pintar).

### Entrada

A entrada deve ser feita pela entrada padrão ( stdin ). O arquivo é formado por uma sequência de linhas, onde cada linha representa um carro iniciando a montagem. Cada linha tem 4 campos: o primeiro é o tempo de chegada (em min), o segundo é o tempo de montagem da carroceria (em min), o terceiro é o identificador da carroceria e o quarto o modelo do carro (uma string de no máximo 3 caracteres). Estas linhas estão ordenadas pelo primeiro campo (tempos menores no início).

### Saída

A saída deve ser feita pela saída padrão ( stdout ). O arquivo será composto por uma sequência de linhas. Uma linha para cada evento (entra ou carrega). O evento 'entra' significa que o container foi para o pátio. O evento 'carrega' significa que o container começa a ser içado para o navio (a partir deste momento o guindaste esta ocupado e deve­se contar 3 ciclos para libera­lo). Cada linha tem 3 campos separados por espaço (um único espaço entre cada par de campos). O primeiro campo é o tipo do evento. O segundo campo é o tempo inicial do evento (em min). E o terceiro é o identificador do container.

Exemplo de arquivos com uma entrada e uma saída válida:

Entrada|Saída
-|-
2 7 A BUL<br />4 5 B COW<br />7 7 C BUL<br />9 3 D OXX<br />10 5 E COW<br />12 3 F OXX<br />14 3 G OXX|montar 2 A <br />montar 4 B <br />montar 7 C <br />pintar 9 A <br />montar 10 D <br />pintar 14 D <br />montar 15 F <br />pintar 19 B <br />montar 20 G <br />pintar 24 F <br />pintar 29 C <br />pintar 34 G

**Exemplo 1:** "2 7 A", seria 2+7 (entrada + montagem), entao "pintar 9 A". Neste ponto começa a pintura da carroceria.  
**Exemplo 2:** "9 3 D", a carroceria D começa ser montada no tempo 10 (restrição do sistema de 1 operação por minuto) e por prioridade toma a frente das outras.  
**Exemplo 3:** "4 5 B", a carroceria B cede a vez para D no tempo 14 e segue para pintura apenas no tempo 19, pois volta a ter prioridade pelo tempo de espera.  

### Requisitos mínimos

O trabalho deve ser feito de forma que possa ser compilado e executado nas servidoras de computação do Departamento de Informática.

O nome do executável deve ser `$moocars`.

Não devem ter nenhuma opção de linha comando.

### O que deve ser entregue

Além dos arquivos fonte, deve acompanhar um makefile e um relatório com no máximo 2 páginas contendo os nomes dos alunos, uma descrição das estruturas de dados e das soluções encontradas e uma documentação sintetizada do sistema implementado.

Qualquer particularidade deve estar descrita neste texto.

Para compilar será usado o comando make (sem nenhum parâmetro).

Para testar será executado um script como o abaixo.

```terminal
moocars < teste.in > teste.out
diff teste.sol teste.out
```

Onde `teste.in` é o arquivo de entrada do teste e `teste.sol` é o esperado como saída.
Caso o teste seja positivo (não imprime nada) será analisado o código fonte.
