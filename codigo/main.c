#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 3   // tamanho do tabuleiro 3x3

// --------------------------------------------------
// ESTRUTURA DO TABULEIRO
// --------------------------------------------------
typedef struct {
    char casas[TAM][TAM];
} Tabuleiro;


// --------------------------------------------------
// FUNÇÕES DO TABULEIRO
// --------------------------------------------------
void inicializarTabuleiro(Tabuleiro *t) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            t->casas[i][j] = ' ';
}

void mostrarTabuleiro(const Tabuleiro *t) {
    printf("\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf(" %c ", t->casas[i][j]);
            if (j < TAM - 1) printf("|");
        }
        printf("\n");
        if (i < TAM - 1) printf("-----------\n");
    }
    printf("\n");
}

int casaVazia(const Tabuleiro *t, int linha, int coluna) {
    if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM)
        return 0; // fora do tabuleiro

    return t->casas[linha][coluna] == ' ';
}

void colocarJogada(Tabuleiro *t, int linha, int coluna, char simbolo) {
    t->casas[linha][coluna] = simbolo;
}


// --------------------------------------------------
// LÓGICA DO JOGO
// --------------------------------------------------
int validarJogada(const Tabuleiro *t, int linha, int coluna) {

    if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
        printf("ERRO: Essa posição está fora do tabuleiro. Use valores entre 1 e 3.\n");
        return 0;
    }

    if (!casaVazia(t, linha, coluna)) {
        printf("ERRO: Essa casa já está ocupada.\n");
        return 0;
    }

    return 1;
}

static int linhaGanhou(const Tabuleiro *t, int linha, char simbolo) {
    for (int j = 0; j < TAM; j++)
        if (t->casas[linha][j] != simbolo)
            return 0;
    return 1;
}

static int colunaGanhou(const Tabuleiro *t, int coluna, char simbolo) {
    for (int i = 0; i < TAM; i++)
        if (t->casas[i][coluna] != simbolo)
            return 0;
    return 1;
}

static int diagonalPrincipal(const Tabuleiro *t, char simbolo) {
    for (int i = 0; i < TAM; i++)
        if (t->casas[i][i] != simbolo)
            return 0;
    return 1;
}

static int diagonalSecundaria(const Tabuleiro *t, char simbolo) {
    for (int i = 0; i < TAM; i++)
        if (t->casas[i][TAM - 1 - i] != simbolo)
            return 0;
    return 1;
}

int verificarVencedor(const Tabuleiro *t, char simbolo) {
    for (int i = 0; i < TAM; i++)
        if (linhaGanhou(t, i, simbolo) || colunaGanhou(t, i, simbolo))
            return 1;

    return diagonalPrincipal(t, simbolo) || diagonalSecundaria(t, simbolo);
}

int verificarEmpate(const Tabuleiro *t) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (t->casas[i][j] == ' ')
                return 0;
    return 1;
}


// --------------------------------------------------
// JOGADA DA CPU (Computador)
// --------------------------------------------------
void jogadaCPU(Tabuleiro *t, char cpu, char jogador) {

    int jogadasPossiveis[9][2];
    int quantidade = 0;

    // 1. tentar jogada vencedora
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (casaVazia(t, i, j)) {
                t->casas[i][j] = cpu;
                if (verificarVencedor(t, cpu)) {
                    colocarJogada(t, i, j, cpu);
                    return;
                }
                t->casas[i][j] = ' ';
            }

    // 2. bloquear jogada do jogador
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (casaVazia(t, i, j)) {
                t->casas[i][j] = jogador;
                if (verificarVencedor(t, jogador)) {
                    colocarJogada(t, i, j, cpu);
                    return;
                }
                t->casas[i][j] = ' ';
            }

    // 3. jogar aleatório
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (casaVazia(t, i, j)) {
                jogadasPossiveis[quantidade][0] = i;
                jogadasPossiveis[quantidade][1] = j;
                quantidade++;
            }

    if (quantidade > 0) {
        srand((unsigned)time(NULL));
        int escolha = rand() % quantidade;
        colocarJogada(t, jogadasPossiveis[escolha][0], jogadasPossiveis[escolha][1], cpu);
    }
}


// --------------------------------------------------
// EXECUTAR JOGO
// --------------------------------------------------
void iniciarJogo(int modo) {
    Tabuleiro t;
    inicializarTabuleiro(&t);

    char jogador1 = 'X';
    char jogador2 = 'O';

    char atual = jogador1;

    while (1) {

        mostrarTabuleiro(&t);

        int linha, coluna;

        // --- CPU joga ---
        if (modo == 2 && atual == jogador2) {
            printf("CPU (O) está a jogar...\n");
            jogadaCPU(&t, jogador2, jogador1);
        }

        // --- Jogador humano joga ---
        else {
            printf("Jogador (%c), introduza linha e coluna (ex: 2 3): ", atual);

            if (scanf("%d %d", &linha, &coluna) != 2) {
                printf("ERRO: Entrada inválida! Use números.\n");
                int lixo;
                while ((lixo = getchar()) != '\n' && lixo != EOF) {}
                continue;
            }

            linha--; // converter 1-3 em 0-2
            coluna--;

            if (!validarJogada(&t, linha, coluna))
                continue;

            colocarJogada(&t, linha, coluna, atual);
        }

        // Verificar vitória
        if (verificarVencedor(&t, atual)) {
            mostrarTabuleiro(&t);

            if (modo == 2 && atual == jogador2)
                printf("A CPU venceu!\n");
            else
                printf("O jogador %c venceu!\n", atual);

            return;
        }

        // Verificar empate
        if (verificarEmpate(&t)) {
            mostrarTabuleiro(&t);
            printf("Empate!\n");
            return;
        }

        // Trocar jogador
        atual = (atual == jogador1 ? jogador2 : jogador1);
    }
}


// --------------------------------------------------
// MAIN
// --------------------------------------------------
int main() {

    int modo;

    printf("======= JOGO DO GALO =======\n");
    printf("1 - Jogador vs Jogador (X vs O)\n");
    printf("2 - Jogador vs CPU (X vs O)\n");

    do {
        printf("Escolha o modo: ");
        if (scanf("%d", &modo) != 1) {
            printf("ERRO: Introduza um número válido.\n");
            int lixo;
            while ((lixo = getchar()) != '\n' && lixo != EOF) {}
            modo = 0;
        }
    } while (modo != 1 && modo != 2);

    iniciarJogo(modo);

    return 0;
}
