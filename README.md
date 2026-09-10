# Space Inaders em C (Allegro 5)

## 1. Visão Geral do Jogo
"Space Invaders" é um jogo de tiro espacial clássico onde o objetivo principal é destruir ondas de inimigos alienígenas que descem em direção à sua nave, enquanto evita ser atingido por eles. O jogo é dividido em níveis, com a dificuldade aumentando a cada nível. Power-ups podem aparecer para auxiliar o jogador.

## 2. Controles
O jogo utiliza o teclado para movimentação e disparo:
*   **Mover para a Esquerda:** Tecla A
*   **Mover para a Direita:** Tecla D
*   **Atirar:** Tecla ESPAÇO
*   **Sair do Jogo:** Tecla ESC (em qualquer tela, incluindo menus e durante o jogo), ou ao fechar o display

## 3. Naves e Dificuldade
Ao iniciar o jogo, você será levado ao menu principal, onde as seguintes opções estão disponíveis:
*   **JOGAR:** Inicia o jogo direcionando para a tela de seleção de dificuldade.
*   **NAVE:** Permite a escolha entre três tipos:
    *   NORMANDY: Nave padrão.
    *   MILLENIUM FALCOM: Nave com maior velocidade de movimento.
    *   PÉROLA NEGRA: Nave com um disparo de maior área.

Dificuldades disponíveis: EASY, NORMAL e HARD.

## 4. Power-Ups
*   **Piercing (Mario):** Ao coletar, seus disparos atravessam múltiplos inimigos por um tempo limitado. A fonte do score e do tempo muda para a fonte do Mario, e a música de fundo é substituída temporariamente por um som do Mario. A cor da nave também muda. O cenário também é alterado.
*   **Speed Boost (Sonic):** Aumenta a velocidade dos seus disparos por um tempo limitado. A fonte do score e do tempo muda para a fonte do Sonic, e a música de fundo é substituída temporariamente por um som do Sonic. A cor da nave também muda. O cenário também é alterado.

## 5. Detalhes da Implementação
O jogo foi desenvolvido em C utilizando a biblioteca Allegro 5, com estrutura focada em manipulação de gráficos, áudio e eventos em tempo real.

### Estrutura de Arquivos
*   `meu_codigo.h`: Arquivo de cabeçalho que define as estruturas de dados (structs) e protótipos de funções.
*   `meu_codigo.c`: Contém a implementação das funções declaradas no cabeçalho.
*   `tp.c`: Contém a função main e a lógica principal do jogo, incluindo inicialização da Allegro, loop do jogo, tratamento de eventos e gerenciamento de estados.
*   `RECORDE_EASY.txt`, `RECORDE_NORMAL.txt`, `RECORDE_HARD.txt`: Arquivos de texto usados para armazenar os recordes de pontuação para cada dificuldade.

### Como compilar e executar
```bash
# Clone o repositório
git clone [https://github.com/gustavocsales/Space_Inaders.git](https://github.com/gustavocsales/Space_Inaders.git)

# Compile utilizando o make e a biblioteca Allegro 5
sudo apt install liballegro5-dev
make

# Execute o jogo
./space_inaders
