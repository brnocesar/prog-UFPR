# Segundo Trabalho de Oficina de Computação (2013/1)

## O Jogo da Velha

O Jogo da Velha mais conhecido é composto de um tabuleiro com nove casas e dois tipos de marcação: "X" (letra X maiúscula) e "O" (letra O maiúscula). As regras de movimento do jogo são as seguintes:

1. Dois adversários se alternam para fazer as marcações nos espaços inicialmente em branco das nove casa (cada espaço em branco será representado por um "\_" - sublinhado);
2. O jogador que começa a partida, marca as casas com "X" ao passo que o segundo a jogar, marca com "O";
3. Vence a partida o jogador que completar três marcas próprias em uma linha ou coluna ou diagonal.

Fazer dois programas em linguagem C. O primeiro programa deve ser colocado no arquivo de nome `bcs12-aprendiz.c` (por exemplo, se o seu usuário for bcs12). A finalidade dele é aprender com várias derrotas sucessivas em partidas jogadas contra humanos. Durante a execução de cada partida, a interface de entrada e saı́da é totalmente padrão. Assim, o humano entra a configuração de um tabuleiro com sua opção de movimento por meio do teclado e o programa recebe essa configuração por meio de comandos de leitura da sequência de nove caracteres, tanto os de marcação ( "X" ou "O") como o sublinhado ("\_"). A sequência representa a configuração de um tabuleiro como se suas linhas fossem contatenadas uma atrás de outra. Por exemplo, a sequência "O_X_X_X_O" representa uma tabuleiro assim:

```terminal
O_X
_X_
X_O
```

Após a leitura de uma configuração, o programa deve gerar uma outra configuração a partir de movimento válido qualquer e imprimi-la na saı́da padrão usando os mesmos caracteres. A execução termina quando o programa gera e imprime um tabuleiro de vitória ou quando o humano entra um tabuleiro de vitória. Um exemplo de execução com uma partida completa está listada abaixo.

```terminal
./bcs12-aprendiz
Quem joga primeiro? (digite 1 para humano ou 2 para maquina): 1 <ENTER>
X________<ENTER>
X___O____
X_X_O____<ENTER>
XOX_O____
XOXXO____<ENTER>
XOXXO___O
XOXXO_X_O<ENTER>
```

O programa em `bcs12-aprendiz.c` deve alocar uma lista dinâmica para cada partida com a represenração dos movimentos alternados e/ou dos tabuleiros entrados pelo humano e gerados pelo programa. No caso da partida terminar em derrota do programa, a lista dinâmica deve ser gravada em no arquivo de formato texto padrão. Tal como consta nas intruções acima, o arquivo texto será entregue junto com os arquivos de programa. Quanto mais partidas de derrota do programa forem adicionadas no arquivo texto, mais chance de vencer o programa associado de nome `bcs12-jogador.c` terá na competição artificial que será executada.

O segundo programa deve ser colocado no arquivo de nome `bcs12-jogador.c`. Ele deve utilizar o mesmo arquivo texto com as partidas que resultaram em derrota contra humanos e, com a ajuda dele, computar apenas 1 (um) movimento em resposta a 1 (um) tabuleiro lido do teclado a cada vez que é executado. Como resultado único da execução, o programa `bcs12-jogador.c` deve imprimir o tabuleiro computado na saı́da padrão e, logo em seguida, terminar. Um exemplo de execução com o cômputo de um movimento está listada abaixo.

```terminal
./bcs12-jogador
O_X_X____<ENTER>
O_X_X_O__
```

**Observação:** se o programa bcs12-jogador.c ler um tabuleiro de vitória ou de derrota, ele deve terminar sua execução (tal como já era esperado), mas não deve imprimir nada na saı́da padrão. Exemplo:

```terminal
./bcs12-jogador
O_XXXXO_O<ENTER
```

Finalmente, é importante você pesquisar sobre os conceitos de registros, ponteiros, e de alocação dinâmica de memória para a implementação de listas dinâmicas para representar os movimentos e/ou tabuleiros de uma partida.
Não esqueça de elaborar o seu código de forma modular e abstrata. Isso é importante. Bom trabalho!

## Entrega

Siga as instruções abaixo para entender quais arquivos serão empacotados e comprimidos:

1. Faça um arquivo com o programa-fonte que é capaz de aprender com sucessivas derrotas em várias partidas do Jogo da Velha, cujo nome será `bcs12-aprendiz.c` e garanta que o código-fonte será compatı́vel com o compilador gcc (GNU C) da servidora de processamento macalan do Departamento de Informática;
2. Gere automaticamente um arquivo texto padrão com os dados resultantes da execução do programa de aprendizagem do item anterior;
3. Faça um arquivo com o programa-fonte de geração de apenas um movimento em qualquer estágio de uma partida do Jogo da Velha, cujo nome será `bcs12-jogador.c`;
