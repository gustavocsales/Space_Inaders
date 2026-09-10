# Space Inaders em C (Allegro 5)

## 1. Visão Geral do Jogo
"Space Invaders" é um jogo de tiro espacial clássico onde o objetivo principal é destruir ondas de inimigos alienígenas que descem em direção à sua nave, enquanto evita ser atingido por eles[cite: 2]. O jogo é dividido em níveis, com a dificuldade aumentando a cada nível[cite: 2]. Power-ups podem aparecer para auxiliar o jogador[cite: 2].

## 2. Controles
O jogo utiliza o teclado para movimentação e disparo[cite: 2]:
*   **Mover para a Esquerda:** Tecla A[cite: 2]
*   **Mover para a Direita:** Tecla D[cite: 2]
*   **Atirar:** Tecla ESPAÇO[cite: 2]
*   **Sair do Jogo:** Tecla ESC (em qualquer tela, incluindo menus e durante o jogo), ou ao fechar o display[cite: 2]

## 3. Naves e Dificuldade
Ao iniciar o jogo, você será levado ao menu principal, onde as seguintes opções estão disponíveis[cite: 2]:
*   **JOGAR:** Inicia o jogo direcionando para a tela de seleção de dificuldade[cite: 2].
*   **NAVE:** Permite a escolha entre três tipos[cite: 2]:
    *   NORMANDY: Nave padrão[cite: 2].
    *   MILLENIUM FALCOM: Nave com maior velocidade de movimento[cite: 2].
    *   PÉROLA NEGRA: Nave com um disparo de maior área[cite: 2].

Dificuldades disponíveis: EASY, NORMAL e HARD[cite: 2].

## 4. Power-Ups
*   **Piercing (Mario):** Ao coletar, seus disparos atravessam múltiplos inimigos por um tempo limitado[cite: 2]. A fonte do score e do tempo muda para a fonte do Mario, e a música de fundo é substituída temporariamente por um som do Mario[cite: 2]. A cor da nave também muda[cite: 2]. O cenário também é alterado[cite: 2].
*   **Speed Boost (Sonic):** Aumenta a velocidade dos seus disparos por um tempo limitado[cite: 2]. A fonte do score e do tempo muda para a fonte do Sonic, e a música de fundo é substituída temporariamente por um som do Sonic[cite: 2]. A cor da nave também muda[cite: 2]. O cenário também é alterado[cite: 2].

## 5. Detalhes da Implementação
O jogo foi desenvolvido em C utilizando a biblioteca Allegro 5, com estrutura focada em manipulação de gráficos, áudio e eventos em tempo real[cite: 2].

### Estrutura de Arquivos
*   `meu_codigo.h`: Arquivo de cabeçalho que define as estruturas de dados (structs) e protótipos de funções[cite: 2].
*   `meu_codigo.c`: Contém a implementação das funções declaradas no cabeçalho[cite: 2].
*   `tp.c`: Contém a função main e a lógica principal do jogo, incluindo inicialização da Allegro, loop do jogo, tratamento de eventos e gerenciamento de estados[cite: 2].
*   `RECORDE_EASY.txt`, `RECORDE_NORMAL.txt`, `RECORDE_HARD.txt`: Arquivos de texto usados para armazenar os recordes de pontuação para cada dificuldade[cite: 2].

### Como compilar e executar
```bash
# Clone o repositório
git clone [https://github.com/boxtaplayer/NOME_DO_REPOSITORIO.git](https://github.com/boxtaplayer/NOME_DO_REPOSITORIO.git)

# Compile utilizando o make e a biblioteca Allegro 5
sudo apt install liballegro5-dev
make

# Execute o jogoR
./space_inaders
